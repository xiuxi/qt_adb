#include "Dialog_AdbProcess.h"
#include <QApplication>
#include "httpApi/postList.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog_AdbProcess w;


    w.show();

    return a.exec();
}
