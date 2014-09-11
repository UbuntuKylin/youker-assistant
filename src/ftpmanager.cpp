#include "ftpmanager.h"
#include <QDir>

class FtpManager;

FtpManager::FtpManager(QString _host, QString userName, QString passWd, qint16 _port, QObject *parent):
    QObject(parent),
    m_userName(userName),
    m_passwd(passWd),
    m_File(0),
    m_IsOpenFile(false)
{
    myFtp = new QFtp(this);
    myFtp->setTransferMode(QFtp::Active);
//    myFtp->setTransferMode(QFtp::Passive);
    //连接ftp服务器
    myFtp->connectToHost(_host,_port);
    //进度条显示
    connect(myFtp,SIGNAL(dataTransferProgress(qint64,qint64)),SLOT(start_update_progress(qint64,qint64)));
    //状态显示
    connect(myFtp,SIGNAL(commandFinished(int,bool)),SLOT(ftp_command_finish(int,bool)));
}

FtpManager::~FtpManager()
{
    delete myFtp;
}

//停止Ftp动作
void FtpManager::start_abort()
{
    myFtp->abort();
}

//下载文件
void FtpManager::start_download(QString _remoteFile,QString _localFile)
{
    m_File = new QFile(_localFile);

    if(m_File->open(QIODevice::WriteOnly))
    {
        m_IsOpenFile = true;
        myFtp->get(_remoteFile,m_File);//kobe 0903
    }
    else
    {
        delete m_File;
        m_File = NULL;
        qDebug() << tr("local file %1 open failed.").arg(_localFile);
    }
}

void FtpManager::start_upload(QString _localFile,QString _remoteFile)
{
    m_File = new QFile(_localFile);

    if(m_File->open(QIODevice::ReadOnly))
    {
        m_IsOpenFile = true;
        myFtp->put(m_File,_remoteFile);
    }
    else
    {
        delete m_File;
        m_File = NULL;
        qDebug() << tr("本地文件%1打开失败！").arg(_localFile);
    }
}

void FtpManager::start_update_progress(qint64 _used, qint64 _total)
{
    int tmpVal = _used / (double)_total * 100;
    emit send_progress_value(tmpVal);
}

void FtpManager::ftp_command_finish(int tmp, bool en)
{
    Q_UNUSED(tmp);

    if(myFtp->currentCommand() == QFtp::ConnectToHost){

        if(en)
            qDebug() << (tr("connect ftp server error:%1").arg(myFtp->errorString()));

        else
        {
            qDebug() << (tr("connect ftp server success"));
            myFtp->login(m_userName,m_passwd);//登陆服务器
        }
    }

    if (myFtp->currentCommand() == QFtp::Login){

        if(en) {
            qDebug() << (tr("login ftp server error:%1").arg(myFtp->errorString()));
        }
        else {
            qDebug() << (tr("login ftp server success"));
            // start to download
            QString uk_path = QDir::homePath() + "/.config/ubuntukylin/youker-assistant/uk-img/";
            QDir tmpDir(uk_path);
            if(!tmpDir.exists())
            {
                this->start_download("uk-img.zip","/tmp/uk-img.zip");
//                this->start_upload("/home/trusty/test.txt","test.txt");
            }
        }
    }

    if (myFtp->currentCommand() == QFtp::Get)
    {
        if(en)
        {
            qDebug() << (tr("download error:%1").arg(myFtp->errorString()));
        }

        else
        {
            qDebug() << (tr("download over"));
            emit this->downloadok();
            m_File->flush();
        }

        m_File->close();
        m_IsOpenFile = false;
        delete m_File;
        m_File = NULL;
    }
    else if(myFtp->currentCommand() == QFtp::Put)
    {
        if(en)
        {
            qDebug() << (tr("上传出现错误：%1").arg(myFtp->errorString()));
        }
        else
        {
            qDebug() << (tr("已经完成文件上传"));
        }

        m_File->close();
        m_IsOpenFile = false;
        delete m_File;
        m_File = NULL;
    }
    else if (myFtp->currentCommand() == QFtp::Close)
    {
        qDebug() << (tr("had close connect"));
        if(m_IsOpenFile)
        {
            m_File->close();
            delete m_File;
            m_File = NULL;
        }
    }
}
