#ifndef THREADADBSLOTS_H
#define THREADADBSLOTS_H

#include <QObject>

class ThreadADBSlots : public QObject
{
    Q_OBJECT
public:
    ThreadADBSlots(QObject *parent = 0);
    bool writeFileEnv(int devid ,QString & filePath);
    bool writeFileEnv(int devid ,QString & filePath,QString & head);
signals:
    void changProgress_signal_thread(QString ,int, ThreadADBSlots *);
    void devid_signal();
    void showwringmes_signal(const QString& title, const QString& mes);
public slots:
    void upadataSystem(bool ischeck, int temp,bool isBrundev, QString head);

};

#endif // THREADADBSLOTS_H
