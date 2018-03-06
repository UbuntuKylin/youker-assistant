/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#include "propertiesdialog.h"
#include "processworker.h"
#include "../widgets/mytristatebutton.h"
#include "util.h"

#include <QApplication>
#include <QDateTime>
#include <QPushButton>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QScreen>
#include <QWidget>
#include <QFileInfo>
#include <QIcon>

const int spacing = 8;

PropertiesDialog::PropertiesDialog(QWidget *parent, pid_t processId) : QDialog(parent)
  , mousePressed(false)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint/*  | Qt::WindowCloseButtonHint*/| Qt::WindowStaysOnTopHint);
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_Resized, false);
//    this->setMaximumSize(480, 600);
//    this->setMinimumWidth(320);

    this->setFixedWidth(380);

    pid = processId;

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 5);
    m_topLayout = new QHBoxLayout;
    m_topLeftLayout = new QHBoxLayout;
    m_topLeftLayout->setContentsMargins(20, 20, 0, 0);
    m_topLeftLayout->setSpacing(10);
    m_topRightLayout = new QHBoxLayout;
    m_topRightLayout->setMargin(0);
    m_topRightLayout->setSpacing(5);
    m_topLayout->addLayout(m_topLeftLayout);
    m_topLayout->addStretch();
    m_topLayout->addLayout(m_topRightLayout);

    /*userLayout = new QHBoxLayout();
    userLayout->setContentsMargins(0, 0, 0, 0);
    nameLayout = new QHBoxLayout();
    nameLayout->setContentsMargins(0, 0, 0, 0);
    cmdlineLayout = new QHBoxLayout();
    cmdlineLayout->setContentsMargins(0, 0, 0, 0);
    cpuDurationLayout = new QHBoxLayout();
    cpuDurationLayout->setContentsMargins(0, 0, 0, 0);
    startTimeLayout = new QHBoxLayout();
    startTimeLayout->setContentsMargins(0, 0, 0, 0);*/

    m_logoLabel = new QLabel();
    m_logoLabel->setStyleSheet("QLabel{background:transparent;border:none;}");
    m_logoLabel->setFixedSize(44, 58);
    m_logoLabel->setContentsMargins(0, 0, 0, 0);
    m_logoLabel->setPixmap(QPixmap(":/res/sub_logo.png"));

    closeButton = new MyTristateButton();
    closeButton->setObjectName("CloseButton");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
//    connect(closeButton, &MyTristateButton::clicked, this, [=] {
//        this->close();
//    });

    m_iconLabel = new QLabel();
    m_iconLabel->setStyleSheet("QLabel{background:transparent;border:none;}");
    m_iconLabel->setFixedSize(48, 48);
    m_iconLabel->setContentsMargins(0, 0, 0, 0);

    m_titleLabel = new QLabel();
    m_titleLabel->setStyleSheet("QLabel{background-color:transparent;font-size:18px;color:#000000;}");
    m_titleLabel->setFixedWidth(230);
    m_titleLabel->setWordWrap(true);

    m_topLeftLayout->addWidget(m_iconLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_topLeftLayout->addWidget(m_titleLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);

    m_topRightLayout->addWidget(m_logoLabel, 0, Qt::AlignTop | Qt::AlignRight);
    m_topRightLayout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);

    QLabel *topSplit = new QLabel();
    topSplit->setStyleSheet("QLabel{background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #f1f1f1, stop:1 #e0e0e0);}");
//    topSplit->setStyleSheet("QLabel{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop:0 #f1f1f1, stop:1 #e0e0e0);}");
    topSplit->setFixedSize(320, 1);

    QLabel *bottomSplit = new QLabel();
    bottomSplit->setStyleSheet("QLabel{background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #f1f1f1, stop:1 #e0e0e0);}");
//    bottomSplit->setStyleSheet("QLabel{background: qlineargradient(x1:0, y1:0, x2:1, y2:0,stop:0 #f1f1f1, stop:1 #e0e0e0);}");
    bottomSplit->setFixedSize(320, 1);

    m_infoFrame = new QFrame;
    m_infoFrame->setMaximumWidth(320);
    m_infoFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_bottomLayout = new QHBoxLayout;
    m_bottomLayout->setContentsMargins(0,0,20,0);
    m_bottomLayout->setSpacing(0);
    m_okBtn = new QPushButton;
    m_okBtn->setFixedSize(91, 25);
    m_okBtn->setObjectName("blackButton");
    m_okBtn->setFocusPolicy(Qt::NoFocus);
    m_okBtn->setText(tr("OK"));
    connect(m_okBtn, &QPushButton::clicked, this, [=] {
        this->close();
    });
    m_bottomLayout->addWidget(m_okBtn, 0, Qt::AlignBottom | Qt::AlignRight);

    m_layout->addLayout(m_topLayout);
    m_layout->addSpacing(10);
    m_layout->addWidget(topSplit, 0, Qt::AlignCenter);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_infoFrame, 0, Qt::AlignCenter);
    m_layout->addSpacing(5);
    m_layout->addWidget(bottomSplit, 0, Qt::AlignCenter);
    m_layout->addSpacing(5);
    m_layout->addLayout(m_bottomLayout);
    m_layout->addSpacing(10);
    m_layout->addStretch();

    QGridLayout *infoGrid = new QGridLayout(m_infoFrame);
    infoGrid->setMargin(0);
    infoGrid->setHorizontalSpacing(spacing);
    infoGrid->setVerticalSpacing(spacing);
    infoGrid->setColumnStretch(0, 10);
    infoGrid->setColumnStretch(1, 100);

    QStringList titleList;
    titleList << QObject::tr("User name:") << QObject::tr("Process name:") << QObject::tr("Command line:") << QObject::tr("CPU Time:") << QObject::tr("Started Time:");
    for (int i = 0; i < titleList.length(); ++i) {
        QLabel *titleLabel = new QLabel(titleList.value(i));
        titleLabel->setStyleSheet("QLabel{background-color:transparent;font-size:12px;color:#999999;}");
        titleLabel->setMinimumHeight(20);

        QLabel *infoLabel = new QLabel();
        infoLabel->setStyleSheet("QLabel{background-color:transparent;font-size:12px;color:#000000;}");
        infoLabel->setWordWrap(true);
        infoLabel->setMinimumHeight(28);
        infoLabel->setMinimumWidth(220);
        infoLabel->setMaximumWidth(240);
        infoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        infoLabel->adjustSize();
        m_labelList << infoLabel;
        infoGrid->addWidget(titleLabel);
        infoGrid->addWidget(infoLabel);
    }

    /*userTitleLabel = new QLabel(QString("%1:").arg(tr("User name")));
    userTitleLabel->setStyleSheet("QLabel { background-color : transparent; color : #666666; }");
    userTitleLabel->setFixedWidth(100);
    userTitleLabel->setAlignment(Qt::AlignRight);

    userLabel = new QLabel();
    userLabel->setStyleSheet("QLabel { background-color : transparent; color : #000000; }");

    userLayout->addWidget(userTitleLabel);
    userLayout->addWidget(userLabel);
    userLayout->addSpacing(20);

    nameTitleLabel = new QLabel(QString("%1:").arg(tr("Process name")));
    nameTitleLabel->setStyleSheet("QLabel { background-color : transparent; color : #666666; }");
    nameTitleLabel->setFixedWidth(100);
    nameTitleLabel->setAlignment(Qt::AlignRight);

    m_appNameLabel = new QLabel();
    m_appNameLabel->setStyleSheet("QLabel { background-color : transparent; color : #000000; }");

    nameLayout->addWidget(nameTitleLabel);
    nameLayout->addWidget(m_appNameLabel);
    nameLayout->addSpacing(20);

    cmdlineTitleLabel = new QLabel(QString("%1:").arg(tr("Command line")));
    cmdlineTitleLabel->setStyleSheet("QLabel { background-color : transparent; color : #666666; }");
    cmdlineTitleLabel->setFixedWidth(100);
    cmdlineTitleLabel->setAlignment(Qt::AlignRight);
//    cmdlineTitleLabel->setWordWrap(true);
//    cmdlineTitleLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    cmdlineLabel = new QLabel();
    cmdlineLabel->setStyleSheet("QLabel { background-color : transparent; color : #000000; }");
    cmdlineLabel->setWordWrap(true);
    cmdlineLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    cmdlineLayout->addWidget(cmdlineTitleLabel);
    cmdlineLayout->addWidget(cmdlineLabel);
    cmdlineLayout->addSpacing(20);

    cpuDurationTitleLabel = new QLabel(QString("%1:").arg(tr("CPU Time")));
    cpuDurationTitleLabel->setStyleSheet("QLabel { background-color : transparent; color : #666666; }");
    cpuDurationTitleLabel->setFixedWidth(100);
    cpuDurationTitleLabel->setAlignment(Qt::AlignRight);

    cpuDurationLabel = new QLabel();
    cpuDurationLabel->setStyleSheet("QLabel { background-color : transparent; color : #000000; }");
    cpuDurationLabel->setWordWrap(true);

    cpuDurationLayout->addWidget(cpuDurationTitleLabel);
    cpuDurationLayout->addWidget(cpuDurationLabel);
    cpuDurationLayout->addSpacing(20);

    startTimeTitleLabel = new QLabel(QString("%1:").arg(tr("Started Time")));
    startTimeTitleLabel->setStyleSheet("QLabel { background-color : transparent; color : #666666; }");
    startTimeTitleLabel->setFixedWidth(100);
    startTimeTitleLabel->setAlignment(Qt::AlignRight);

    startTimeLabel = new QLabel();
    startTimeLabel->setStyleSheet("QLabel { background-color : transparent; color : #000000; }");
    startTimeLabel->setWordWrap(true);

    startTimeLayout->addWidget(startTimeTitleLabel);
    startTimeLayout->addWidget(startTimeLabel);
    startTimeLayout->addSpacing(20);

    m_layout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);
    m_layout->addSpacing(20);
    m_layout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);
    m_layout->addSpacing(14);
    m_layout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    m_layout->addSpacing(20);
    m_layout->addLayout(userLayout);
    m_layout->addLayout(nameLayout);
    m_layout->addLayout(cmdlineLayout);
    m_layout->addLayout(cpuDurationLayout);
    m_layout->addLayout(startTimeLayout);
    m_layout->addSpacing(20);*/

    this->moveToCenter();

    this->initProcproperties();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(refreshProcproperties()));
    timer->start(3000);
}

PropertiesDialog::~PropertiesDialog()
{
    if (timer != NULL) {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(refreshProcproperties()));
        if(timer->isActive()) {
            timer->stop();
        }
        delete timer;
        timer = NULL;
    }

    delete closeButton;
    delete m_iconLabel;
    delete m_titleLabel;
    delete m_okBtn;

    QLayoutItem *child;
    while ((child = m_topLeftLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_topRightLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_topLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_bottomLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    m_labelList.clear();
    delete m_infoFrame;
    /*delete userTitleLabel;
    delete userLabel;
    delete nameTitleLabel;
    delete m_appNameLabel;
    delete cmdlineTitleLabel;
    delete cpuDurationLabel;
    delete cpuDurationTitleLabel;
    delete startTimeLabel;
    delete startTimeTitleLabel;
    delete cmdlineLabel;
    delete userLayout;
    delete nameLayout;
    delete cmdlineLayout;
    delete cpuDurationLayout;
    delete startTimeLayout;*/
    delete m_layout;
}

void PropertiesDialog::updateLabelFrameHeight()
{
    int labelTotalHeight = 0;
    foreach (QLabel *label, m_labelList) {
        label->adjustSize();
        labelTotalHeight += label->size().height() + spacing;
    }
    m_infoFrame->setFixedHeight(labelTotalHeight);
    m_infoFrame->adjustSize();
    this->adjustSize();
}

void PropertiesDialog::initProcproperties()
{
    ProcessWorker *info;
    info = ProcessWorker::find(pid);
    if (info) {
        QString username = QString::fromStdString(info->user);
//        long nice = info->nice;
        QString name = QString::fromStdString(info->name);
//        QString status = formatProcessState(info->status);
//        uint cpu = info->pcpu;
//        long memory = info->mem;

        std::string desktopFile;
        desktopFile = getDesktopFileAccordProcName(name, "");

        QPixmap icon_pixmap;
        int iconSize = 48 * qApp->devicePixelRatio();



        QIcon defaultExecutableIcon = QIcon::fromTheme("application-x-executable");//gnome-mine-application-x-executable
        if (defaultExecutableIcon.isNull()) {
            defaultExecutableIcon = QIcon("/usr/share/icons/kylin-icon-theme/48x48/mimetypes/application-x-executable.png");
            if (defaultExecutableIcon.isNull())
                defaultExecutableIcon = QIcon(":/res/autostart-default.png");
        }
        QPixmap defaultPixmap = defaultExecutableIcon.pixmap(iconSize, iconSize);
//        QPixmap defaultPixmap = QIcon::fromTheme("application-x-executable").pixmap(iconSize, iconSize);
        if (desktopFile.size() == 0) {
            icon_pixmap = defaultPixmap;
            icon_pixmap.setDevicePixelRatio(qApp->devicePixelRatio());
        } else {
            icon_pixmap = getAppIconFromDesktopFile(desktopFile, 48);
            if (icon_pixmap.isNull()) {
                icon_pixmap = defaultPixmap;
                icon_pixmap.setDevicePixelRatio(qApp->devicePixelRatio());
            }
            //QPixmap pixmap = QPixmap::fromImage(img).scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        QString displayName = getDisplayNameAccordProcName(name, desktopFile);
        m_iconLabel->setPixmap(icon_pixmap);
        m_titleLabel->setText(displayName);
        /*userLabel->setText(username);
        m_appNameLabel->setText(QString(info->name));
        cmdlineLabel->setText(QString(info->arguments));
        startTimeLabel->setText(QFileInfo(QString("/proc/%1").arg(pid)).created().toString("yyyy-MM-dd hh:mm:ss"));
        cpuDurationLabel->setText(formatDurationForDisplay(100 * info->cpu_time / info->frequency));*/

        QStringList valueList;
        valueList << username << QString(info->name) << QString(info->arguments)
                   << QFileInfo(QString("/proc/%1").arg(pid)).created().toString("yyyy-MM-dd hh:mm:ss")
                   << formatDurationForDisplay(100 * info->cpu_time / info->frequency);

        for (int i = 0; i < this->m_labelList.length(); ++i) {
            this->m_labelList.value(i)->setText(valueList.value(i));
        }
    }
    this->updateLabelFrameHeight();
}

void PropertiesDialog::refreshProcproperties()
{
    ProcessWorker *info;
    info = ProcessWorker::find(pid);
    if (info) {
        for (int i = 0; i < this->m_labelList.length(); ++i) {
            if (i == 3)
                this->m_labelList.value(i)->setText(QFileInfo(QString("/proc/%1").arg(pid)).created().toString("yyyy-MM-dd hh:mm:ss"));
            if (i == 4)
                this->m_labelList.value(i)->setText(formatDurationForDisplay(100 * info->cpu_time / info->frequency));
        }
        //startTimeLabel->setText(QFileInfo(QString("/proc/%1").arg(pid)).created().toString("yyyy-MM-dd hh:mm:ss"));
        //cpuDurationLabel->setText(formatDurationForDisplay(100 * info->cpu_time / info->frequency));
    }
}

pid_t PropertiesDialog::getPid()
{
    return pid;
}

QRect PropertiesDialog::getParentGeometry() const
{
    if (this->parentWidget()) {
        return this->parentWidget()->window()->geometry();
    } else {
        QPoint pos = QCursor::pos();

        for (QScreen *screen : qApp->screens()) {
            if (screen->geometry().contains(pos)) {
                return screen->geometry();
            }
        }
    }

    return qApp->primaryScreen()->geometry();
}

void PropertiesDialog::moveToCenter()
{
    QRect qr = geometry();
    qr.moveCenter(this->getParentGeometry().center());
    move(qr.topLeft());
}

void PropertiesDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }

    QDialog::mousePressEvent(event);
}

void PropertiesDialog::mouseReleaseEvent(QMouseEvent *event)
{
    this->mousePressed = false;

    QDialog::mouseReleaseEvent(event);
}

void PropertiesDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }

    QDialog::mouseMoveEvent(event);
}

void PropertiesDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制圆角矩形
    painter.setPen(QPen(QColor("#0d87ca"), 0));//边框颜色 #3f96e4
    painter.setBrush(QColor("#e9eef0"));//背景色
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(1);
    QRectF r(0 / 2.0, 0 / 2.0, width() - 0, height() - 0);//左边 上边 右边 下边
    painter.drawRoundedRect(r, 4, 4);


    //绘制背景色
//    QPainterPath path;
//    path.addRect(QRectF(rect()));
//    painter.setOpacity(1);
//    painter.fillPath(path, QColor("#ffffff"));

    QDialog::paintEvent(event);
}
