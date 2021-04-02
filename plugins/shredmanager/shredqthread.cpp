#include "shredqthread.h"
#include <QDebug>

ShredQThread::ShredQThread(char *ch)
{
    this->filename = ch;
}

ShredQThread::~ShredQThread()
{

}

void ShredQThread::run()
{
    int result = do_file(filename);
    if (result == 0)
    {
        //success
        emit success();
    }
    else
    {
        //failed
        qDebug() << Q_FUNC_INFO << result;
        emit failed();
    }
}
