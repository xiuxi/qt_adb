#include "Adb_Progress.h"
#include <QMessageBox>


Adb_Progress::Adb_Progress(QObject *parent) : QObject(parent)
{
    AdbProcess = new QProcess(0);
    AdbPath = QCoreApplication::applicationDirPath();
    AdbPath +="/adbcopy";
    AdbProcess->setWorkingDirectory(AdbPath);

}

Adb_Progress::~Adb_Progress()
{
    AdbProcess->deleteLater();
}

bool Adb_Progress::restartAdb()
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+"kill-server";
    qDebug()<<"kill - server"<<apath;
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        emit isSucced_signal(false);
    }
    else
    {
        QString aapath = AdbPath+"/adb.exe "+"start-server";
        qDebug()<<"start - server"<<aapath;
        AdbProcess->start(aapath);
        if(!AdbProcess->waitForFinished(-1))
        {
            emit isSucced_signal(false);
            ret = false;
        }
        else
        {
            ret = true;
        }
    }
    return ret;
}

bool Adb_Progress::remount()
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+"remount";
    qDebug()<<"remount"<<apath;
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        emit isSucced_signal(false);
        ret = false;
    }
    else
    {
        QString output = QString::fromLocal8Bit(AdbProcess->readAll());
        qDebug()<<output;
        if(!output.isEmpty())
        {
            if(!output.contains("succeeded",Qt::CaseInsensitive))
            {
                //emit
                //QMessageBox::question(NULL, "Question", QObject::tr("Please check whether the ADB installed correctly"), QMessageBox::Cancel, QMessageBox::Cancel);
            }
            else
            {
                ret = true;
            }
        }

    }
    return ret;
}

bool Adb_Progress::mkdir(QString path)
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+" shell " +"mkdir -p "+path;

    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
    qDebug()<<"ASB mkdir  FALSE ";
        ret = false;
    }
    else
    {
        ret = true;


    }
    return ret;
}

bool Adb_Progress::ls(QString cmd)
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+" shell " +" ls "+cmd;

    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
    qDebug()<<"ASB mkdir  FALSE ";
        ret = false;
    }
    else
    {
        ret = true;


    }
    return ret;
}

bool Adb_Progress::adbroot()
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+"root";
    qDebug()<<"remount"<<apath;
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {

        ret = false;
    }
    else
    {
        ret = true;
    }
    return ret;
}

bool Adb_Progress::fastbootConnect()
{
    bool ret =false;
    QString apath = AdbPath+"/fastboot.exe "+"devices" ;
    //QMessageBox:: question(NULL, "const  ",apath,QMessageBox::Cancel, QMessageBox::Cancel);
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        ret = false;
    }
    else
    {
        QString temp = AdbProcess->readAllStandardOutput();
        //  QMessageBox:: question(NULL, "const  ",temp,QMessageBox::Cancel, QMessageBox::Cancel);
        qDebug()<< "fastbootConnect"<<temp;
        if(temp.isEmpty())
        {
            ret = false;
        }
        else{
            ret = true;
        }

    }
    return ret;
}
bool Adb_Progress::fastbootReboot()
{
    bool ret =false;
    QString apath = AdbPath+"/fastboot.exe "+"reboot" ;

    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        ret = false;
    }
    else
    {
        QString temp = AdbProcess->readAllStandardOutput();
        qDebug()<< "fastbootConnect"<<temp;
        if(temp.isEmpty())
        {
            ret = false;
        }
        else{
            ret = true;
        }

    }
    return ret;
}
bool Adb_Progress::fastbootFlash(const QString &cmd,const QString &path_env)
{
    bool ret =false;
    QString apath = AdbPath+"/fastboot.exe "+"flash  "+ " "+ cmd+" "+path_env ;

    qDebug()<<"GetDevice"<<apath;
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        ret = false;
        qDebug()<<"ret = false;";
    }
    else
    {
        QByteArray temp = AdbProcess->readAllStandardError();
        QString temp1(temp);
        qDebug()<< "fastbootFlash  ::" <<temp1;

        if(temp.contains("finished. total time"))
        {ret = true;}
        else
            ret=false;

        if(temp.contains("OKAY"))
        {ret = true;}
        else
            ret=false;


        if(!temp.contains("FAILED"))
        {ret = true;}
        else
            ret=false;
        if(!temp.contains("error"))
        {ret = true;}
        else
            ret=false;

    }
    return ret;
}

bool Adb_Progress::CommandFromUI(const QString &command)
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+command;
    qDebug()<<"GetDevice"<<apath;
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        ret = false;
    }
    else
    {
        ret = true;}
    return ret;
}

bool Adb_Progress::CommandFromUI(const QString &command, const QString &parameter)
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+command +" "+  parameter;
    qDebug()<<"GetDevice"<<apath;
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        ret = false;
    }
    else
    {
        ret = true;
    }
    return ret;
}

bool Adb_Progress::CommandFromUI(const QString &command, const QString &parameter, const QString &AndroidPath)
{
    bool ret = false;
    QString apath = AdbPath+"/adb.exe "+command +" "+  parameter +" "+AndroidPath;
    qDebug()<<"GetDevice"<<apath;
    AdbProcess->start(apath);
    if(!AdbProcess->waitForFinished(-1))
    {
        ret = false;
    }
    else
    {
        QByteArray temp = AdbProcess->readAllStandardError();
        QString temp1(temp);
        qDebug()<< "adb  "<<" command::" << command <<temp1;

        if(temp.contains("No such file or directory"))
        {
            ret = false;
        }
        else
        {
            ret=true;
        }

    }
    return ret;
}

