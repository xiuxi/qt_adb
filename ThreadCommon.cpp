#include "ThreadCommon.h"
#include <QDebug>
int ThreadCommon::threadCount = 0;
ThreadCommon::ThreadCommon(QObject *parent)
    : QThread(parent)
    ,m_pWorkObj(NULL)
{
    threadCount++;

  //  qDebug()<<"ThreadCommon current thread = " << this->getThreadCount();
    connect(this, SIGNAL(finished()), this, SLOT(slot_destoryMe()));
}

void ThreadCommon::slot_destoryMe()
{
    //qDebug()<<"[INFO ] ["<<__FILE__<<":"<<__LINE__<<"]: "<< "entry slot_destoryMe()";

    this->deleteLater();

   // qDebug()<<"[INFO ] ["<<__FILE__<<":"<<__LINE__<<"]: "<<"exit slot_destoryMe()";
}

void ThreadCommon::slot_destoryWorkObj()
{
   // qDebug()<<"[INFO ] ["<<__FILE__<<":"<<__LINE__<<"]: "<<"entry slot_destoryWorkObj()";


    this->exit();

    //qDebug()<<"[INFO ] ["<<__FILE__<<":"<<__LINE__<<"]: "<<"exit slot_destoryWorkObj()";
}

void ThreadCommon::setWorkObj(QObject *obj)
{
    m_pWorkObj = obj;
    connect(m_pWorkObj, SIGNAL(destroyed()), this, SLOT(slot_destoryWorkObj()));
}
int  ThreadCommon::getThreadCount()
{

    return threadCount;
}

ThreadCommon::~ThreadCommon()
{
    threadCount--;
    this->wait();
   qDebug()<<"[INFO ] ["<<__FILE__<<":"<<__LINE__<<"]: "<< "excute ~WorkThread()" <<currentThreadId() ;
}

