#include "ai_module.h"

#include <QTextToSpeech>

Ai_Module::Ai_Module(QObject *parent)
    : QObject{parent}
{
    Net_Manager = new QNetworkAccessManager(this);
}



/*
 * 功能 :发送请求
*/
void Ai_Module::startRequest(QUrl url)
{

}

/*
 * 功能 :发送Json数据
*/
void Ai_Module::SendJsonData()
{
    QUrl url = QUrl("https://open.bigmodel.cn/api/paas/v4/chat/completions");
    QNetworkRequest NetRequest;

    NetRequest.setUrl(url);
    NetRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

    //设置请求头//post请求设置为json，才能发送josn格式文件
    NetRequest.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    NetRequest.setRawHeader("Authorization", "b580f29ac7eeac9064c7e0eafc491a0c.VlUwthxNwxsIjlQ3");

    QJsonObject Messages;
    Messages.insert("model","glm-4-flash");

    //创建一个Json对象 { }
    QJsonObject Exchange;
    //用户发送的信息
    Exchange.insert("role","user");

    // QJsonValue &value
    Exchange.insert("content","李白是哪个朝代的诗人");
    // 定义 [ ] 对象
    QJsonArray MessagesArray;
    MessagesArray.append(Exchange);

    Messages.insert("messages",MessagesArray);

    // //创建一个QJsonDocument类对象，jsonDoc可以将Json格式数据转换之后，使用post发送
    QJsonDocument jsonDoc = QJsonDocument(Messages);
    QByteArray post_data = jsonDoc.toJson(QJsonDocument::Compact);
    qDebug() << post_data.data();
    //发送post请求
    //reply = Net_Manager->post(NetRequest,post_data);
    // // 连接finished()信号到槽函数
    // connect(reply, &QNetworkReply::finished, this, &Ai_Module::finshedSlot);
    // 发送 POST 请求
    reply = Net_Manager->post(NetRequest, post_data);

    // 连接信号和槽以处理响应
    connect(reply, &QNetworkReply::finished, this, &Ai_Module::finshedSlot);

    // // 连接错误信号以处理网络错误
    // connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, [reply](QNetworkReply::NetworkError code) {
    //     qDebug() << "Network error:" << code << reply->errorString();
    //     reply->deleteLater();
    // });

    // // 可选：连接 SSL 错误信号（如果使用了 HTTPS）
    // connect(Ai_Module::reply, &QNetworkReply::sslErrors, this, [reply](const QList<QSslError> &errors) {
    //     qDebug() << "SSL errors:" << errors;
    //     Ai_Module::reply->ignoreSslErrors(errors); // 忽略 SSL 错误（仅用于测试，生产环境中不建议）
    // });

}

void Ai_Module::SpeckResponse(QJsonObject &jsonObj)
{
    QTextToSpeech* a = new QTextToSpeech();
    //getJson(jsonObj);

    //QTextToSpeech *b = new QTextToSpeech(); // 创建 QTextToSpeech 对象
    // b->setVoice(QTextToSpeech::Voice("en_US")); // 设置语音，这里以英语（美国）为例
    // b->setPitch(1.0); // 设置音调
    // //b->setSpeechRate(0.5); // 设置语速

    QTextToSpeech *textToSpeech = new QTextToSpeech();
    QList<QVoice> voices = textToSpeech->availableVoices();

    // 假设我们想要找到名为 "QLocale::Chinese" 的语音
    QVoice voiceToUse;
    foreach (const QVoice &voice, voices) {
        //qDebug() << voice.name() ;
        if (voice.name() == QLocale::Chinese) {
            voiceToUse = voice;
            break;
        }
    }

    // 如果找到了语音，则设置它
    textToSpeech->setVoice(voiceToUse);

    // 开始朗读文本
    textToSpeech->say(getJson(jsonObj));
    //speak_model speak;
    //speak.startSpeckSend("D:\creatdome\onedome\Smart-Beauty-Assistant\Smart-Beauty-Assistant\1.pcm");
}
/*
 * 示例要发送的Json数据 *
{
  "model" : "glm-4-falsh" ,
  "messages": [
    {
      "role": "user",
      "content": "请为我的新产品创作一个口号。"
    },
    {
      "role": "assistant",
      "content": "好的，请告诉我一些关于你产品的信息。"
    },
    {
      "role": "user",
      "content": "这是一个环保水瓶。"
    },
    {
      "role": "assistant",
      "content": "清新每一口，守护地球的选择！"
    },
    {
      "role": "user",
      "content": "你能再提供一个更有创意的口号吗？"
    },
    {
      "role": "assistant",
      "content": "携手绿色，畅享每一滴！"
    }
  ]
}
*/

//解析Json数据
QString Ai_Module::getJson(QJsonObject &jsonObj)
{
    qDebug() << "------------------发送数据的返回---------------------";

    // 将QJsonObject转换为QJsonDocument, 解析json数据
    QJsonDocument jsonDoc(jsonObj);

    if(!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();

        // 获取"choices"数组
        QJsonArray choicesArray = jsonObj["choices"].toArray();

        // 假设我们只需要第一个choice（根据索引0）
        if (!choicesArray.isEmpty()) {
            //代表获取一个元素
            QJsonObject choiceObj = choicesArray[0].toObject();

            // 获取"message"对象
            QJsonObject messageObj = choiceObj["message"].toObject();

            // 提取"content"字段的值
            qDebug() << messageObj["content"].toString();

            return messageObj["content"].toString();
        }
    }
    return "";
}

//用来接收返回的Json数据
void Ai_Module::finshedSlot()
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData.data();

        //转换格式
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();
        QTextToSpeech* a = new QTextToSpeech();
        SpeckResponse(jsonObj);
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}
