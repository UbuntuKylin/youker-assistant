#include "cleandetailveiw.h"
#include "../component/selectcategorywidget.h"
#include "../component/selectwidget.h"
#include <QDebug>
#include "../component/utils.h"

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
    top_tip->setStyleSheet("color:rgb(0,0,0,185)");
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
    connect(onkeyclean,&QPushButton::clicked,this,[=]{
//        emit this->startOneKeyClean();
        receiveCleanSignal();
    });

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

    btn_return = new QPushButton(frame);
    btn_return->setText(tr("Return"));
    btn_return->setGeometry(QRect(240,30,88,36));
    btn_return->setStyleSheet("QPushButton{width:88px;height:36px;\
                              background:rgba(231,231,231,1);\
                              border-radius:18px;font-size:14px;color:black;}\
                              QPushButton:hover{width:88px;height:36px;\
                              background:rgba(67,127,240,1);\
                              border-radius:18px;font-size:14px;color:white;}");
    btn_return->setVisible(false);
    connect(btn_return,SIGNAL(clicked()),this,SIGNAL(hideThisWidget()));

    top_layout->addWidget(frame/*,1,Qt::AlignCenter*/);
}

void CleandetailVeiw::InitBottomWidget()
{
    QFrame *frame = new QFrame(this);
    QHBoxLayout *m_layout = new QHBoxLayout(frame);
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->setContentsMargins(120,65,110,125);

    QFrame *cache_frame = new QFrame(frame);
    QVBoxLayout *cache_layout = new QVBoxLayout(cache_frame);
    cache_icon = new QLabel(cache_frame);
    QPixmap icon(":/res/cache.png");
    cache_icon->setPixmap(icon);
    cache_icon->setFixedSize(icon.size());
    cache_layout->addWidget(cache_icon);

    cache_tip = new QLabel(cache_frame);
    cache_tip->setStyleSheet("color:rgb(0,0,0,185)");
    QFont font;
    font.setPixelSize(18);
//    font.setBold(QFont::Bold);
    cache_tip->setFont(font);
    cache_tip->setText(tr("System cache"));
    cache_layout->addWidget(cache_tip);

    QLabel *lable1 = new QLabel(cache_frame);
    lable1->setStyleSheet("color:rgb(0,0,0,165)");
    lable1->setText(tr("Clear package、thumbnails and browser cache"));
    lable1->setWordWrap(true);
    cache_layout->addWidget(lable1);

    cache_btn = new QPushButton(cache_frame);
    cache_btn->setObjectName("Cache");
    cache_btn->setText(tr("Details"));
    cache_btn->setFixedSize(80,36);
    cache_btn->setStyleSheet("QPushButton{width:80px;height:36px;\
                             background:rgba(231,231,231,1);\
                             border-radius:18px;font-size:14px;color:rgba(50,97,247,1);}\
                             QPushButton:hover{width:80px;height:36px;\
                             background:rgba(67,127,240,1);\
                             border-radius:18px;font-size:14px;color:white;}");
    cache_layout->addStretch(1);
    cache_layout->addWidget(cache_btn);
    cache_btn->setVisible(false);

    connect(cache_btn,SIGNAL(clicked()),this,SLOT(ShowDetailsPage()));

    QFrame *cookie_frame = new QFrame(frame);
    QVBoxLayout *cookie_layout = new QVBoxLayout(cookie_frame);
    cookie_icon = new QLabel(cookie_frame);
    QPixmap icon1(":/res/cookies.png");
    cookie_icon->setPixmap(icon1);
    cookie_icon->setFixedSize(icon1.size());
    cookie_layout->addWidget(cookie_icon);

    cookie_tip = new QLabel(cookie_frame);
    cookie_tip->setStyleSheet("color:rgb(0,0,0,185)");
    cookie_tip->setFont(font);
    cookie_tip->setText(tr("Cookies"));
    cookie_layout->addWidget(cookie_tip);

    QLabel *lable2 = new QLabel(cookie_frame);
    lable2->setStyleSheet("color:rgb(0,0,0,165)");
//    lable2->setText(tr("Clear internet、games、shopping history, etc."));
    lable2->setText(tr("Clear internet、games、shopping history, etc."));
    lable2->setWordWrap(true);
    cookie_layout->addWidget(lable2);

    cookie_btn = new QPushButton(cookie_frame);
    cookie_btn->setObjectName("Cookie");
    cookie_btn->setText(tr("Details"));
    cookie_btn->setFixedSize(80,36);
    cookie_btn->setStyleSheet("QPushButton{width:80px;height:36px;\
                             background:rgba(231,231,231,1);\
                             border-radius:18px;font-size:14px;color:rgba(50,97,247,1);}\
                             QPushButton:hover{width:80px;height:36px;\
                             background:rgba(67,127,240,1);\
                             border-radius:18px;font-size:14px;color:white;}");
    cookie_layout->addStretch(1);
    cookie_layout->addWidget(cookie_btn);
    cookie_btn->setVisible(false);

    connect(cookie_btn,SIGNAL(clicked()),this,SLOT(ShowDetailsPage()));

    QFrame *history_frame = new QFrame(frame);
    QVBoxLayout *history_layout = new QVBoxLayout(history_frame);
    history_icon = new QLabel(history_frame);
    QPixmap icon2(":/res/history.png");
    history_icon->setPixmap(icon2);
    history_icon->setFixedSize(icon2.size());
    history_layout->addWidget(history_icon);

    history_tip = new QLabel(history_frame);
    history_tip->setStyleSheet("color:rgb(0,0,0,185)");
    history_tip->setFont(font);
    history_tip->setText(tr("Historical trace"));
    history_layout->addWidget(history_tip);

    QLabel *lable3 = new QLabel(history_frame);
    lable3->setStyleSheet("color:rgb(0,0,0,165)");
    lable3->setText(tr("Clear browser and system usage traces"));
    lable3->setWordWrap(true);
    history_layout->addWidget(lable3);

//    history_btn = new QPushButton(history_frame);
//    history_btn->setObjectName("History");
//    history_btn->setText(tr("Details"));
//    history_btn->setFixedSize(80,36);
//    history_btn->setStyleSheet("QPushButton{width:80px;height:36px;\
//                             background:rgba(231,231,231,1);\
//                             border-radius:18px;font-size:14px;color:rgba(50,97,247,1);}\
//                             QPushButton:hover{width:80px;height:36px;\
//                             background:rgba(67,127,240,1);\
//                             border-radius:18px;font-size:14px;color:white;}");
//    history_layout->addWidget(history_btn);
//    history_btn->setVisible(false);
//    connect(history_btn,SIGNAL(clicked()),this,SLOT(ShowDetailsPage()));
    history_layout->addStretch(1);

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
    btn_return->setVisible(false);
    cache_btn->setVisible(false);
//    history_btn->setVisible(false);
    cookie_btn->setVisible(false);

    QPixmap icon(":/res/cache.png");
    cache_icon->setPixmap(icon);
    cache_icon->setFixedSize(icon.size());

    QPixmap icon1(":/res/cookies.png");
    cookie_icon->setPixmap(icon1);
    cookie_icon->setFixedSize(icon1.size());

    QPixmap icon2(":/res/history.png");
    history_icon->setPixmap(icon2);
    history_icon->setFixedSize(icon2.size());

    cache_apt_list.clear();
    cache_sum = 0;
    history_sum = 0;
    cookie_sum = 0;
}

void CleandetailVeiw::getScanResult(QString msg)
{
//    qDebug() << Q_FUNC_INFO << msg;
//    if(msg != ""){
//          top_tip->setText(msg);
//    }
}

void CleandetailVeiw::finishScanResult(QString msg)
{
//    qDebug() << Q_FUNC_INFO << msg;
//    if(msg == "onekey")
//    {
//        qDebug() << Q_FUNC_INFO <<trace << cookies << garbage;
//        if(trace == "0" && cookies == "0" && garbage == "0.00 B")
//        {
//            top_tip->setText(tr("There's nothing to clean up."));
//            cancel_btn->setVisible(false);
//            onkeyclean->setVisible(false);
//            return_btn->setVisible(true);
//        }
//        else
//        {
//            top_tip->setText(tr("Scan complete!"));
//            cancel_btn->setVisible(false);
//            onkeyclean->setVisible(true);
//            return_btn->setVisible(false);
//            btn_return->setVisible(true);
//        }
//    }
}

void CleandetailVeiw::getScanAllResult(QString flag, QString msg)
{
//    qDebug() << Q_FUNC_INFO  <<flag << msg;
//    if(flag == "h") {
//        trace = msg;
//        if(msg != "0")
//        {
//            history_tip->setText(msg+tr(" historical use traces"));
//            history_btn->setVisible(true);
//        }
//        else
//        {
//            history_tip->setText(msg+tr(" historical use traces"));
//            history_btn->setVisible(false);
//        }
//    }
//    else if(flag == "k") {
//        cookies = msg;
//        if(msg != "0")
//        {
//            cookie_tip->setText(tr("Cleanable cookie ")+msg);
//            cookie_btn->setVisible(true);
//        }
//        else {
//            cookie_tip->setText(tr("Cleanable cookie ")+"0 M");
//            cookie_btn->setVisible(false);
//        }
//    }
//    else if(flag == "c") {
//        garbage = msg;
//        if(msg != "0.00 B")
//        {
//            cache_tip->setText(tr("Cleanable cache ")+msg.mid(0,msg.indexOf("."))+" M");
//            cache_btn->setVisible(true);
//        }
//        else
//        {
//            cache_tip->setText(tr("Cleanable cache ")+"0 M");
//            cache_btn->setVisible(false);
//        }
//    }

}

void CleandetailVeiw::OnClikedCleanBtn()
{
    top_tip->setText(tr("Computer cleanup in progress..."));
}

void CleandetailVeiw::showReciveData(const QStringList &data)
{
    //----------------------------------------------------------------Cache---------------------------
    qDebug() << Q_FUNC_INFO << "+" << data;
    if(data.at(0).split(".").at(0) == "Belong:Cache" && !data.at(1).isEmpty())
    {
        top_tip->setText(data.at(1).split(":").at(1));

        QStringList r = data.at(3).split(":").at(1).split(" ");
        qDebug() << Q_FUNC_INFO << "+" << r << cache_sum << r.at(0).toFloat()*1024;
        if(QString::compare(r.at(1),"MB") == 0 )
            cache_sum += r.at(0).toFloat()*1024;
        else
            cache_sum += r.at(0).toFloat();

        if(data.at(0) == "Belong:Cache.apt" && !data.at(1).isEmpty())
        {
            if(data.at(1).contains(":"))
            {
                cache_apt_list.append(data.at(1).split(":").at(1));
            }
        }
        else if(data.at(0) == "Belong:Cache.software-center" && !data.at(1).isEmpty())
        {
            if(data.at(1).contains(":"))
            {
                cache_software_list.append(data.at(1).split(":").at(1));
            }
        }
        else if(data.at(0) == "Belong:Cache.thumbnails" && !data.at(1).isEmpty())
        {
            if(data.at(1).contains(":"))
            {
                cache_thumbnails_list.append(data.at(1).split(":").at(1));
            }
        }
        else if(data.at(0) == "Belong:Cache.firefox" && !data.at(1).isEmpty())
        {
            if(data.at(1).contains(":"))
            {
                cache_firefox_list.append(data.at(1).split(":").at(1));
            }
        }
        else if(data.at(0) == "Belong:Cache.chromium" && !data.at(1).isEmpty())
        {
            if(data.at(1).contains(":"))
            {
                cache_chromium_list.append(data.at(1).split(":").at(1));
            }
        }
    }
    else
    {
        if(data.at(0).split(".").at(0) == "Belong:Cookies" && !data.at(1).isEmpty())
        {
            if(data.at(0) == "Belong:Cookies.firefox" && !data.at(1).isEmpty())
            {
                if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
                {
                    cookies_firefox_list.append(data.at(1).split(":").at(1));
                }
            }
            else if(data.at(0) == "Belong:Cookies.chromium" && !data.at(1).isEmpty())
            {
                if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
                {
                    cookies_chromium_list.append(data.at(1).split(":").at(1));
                }
            }
        }
        //----------------------------------------------------------------History Trace---------------------------
        else if(data.at(0).split(".").at(0) == "Belong:History" && !data.at(1).isEmpty())
        {
             QString r = data.at(1).split(":").at(1);

             history_sum += r.toInt();

            if(data.at(0) == "Belong:History.firefox" && !data.at(1).isEmpty())
            {
                if(data.at(1).contains(":"))
                {
                    if(data.at(1).split(":").at(1).toInt() != 0) {
                        trace_firefox_count = data.at(1).split(":").at(1);
                    }
                }
            }
            else if(data.at(0) == "Belong:History.chromium" && !data.at(1).isEmpty())
            {
                if(data.at(1).contains(":"))
                {
                    if(data.at(1).split(":").at(1).toInt() != 0) {
                        trace_chromium_count = data.at(1).split(":").at(1);
                    }
                }
            }
            else if(data.at(0) == "Belong:History.system" && !data.at(1).isEmpty())
            {
                if(data.at(1).contains(":"))
                {
                    if(data.at(1).split(":").at(1).toInt() != 0) {
                        trace_system_count = data.at(1).split(":").at(1);
                    }
                }
            }
            else if(data.at(0) == "Belong:History.bash" && !data.at(1).isEmpty() && !data.at(2).isEmpty())
            {
                if(data.at(1).contains(":"))
                {
                    trace_bash_size= data.at(1).split(":").at(1);
                    trace_bash_path= data.at(2).split(":").at(1);
                }
        //        qDebug() << "bash------------";
        //        qDebug() << data.at(1);//"Size:55.67 KB"
        //        qDebug() << data.at(2);/"Path:/home/kobe/.bash_history"
            }
            else if(data.at(0) == "Belong:History.X11")// && !data.at(1).isEmpty() && !data.at(2).isEmpty()
            {
        //        qDebug() << "x11------------";
        //        qDebug() << data.at(1);//Path:/home/kobe/.xsession-errors
        //        qDebug() << data.at(2);//Type:file
        //        qDebug() << data.at(3);//Size:0.98 KB
                if(data.at(1).contains(":"))
                {
                    trace_x11_list.append(data.at(1).split(":").at(1));
                }
            }
        }
    }
}

void CleandetailVeiw::showReciveStatus(const QString &status)
{
    qDebug() << Q_FUNC_INFO << status;

    if(status == "Complete:History") {
        history_tip->setText(QString::number(history_sum)+tr(" historical use traces"));
//        if(history_sum != 0)
//            history_btn->setVisible(true);
//        else
//            history_btn->setVisible(false);
    }
    else if(status == "Complete:Cookies") {
        cookie_tip->setText(tr("Cleanable cookie ")+QString::number(cookie_sum)+tr(" items"));
        if(cookie_sum != 0)
            cookie_btn->setVisible(true);
        else
            cookie_btn->setVisible(false);
    }
    else if(status == "Complete:Cache") {
        if(cache_sum < 1024)
            cache_tip->setText(tr("Cleanable cache ")+QString::number(cache_sum)+" KB");
        else
            cache_tip->setText(tr("Cleanable cache ")+QString::number(cache_sum/1024,'f',1)+" M");

        if(cache_sum != 0)
            cache_btn->setVisible(true);
        else
            cache_btn->setVisible(false);
    }
    else if(status == "Complete:All"){
        if(cache_sum == 0 && cookie_sum == 0 && history_sum == 0){
            top_tip->setText(tr("There's nothing to clean up."));
            cancel_btn->setVisible(false);
            onkeyclean->setVisible(false);
            return_btn->setVisible(true);
        }
        else{
            top_tip->setText(tr("Scan complete!"));
            cancel_btn->setVisible(false);
            onkeyclean->setVisible(true);
            return_btn->setVisible(false);
            btn_return->setVisible(true);
        }

        m_selectedAptList = cache_apt_list+cache_software_list+cache_thumbnails_list;
    }
}

void CleandetailVeiw::getCleanResult(QString msg)
{
//    qDebug() << Q_FUNC_INFO << msg;
//    return msg;
//    if(msg == "no")
//    {
//        top_tip->setText(tr("Computer cleanup in progress..."));
//        QMovie *movie = new QMovie(":/res/drive/clean_anime.gif");
//        movie->setSpeed(200);

//        cache_icon->setMovie(movie);
//        cache_icon->setFixedSize(48,48);

//        cookie_icon->setMovie(movie);
//        cookie_icon->setFixedSize(48,48);

//        history_icon->setMovie(movie);
//        history_icon->setFixedSize(48,48);

//        movie->start();

//        cache_btn->setVisible(false);
//        cookie_btn->setVisible(false);
//        history_btn->setVisible(false);
//        btn_return->setVisible(false);
//    }
//    else if(msg == "o")
//    {
//        top_tip->setText(tr("Clearance completed!"));
//        cancel_btn->setVisible(false);
//        onkeyclean->setVisible(false);
//        return_btn->setVisible(true);
//    }
//    else if(msg == "c")
//    {
//        QPixmap pixmap(":/res/drive/finish1.png");
//        cache_icon->setPixmap(pixmap);
//        cache_icon->setFixedSize(pixmap.size());
//        cache_icon->update();
//    }
//    else if(msg == "k")
//    {
//        QPixmap pixmap(":/res/drive/finish1.png");
//        cookie_icon->setPixmap(pixmap);
//        cookie_icon->setFixedSize(pixmap.size());
//        cookie_icon->update();
//    }
//    else if(msg == "h")
//    {
//        QPixmap pixmap(":/res/drive/finish2.png");
//        history_icon->setPixmap(pixmap);
//        history_icon->setFixedSize(pixmap.size());
//        history_icon->update();
//    }
}

void CleandetailVeiw::ShowDetailsPage()
{
//    qDebug() << Q_FUNC_INFO << __LINE__ << "------------" <<cache_apt_list;
    QObject *object = QObject::sender();
    QPushButton *button = qobject_cast<QPushButton *>(object);
    QString btn_name = button->objectName();

    if(QString::compare(btn_name,"Cache") == 0)
    {
        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheApt, tr("Cleanable Cache"));
        w->loadData(tr("Cleanable Cache"), m_selectedAptList);
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    else if(QString::compare(btn_name,"Cookie") == 0){
        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheApt, tr("Cleanable Cookie"));
        w->loadData(tr("Cleanable Cookie"), cookies_chromium_list);
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
//    else if(QString::compare(btn_name,"History") == 0){
//        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheApt, tr("Cleanable History"));
//        w->loadData(tr("Cleanable History"), );
//        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
//        w->exec();
//        delete w;
//    }
}

void CleandetailVeiw::showCleanerData(const QStringList &data)
{
    qDebug() << Q_FUNC_INFO << data;
}

void CleandetailVeiw::showCleanerStatus(const QString &status, const QString &domain)
{
    qDebug() << Q_FUNC_INFO << status << domain;
    if(status == "Complete:file" && domain == "cache") {
        history_tip->setText(tr("Clear ") + QString::number(history_sum)+" historical traces");

        QPixmap pixmap(":/res/drive/finish1.png");
        cache_icon->setPixmap(pixmap);
        cache_icon->setFixedSize(pixmap.size());
        cache_icon->update();
    }
    else if(status == "Complete:cookie" && domain == "cookie") {
        cookie_tip->setText(tr("Clear cookie ")+QString::number(cookie_sum)+tr(" items"));

        QPixmap pixmap(":/res/drive/finish1.png");
        cookie_icon->setPixmap(pixmap);
        cookie_icon->setFixedSize(pixmap.size());
        cookie_icon->update();
    }
    else if(status == "Complete:history" && domain == "history") {
        cache_tip->setText(tr("Clear cache ")+QString::number(cache_sum/1024,'f',0)+" M");

        QPixmap pixmap(":/res/drive/finish2.png");
        history_icon->setPixmap(pixmap);
        history_icon->setFixedSize(pixmap.size());
        history_icon->update();
    }
}

void CleandetailVeiw::showCleanerError(const QString &status)
{

}

void CleandetailVeiw::onRefreshSelectedItems(CleanerModuleID id, const QStringList &infos)
{
//    qDebug() <<"======================"<< Q_FUNC_INFO << infos;

    switch (id) {
    case CleanerModuleID::CacheApt:
        m_selectedAptList.clear();
        m_selectedAptList = infos;
        break;
    case CleanerModuleID::CacheSoftware:
        m_selectedSoftwareList.clear();
        m_selectedSoftwareList = infos;
        break;
    case CleanerModuleID::CacheThumbnail:
        m_selectedThumbnailsList.clear();
        m_selectedThumbnailsList = infos;
        break;
    case CleanerModuleID::CacheFirefox:
        m_selectedFirefoxCacheList.clear();
        m_selectedFirefoxCacheList = infos;
        break;
    case CleanerModuleID::CacheChromium:
        m_selectedChromiumCacheList.clear();
        m_selectedChromiumCacheList = infos;
        break;
    case CleanerModuleID::CookieFirefox:
        m_selectedFirefoxCookieList.clear();
        m_selectedFirefoxCookieList = infos;
        break;
    case CleanerModuleID::CookieChromium:
        m_selectedChromiumCookieList.clear();
        m_selectedChromiumCookieList = infos;
        break;
    case CleanerModuleID::TraceX11:
        m_selectedTraceX11List.clear();
        m_selectedTraceX11List = infos;
        break;
    default:
        break;
    }
}

void CleandetailVeiw::receiveCleanSignal()
{
    this->getAllSelectedItems();
    if(argsData.empty()) {
        qDebug() << Q_FUNC_INFO << "no argsData";
    }
    else {
        emit this->startCleanSystem(argsData);
    }
}

void CleandetailVeiw::receivePolicyKitSignal(bool status)
{
    qDebug() << Q_FUNC_INFO << status;
    if(status){
        top_tip->setText(tr("Computer cleanup in progress..."));
        QMovie *movie = new QMovie(":/res/drive/clean_anime.gif");
        movie->setSpeed(200);

        cache_icon->setMovie(movie);
        cache_icon->setFixedSize(48,48);

        cookie_icon->setMovie(movie);
        cookie_icon->setFixedSize(48,48);

        history_icon->setMovie(movie);
        history_icon->setFixedSize(48,48);

//        timerUpDate(true);
        cache_tip->setText(tr("Cleaning up......"));
        history_tip->setText(tr("Cleaning up......"));
        cookie_tip->setText(tr("Cleaning up......"));

        movie->start();

        cache_btn->setVisible(false);
        cookie_btn->setVisible(false);
//        history_btn->setVisible(false);
        btn_return->setVisible(false);
    }
}

void CleandetailVeiw::showCleanOverStatus()
{
    qDebug() << Q_FUNC_INFO ;
    top_tip->setText(tr("Clearance completed!"));
    cancel_btn->setVisible(false);
    onkeyclean->setVisible(false);
    return_btn->setVisible(true);
}

void CleandetailVeiw::getAllSelectedItems()
{
    argsData.clear();
    QStringList fileTmp;
//    QStringList packageTmp;
//    QStringList firefoxcookieTmp;
//    QStringList chromiumcookieTmp;
//    QStringList traceTmp;

    qDebug() << Q_FUNC_INFO << m_selectedAptList;

    foreach (QString info, m_selectedAptList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedSoftwareList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedThumbnailsList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedFirefoxCacheList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedChromiumCacheList) {
        fileTmp.append(info);
    }

    if (trace_firefox_count > 0) {
        argsData.insert("firefox-history", QStringList() << trace_firefox_count);
    }
    else if (trace_chromium_count > 0) {
        argsData.insert("chromium-history", QStringList() << trace_chromium_count);
    }
    else if (trace_system_count > 0 ) {
        argsData.insert("system-history", QStringList() << trace_system_count);
    }
    else if (trace_bash_path > 0 ) {
        argsData.insert("bash-history", QStringList() << trace_bash_path);
    }

    if(fileTmp.length() > 0)
        argsData.insert("file", fileTmp);
    if(m_selectedFirefoxCookieList.length() > 0)
        argsData.insert("firefox-cookie", m_selectedFirefoxCookieList);
    if(m_selectedChromiumCookieList.length() > 0)
        argsData.insert("chromium-cookie", m_selectedChromiumCookieList);
    if(m_selectedTraceX11List.length() > 0)
        argsData.insert("x11-history", m_selectedTraceX11List);
}

void CleandetailVeiw::timerUpDate(bool t)
{
    QTimer *timer = new QTimer(this);
    timer->setInterval(250);
    connect(timer,&QTimer::timeout,[=]{
        for(int i = 0; i <= 3 ; i++ ){
            this->animationForTip(i);
        }
    });

    if(t){
        timer->start();
    }
    else{
        timer->stop();
    }
}

void CleandetailVeiw::animationForTip(int f)
{
    switch (f) {
    case 0:
        cache_tip->setText(tr("Cleaning up"));
        history_tip->setText(tr("Cleaning up"));
        cookie_tip->setText(tr("Cleaning up"));
        break;
    case 1:
        cache_tip->setText(tr("Cleaning up.."));
        history_tip->setText(tr("Cleaning up.."));
        cookie_tip->setText(tr("Cleaning up.."));
        break;
    case 2:
        cache_tip->setText(tr("Cleaning up...."));
        history_tip->setText(tr("Cleaning up...."));
        cookie_tip->setText(tr("Cleaning up...."));
        break;
    case 3:
        cache_tip->setText(tr("Cleaning up......"));
        history_tip->setText(tr("Cleaning up......"));
        cookie_tip->setText(tr("Cleaning up......"));
        break;
    default:
        break;
    }
}
