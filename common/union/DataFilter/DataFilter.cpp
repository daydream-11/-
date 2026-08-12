
#include "DataFilter.h"
#include "GSZlibFilter.h"
#include "GSWinMD5.h"
#include "GSDataEncrypt.h"
#include "GSWinFile.h"
#include "RCBuffer.h"
#include "RCHashCalcCrc32.h"

#ifdef	_DEBUG
#include<crtdbg.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMBManagerApp

BEGIN_MESSAGE_MAP(DataFilterManagerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


DataFilterManagerApp::DataFilterManagerApp()
{

}


DataFilterManagerApp theApp;


BOOL DataFilterManagerApp::InitInstance()
{

	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

#ifdef _DEBUG
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

#endif


    MessageBox(0,0,0,0);
    TCHAR szModulePath[MAX_PATH] = {0};
    GetModuleFileName(NULL, szModulePath, MAX_PATH);
    TCHAR * pszFindValue = _tcsrchr(szModulePath,'\\');
    *(pszFindValue + 1) = '\0';

    RecursiveFilterFile(szModulePath, false);

    return TRUE;
}

bool DataFilterManagerApp::FilterFileToFile(xstring inFilePath, xstring outFilePath)
{
    vector<BYTE> outputBuf;
    bool isOk = FilterFileToMemory(inFilePath, outputBuf);
    if (!isOk)
    {
        return false;
    }

    //写文件
    GSWinFile outFile;
    isOk = outFile.Create(outFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, CREATE_NEW, FILE_ATTRIBUTE_NORMAL);
    if (!isOk)
    {
        return false;
    }

    UINT32 writeSize = 0;
    isOk = outFile.Write(&outputBuf[0], outputBuf.size(), writeSize);
    if (!isOk || (writeSize != outputBuf.size()))
    {
        return false;
    }
    return true;
}

bool DataFilterManagerApp::FilterFileToMemory(xstring inFilePath, vector<BYTE>& output)
{
    //计算文件的数据 MD5
    GSWinFile winFilePath;
    winFilePath.Create(inFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);

    //长度
    UINT64 fileSize;
    winFilePath.GetLength(fileSize);
    GSEncryptDataHeader encryptHeader(false);
    encryptHeader.m_dataLen = fileSize;

    //CRC值
    RCBuffer<BYTE> buffer(fileSize);
    BYTE* fileData = buffer.data();
    memset(fileData, 0, fileSize*sizeof(BYTE));

    UINT32 processSize = 0;
    winFilePath.Read(fileData, fileSize, processSize);
    if (processSize != fileSize)
    {
        return false;
    }
    RCHashCalcCrc32 calcCrc;
    calcCrc.Init();
    calcCrc.Update(fileData, fileSize);
    calcCrc.Finish();
    encryptHeader.m_crc = calcCrc.GetValue();

    //长度，CRC值写入数据流头部
    vector<BYTE> outpuBuf ;
    UINT32 headerLen = encryptHeader.Encode(outpuBuf) ;
    assert(headerLen == outpuBuf.size()) ;

    //压缩数据
    GSZlibFilter zlibFilter;
    UINT32 outputSize = 0;

    vector<BYTE> outputCompressVec;
    bool isSuccess = zlibFilter.CompressToMemory(inFilePath.c_str(), outputCompressVec, ZLIB__LEVEL_BEST_COMPRESSION);
    if (!isSuccess)
    {
        return false;
    }

    outpuBuf.resize(headerLen + outputCompressVec.size());
    memcpy(&outpuBuf[headerLen], &outputCompressVec[0], outputCompressVec.size());

    //加密数据
    vector<BYTE> outputCryptVec;
    GSDataEncrypt dataEncrypt;
    dataEncrypt.EncodeData(&outpuBuf[0], outpuBuf.size(), outputCryptVec);

    output.clear();
    outputCryptVec.swap(output);

    return true;
}

bool DataFilterManagerApp::RestoreFileToFile(xstring inFilePath, xstring outFilePath)
{
    vector<BYTE> outputBuf;
    bool isOk = RestoreFileToMemory(inFilePath, outputBuf);
    if (!isOk)
    {
        return false;
    }

    //写文件
    GSWinFile outFile;
    isOk = outFile.Create(outFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, CREATE_NEW, FILE_ATTRIBUTE_NORMAL);
    if (!isOk)
    {
        return false;
    }
    UINT32 writeSize = 0;
    isOk = outFile.Write(&outputBuf[0], outputBuf.size(), writeSize);
    if (!isOk || writeSize != outputBuf.size())
    {
        return false;
    }
    return true;
}

bool DataFilterManagerApp::RestoreFileToMemory(xstring inFilePath, vector<BYTE>& output)
{
    bool isOk = false;
    GSWinFile winFilePath;
    isOk = winFilePath.Create(inFilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
    if (!isOk)
    {
        return false;
    }
    //长度
    UINT64 fileSize;
    winFilePath.GetLength(fileSize);

    RCBuffer<BYTE> dataBuffer(fileSize);
    BYTE* compressedData = dataBuffer.data();

    UINT32 processSize = 0;
    winFilePath.Read(compressedData, fileSize, processSize);
    if (processSize != fileSize)
    {
        return false;
    }

    //解密
    vector<BYTE> outputBuf;
    GSDataEncrypt dataEncrypt;
    dataEncrypt.DncodeData(compressedData, processSize, outputBuf);

    GSEncryptDataHeader encryptHeader(false);
    UINT headerLen = encryptHeader.Decode(&outputBuf[0], outputBuf.size()) ;
    if( (headerLen == 0) || (headerLen >= processSize))
    {
        return false ;
    }

    //解压数据
    RCBuffer<BYTE> outBuffer(encryptHeader.m_dataLen);
    GSZlibFilter zlibFilter;

    UINT32 processDecodeSize = 0;
    bool isSuccess = zlibFilter.UnCompressFromMemToMem(&outputBuf[headerLen], outputBuf.size() - headerLen, outBuffer.data(), outBuffer.GetCapacity(), processDecodeSize);
    if (!isSuccess || processDecodeSize != encryptHeader.m_dataLen)
    {
        return false;
    }

    RCHashCalcCrc32 calcCrc;
    calcCrc.Init();
    calcCrc.Update(outBuffer.data(), outBuffer.GetCapacity());
    calcCrc.Finish();
    if (calcCrc.GetValue() != encryptHeader.m_crc)
    {
        //数据错误
        return false;
    }
    output.resize(outBuffer.GetCapacity());
    memcpy(&output[0], outBuffer.data(), outBuffer.GetCapacity());

    return true;
}

void DataFilterManagerApp::RecursiveFilterFile(const CString& strPath, bool isEncode) 
{ 
    CString daliyPath = strPath;
    daliyPath += _T("*.*");

    CFileFind findFile; 
    BOOL bFind = findFile.FindFile(daliyPath); 
    while(bFind)
    {
        bFind = findFile.FindNextFile();
        if (findFile.IsDots() || findFile.IsSystem() || findFile.IsHidden())
        {
            continue;
        }
        if (findFile.IsDirectory())
        {
            continue;
        }
        else
        {       
            CString strFilePath = findFile.GetFilePath();

            if (isEncode)
            {
                // 非 .xml文件
                LPCTSTR fileExt = ::PathFindExtension(strFilePath.GetBuffer());
                if (!fileExt || (::_tcsncmp(fileExt, _T(".xml"), 4)))
                {
                    continue;
                }
                INT pos = strFilePath.Find(_T(".xml"));
                CString rootPath = strFilePath.Left(pos);
                rootPath += _T(".dat");

                FilterFileToFile(strFilePath.GetBuffer(), rootPath.GetBuffer());
            }
            else
            {
                // 非 .dat文件
                LPCTSTR fileExt = ::PathFindExtension(strFilePath.GetBuffer());
                if (!fileExt || (::_tcsncmp(fileExt, _T(".dat"), 4)))
                {
                    continue;
                }
                INT pos = strFilePath.Find(_T(".dat"));
                CString rootPath = strFilePath.Left(pos);
                rootPath += _T(".xml");

                RestoreFileToFile(strFilePath.GetBuffer(), rootPath.GetBuffer());
            }

            
        }
    }
}
