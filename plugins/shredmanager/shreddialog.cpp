/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "shreddialog.h"


//ShredDialog::ShredDialog(ShredManager *plugin, QDialog *parent)
//    :QDialog(parent)
ShredDialog::ShredDialog(QWidget *parent) :
    QWidget(parent)
    , mousePressed(false)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid

    this->setWindowTitle(tr("Kylin Shred Manager"));
    this->setWindowIcon(QIcon(":/model/res/plugin/shredder.png"));

    this->setFixedSize(500, 471);
//    process_plugin = plugin;

//    shredSettings = new QSettings(KYLIN_COMPANY_SETTING, KYLIN_SETTING_FILE_NAME_SETTING);
//    shredSettings->setIniCodec("UTF-8");

//    title_bar = new KylinTitleBar();
//    initTitleBar();
    title_bar = new MyTitleBar(tr("Shred Manager"), false, this);
    title_bar->setFixedSize(this->width()-20, TITLE_BAR_HEIGHT);

    toolkits = new Toolkits(0, this->width(), this->height());

    select_edit = new QLineEdit();
    select_edit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");
    select_edit->setFixedWidth(400);
    select_edit->setReadOnly(true);
    select_btn = new KylinEditButton(select_edit);
    shred_btn = new QPushButton();
    cacel_btn = new QPushButton();
    shred_btn->setFixedSize(91, 25);
    shred_btn->setObjectName("blackButton");
    shred_btn->setFocusPolicy(Qt::NoFocus);
    cacel_btn->setFixedSize(91, 25);
    cacel_btn->setObjectName("blackButton");
    cacel_btn->setFocusPolicy(Qt::NoFocus);

    tipLabel = new QLabel();
    tipLabel->setFixedSize(400,34);
    tipLabel->setStyleSheet("color:#BFBFBF;font-size:12px");
    tipLabel->setWordWrap(true);
    tipLabel->setIndent(5);
    tipLabel->setAlignment(Qt::AlignCenter);

    barLabel = new QLabel();
    barLabel->setFixedSize(90,20);
    barLabel->setStyleSheet("color:#595959;font-size:14px");
    barLabel->setAlignment(Qt::AlignCenter);

    progressbar = new QProgressBar();
    progressbar->setOrientation(Qt::Horizontal);
    progressbar->setFixedSize(250,40);
    progressbar->setValue(100);
    progressbar->setMinimum(0);
    progressbar->setMaximum(100);
    progressbar->setFormat(QString::fromLocal8Bit("Shattering..."));
    progressbar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    connect(&myTimer,&QTimer::timeout,this,&ShredDialog::progressbarFlash);
    myTimer.setInterval(5);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addStretch();
    layout1->addWidget(select_edit);
    layout1->addStretch();

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addStretch();
    layout2->addWidget(shred_btn);
    layout2->addWidget(cacel_btn);
    layout2->addStretch();
    layout2->setMargin(0);

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addStretch();
    layout3->addWidget(tipLabel);
    layout3->addStretch();

    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->addStretch();
    layout4->addWidget(barLabel);
    layout4->addWidget(progressbar);
    layout4->addStretch();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();
    layout->addLayout(layout4);
    layout->addLayout(layout1);
    layout->addLayout(layout3);
    layout->addLayout(layout2);
    layout->addStretch();
    layout->setSpacing(10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(layout);
    main_layout->setSpacing(20);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(10, 10, 0, 0);
    setLayout(main_layout);

    progressbar->setVisible(false);
    barLabel->setVisible(false);

    this->setLanguage();
    this->initConnect();

    this->moveCenter();
}

ShredDialog::~ShredDialog()
{
//    if (shredSettings != NULL)
//    {
//        shredSettings->sync();
//        delete shredSettings;
//        shredSettings = NULL;
//    }
}

void ShredDialog::setLanguage()
{
    select_edit->setText(tr("No select any file which need to be shredded"));
    shred_btn->setText(tr("Shred File"));
    cacel_btn->setText(tr("Deselect"));
    tipLabel->setText(tr("Note: The file shredding process cannot be cancelled, please operate with caution!"));
    barLabel->setText(tr("Shattering..."));
}

void ShredDialog::initConnect()
{
    connect(select_btn, SIGNAL(clicked()), this, SLOT(onSelectButtonClicked()));
    connect(shred_btn, SIGNAL(clicked()), this, SLOT(onShredButtonClicked()));
    connect(cacel_btn, SIGNAL(clicked()), this, SLOT(onCacelButtonClicked()));
//    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
    connect(title_bar,SIGNAL(closeSignal()), this, SLOT(onCloseButtonClicked()));
}

void ShredDialog::onCloseButtonClicked()
{
    this->close();
}

void ShredDialog::progressbarFlash()
{
    if(i == 100){
        progressbar->setInvertedAppearance(!(progressbar->invertedAppearance()));
        i = 0;
        progressbar->setValue(i);
    }else{
        progressbar->setValue(i);
        i++;
    }
}

//void ShredDialog::onMinButtonClicked()
//{
//    this->showMinimized();
////    this->hide();
//}

//QString ShredDialog::getCurrrentSkinName()
//{
//    shredSettings->beginGroup("Background");
//    QString skin = shredSettings->value("Path").toString();
//    if(skin.isEmpty()) {
//        skin = ":/background/res/skin/1.png";
//    }
//    else {
//        QStringList skinlist;
//        QString path = "/var/lib/kylin-assistant-daemon/default/";
//        QDir picdir(path);
//        picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//        picdir.setSorting(QDir::Size | QDir::Reversed);
//        QStringList filters;
//        filters << "*.jpg" << "*.png";
//        picdir.setNameFilters(filters);
//        QFileInfoList list = picdir.entryInfoList();
//        if(list.size() < 1) {
//            skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
//        }
//        else {
//            for (int j = 0; j < list.size(); ++j) {
//                QFileInfo fileInfo = list.at(j);
//                skinlist << path + fileInfo.fileName();
//            }
//            skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
//        }

//        QList<QString>::Iterator it = skinlist.begin(), itend = skinlist.end();
//        bool flag = false;
//        for(;it != itend; it++)
//        {
//            if(*it == skin) {
//                flag = true;
//                break;
//            }
//        }
//        if (flag == false) {
//            skin = skinlist.at(0);
//        }
//    }
//    shredSettings->endGroup();
//    shredSettings->sync();
//    return skin;
//}

//void ShredDialog::initTitleBar()
//{
//    QString skin = this->getCurrrentSkinName();
//    title_bar->setTitleWidth(500);
//    title_bar->setTitleName(tr("Shred Manager"));
////    title_bar->setTitleBackgound(":/background/res/skin/1.png");
//    title_bar->setTitleBackgound(skin);
//}

//void ShredDialog::resetSkin()
//{
//    QString skin = this->getCurrrentSkinName();
//    title_bar->resetBackground(skin);
//}

//void ShredDialog::onSelecteComboActivated(int index)
//{
//}

void ShredDialog::onSelectButtonClicked()
{
    QString fileName=QFileDialog::getOpenFileName(0, tr("Select file"), QDir::homePath(), tr("All Files(*)"));
    select_edit->setText(fileName);

    /*QStringList fileNameList;
    QString fileName;
    QFileDialog* fd = new QFileDialog(this);
//    fd->setStyleSheet("QFileDialog{background-color:blue;}");
    fd->resize(500, 471);
//    fd->setFilter(tr("Allfile(*)"));
    fd->setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
//    fd->setFilter( "Allfile(*.*);;mp3file(*.mp3);;wmafile(*.wma);;wavefile(*.wav)");
    fd->setViewMode(QFileDialog::List);//设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted)
    {
        fileNameList = fd->selectedFiles();
        fileName = fileNameList[0];
        select_edit->setText(fileName);
    }
    else
        fd->close();*/
}

void ShredDialog::onShredButtonClicked()
{
    if(select_edit->text().length() == 0 || !select_edit->text().contains("/"))
    {
        toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Select file!"));
    }
    else
    {
        myTimer.start();
        cacel_btn->setVisible(false);
        shred_btn->setDisabled(true);
        progressbar->setValue(0);
        progressbar->setVisible(true);
        barLabel->setVisible(true);

        char* ch;
        QByteArray ba = select_edit->text().toUtf8();
        ch=ba.data();

        myThread = new ShredQThread(ch);
        thread = new QThread();
        myThread->moveToThread(thread);
        connect(myThread,&ShredQThread::success,this, [=] {
            cacel_btn->setVisible(true);
            shred_btn->setDisabled(false);
            progressbar->setVisible(false);
            barLabel->setVisible(false);
            toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Shred successfully!"));
            select_edit->setText(tr("No select any file which need to be shredded"));           
            thread->exit();
            myTimer.stop();
        });

        connect(myThread,&ShredQThread::failed,this, [=] {
            cacel_btn->setVisible(true);
            shred_btn->setDisabled(false);
            progressbar->setVisible(false);
            barLabel->setVisible(false);
            toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Shred failed!"));
            thread->exit();
            myTimer.stop();
        });

        connect(thread,&QThread::started,myThread,&ShredQThread::run);

        connect(thread, &QThread::finished, this, [=] {
            thread->deleteLater();
            qDebug() << "ShredQThread thread finished......";
        });

        thread->start();
//        int result = do_file(ch);
//        if (result == 0)
//        {
//            //success
//            toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Shred successfully!"));
//            select_edit->setText(tr("No select any file which need to be shredded"));
//        }
//        else
//        {
//            //failed
//            toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Shred failed!"));
//        }
    }
}

void ShredDialog::onCacelButtonClicked()
{
    select_edit->setText(tr("No select any file which need to be shredded"));
}

void ShredDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
//  emit SignalClose();
}

void ShredDialog::moveCenter()
{
    QPoint pos = QCursor::pos();
    QRect primaryGeometry;
    for (QScreen *screen : qApp->screens()) {
        if (screen->geometry().contains(pos)) {
            primaryGeometry = screen->geometry();
        }
    }

    if (primaryGeometry.isEmpty()) {
        primaryGeometry = qApp->primaryScreen()->geometry();
    }

    this->move(primaryGeometry.x() + (primaryGeometry.width() - this->width())/2,
               primaryGeometry.y() + (primaryGeometry.height() - this->height())/2);
}

void ShredDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void ShredDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void ShredDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundRect(10,10,this->width()-20,this->height()-20,5,5);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillPath(path,QBrush(Qt::white));
    QColor color(0,0,0,50);
    for(int i = 0 ; i < 10 ; ++i)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundRect(10-i,10-i,this->width()-(10-i)*2,this->height()-(10-i)*2,5,5);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }

    QWidget::paintEvent(event);
}

void ShredDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }

    QWidget::mouseMoveEvent(event);
}
