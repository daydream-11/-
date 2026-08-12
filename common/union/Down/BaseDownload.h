#ifndef __BASE_DOWNLOAD_H__

#define __BASE_DOWNLOAD_H__

class IDownloadProcEvent
{
public:
	// 下载失败事件
	virtual void OnSetDownloadFail(){};
	// 下载完成事件
	virtual void OnSetDownloadFinish(){};
	// 设置需要下载的大小
	virtual void OnSetDownloadFileSize(int nDownloadFileSize){}
	// 设置已经下载的大小
	virtual void OnSetAlreadyDownloadSize(int nAlreadyDownloadSize){}
	// 设置当前的下载速度
	virtual void OnSetCurrentDownloadSpeed(float fCurrentDownloadSpeed){}
};

#endif
