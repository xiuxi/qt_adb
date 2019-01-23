#include "postList.h"
#include <QTextCodec>
#include <QPair>
#include <QFile>
#include <QCoreApplication>
#include <QDataStream>

postList::postList()
{

}
void postList::requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode)
{
    qDebug()<< "aa"<<data;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString string = codec->toUnicode(data);
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
