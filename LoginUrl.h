//
// Created by Administrator on 2024/9/25.
//

#ifndef MYWEBENGINE_LOGINURL_H
#define MYWEBENGINE_LOGINURL_H

#include "QObject"
#include "web_info.h"
#include "HttpRequest.h"
class LoginUrl: public QObject {
Q_OBJECT
//    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
//    Q_PROPERTY(int sampleRate READ sampleRate)
//    Q_PROPERTY(int channelCount READ channelCount)
public:
    LoginUrl();

    Q_INVOKABLE void SendWeiXinLoginContext(QString productName);

    Q_INVOKABLE void RequestWeixinData(QString,QString,QString);

    Q_INVOKABLE QString getMac();

private slots:
    void readLoginUrlFromJson(int statusCode, const QByteArray &data);

signals:
    void sendWeiXinLoginUrl(QString);
    QString sendWeiXinUserInfo(int, QString, QString, QString, QString, int64_t);
private:
    HttpRequest httpRequest;
};

//int IsPhysicalNetworkCard(LPCTSTR pszGuid);
#endif //MYWEBENGINE_LOGINURL_H
