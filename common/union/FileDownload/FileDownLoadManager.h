#pragma once

#include "Public.h"

#include "VectorRegister.h"

class IFileDownLoadEvent
{
public:
	virtual void OnFileProgressEvent(int totalSize,int completeSize, double fAverageSpeed) = 0;
	
};

class FileDownLoadManager
	: public VectorRegister<IFileDownLoadEvent>
{
public:
	FileDownLoadManager(void);
public:
	virtual ~FileDownLoadManager(void);
private:
	class MyDownload;
	MyDownload* m_pMyDownload;
public:
	// обть
	bool DownloadFile(const xstring& strUrlPath, const xstring& strDownloadSaveFile);
	void OnFileProgress(int totalSize,int completeSize, double fAverageSpeed);

	//

};
