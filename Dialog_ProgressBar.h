#ifndef DIALOG_PROGRESSBAR_H
#define DIALOG_PROGRESSBAR_H

#include <QDialog>
#include "ThreadADBSlots.h"
namespace Ui {
class Dialog_ProgressBar;
}

class Dialog_ProgressBar : public QDialog
{
    Q_OBJECT
private:
    ThreadADBSlots *pThreadADBSlots;
public:
    explicit Dialog_ProgressBar(QWidget *parent = 0);
     ~Dialog_ProgressBar();
public slots:
    void showDialog_slot(QString ,int ,ThreadADBSlots *);

signals:
     void cancel_signal();
private slots:
    void on_ok_clicked();

    void on_cen_clicked();

private:
    Ui::Dialog_ProgressBar *ui;
};

#endif // DIALOG_PROGRESSBAR_H
