#include "cleandetailveiw.h"
#include <QDebug>

CleandetailVeiw::CleandetailVeiw(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(860,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                        border-bottom-right-radius:10px;\
                        border-bottom-left-radius:10px}");

    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0,0,0,0);

    InitWidget();

//    this->setLayout(main_layout);
}

CleandetailVeiw::~CleandetailVeiw()
{

}

void CleandetailVeiw::InitWidget()
{
    QFrame *top_widget = new QFrame(this);
    top_widget->setFixedSize(860,98);
    top_layout = new QHBoxLayout(top_widget);
    top_layout->setSpacing(0);
    top_layout->setMargin(0);
    top_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(top_widget);

    QFrame *spilterLine = new QFrame(this);
    spilterLine->setFixedSize(860, 2);
    spilterLine->setStyleSheet("QFrame{background:rgba(238,238,238,1);}");
    spilterLine->setFrameShape(QFrame::HLine);
    spilterLine->setFrameShadow(QFrame::Plain);
    main_layout->addWidget(spilterLine);

    QFrame *bottom_widget =new QFrame(this);
    bottom_widget->setFixedSize(860,360);
    bottom_layout = new QVBoxLayout(bottom_widget);
    bottom_layout->setSpacing(0);
    bottom_layout->setMargin(0);
    bottom_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(bottom_widget);

    InitTopWidget();
    InitBottomWidget();

    this->setLayout(main_layout);
}

void CleandetailVeiw::InitTopWidget()
{
    QFrame *frame = new QFrame();
    frame->setFixedSize(860,100);

    top_tip = new QLabel(frame);
    QFont font;
    font.setPixelSize(30);
    font.setBold(QFont::Bold);
    top_tip->setFont(font);
    top_tip->setText(tr("Computer scan in progress..."));
    top_tip->setGeometry(QRect(100,25,470,40));

    cancel_btn = new QPushButton(frame);
    cancel_btn->setText(tr("Cancel"));
    cancel_btn->setStyleSheet("QPushButton{width:120px;height:36px;\
                              border:2px solid rgba(153,153,153,1);\
                              border-radius:18px;font-size:18px;}\
                              QPushButton:hover{width:120px;height:36px;\
                              border:2px solid rgba(34,103,242,1);\
                              border-radius:18px;font-size:18px;}\
                              QPushButton:pressed{width:120px;height:36px;\
                              background:rgba(34,103,242,1);color:white;\
                              border-radius:18px;font-size:18px;}");
    cancel_btn->setGeometry(QRect(620,30,120,36));
//    cancel_btn->setVisible(false);
    connect(cancel_btn,SIGNAL(clicked()),this,SIGNAL(hideThisWidget()));

    onkeyclean = new QPushButton(frame);
    onkeyclean->setText(tr("Cleanup"));
    onkeyclean->setStyleSheet("QPushButton{width:160px;height:48px;\
                              background:rgba(34,103,242,1);\
                              border-radius:24px;font-size:20px;color:white;}\
                              QPushButton:hover{width:160px;height:48px;\
                              background:rgba(67,127,240,1);\
                              border-radius:24px;font-size:20px;color:white;}");
    onkeyclean->setGeometry(QRect(600,25,160,48));
    onkeyclean->setVisible(false);
    connect(onkeyclean,SIGNAL(clicked()),this,SIGNAL(startOneKeyClean()));
//    connect(onkeyclean,SIGNAL(clicked()),this,SLOT(OnClikedCleanBtn()));

    return_btn = new QPushButton(frame);
    return_btn->setText(tr("Return"));
    return_btn->setStyleSheet("QPushButton{width:160px;height:48px;\
                              background:rgba(34,103,242,1);\
                              border-radius:24px;font-size:20px;color:white;}\
                              QPushButton:hover{width:160px;height:48px;\
                              background:rgba(67,127,240,1);\
                              border-radius:24px;font-size:20px;color:white;}");
    return_btn->setGeometry(QRect(600,25,160,48));
    return_btn->setVisible(false);
    connect(return_btn,SIGNAL(clicked()),this,SIGNAL(hideThisWidget()));


    top_layout->addWidget(frame/*,1,Qt::AlignCenter*/);
}

void CleandetailVeiw::InitBottomWidget()
{
    QFrame *frame = new QFrame(this);
    QHBoxLayout *m_layout = new QHBoxLayout(frame);
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->setContentsMargins(120,65,110,150);

    QFrame *cache_frame = new QFrame(frame);
    QVBoxLayout *cache_layout = new QVBoxLayout(cache_frame);
    cache_icon = new QLabel(cache_frame);
    QPixmap icon(":/res/cache.png");
    cache_icon->setPixmap(icon);
    cache_icon->setFixedSize(icon.size());
    cache_layout->addWidget(cache_icon);

    cache_tip = new QLabel(cache_frame);
    QFont font;
    font.setPixelSize(18);
    font.setBold(QFont::Bold);
    cache_tip->setFont(font);
    cache_tip->setText(tr("System cache"));
    cache_layout->addWidget(cache_tip);

    QLabel *lable1 = new QLabel(cache_frame);
    lable1->setText(tr("Clear package、thumbnails and browser cache"));
    lable1->setWordWrap(true);
    cache_layout->addWidget(lable1);

    QFrame *cookie_frame = new QFrame(frame);
    QVBoxLayout *cookie_layout = new QVBoxLayout(cookie_frame);
    cookie_icon = new QLabel(cookie_frame);
    QPixmap icon1(":/res/cookies.png");
    cookie_icon->setPixmap(icon1);
    cookie_icon->setFixedSize(icon1.size());
    cookie_layout->addWidget(cookie_icon);

    cookie_tip = new QLabel(cookie_frame);
    cookie_tip->setFont(font);
    cookie_tip->setText(tr("Cookies"));
    cookie_layout->addWidget(cookie_tip);

    QLabel *lable2 = new QLabel(cookie_frame);
    lable2->setText(tr("Clear internet、games、shopping history, etc."));
    lable2->setWordWrap(true);
    cookie_layout->addWidget(lable2);

    QFrame *history_frame = new QFrame(frame);
    QVBoxLayout *history_layout = new QVBoxLayout(history_frame);
    history_icon = new QLabel(history_frame);
    QPixmap icon2(":/res/history.png");
    history_icon->setPixmap(icon2);
    history_icon->setFixedSize(icon2.size());
    history_layout->addWidget(history_icon);

    history_tip = new QLabel(history_frame);
    history_tip->setFont(font);
    history_tip->setText(tr("Historical trace"));
    history_layout->addWidget(history_tip);

    QLabel *lable3 = new QLabel(history_frame);
    lable3->setText(tr("Clear browser and system usage traces"));
    lable3->setWordWrap(true);
    history_layout->addWidget(lable3);

    m_layout->addWidget(history_frame);
    m_layout->addWidget(cookie_frame);
    m_layout->addWidget(cache_frame);

    bottom_layout->addWidget(frame);
}

void CleandetailVeiw::ResetUI()
{
    cache_tip->setText(tr("System cache"));
    history_tip->setText(tr("Historical trace"));
    cookie_tip->setText(tr("Cookies"));
    top_tip->setText(tr("Computer scan in progress..."));
    cancel_btn->setVisible(true);
    onkeyclean->setVisible(false);
    return_btn->setVisible(false);
}

void CleandetailVeiw::getScanResult(QString msg)
{
    qDebug() << Q_FUNC_INFO << msg;
    if(msg != ""){
          top_tip->setText(msg);
    }
}

void CleandetailVeiw::finishScanResult(QString msg)
{
    qDebug() << Q_FUNC_INFO << msg;
    if(msg == "onekey")
    {
        qDebug() << Q_FUNC_INFO <<trace << cookies << garbage;
        if(trace == "0" && cookies == "0" && garbage == "0.00 B")
        {
            top_tip->setText(tr("There's nothing to clean up."));
            cancel_btn->setVisible(false);
            onkeyclean->setVisible(false);
            return_btn->setVisible(true);
        }
        else
        {
            top_tip->setText(tr("Scan complete!"));
            cancel_btn->setVisible(false);
            onkeyclean->setVisible(true);
            return_btn->setVisible(false);
        }
    }
}

void CleandetailVeiw::getScanAllResult(QString flag, QString msg)
{
    qDebug() << Q_FUNC_INFO  <<flag << msg;
    if(flag == "h") {
        trace = msg;
        if(msg != "0")
        {
            history_tip->setText(msg+tr(" historical use traces"));
        }
        else
        {
            history_tip->setText(msg+tr(" historical use traces"));
        }
    }
    else if(flag == "k") {
        cookies = msg;
        if(msg != "0")
        {
            cookie_tip->setText(tr("Cleanable cookie ")+msg);
        }
        else {
            cookie_tip->setText(tr("Cleanable cookie ")+"0 M");
        }
    }
    else if(flag == "c") {
        garbage = msg;
        if(msg != "0")
        {
            cache_tip->setText(tr("Cleanable cache ")+msg.mid(0,msg.indexOf("."))+" M");
        }
        else
        {
            cache_tip->setText(tr("Cleanable cache ")+"0 M");
        }
    }

}

void CleandetailVeiw::OnClikedCleanBtn()
{
    top_tip->setText(tr("Computer cleanup in progress..."));
}

void CleandetailVeiw::getCleanResult(QString msg)
{
    qDebug() << Q_FUNC_INFO << msg;
//    return msg;
    if(msg == "no")
    {
        top_tip->setText(tr("Computer cleanup in progress..."));
        QMovie *movie = new QMovie(":/res/drive/clean_anime.gif");
        movie->setSpeed(200);

        cache_icon->setMovie(movie);
        cache_icon->setFixedSize(48,48);

        cookie_icon->setMovie(movie);
        cookie_icon->setFixedSize(48,48);

        history_icon->setMovie(movie);
        history_icon->setFixedSize(48,48);

        movie->start();
    }
    else if(msg == "o")
    {
        top_tip->setText(tr("Clearance completed!"));
        cancel_btn->setVisible(false);
        onkeyclean->setVisible(false);
        return_btn->setVisible(true);
    }
    else if(msg == "c")
    {
        QPixmap pixmap(":/res/drive/finish1.png");
        cache_icon->setPixmap(pixmap);
        cache_icon->setFixedSize(pixmap.size());
        cache_icon->update();
    }
    else if(msg == "k")
    {
        QPixmap pixmap(":/res/drive/finish1.png");
        cookie_icon->setPixmap(pixmap);
        cookie_icon->setFixedSize(pixmap.size());
        cookie_icon->update();
    }
    else if(msg == "h")
    {
        QPixmap pixmap(":/res/drive/finish2.png");
        history_icon->setPixmap(pixmap);
        history_icon->setFixedSize(pixmap.size());
        history_icon->update();
    }
}
