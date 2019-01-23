#include "ThreadADBSlots.h"
#include "Adb_Progress.h"
#include <QMessageBox>
#include <QFile>
#include <QThread>
void ThreadADBSlots::upadataSystem(bool ischeck, int temp ,bool isBrundev ,QString head) //使用线程来烧录机器
{
    Adb_Progress AdbProgress;
    QString override_path =QCoreApplication::applicationDirPath();
    QString nand  = override_path+"/img/2ndboot.bin";
    QString uboot  = override_path+"/img/u-boot.bin";
    QString boot  = override_path+"/img/boot.img";
    QString cache  = override_path+"/img/cache.img";
    QString system  = override_path+"/img/system.img";

    QString userdata  = override_path+"/img/userdata.img";



    emit changProgress_signal_thread(tr("更新2ndboot……"),0,this);

    if(AdbProgress.fastbootFlash("2ndboot",nand))
    {
        emit changProgress_signal_thread("更新2ndboot成功",1,this);
    }
    else
    {
         showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
        //QMessageBox::question(this,"检查是否连接设备",tr("跟新2ndboot失败"),QMessageBox::Ok);
        this->deleteLater();
        return;
    }

    emit changProgress_signal_thread("更新bootloader……",2,this);
    if(AdbProgress.fastbootFlash("bootloader",uboot))
    {
        emit changProgress_signal_thread("更新bootloader成功",3,this);
    }
    else
    {
         showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
       // QMessageBox::question(this,"检查是否连接设备",tr("跟新bootloader失败"),QMessageBox::Ok);
         this->deleteLater();
        return;
    }

    emit changProgress_signal_thread("更新boot……",4,this);
    if(AdbProgress.fastbootFlash("boot",boot))
    {
        emit changProgress_signal_thread("更新boot成功",5,this);
    }
    else
    {
         showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
      //  QMessageBox::question(this,"检查是否连接设备",tr("跟新boot失败"),QMessageBox::Ok);
         this->deleteLater();
        return;
    }
  QThread::sleep(1);
    emit changProgress_signal_thread("更新cache……",6,this);
    if(AdbProgress.fastbootFlash("cache",cache))
    {
        emit changProgress_signal_thread("更新cache成功",7,this);
    }
    else
    {
         showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
        //QMessageBox::question(this,"检查是否连接设备",tr("跟新cache失败"),QMessageBox::Ok);
         this->deleteLater();
        return;
    }

  QThread::sleep(1);
    emit changProgress_signal_thread("更新system……",8,this);
    if(AdbProgress.fastbootFlash("system",system))
    {
        emit changProgress_signal_thread("更新system成功",9,this);
    }
    else
    {
         showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
       // QMessageBox::question(this,"检查是否连接设备",tr("更新system失败"),QMessageBox::Ok);
         this->deleteLater();
        return;
    }
    QThread::sleep(1);
    emit changProgress_signal_thread("更新userdata……",10,this);
    if(AdbProgress.fastbootFlash("userdata",userdata))
    {
        emit changProgress_signal_thread("更新system成功",11,this);
    }
    else
    {
         showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
        //QMessageBox::question(this,"检查是否连接设备",tr("更新userdata失败"),QMessageBox::Ok);
        showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
        this->deleteLater();
        return;
    }


    if(isBrundev)
    {
        QThread::sleep(1);
        emit changProgress_signal_thread("更新产品序列号……",12,this);
        // int  temp = ui->lineEdit_devid->text().trimmed().toInt();
        QString path;
        if( writeFileEnv(temp ,path,head))
        {
            if(AdbProgress.fastbootFlash("env",path))
            {
                if(ischeck)
                {
                    emit devid_signal();
                }
                emit changProgress_signal_thread("更新更新产品序列号成功",13,this);
                qDebug()<<"on_ChangDEVID_clicked"<<temp;
                //        ui->lineEdit_devid->setText(QString::number(temp));
            }
            else
            {
                showwringmes_signal("检查是否连接设备",tr("更新userdata失败"));
                //          QMessageBox::warning(this,"检查是否连接设备",tr("请检查是否连接设备，并且设备进入fastboot模式！！！"),QMessageBox::Ok);
                this->deleteLater();
                return;
            }

        }
    }
    else
    {
        QThread::sleep(1);
        emit changProgress_signal_thread("更新成功",13,this);
    }
    QThread::sleep(1);
    AdbProgress.fastbootReboot();
    this->deleteLater();








}

bool ThreadADBSlots::writeFileEnv(int devid ,QString & filePath)
{
    bool ret = false;
    filePath = QCoreApplication::applicationDirPath();
    filePath+= "/env.txt";

    QString devid_sn ;
    devid_sn =  devid_sn.sprintf("%08d",devid);
    qDebug()<<"on_ChangDEVID_clicked = "<<devid_sn;
    QString writeTemp =QString("bootargs=\"console=ttyAMA0,115200n8 androidboot.hardware=lepus androidboot.console=ttyAMA0 androidboot.serialno=%1 initrd=0x49000000,0x200000 init=/init no_console_suspend\";").arg(devid_sn);

    QFile file(filePath);
    QTextStream fileString(&file);
    if(file.open(QFile::WriteOnly))
    {
        fileString <<writeTemp;
        ret = true;
        file.close();
    }
    else ret = false;
    return ret;

}
bool ThreadADBSlots::writeFileEnv(int devid ,QString & filePath,QString & head)
{
    bool ret = false;
    filePath = QCoreApplication::applicationDirPath();
    filePath+= "/env.txt";

    QString devid_sn ;
    devid_sn =  devid_sn.sprintf("%08d",devid);
    devid_sn = head + devid_sn;
    qDebug()<<"on_ChangDEVID_clicked = "<<devid_sn;
    QString writeTemp =QString("bootargs=\"console=ttyAMA0,115200n8 androidboot.hardware=lepus androidboot.console=ttyAMA0 androidboot.serialno=%1 initrd=0x49000000,0x200000 init=/init no_console_suspend\";").arg(devid_sn);

    QFile file(filePath);
    QTextStream fileString(&file);
    if(file.open(QFile::WriteOnly))
    {
        fileString <<writeTemp;
        ret = true;
        file.close();
    }
    else ret = false;
    return ret;

}
ThreadADBSlots::ThreadADBSlots(QObject *parent) : QObject(parent)
{

}
