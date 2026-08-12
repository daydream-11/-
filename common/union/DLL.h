
//
// DLL.h - 为组件DLL提供方与使用方提供相关规范
//
//      Copyright (c) 2007-12-21 Shiqian Software. 殷亮. All rights reserved.
//      Version 1.0.071221
//


#ifndef __DLL_H__
#define __DLL_H__


// STL库
#include <map>
#include <string>
#include <xstring>
using namespace std;
#include "Public.h"



// $ 为跨平台开发所提供的宏 ===================================================
#if defined(__WXMSW__) || defined(WIN32)
    // WIN32
    # define SYSTEM_WIN
    # include <windows.h>

    typedef HMODULE     DllHandle;
    // 导出函数统一修饰符
    # define DLLEXPORT extern "C" __declspec(dllexport)
    // 加载动态库
    # define OPEN_DLL(filename) LoadLibrary( filename) 
    // 加载函数地址
    # define GET_DLL_SYMBOL(handle,funname) GetProcAddress( handle, funname)
    // 卸载动态库
    # define FREE_DLL(handle) FreeLibrary( handle)

#else
    // UNIX/LINUX
    # include <dlfcn.h>

    typedef void*       DllHandle;
    // 导出函数统一修饰符
    # define DLLEXPORT extern "C"
    // 加载动态库
    # define OPEN_DLL(filename) dlopen( filename, RTLD_LAZY)
    // 加载函数地址
    # define GET_DLL_SYMBOL(handle,funname) dlsym( handle, funname)
    // 卸载动态库
    # define FREE_DLL(handle) dlclose( handle)

#endif


// $ 为动态库方提供的宏，该宏将自动根据所给的类名，将类导出 ===================
# define EXPORT_DLL_CLASS( class_name, want_env)    \
                                                    \
	DLLEXPORT CDllClass* NewInstance##want_env()   \
    {                                               \
        return new class_name;                      \
    }												\
													\
	DLLEXPORT void CleanUp##want_env()				\
	{												\
	}


// $ 本头文件中类的前置声明 ===================================================

class CDllManager;
class CDllClass;


// $ DLL中必须有的全局函数 ====================================================

/**
 * NewInstanceFun声明了一个返回一个对象实例指针的函数原型，在每个实现的DLL中都
 * 应该定义这么一个函数，并命名为NewInstance，以便主程序调用。
 * 当然，也可以使用后面提供的EXPORT_DLL_CLASS宏来简单定义该函数
 */
typedef void* (*NewInstanceFun)();

/**
 * CleanUpFun声明了一个无参函数，在每一个DLL中都应该定义这么一个函数，并命名为
 * CleanUp，以便主程序调用。
 */
typedef void (*CleanUpFun)();


// $ DLL中必须继承的基类 ======================================================

/**
 * CDllClass类指定了DLL中要导出的类必须实现的接口
 *
 * @author 殷亮
 */
class CDllClass
{
public:
    /** @name 构造与析构 */
    /// @{

    /**
     * 析构函数
     */
    virtual ~CDllClass()
    {
    }

    /// @}

    /** @name 公共接口函数 */
    /// @{

    /**
     * 设置动态库管理对象指针，方便动态库内也能再次加载下一层动态库
     * 
     * @param _pDllManager 动态库管理者指针
     */
    void SetDllManagerPtr( CDllManager* _pDllManager)
    {
        this->m_pDllManager = _pDllManager;
    }

    /**
     * DeleteThis函数用于销毁自身实例
     */
    virtual void DeleteThis()
    {
        delete this;
    }
    
    /// @}

protected:
// 如果其它类想访问IWnDllClass的受保护成员，可以在包含DLL.h之前定义FRIEND_CLASS宏
// 如 # define FRIEND_CLASS friend class CTest;
# ifdef FRIEND_CLASS
    FRIEND_CLASS
# endif

    CDllManager* m_pDllManager;
};



// $ 调用方使用类 =============================================================

typedef map<xstring, DllHandle, less<xstring> > CStrDllHandleMap;

/**
 * CDllManager函数用于管理组件模块的加载与销毁，使用时请定义一个全局的CCBSDllManager
 * 对象，以便程序自动地帮你卸载已经加载的动态库
 *
 * @author 殷亮
 */
class CDllManager
{
public:

    /**
     * GetInstance函数通过文件名创建加载动态库，并创建动态库中类的新实例
     * @author 殷亮
     *
     * @param strDllFileName 动态库文件名
     * @return 如果创建成功，返回创建的实例指针，否则返回空
     */
    inline CDllClass* GetInstance(const xstring & strDllFileName, const string & strClassName)
    {
        DllHandle                       hDll;
        xstring                         strFullDllFileName;
        CStrDllHandleMap::iterator    itr;  

        // 查找该动态库是否已经加载
        itr = this->m_mapLoadedDlls.find( strDllFileName);

        // 如果已经加载了，直接从已加载的句柄中获取对象
        if (itr != this->m_mapLoadedDlls.end())
        {
            return this->CreateInstanceFromHandle( itr->second, strClassName);
        }

        // 确保 Linux 下能加载动态库
        # ifndef SYSTEM_WIN
		    strFullDllFileName += "./";
            strFullDllFileName += strDllFileName;
        # else
            strFullDllFileName = strDllFileName;
        # endif

        // 如果是第一次加载，则先加载动态库，然后再动态库的相关信息保存到MAP中
        // 最后再从动态库中获取对象
        if (hDll = OPEN_DLL( strFullDllFileName.c_str()))
        {
            this->m_mapLoadedDlls.insert( CStrDllHandleMap::value_type( strDllFileName, hDll));
            return this->CreateInstanceFromHandle( hDll, strClassName);
        }
        else
        {
            return NULL;
        }
    }

    /**
     * UnloadDll函数用于显示卸载一个已加载的动态库，由于CDllManager类会在析构
     * 时卸载已经加载的所有动态库，所以除非出于对性能的考虑，不建议使用该函数
     * @author 殷亮
     *
     * @param strDllFileName 动态库文件名
     * @return true-成功；false-失败
     */
    inline bool UnloadDll(xstring strDllFileName)
    {
        CStrDllHandleMap::iterator    itr;  

        // 查找该动态库是否已经加载
        itr = this->m_mapLoadedDlls.find( strDllFileName);

        // 如果已经加载了，则卸载该动态库
        if (itr != this->m_mapLoadedDlls.end())
        {
            FREE_DLL( (*itr).second);
            this->m_mapLoadedDlls.erase( itr);  // 从MAP中删除
            return true;
        }

        return false;
    }

    /**
     * 析构函数，在析构函数里卸载所有已经加载的动态库
     */
    inline ~CDllManager()
    {
		//CleanUpFun		                fun;
        CStrDllHandleMap::iterator    itr; 

        for (itr=this->m_mapLoadedDlls.begin(); itr!=this->m_mapLoadedDlls.end(); itr++)
        {
            //fun = (CleanUpFun) GET_DLL_SYMBOL( itr->second, "CleanUp");
            //fun();
            FREE_DLL( itr->second);
        }
    }

private:
    /**
     * CreateInstanceFromHandle函数通过动态库句柄创建动态库中类的新实例
     * @author 殷亮
     *
     * @param hDll 动态库的有效句柄
     * @return 如果创建成功，返回创建的实例指针，否则返回空
     */
    inline CDllClass* CreateInstanceFromHandle( DllHandle hDll, const string & strClassName)
    {
        CDllClass*       pInstance;
        NewInstanceFun      fun;
		string strFunName = "NewInstance";
		if (strClassName == "")
		{
			strFunName += "NULL";
		}
		else
		{
			strFunName += strClassName;
		}
		if (!(fun = (NewInstanceFun) GET_DLL_SYMBOL( hDll, strFunName.c_str())))
        {
            return NULL;
        }

        if (!(pInstance = (CDllClass*)fun()))
        {
            pInstance->DeleteThis();
            return NULL;
        }

        pInstance->SetDllManagerPtr( this);

        return pInstance;
    }

private:
    CStrDllHandleMap      m_mapLoadedDlls;
};


# endif
