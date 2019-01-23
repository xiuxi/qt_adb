#include "httpApi.h"
#include <QTextCodec>
#include <QPair>
#include <QFile>
#include <QCoreApplication>
#include <QDataStream>
httpApi::httpApi()
{
    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
}

httpApi::~httpApi()
{
    networkAccessManager.disconnect();

}

void httpApi::get(const QString url)
{
    httpRequest.setUrl(QUrl(url));
    networkAccessManager.get(httpRequest);
}

void httpApi::post(const QString url, const QByteArray &data)
{
    httpRequest.setUrl(QUrl(url));
  //  httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
   // httpRequest.setHeader(QNetworkRequest::ContentLengthHeader, bytePost.length());
  //  QNetworkReply *pReply = pManager->post(request, bytePost);
    networkAccessManager.post(httpRequest, data);
}

void httpApi::postJson(const QString url, const QByteArray &data)
{
    httpRequest.setUrl(QUrl(url));
    httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    httpRequest.setHeader(QNetworkRequest::ContentLengthHeader, data.length());
    httpRequest.setRawHeader("api-key", "6de8673afe224c9c57d52e9e8cfb6e48");

    networkAccessManager.post(httpRequest, data);
    qDebug()<<"postJson "<< data;
}


void httpApi::serviceRequestFinished(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "BaseAPI...serviceRequestFinished...statusCode:" << statusCode;

    if(reply->error() == QNetworkReply::NoError) {
        requestFinished(reply, reply->readAll(), statusCode);
    } else {
        requestFinished(reply, "", statusCode);
    }

    // At the end of that slot, we won't need it anymore
    reply->deleteLater();
}
void httpApi::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    qDebug()<< "aa"<<data;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString string = codec->toUnicode(data);
    qDebug()<<"requestFinished" <<string;
    string = string.replace("\"","");
    qDebug()<< "aa"<<string;

    if (statusCode == 200) {
        QString Path = QCoreApplication::applicationDirPath();
        Path+="/list.conf";
        QFile file(Path);
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Can't open file for writing";

        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_6);
        out  << data;
        file.close();

        emit readRead();


    }
}
