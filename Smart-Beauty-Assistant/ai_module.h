#ifndef AI_MODULE_H
#define AI_MODULE_H

#include <QObject>
#include "speak_model.h"

// json
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// network
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QUrlQuery>

//api
#include <QAuthenticator>
#include <QByteArray>
#include <QDebug>


class Ai_Module : public QObject
{
    Q_OBJECT
public:
    explicit Ai_Module(QObject *parent = nullptr);
    void startRequest(QUrl url);
    void SendJsonData();//发送Json数据
    void SpeckResponse(QJsonObject &jsonObj);
public:
    //解析Json数据
    QString getJson(QJsonObject &jsonObj);

signals:

private slots:
    void finshedSlot();//用来接收返回的Json数据

private:
    //网络访问管理
    QNetworkAccessManager* Net_Manager;
    //接收数据
    QNetworkReply *reply;
    QString * api_key;
    int request_type;
    bool timeout;
};

#endif // AI_MODULE_H
