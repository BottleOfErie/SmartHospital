#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include "QwenClient.h"

QwenClient& QwenClient::getInstance(){
    static QwenClient instance;
    return instance;
}

QwenClient::QwenClient()
{
    manager=new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(networkReply(QNetworkReply*)));
}

QwenClient::~QwenClient(){
    delete manager;
}

void QwenClient::setAPI_KEY(char* key){
    API_KEY=QByteArray(key);
}

void QwenClient::networkReply(QNetworkReply* reply){
    QString info = reply->readAll();
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(info.toUtf8(),&err);
    bool hasReply=false;
    if(!doc.isNull()){
        QJsonObject file=doc.object();
        if(file.contains("output")){
            QJsonValue output=file.value("output");
            if(output.isObject()){
                QJsonObject outputObj=output.toObject();
                if(outputObj.contains("choices")){
                    QJsonValue choices=outputObj.value("choices");
                    if(choices.isArray()){
                        QJsonArray choicesObj=choices.toArray();
                        if(choicesObj.count()>0){
                            QJsonValue first=choicesObj[0];
                            if(first.isObject()){
                                QJsonObject firstObj=first.toObject();
                                if(firstObj.contains("message")){
                                    QJsonValue message=firstObj.value("message");
                                    if(message.isObject()){
                                        QJsonObject messageObj=message.toObject();
                                        if(messageObj.contains("content")){
                                            QJsonValue content=messageObj.value("content");
                                            if(content.isString()){
                                                QString str=content.toString();
                                                hasReply=true;
                                                qDebug("aiReply:%s",str.toStdString().data());
                                                emit aiReply(str);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    reply->deleteLater();
    if(!hasReply){
        qDebug("Wrong aiReply:%s",info.toStdString().data());
        emit aiReply(QString("AI服务异常，请联系设备管理员"));
    }
}

void QwenClient::ask(QString question){
    if(API_KEY.compare("")==0){
        qDebug("Cannot Use Ai Service!No API_KEY!");
        emit aiReply("Cannot Use Ai Service!No API_KEY!");
        return;
    }
    QNetworkRequest request=QNetworkRequest(QUrl("https://dashscope.aliyuncs.com/api/v1/services/aigc/text-generation/generation"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setRawHeader("Authorization","Bearer "+API_KEY);

    char* prefix="{\"model\": \"qwen-turbo\", \"input\":{\"messages\":[{\"role\": \"system\",\"content\": \"You are a highly advanced medical AI designed to assist patients in adapting to hospital services.\"},{\"role\": \"user\",\"content\":\"";
    char* suffix="\"}]},\"parameters\": {\"result_format\": \"message\"}}";
    char requestData[2048];
    sprintf(requestData,"%s%s%s",prefix,question.toUtf8().data(),suffix);
    manager->post(request,requestData);
}
