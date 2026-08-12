//
//文件名称：	Type.h
//功能描述：	类型定义，区分不同操作系统间系统调用的设置，所有当前工程
//				内的代码都必须第一个引用此文件
//版本说明：	Windows操作系统需要定义宏：__WINDOWS__
//				Linux操作系统需要定义宏：__LINUX__
//
//

#ifndef __TYPE_H__
#define __TYPE_H__

#include <map>
#include <vector>

//根据指针值删除内存
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) if((x) != NULL ) {delete (x); (x) = NULL;}
#endif
//根据指针值删除数组类型内存
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) if((x) != NULL) {delete[] (x); (x) = NULL;}
#endif
//根据指针调用free接口
#ifndef SAFE_FREE
#define SAFE_FREE(x) if((x) != NULL) {free(x); (x) = NULL;}
#endif
//根据指针调用Release接口
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if((x)!=NULL ) {(x)->Release(); (x) = NULL;}
#endif

#if defined(NDEBUG)
	#define __ENTER_FUNCTION {try{
	#define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__FUNCTION__);}}
#else
	#define __ENTER_FUNCTION {try{
	#define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__FUNCTION__);}}
#endif


// 清空vector并且释放指针
template<typename T>
void DeleteVectorObject(T & myVector)
{
	size_t size = myVector.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (myVector[i] != NULL)
		{
			delete myVector[i];
		}
	}
	myVector.clear();
}

template<typename T, typename V>
void ClearVectorObject(V *pVector)
{
	if (pVector != NULL)
	{
		typedef typename V::iterator VIterator;
		for(VIterator iter = pVector->begin(); iter != pVector->end(); ++iter)
		{
			T myV = *iter;
			if (myV != NULL)
			{
				delete myV;
				myV = NULL;
			}
		}
		pVector->clear();
	}
}

template<typename V>
void ClearVectorObject2(V *pVector)
{
	if (pVector != NULL)
	{
		typedef typename V::iterator VIterator;
		for(VIterator iter = pVector->begin(); iter != pVector->end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		pVector->clear();
	}
}


template<typename T, typename V>
void DeleteVectorObject(V *pVector)
{
	if (pVector != NULL)
	{
		typedef typename V::iterator VIterator;
		for(VIterator iter = pVector->begin(); iter != pVector->end(); ++iter)
		{
			T myV = *iter;
			if (myV != NULL)
			{
				SAFE_DELETE(myV);
			}
		}
		pVector->clear();
		SAFE_DELETE(pVector);
	}
}

// 清空map并且释放指针
template<typename T>
void DeleteMapObject(T & myMap)
{
	typedef typename T::iterator TIterator;
	for(TIterator iter = myMap.begin(); iter != myMap.end(); ++iter)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
		}
	}
	myMap.clear();
}

// 清空map并且释放指针
template<typename T, typename V>
void DeleteMapObject(V *pV)
{
	if (pV != NULL)
	{
		typedef typename V::iterator VIterator;
		for(VIterator iter = pV->begin(); iter != pV->end(); ++iter)
		{
			T myT = iter->second;
			if (myT != NULL)
			{
				delete myT;
				myT = NULL;
			}
		}
		pV->clear();
		delete pV;
		pV = NULL;
	}
}

#ifdef WIN32
#define foreach(T, container, it)			for(T::iterator it = (container).begin(); it!=(container).end(); ++it)
#define foreach_pointer(T, container, it)	for(T::iterator it = (container)->begin();it!=(container)->end(); ++it)
#define foreach_pointer_iter(T, container)	for(T::iterator it = (container)->begin();it!=(container)->end(); ++it)
#define foreach_const(T, container, it)		for(T::const_iterator it = (container).begin(); it!=(container).end(); ++it)
#else
#define foreach_pointer(T, container)	for(typeof((container)->begin()) it = (container)->begin();it!=(container)->end(); ++(it))
//#define foreach(T, container)			for(typeof((container).begin()) it = (container).begin();it!=(container).end(); ++(it))
//#define foreach_const(T, container)		for(typeof(container)::const_iterator it = (container).begin();it!=(container).end(); ++(it))

#define foreach(T, container) for(bool __foreach_ctrl__=true;__foreach_ctrl__;)\
	for(typedef typeof(container) __foreach_type__;__foreach_ctrl__;__foreach_ctrl__=false)\
	for(__foreach_type__::iterator it=container.begin();it!=container.end();it++)

#define foreach_const(T, container) for(bool __foreach_ctrl__=true;__foreach_ctrl__;)\
	for(typedef typeof(container) __foreach_type__;__foreach_ctrl__;__foreach_ctrl__=false)\
	for(__foreach_type__::const_iterator it=container.begin();it!=container.end();it++)
#endif //WIN32

#define PUSH_SPLIT_PY(pTrie, container) { CSplitPinYin mySplitPinYin; \
		this->GetSplitPYByTrie(pTrie, mySplitPinYin);\
		container->push_back(mySplitPinYin); }

#endif
