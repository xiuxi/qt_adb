#ifndef DIALOG_ADBPROCESS_H
#define DIALOG_ADBPROCESS_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "Adb_Progress.h"
#include <QSettings>
#include "Dialog_ProgressBar.h"
#include <QMessageBox>
#include "ThreadADBSlots.h"
#include "ThreadCommon.h"
#include"AES/aes.h"
#include "httpApi/httpApi.h"
#include "ListProtocol.h"
namespace Ui {
class Dialog_AdbProcess;
}

class Dialog_AdbProcess : public QWidget
{
    Q_OBJECT
private:
    bool isFirst;
    QString picPath ,picPathSetting;
    Adb_Progress *AdbProgress;
    Dialog_ProgressBar *DialogProgressBar;
    httpApi post;
    QHash<QString, QString> map;
    QList<ListProtocol> list;
public:
     void firstReadList();
    explicit Dialog_AdbProcess(QWidget *parent = 0);
    ~Dialog_AdbProcess();
      bool writeFileEnv (int ,QString &);
    bool writeFileEnv (int ,QString & ,QString &);
    bool  writeFileUnitID(QString devid ,QString unit ,QString &filePath);
    void  postLista();
    void  postLista(QString ip ,QString com);
    void showList();
signals:
    void changProgress(QString  ,int, ThreadADBSlots *);
    void startThread_singnal(bool,int,bool,QString);
private slots:
    void on_changeLogo_clicked();

    void on_pushLogo_clicked();
void readList();
    void on_ChangDEVID_clicked();

    void on_restartADB_clicked();

    void cancel_slot();
    void devid_slot();
    void changProgress_signal_thread_slot(QString  ,int,ThreadADBSlots *);
    void showwringmes(const QString& title, const QString& mes);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_ComboBox_depict_currentIndexChanged(int index);

private:
    Ui::Dialog_AdbProcess *ui;
};

#endif // DIALOG_ADBPROCESS_H
