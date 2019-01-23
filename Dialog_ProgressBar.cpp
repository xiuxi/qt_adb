#include "Dialog_ProgressBar.h"
#include "ui_Dialog_ProgressBar.h"

Dialog_ProgressBar::Dialog_ProgressBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ProgressBar)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(13);
    ui->progressBar->setValue(0);

}

void Dialog_ProgressBar::showDialog_slot(QString temp, int seep,ThreadADBSlots *ppThreadADBSlots)
{
    ui->ok->setEnabled(false);

    if(pThreadADBSlots ==NULL)
    {
        pThreadADBSlots = ppThreadADBSlots;
    }
    int okbuttonEnabed = 13;
    ui->progressBar->setValue(seep);
    ui->label_report->setText(temp);
    if(seep ==okbuttonEnabed )
    {
          ui->ok->setEnabled(true);
          ui->label_report->setText(tr("烧录完成"));
    }
    this->show();
}

Dialog_ProgressBar::~Dialog_ProgressBar()
{
    delete ui;
}

void Dialog_ProgressBar::on_ok_clicked()
{
       this->hide();
      ui->progressBar->setValue(0);
       ui->label_report->setText("");
}

void Dialog_ProgressBar::on_cen_clicked()
{
    emit cancel_signal();
  //  if(pThreadADBSlots !=NULL)
    {
  //      pThreadADBSlots->deleteLater();
    }
    this->hide();
}
