//
// Created by miaog on 2024/12/24.
//

#ifndef NOKAMODEL_GLOBAL_DATA_H
#define NOKAMODEL_GLOBAL_DATA_H

#include <sstream>
#include "QString"
#include "QCoreApplication"
#include "QNetworkAccessManager"
#include "iostream"
#include "HttpRequest.h"
#include "web_info.h"

#ifdef Q_OS_WIN
#include "windows.h"
#include "SDK360.h"

struct FUN_360LY
{
    FUN_SDK360_Init SDK360_Init = nullptr;
    FUN_SDK360_UnInit SDK360_UnInit = nullptr;
    FUN_SDK360_AsyncPay SDK360_AsyncPay = nullptr;
    FUN_SDK360_CancelPay SDK360_CancelPay = nullptr;

    std::string qid;
    std::string appid;

    bool init = false;
};
#endif

class Singleton360Data {
private:
    static Singleton360Data* instance;

    Singleton360Data() {
        std::cout << "Singleton instance created." << std::endl;
    }

    Singleton360Data(const Singleton360Data&) = delete;
    Singleton360Data& operator=(const Singleton360Data&) = delete;

#ifdef Q_OS_WIN
    FUN_360LY m_fun360LY;
#endif

public:
    static Singleton360Data* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton360Data();
        }
        return instance;
    }

    bool Init360LY() {
#ifdef Q_OS_WIN
        QString sdkFile = QCoreApplication::applicationDirPath();
        sdkFile += "/x64/360Lysdk64.dll";

        HMODULE hModule = LoadLibraryA(sdkFile.toStdString().c_str());

        if (!hModule) {
            return false;
        }

        m_fun360LY.SDK360_Init = (FUN_SDK360_Init) GetProcAddress(hModule, "SDK360_Init");
        m_fun360LY.SDK360_UnInit = (FUN_SDK360_UnInit) GetProcAddress(hModule, "SDK360_UnInit");
        m_fun360LY.SDK360_AsyncPay = (FUN_SDK360_AsyncPay) GetProcAddress(hModule, "SDK360_AsyncPay");
        m_fun360LY.SDK360_CancelPay = (FUN_SDK360_CancelPay) GetProcAddress(hModule, "SDK360_CancelPay");

        if (!m_fun360LY.SDK360_Init
            || !m_fun360LY.SDK360_UnInit
            || !m_fun360LY.SDK360_AsyncPay
            || !m_fun360LY.SDK360_CancelPay) {
            return false;
        }


        QEventLoop loop;
        int statusCode;
        QByteArray responseData;
        QString sUrl = WEB_360LY;

        HttpRequest httpRequest;

        QObject::connect(&httpRequest, &HttpRequest::requestFinished,
                         [&loop, &statusCode, &responseData](int code, const QByteArray &data) {
                             statusCode = code;
                             responseData = data;
                             loop.quit();
                         });

        httpRequest.get(sUrl);
        loop.exec();

        if(statusCode == 200){
            QString result = responseData;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(result.toUtf8());
            QJsonObject jsonObject = jsonDoc.object();
            if(jsonObject.contains("code")&& jsonObject["code"].toInt() == 0){
                std::stringstream ss;
                ss<< (long long)jsonObject["data"].toObject()["qid"].toDouble();
                m_fun360LY.qid = ss.str();
                m_fun360LY.appid = jsonObject["data"].toObject()["appId"].toString().toStdString();

                char* end;
                errno = 0;
                ULONGLONG value = std::strtoull(m_fun360LY.qid.c_str(), &end, 10);

                if ((errno == ERANGE && value == ULLONG_MAX) ||
                    (errno != 0 && value == 0)) {
                    return false;
                }

                if (*end != '\0') {
                    return false;
                }

                EnvInfo envInfo;
                envInfo.dwSize = sizeof(EnvInfo);
                QString appid1 = QString::fromLocal8Bit(m_fun360LY.appid);
                wcscpy_s(envInfo.wszAppId, 128, appid1.toStdWString().c_str());
                envInfo.u64Qid = value;

                if (0 == m_fun360LY.SDK360_Init(&envInfo))
                {
                    m_fun360LY.init = true;
                }
                qDebug()<<"360API init success";
            }else{
                qDebug()<<u8"返回出错";
                qDebug()<<jsonObject;
                return false;
            }

        }else{
            qDebug()<<u8"请求出错";
            return false;
        }

        return true;
#else
        // 360 SDK is Windows-only
        Q_UNUSED(QCoreApplication::applicationDirPath());
        return false;
#endif
    }

#ifdef Q_OS_WIN
    FUN_360LY &getFun360LY() {
        return m_fun360LY;
    }
#endif
};


#endif //NOKAMODEL_GLOBAL_DATA_H
