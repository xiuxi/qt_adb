#include "Dialog_AdbProcess.h"
#include "ui_Dialog_AdbProcess.h"

#include <QJsonParseError>
#include<QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextCodec>
Dialog_AdbProcess::Dialog_AdbProcess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dialog_AdbProcess)
{
    isFirst= false;
//postLista();
    ui->setupUi(this);
    connect(&post,SIGNAL(readRead()),this,SLOT(readList()));
    firstReadList();



    picPath = QCoreApplication::applicationDirPath();
    picPath +="/bootanimation.zip";
    ui->lineEdit_picpath_PC->setText(picPath);
    ui->lineEdit_devid->setValidator(new QIntValidator(0, 99999999, this));

    QString envfile = QCoreApplication::applicationDirPath();
    envfile+="/env.txt";
    QFileInfo fileInfo(envfile); //如果存在就直接读取文件获取devid
    if(fileInfo.isFile())
    {
        QFile file (envfile);
        QTextStream filestream(&file);
        if(file.open(QFile::ReadOnly))
        {
            QString temp =filestream. readAll();
            int a=  temp.indexOf("serialno");
            int  temp_int = temp.mid(a+9,8).toInt();
            qDebug()<<"temp"<<temp  << a <<temp_int;
            if(ui->checkBox_devid->isChecked()) //如果自增开启就自动加+1
            {
                temp_int++;
            }
            QString devid ;
            devid =  devid.sprintf("%08d",temp_int);
            ui->lineEdit_devid->setText(devid);
            file.close();
        }

    }
    AdbProgress = new Adb_Progress(this);
    DialogProgressBar= new Dialog_ProgressBar(this);
    DialogProgressBar->hide();
    connect(this,&Dialog_AdbProcess::changProgress,DialogProgressBar,&Dialog_ProgressBar::showDialog_slot);
}
void Dialog_AdbProcess::showList(){
    ui->comboBox->clear();
    ui->ComboBox_depict->clear();
    if(map.isEmpty())
    {

    }
    else
    {
        QHash<QString, QString>::iterator i;
        for( i=map.begin(); i!=map.end(); ++i)
        {
            ui->comboBox->addItem(i.key());
        }
        QString tem = ui->comboBox->currentText();
        for(int  j = 0 ;j<list.size();j++)
        {
           ListProtocol listPro ;
           listPro =  list.at(j);
           if(listPro.getName() == tem)
           {
                ui->ComboBox_depict->addItem(listPro.getDepict());
           }

        }
         QString tem_2 = ui->ComboBox_depict->currentText();

         for(int  j = 0 ;j<list.size();j++)
         {
            ListProtocol listPro ;
            listPro =  list.at(j);
            if(listPro.getName() == tem &&listPro.getDepict() == tem_2)
            {
                 ui->LineEdit_IDshow->setText(listPro.getType());
            }

         }

    }
}
void Dialog_AdbProcess::firstReadList()
{
    readList();
    if(isFirst)
    {
        postLista();
    }
}
void Dialog_AdbProcess::postLista()
{

    QByteArray postData;
    // connect(&post,SIGNAL(readRead()),this,SLOT(readList());
    postData.append("software_verson");
    QString url ="http://192.168.1.249:9090/alky_gps_server/software_verson?software_verson=1";
    post.post(url,postData);
}

void Dialog_AdbProcess:: postLista(QString ip ,QString com)
{

    QByteArray postData;
    //  connect(&post,SIGNAL(readRead()),this,SLOT(readList());
    postData.append("software_verson");

    QString url =QString("http://%1:%2/alky_gps_server/software_verson?software_verson=1").arg(ip).arg(com);
    post.post(url,postData);
}


Dialog_AdbProcess::~Dialog_AdbProcess()
{
    delete AdbProgress;
    delete DialogProgressBar;
    delete ui;
}

bool Dialog_AdbProcess::writeFileEnv(int devid ,QString & filePath)
{
    bool ret = false;
    QString devsn ;
    devsn =  devsn.sprintf("%08d",devid);
devsn  = "T0"+devsn;
qDebug()<<"writeFileEnv = "<<devsn;
    filePath = QCoreApplication::applicationDirPath();

    filePath+= "/env.txt";

    QString writeTemp =QString("bootargs=\"console=ttyAMA0,115200n8 androidboot.hardware=lepus androidboot.console=ttyAMA0 androidboot.serialno=%1 initrd=0x49000000,0x200000 init=/init no_console_suspend\";").arg(devsn);

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
bool Dialog_AdbProcess::writeFileEnv(int devid ,QString & filePath ,QString &head)
{
    bool ret = false;
    QString devsn ;
    devsn =  devsn.sprintf("%08d",devid);
    devsn  = head+devsn;
qDebug()<<"writeFileEnv = "<<devsn;
    filePath = QCoreApplication::applicationDirPath();

    filePath+= "/env.txt";

    QString writeTemp =QString("bootargs=\"console=ttyAMA0,115200n8 androidboot.hardware=lepus androidboot.console=ttyAMA0 androidboot.serialno=%1 initrd=0x49000000,0x200000 init=/init no_console_suspend\";").arg(devsn);

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

bool  Dialog_AdbProcess::writeFileUnitID(QString devid ,QString unit ,QString &filePath)
{



//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    bool ret = false;
    QString devsn ;
    filePath = QCoreApplication::applicationDirPath();
    filePath+= "/product.conf";
    //  unsigned char  *key =(unsigned char  *) "lin";

    QString  q_str;
    char*  before;
    QByteArray ba = unit.toUtf8();
    before=ba.data();
    char after[1024]={0};
    char result[1024]={0};
    unsigned char key[] =  "1234567890123456";
    //加密函数
    AES aes(key);
    aes.Bm53Cipher(before,after);
    qDebug()<<"AES :"<<QString(after);

    QString writeTemp =QString("comsumerId=%1\r\ncomsumerUnit=%2").arg(devid).arg(QString(after));

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
void Dialog_AdbProcess::on_changeLogo_clicked()
{
    qDebug()<<"on_changeLogo_clicked";
    QSettings settings("MySoft", "Star Runner");

    picPathSetting = settings.value("filePath").toString();
    if(picPathSetting.isEmpty())
    {
        picPath = QFileDialog::getOpenFileName(this, tr("get File"),
                                               QApplication::applicationDirPath(),
                                               tr("Logo (*.zip)"));
    }
    else
    {
        picPath = QFileDialog::getOpenFileName(this, tr("get File"),
                                               picPathSetting,
                                               tr("Logo (*.zip)"));
    }

    QFileInfo fileInfo(picPath);
    if( fileInfo.isFile())
    {
        settings.setValue("filePath",fileInfo.dir().path());

        ui->lineEdit_picpath_PC->setText(picPath);
    }
    else
    {

    }
}


void Dialog_AdbProcess:: readList(){
    QString Path = QCoreApplication::applicationDirPath();
    Path+="/list.conf";
    QFile file(Path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open file for reading: ";
        isFirst = true;//打不开
        return ;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_6);
    QByteArray s;
    in >>  s;
    file.close();
    if(s.isEmpty())  // 数据为空
    {
        isFirst = true;
    }
    else{
        isFirst = false;
        map.clear();
        list.clear();
        QJsonParseError jsonError;
        QJsonArray json_array = QJsonDocument::fromJson(s, &jsonError).array();
        if(jsonError.error == QJsonParseError::NoError) {

            for(int i = 0; i < json_array.size(); ++i) {
                QJsonObject json = json_array.at(i).toObject();
        ListProtocol *tem = new ListProtocol(json.value("depict").toString(),json.value("name").toString(),json.value("type").toString());
                qDebug()<< "name"<<  json.value("name").toString();
                map.insert(json.value("name").toString(),json.value("type").toString() );

                list.append(*tem);
                qDebug()<<"type" << json.value("type").toString();
            }

        }
        showList();
    }
}
void Dialog_AdbProcess::on_pushLogo_clicked()
{


    if(!picPath.isEmpty()){
        if(!AdbProgress->remount()) // 配置安卓可读可写
        {
            AdbProgress->adbroot();
            QMessageBox::warning(this,"Check ADB Server",tr("请检查usb 和 adb 是否 连接 正常！！！"),QMessageBox::Ok);
        }
        else
        {
            AdbProgress->adbroot();

            bool temp = AdbProgress->CommandFromUI("push",picPath,"/system/media/");
            if(!temp)
            {
                QMessageBox::warning(this,"Check ADB Server",tr("请检查usb 和 adb 是否连连接正常！同时检查是否选择bootanimation.zip 文件"),QMessageBox::Ok);
            }
            else
            {
                QMessageBox::information(this,"成功",tr("更新开机动画成功"),QMessageBox::Ok);
            }
        }
    }
}
void Dialog_AdbProcess::on_ChangDEVID_clicked()
{

    if (!AdbProgress->fastbootConnect())
    {
        QMessageBox::warning(this,"检查是否连接设备",tr("请检查是否连接设备，并且设备进入fastboot模式！！！"),QMessageBox::Ok);
        return;
    }



    if(!ui->lineEdit_devid->text().isEmpty())
    {
        int  temp = ui->lineEdit_devid->text().trimmed().toInt();
        QString head = ui->lineEdit_head->text().trimmed();
        QString path;
        if( writeFileEnv(temp ,path,head))
        {
            if(AdbProgress->fastbootFlash("env",path))
            {
                if(ui->checkBox_devid->isChecked())
                {
                    temp++;
                }
                AdbProgress->fastbootReboot();

                qDebug()<<"on_ChangDEVID_clicked"<<temp;

                QString devid ;
                devid =  devid.sprintf("%08d",temp);


                ui->lineEdit_devid->setText(devid);
                QMessageBox::warning(this,"成功",tr("成功修改序列号！！！"),QMessageBox::Ok);

            }
            else
            {
                QMessageBox::warning(this,"检查是否连接设备",tr("请检查是否连接设备，并且设备进入fastboot模式！！！"),QMessageBox::Ok);
                return;
            }

        }
    }
    else
    {
        QMessageBox::warning(this,"输入设备序列号",tr("请检查序列号输入是否正常！！！"),QMessageBox::Ok);
        return;
    }



}

/*void Dialog_AdbProcess::on_ChangDEVID_clicked()
{

    if (!AdbProgress->fastbootConnect())
    {
        QMessageBox::warning(this,"检查是否连接设备",tr("请检查是否连接设备，并且设备进入fastboot模式！！！"),QMessageBox::Ok);
        return;
    }


    QString override_path =QCoreApplication::applicationDirPath();
    QString nand  = override_path+"/img/2ndboot.bin";
    QString uboot  = override_path+"/img/u-boot.bin";
    QString boot  = override_path+"/img/boot.img";
    QString cache  = override_path+"/img/cache.img";
    QString system  = override_path+"/img/system.img";

    QString userdata  = override_path+"/img/userdata.img";

    if(!ui->lineEdit_devid->text().isEmpty())
    {


        emit changProgress(tr("更新2ndboot……"),0);

        if(AdbProgress->fastbootFlash("2ndboot",nand))
        {
             emit changProgress("更新2ndboot成功",1);
        }
        else
        {
            QMessageBox::question(this,"检查是否连接设备",tr("跟新2ndboot失败"),QMessageBox::Ok);
            return;
        }

        emit changProgress("更新bootloader……",2);
        if(AdbProgress->fastbootFlash("bootloader",uboot))
        {
             emit changProgress("更新bootloader成功",3);
        }
        else
        {
            QMessageBox::question(this,"检查是否连接设备",tr("跟新bootloader失败"),QMessageBox::Ok);
            return;
        }

        emit changProgress("更新boot……",4);
        if(AdbProgress->fastbootFlash("boot",boot))
        {
             emit changProgress("更新boot成功",5);
        }
        else
        {
            QMessageBox::question(this,"检查是否连接设备",tr("跟新boot失败"),QMessageBox::Ok);
            return;
        }

        emit changProgress("更新cache……",6);
        if(AdbProgress->fastbootFlash("cache",cache))
        {
             emit changProgress("更新cache成功",7);
        }
        else
        {
            QMessageBox::question(this,"检查是否连接设备",tr("跟新cache失败"),QMessageBox::Ok);
            return;
        }


        emit changProgress("更新system……",8);
        if(AdbProgress->fastbootFlash("system",system))
        {
             emit changProgress("更新system成功",9);
        }
        else
        {
            QMessageBox::question(this,"检查是否连接设备",tr("更新system失败"),QMessageBox::Ok);
            return;
        }
        emit changProgress("更新userdata……",10);
        if(AdbProgress->fastbootFlash("userdata",userdata))
        {
             emit changProgress("更新system成功",11);
        }
        else
        {
            QMessageBox::question(this,"检查是否连接设备",tr("更新userdata失败"),QMessageBox::Ok);
            return;
        }




         emit changProgress("更新产品序列号……",12);
        int  temp = ui->lineEdit_devid->text().trimmed().toInt();
        QString path;
        if( writeFileEnv(temp ,path))
        {
            if(AdbProgress->fastbootFlash("env",path))
            {
                if(ui->checkBox_devid->isChecked())
                {
                    temp++;
                }
                emit changProgress("更新更新产品序列号成功",13);
                qDebug()<<"on_ChangDEVID_clicked"<<temp;
                ui->lineEdit_devid->setText(QString::number(temp));
            }
            else
            {
                QMessageBox::warning(this,"检查是否连接设备",tr("请检查是否连接设备，并且设备进入fastboot模式！！！"),QMessageBox::Ok);
                return;
            }

        }
    }
    else
    {
        QMessageBox::warning(this,"输入设备序列号",tr("请检查序列号输入是否正常！！！"),QMessageBox::Ok);
        return;
    }

}

*/

void Dialog_AdbProcess::on_restartADB_clicked()
{
    AdbProgress->restartAdb();
}

void Dialog_AdbProcess::cancel_slot()
{
    delete AdbProgress;
    AdbProgress = new Adb_Progress(this);

}

void Dialog_AdbProcess::devid_slot()
{
    int  temp = ui->lineEdit_devid->text().trimmed().toInt();
    temp++;
    QString devid ;
    devid =  devid.sprintf("%08d",temp);
    ui->lineEdit_devid->setText(devid);
}

void Dialog_AdbProcess::changProgress_signal_thread_slot(QString tem , int temp,ThreadADBSlots *pThreadADBSlots)
{
    emit changProgress(tem,temp,pThreadADBSlots);
}

void Dialog_AdbProcess::showwringmes(const QString &title, const QString &mes)
{
    QMessageBox::question(this,title,mes,QMessageBox::Ok);
}



void Dialog_AdbProcess::on_pushButton_clicked()
{
    if (!AdbProgress->fastbootConnect())
    {
        QMessageBox::warning(this,"检查是否连接设备",tr("请检查是否连接设备，并且设备进入fastboot模式！！！"),QMessageBox::Ok);
        return;
    }
    if(!ui->lineEdit_devid->text().isEmpty())
    {
        int  tempint = ui->lineEdit_devid->text().trimmed().toInt();

        ThreadADBSlots   * pThreadADBSlots =new ThreadADBSlots;
        ThreadCommon *pThreadCommon =new ThreadCommon;

        pThreadADBSlots = new ThreadADBSlots();
        pThreadCommon = new ThreadCommon();

        pThreadCommon->setWorkObj(pThreadADBSlots);
        pThreadADBSlots->moveToThread(pThreadCommon);

        connect(this,&Dialog_AdbProcess::startThread_singnal,pThreadADBSlots,&ThreadADBSlots::upadataSystem);
        connect(pThreadADBSlots,&ThreadADBSlots::changProgress_signal_thread,this,&Dialog_AdbProcess::changProgress_signal_thread_slot);
        connect(pThreadADBSlots,&ThreadADBSlots::devid_signal,this,&Dialog_AdbProcess::devid_slot);
        connect(pThreadADBSlots,&ThreadADBSlots::showwringmes_signal,this,&Dialog_AdbProcess::showwringmes);

        pThreadCommon->start();
        bool temp = ui->checkBox_devid->isChecked();
        bool temp2 = ui->checkBox_devid_2->isChecked();
        QString head = ui->lineEdit_head->text().trimmed();
        emit  startThread_singnal(temp,tempint,temp2,head);

    }
    else
    {
        QMessageBox::warning(this,"输入设备序列号",tr("请检查序列号输入是否正常！！！"),QMessageBox::Ok);
        return;
    }

}

void Dialog_AdbProcess::on_pushButton_2_clicked()
{
    if(!ui->LineEdit_IDshow->text().isEmpty())
    {
        QString path;
        if(writeFileUnitID(ui->LineEdit_IDshow->text(),ui->unitLineEdit->text(),path))
        {
            if(AdbProgress->mkdir("/sdcard/well"))
            {
                if(!AdbProgress->remount()) // 配置安卓可读可写
                {
                    AdbProgress->adbroot();
                    QMessageBox::warning(this,"Check ADB Server",tr("请检查usb 和 adb 是否 连接 正常！！！"),QMessageBox::Ok);
                }
                else
                {
                    AdbProgress->adbroot();

                    bool temp = AdbProgress->CommandFromUI("push",path,"/sdcard/well");
                    if(!temp)
                    {
                        QMessageBox::warning(this,"Check ADB Server",tr("请检查usb 和 adb 是否连连接正常！同时检查是否选择bootanimation.zip 文件"),QMessageBox::Ok);
                    }
                    else
                    {
                        if(AdbProgress->ls("-la  /sdcard/well"))
                        {
                        QMessageBox::information(this,"成功",tr("更新用戶代码和单位成功"),QMessageBox::Ok);
}
                    }
                }
            }
            else{
                QMessageBox::warning(this,"Check ADB Server",tr("请检查usb 和 adb 是否 连接 正常！！！"),QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::warning(this,"写文件失败",tr("请检查输入id 和 Unite是全部添写！是否存在特殊字符！！"),QMessageBox::Ok);
        }
    }
    else{
        QMessageBox::warning(this,"输入id 和 Unite",tr("请检查输入id 和 Unite是全部添写！！！"),QMessageBox::Ok);
        return;
    }
}

void Dialog_AdbProcess::on_comboBox_currentIndexChanged(const QString &arg1)
{

    ui->ComboBox_depict->clear();
    qDebug()<<"on_comboBox_currentIndexChanged  "<< arg1;
       // ui->LineEdit_IDshow->setText(map.value(arg1));
        QString tem = ui->comboBox->currentText();
        for(int  j = 0 ;j<list.size();j++)
        {
           ListProtocol listPro ;
           listPro =  list.at(j);
           if(listPro.getName() == tem)
           {
                ui->ComboBox_depict->addItem(listPro.getDepict());
           }

        }
         QString tem_2 = ui->ComboBox_depict->currentText();

         for(int  j = 0 ;j<list.size();j++)
         {
            ListProtocol listPro ;
            listPro =  list.at(j);
            if(listPro.getName() == tem &&listPro.getDepict() == tem_2)
            {
                 ui->LineEdit_IDshow->setText(listPro.getType());
            }

         }
}

void Dialog_AdbProcess::on_pushButton_3_clicked()
{
   if(ui->iPLineEdit->text().isEmpty()|| ui->cOMLineEdit->text().isEmpty())
    {
        ui->comboBox->clear();
        ui->ComboBox_depict->clear();
        postLista();
    }
   else
    {
        ui->comboBox->clear();
        ui->ComboBox_depict->clear();
        postLista(ui->iPLineEdit->text(),ui->cOMLineEdit->text());
    }
  //  QString aaa = "http://34.217.203.141:8090/realtimeupload/eventlog" ;
  //  QByteArray tem =QString( "{ \"cmd\": \"upload\", \"deviceid\": \"1818000000001163\", \"rec_no\": \"\",\"category\": \"Handset Power\",\"actionTime\": \"2018-05-15 10:16:33\",\"result\": \"Handset power on\",\"brac\": \"\",\"unit\": \" %\",\"longitude\": \"00'0\",\"latitude\": \"00'0\",\"picture_path\": \"\",\"cam\": \"\"}").toLocal8Bit();
  // post.postJson(aaa,tem);
}

void Dialog_AdbProcess::on_ComboBox_depict_currentIndexChanged(int index)
{
    QString tem = ui->comboBox->currentText();
     QString tem_2 = ui->ComboBox_depict->currentText();
     for(int  j = 0 ;j<list.size();j++)
     {
        ListProtocol listPro ;
        listPro =  list.at(j);
        if(listPro.getName() == tem &&listPro.getDepict() == tem_2)
        {
             ui->LineEdit_IDshow->setText(listPro.getType());
        }

     }
}
