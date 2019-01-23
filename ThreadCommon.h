#ifndef THREADCOMMO_H
#define THREADCOMMO_H
#include <QThread>

class ThreadCommon: public QThread
{
    Q_OBJECT
private:
    static int  threadCount;

public:
    ThreadCommon(QObject *parent = NULL);
    ~ThreadCommon();
    void setWorkObj(QObject *obj);
    static int getThreadCount();

    private slots:
        void slot_destoryMe();
        void slot_destoryWorkObj();

private:
    QObject *m_pWorkObj;
};

#endif // THREADCOMMO_H
