#ifndef ADB_PROGRESS_H
#define ADB_PROGRESS_H

#include <QObject>
#include <QProcess>
#include <QApplication>
#include <QDebug>

class Adb_Progress:QObject
{
    Q_OBJECT
private:
    QProcess *AdbProcess;
    QString  AdbPath;
public:
    Adb_Progress(QObject *parent = 0);
    ~Adb_Progress();
    bool restartAdb();
    bool remount();
    bool adbroot();
   bool mkdir(QString path);
   bool ls(QString cmd);
    bool fastbootConnect();
    bool fastbootFlash(const QString &cmd,const QString &path_env);
    bool fastbootReboot();
signals:
    void isSucced_signal(bool);

public :

    bool CommandFromUI(const QString& command);
    bool CommandFromUI(const QString& command,const QString& parameter);
    bool CommandFromUI(const QString& command,const QString& parameter,const QString& AndroidPath);


};

#endif // ADB_PROGRESS_H
