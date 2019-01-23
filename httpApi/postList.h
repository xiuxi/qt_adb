#ifndef POSTLIST_H
#define POSTLIST_H
#include "httpApi.h"

class postList : public httpApi
{
    Q_OBJECT
public:
    postList();
protected:
    void requestFinished(QNetworkReply* reply, const QByteArray data, const int statusCode);
signals:
      void readRead();

};

#endif // POSTLIST_H
