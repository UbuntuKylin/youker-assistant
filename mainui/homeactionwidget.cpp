#include "homeactionwidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDateTime>

HomeActionWidget::HomeActionWidget(QWidget *parent, QSettings *mSettings)
    : QWidget(parent), pSettings(mSettings)
{
//    this->resize(900, 227);
    this->setFixedSize(900, 227);
    is_move = false;
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");
//    this->setAttribute(Qt::WA_TranslucentBackground,true);//背景透明
//    this->setStyleSheet("background-color:transparent;");
//    QPalette palette_back;
//    palette_back.setBrush(QPalette::Background, QBrush(QPixmap(":/background/res/skin/1.png")));
//    this->setPalette(palette_back);

//    QPalette palette_back;
//    palette_back.setBrush(QPalette::Background, QBrush(QPixmap(":/background/res/bg/1.png")));
//    this->setPalette(palette_back);

    suggest_label = new QLabel();
    result_label = new QLabel();
    doing_label = new QLabel();
    scan_button = new QPushButton();
    clean_button = new QPushButton();
    back_button = new QPushButton();
    back_button->hide();

    loading_label = new LoadingLabel();
    loading_label->show();
//    movie_label->setScaledContents(true);//设置movie_label自动缩放,显示图像大小自动调整为Qlabel大小
//    QPixmap label_pixmap("");
//    movie_label->setPixmap(label_pixmap);
//    movie_label->setFixedSize(label_pixmap.size());

    suggest_label->setObjectName("whiteLabel");
    suggest_label->setWordWrap(true);//QLabel自动换行
    result_label->setWordWrap(true);//QLabel自动换行
    result_label->setObjectName("tipLabel");
    doing_label->setWordWrap(true);//QLabel自动换行
    doing_label->setObjectName("tipLabel");
    doing_label->hide();

    scan_button->setFixedSize(204, 65);
    scan_button->setFocusPolicy(Qt::NoFocus);
    QPixmap pixmap("://res/scan.png");
    scan_button->setIcon(pixmap);
    scan_button->setIconSize(pixmap.size());
    scan_button->setObjectName("greenButton");
//    QFont scan_font = scan_button->font();
//    scan_font.setPointSize(16);
//    scan_button->setFont(scan_font);
    clean_button->setFixedSize(204, 65);
    clean_button->setFocusPolicy(Qt::NoFocus);
    clean_button->setObjectName("greenButton");
    clean_button->hide();

    back_button->setFocusPolicy(Qt::NoFocus);
    back_button->setFixedSize(50, 30);
    back_button->setObjectName("backButton");
    back_button->setObjectName("underlineButton");

    //set underline
    //    QFont font = back_button->font();
    //    font.setUnderline(true);
    //    back_button->setFont(font);

    //set scan button text color
//    QPalette palette;
//    palette.setColor(QPalette::ButtonText, QColor(255,17,135));
//    scan_button->setPalette(palette);

    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addStretch();
    layout1->addWidget(suggest_label);
    layout1->addWidget(result_label);
    layout1->addWidget(doing_label);
    layout1->addStretch();
    layout1->setSpacing(15);
    layout1->setContentsMargins(0, 20, 0, 0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(loading_label, 0, Qt::AlignHCenter);
    layout2->addLayout(layout1);
    layout2->setSpacing(20);
    layout2->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout3 = new QVBoxLayout();
    layout3->addStretch();
    layout3->addWidget(scan_button, 0, Qt::AlignRight);
    layout3->addWidget(clean_button, 0, Qt::AlignRight);
    layout3->addWidget(back_button, 0, Qt::AlignRight);
    layout3->addStretch();
    layout3->setSpacing(10);
    layout3->setContentsMargins(0, 20, 0, 0);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(layout2);
    main_layout->addStretch();
    main_layout->addLayout(layout3);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(10, 30, 44, 0);

    setLayout(main_layout);


    workFlag = this->getOneKeyFlag();
    if(workFlag.length() > 0)
    {
        if(workFlag == "1")
        {
            //clean
            dateStr = this->getFixCleanDate();
            result_label->setText(tr("The lastest cleanup time is ") + dateStr);
        }
        else if(workFlag == "0")
        {
            //scan
            dateStr = this->getSafeScanDate();
            result_label->setText(tr("The lastest scan time is ") + dateStr);
        }
    }
    else {
        result_label->setText(tr("You have not implemented the one key scan and clean-up operation."));
    }

    this->initConnect();
    this->setLanguage();
}

HomeActionWidget::~HomeActionWidget()
{

}

void HomeActionWidget::initConnect()
{
    connect(scan_button, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(clean_button, SIGNAL(clicked()), this, SLOT(onCleanButtonClicked()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(onEndButtonClicked()));
}

void HomeActionWidget::setLanguage()
{
    suggest_label->setText(tr("Quick clean up system trash, saving disk space and improving the system efficiency!"));//一键清理系统垃圾，帮您节省磁盘空间，让系统运行更加有效率！
    scan_button->setText(tr("Start Scan"));//开始扫描
    clean_button->setText(tr("Start Cleanup"));//开始清理
    back_button->setText(tr("Back"));
    doing_label->setText(tr("Scanning......"));//正在扫描......
}

void HomeActionWidget::getScanResult(QString msg)
{
    doing_label->setText(tr("Scanning:") + msg);//正在扫描:
    qDebug() << msg;
}

void HomeActionWidget::finishScanResult(QString msg)
{
    if(msg == "onekey") {
        doing_label->setText(tr("Scan Over"));//扫描完成
        result_label->setText(tr("The lastest scan time is ") + this->getCurrentDateTime());
        this->writeSafeScanDate();
        scan_button->hide();
        clean_button->show();
        back_button->show();
        clean_button->setEnabled(true);
        loading_label->stopLoading();
    }
}

void HomeActionWidget::getScanAllResult(QString flag, QString msg){
    if(flag == "h") {
        trace = msg;
    }
    else if(flag == "k") {
        cookies = msg;
    }
    else if(flag == "c") {
        garbage = msg;
    }
}

void HomeActionWidget::getCleanResult(QString msg)
{
    if (msg == "yes") {//在弹出输入密码验证时，点击了取消按钮
        loading_label->stopLoading();
        clean_button->setEnabled(true);
    }
    if (msg == "no") {//在弹出输入密码验证时，输入密码，验证通过，此时让动态图片开始显示
        //show dynamic image
        doing_label->setText(tr("Cleaning......"));//正在清理......
        loading_label->startLoading();
        clean_button->setEnabled(false);
    }
    else if (msg == "c") {
        doing_label->setText(tr("Garbage Cleanup OK......"));
    }
    else if (msg == "h") {
        doing_label->setText(tr("History Cleanup OK......"));
    }
    else if (msg == "k") {
        doing_label->setText(tr("Cookies Cleanup OK......"));
    }
    else if (msg == "o") {
        this->writeFixCleanDate();
        //清理完毕后显示清理总数
        result_label->setText(tr("The lastest cleanup time is ") + this->getCurrentDateTime());
        doing_label->setText(tr("Cleanup Cookies:") +cookies + "; Garbage:" + garbage + "; Historical records:" +trace );
        trace.clear();
        cookies.clear();
        garbage.clear();
        loading_label->stopLoading();
        scan_button->show();
        scan_button->setEnabled(true);
        clean_button->hide();
        clean_button->setEnabled(true);
    }
}

void HomeActionWidget::finishCleanError(QString msg)
{
    if (msg == "ce") {
        qDebug() << "GarbageException---------";
    }
    else if (msg == "he") {
        qDebug() << "HistoryException---------";
    }
    else if (msg == "ke") {
        qDebug() << "CookiesException---------";
    }
}

void HomeActionWidget::getCleaningMessage(QString type, QString status)
{
    if(type == "firefoxhistory") {
        if(status == "start") {
            doing_label->setText(tr("Cleaning up history trace of Firefox..."));//正在清理Firefox的历史痕迹...
        }
        else if(status == "end") {
            doing_label->setText(tr("Firefox history trace had been cleared!"));//Firefox的历史痕迹已清理完毕！
        }
    }
    else if(type == "chromiumhistory") {
        if(status == "start") {
           doing_label->setText(tr("Cleaning up history trace of Chromium..."));//正在清理Chromium的历史痕迹...
        }
        else if(status == "end") {
            doing_label->setText(tr("Chromium history trace had been cleared!"));//Chromium的历史痕迹已清理完毕！
        }
    }
    else if(type == "firefoxcookies") {
        if(status == "start") {
            doing_label->setText(tr("Cleaning up Cookies of Firefox..."));//正在清理Firefox的Cookies...
        }
        else if(status == "end") {
            doing_label->setText(tr("Firefox Cookies had been cleared!"));//Firefox的Cookies已清理完毕！
        }
    }
    else if(type == "chromiumcookies") {
        if(status == "start") {
            doing_label->setText(tr("Cleaning up Cookies of Chromium..."));//正在清理Chromium的Cookies...
        }
        else if(status == "end") {
            doing_label->setText(tr("Chromium Cookies had been cleared!"));//Chromium的Cookies已清理完毕！
        }
    }
    else if(type == "apt") {
        if(status == "end") {
            doing_label->setText(tr("Apt cache had been cleared!"));//Apt缓存已清理完毕！
        }
        else {
            doing_label->setText(tr("Cleaning up Apt cache: ") + status);//正在清理Apt缓存：
        }
    }
    else if(type == "software_center") {
        if(status == "end") {
            doing_label->setText(tr("Software Center cache had been cleared!"));//软件中心缓存已清理完毕！
        }
        else {
            doing_label->setText(tr("Cleaning up Software Center cache: ") + status);//正在清理软件中心缓存：
        }
    }
}

void HomeActionWidget::onStartButtonClicked()
{
    scan_button->setEnabled(false);
    loading_label->startLoading();
    suggest_label->hide();
    result_label->hide();
    doing_label->show();
    QStringList args;
    args << "cache" << "history" << "cookies";
    sessionProxy->onekey_scan_function_qt(args);
}

void HomeActionWidget::onCleanButtonClicked()
{
    clean_button->show();
    clean_button->setEnabled(false);
    loading_label->startLoading();
    suggest_label->hide();
    result_label->hide();
    doing_label->setText(tr("Ready to Cleanup......"));//准备清理......
    doing_label->show();
    systemProxy->set_user_homedir_qt();
    systemProxy->clean_by_main_one_key_qt();
}

void HomeActionWidget::onEndButtonClicked()
{
    loading_label->stopLoading();
    scan_button->show();
    scan_button->setEnabled(true);
    clean_button->hide();
    back_button->hide();
    suggest_label->show();
    result_label->show();
    doing_label->hide();
}

void HomeActionWidget::writeFixCleanDate() {
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd"); //设置显示格式
    pSettings->beginGroup("OneKeyClean");
    pSettings->setValue("CleanDate", str);
    pSettings->setValue("Flag", "1");
    pSettings->endGroup();
    pSettings->sync();
}

QString HomeActionWidget::getFixCleanDate() {
    pSettings->beginGroup("OneKeyClean");
    QString value = pSettings->value("CleanDate").toString();
    pSettings->endGroup();
    pSettings->sync();
    return value;
}

QString HomeActionWidget::getCurrentDateTime() {
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd"); //设置显示格式
    return str;
}

void HomeActionWidget::writeSafeScanDate() {
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd"); //设置显示格式
    pSettings->beginGroup("OneKeyClean");
    pSettings->setValue("ScanDate", str);
    pSettings->setValue("Flag", "0");
    pSettings->endGroup();
    pSettings->sync();
}

QString HomeActionWidget::getSafeScanDate() {
    pSettings->beginGroup("OneKeyClean");
    QString value = pSettings->value("ScanDate").toString();
    pSettings->endGroup();
    pSettings->sync();
    return value;
}

QString HomeActionWidget::getOneKeyFlag() {
    pSettings->beginGroup("OneKeyClean");
    QString value = pSettings->value("Flag").toString();
    pSettings->endGroup();
    pSettings->sync();
    return value;
}
