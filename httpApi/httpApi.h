#ifndef BASEAPI_H
#define BASEAPI_H

#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>


class httpApi : public QObject
{
    Q_OBJECT

public:
    httpApi();
    ~httpApi();
    void get(const QString url);
    void post(const QString url, const QByteArray &data);
    void postJson(const QString url, const QByteArray &data);

protected:
     void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) ;

public slots:
    void serviceRequestFinished(QNetworkReply *reply);

private:
    QNetworkRequest httpRequest;
    QNetworkAccessManager networkAccessManager;
    QSettings *settings;
signals:
    void readRead();
};

#endif // BASEAPI_H
