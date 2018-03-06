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

#include "systemmonitor.h"

#include "util.h"
#include <QFileSystemWatcher>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QFile>
#include <QHBoxLayout>
#include <QApplication>
#include <QScreen>
#include <QGraphicsDropShadowEffect>

SystemMonitor::SystemMonitor(QWidget *parent)
    : QFrame(parent)
    , mousePressed(false)
{
//    this->setStyleSheet("QFrame{border: 1px solid #121212;border-radius:1px;background-color:#1f1f1f;}");
//    this->setAttribute(Qt::WA_DeleteOnClose);
//    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint  | Qt::WindowCloseButtonHint);//去掉边框
//    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid

    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
//    installEventFilter(this);

    this->setWindowTitle(tr("Kylin System Monitor"));
    this->setWindowIcon(QIcon(":/model/res/plugin/processmanager.png"));

    this->resize(900, 600);
    setMinimumSize(640, 480);

    proSettings = new QSettings(KYLIN_COMPANY_SETTING, KYLIN_SETTING_FILE_NAME_SETTING);
    proSettings->setIniCodec("UTF-8");

    this->initTitleWidget();
    this->initPanelStack();
    this->initConnections();

    //边框阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(5);
    shadow_effect->setColor(QColor(0, 0, 0, 127));
    shadow_effect->setOffset(2, 4);
    this->setGraphicsEffect(shadow_effect);

    this->moveCenter();
}

SystemMonitor::~SystemMonitor()
{
    if (m_sysMonitorStack) {
        foreach (QObject *child, m_sysMonitorStack->children()) {
            QWidget *widget = static_cast<QWidget *>(child);
            widget->deleteLater();
        }
        delete m_sysMonitorStack;
    }
    if (m_titleWidget) {
        delete m_titleWidget;
        m_titleWidget = nullptr;
    }
    if (process_dialog) {
        delete process_dialog;
        process_dialog = nullptr;
    }
    if (resources_dialog) {
        delete resources_dialog;
        resources_dialog = nullptr;
    }
    if (filesystem_dialog) {
        delete filesystem_dialog;
        filesystem_dialog = nullptr;
    }
    if (proSettings != NULL) {
        delete proSettings;
        proSettings = NULL;
    }
}

void SystemMonitor::resizeEvent(QResizeEvent *e)
{
    if (m_titleWidget) {
        m_titleWidget->resize(width() - 2, MONITOR_TITLE_WIDGET_HEIGHT);
        if (e->oldSize()  != e->size()) {
//            emit m_titleWidget->updateMaxBtn();
            m_titleWidget->onUpdateMaxBtnStatusChanged();
        }
    }
    if (m_sysMonitorStack) {
        m_sysMonitorStack->resize(width() - 2, this->height() - MONITOR_TITLE_WIDGET_HEIGHT - 2);
        m_sysMonitorStack->move(1, MONITOR_TITLE_WIDGET_HEIGHT + 1);
    }
}

void SystemMonitor::recordProcessVisibleColumn(int, bool, QList<bool> columnVisible)
{
    QList<QString> m_visibleColumns;
    m_visibleColumns << "name";

    if (columnVisible[1]) {
        m_visibleColumns << "user";
    }

    if (columnVisible[2]) {
        m_visibleColumns << "status";
    }

    if (columnVisible[3]) {
        m_visibleColumns << "cpu";
    }

    if (columnVisible[4]) {
        m_visibleColumns << "pid";
    }

    if (columnVisible[5]) {
        m_visibleColumns << "command";
    }

    if (columnVisible[6]) {
        m_visibleColumns << "memory";
    }

    if (columnVisible[7]) {
        m_visibleColumns << "priority";
    }

    QString displayedColumns = "";
    for (int i = 0; i < m_visibleColumns.length(); i++) {
        if (i != m_visibleColumns.length() - 1) {
            displayedColumns += QString("%1,").arg(m_visibleColumns[i]);
        } else {
            displayedColumns += m_visibleColumns[i];
        }
    }

    proSettings->beginGroup("PROCESS");
    proSettings->setValue("DisplayedColumns", displayedColumns);
    proSettings->endGroup();
    proSettings->sync();
}

void SystemMonitor::recordSortStatus(int index, bool isSort)
{
    QList<QString> columnNames = { "name", "user", "status", "cpu", "pid", "command", "memory", "priority"};

    proSettings->beginGroup("PROCESS");
    proSettings->setValue("CurrentSortColumn", columnNames[index]);
    proSettings->setValue("IsSort", isSort);
    proSettings->endGroup();
    proSettings->sync();
}

void SystemMonitor::recordFileSysVisibleColumn(int, bool, QList<bool> columnVisible)
{
    QList<QString> m_visibleColumns;
    m_visibleColumns << "device";

    if (columnVisible[1]) {
        m_visibleColumns << "directory";
    }

    if (columnVisible[2]) {
        m_visibleColumns << "type";
    }

    if (columnVisible[3]) {
        m_visibleColumns << "total";
    }

    if (columnVisible[4]) {
        m_visibleColumns << "free";
    }

    if (columnVisible[5]) {
        m_visibleColumns << "available";
    }

    if (columnVisible[6]) {
        m_visibleColumns << "used";
    }

    QString displayedColumns = "";
    for (int i = 0; i < m_visibleColumns.length(); i++) {
        if (i != m_visibleColumns.length() - 1) {
            displayedColumns += QString("%1,").arg(m_visibleColumns[i]);
        } else {
            displayedColumns += m_visibleColumns[i];
        }
    }

    proSettings->beginGroup("FileSystem");
    proSettings->setValue("DisplayedColumns", displayedColumns);
    proSettings->endGroup();
    proSettings->sync();
}

void SystemMonitor::initPanelStack()
{
    m_sysMonitorStack = new QStackedWidget(this);
    m_sysMonitorStack->setStyleSheet("QStackedWidget{background: rgb(255, 255, 255);}");
    m_sysMonitorStack->setObjectName("SystemMonitorStack");
    m_sysMonitorStack->resize(width() - 2, this->height() - TITLE_WIDGET_HEIGHT);
    m_sysMonitorStack->move(1, TITLE_WIDGET_HEIGHT);

    m_sysMonitorStack->setMouseTracking(false);
    m_sysMonitorStack->installEventFilter(this);

    process_dialog = new ProcessDialog(getReadyDisplayProcessColumns(), getCurrentSortColumnIndex(), isSortOrNot(), proSettings);
    process_dialog->getProcessView()->installEventFilter(this);
    connect(process_dialog, &ProcessDialog::changeColumnVisible, this, &SystemMonitor::recordProcessVisibleColumn);
    connect(process_dialog, &ProcessDialog::changeSortStatus, this, &SystemMonitor::recordSortStatus);

    resources_dialog = new ResouresDialog;

    filesystem_dialog = new FileSystemDialog(getReadyDisplayFileSysColumns(), proSettings);
    filesystem_dialog->getFileSysView()->installEventFilter(this);
    connect(filesystem_dialog, SIGNAL(changeColumnVisible(int,bool,QList<bool>)), this, SLOT(recordFileSysVisibleColumn(int,bool,QList<bool>)));

    m_sysMonitorStack->addWidget(process_dialog);
    m_sysMonitorStack->addWidget(resources_dialog);
    m_sysMonitorStack->addWidget(filesystem_dialog);
    m_sysMonitorStack->setCurrentWidget(process_dialog);
}

void SystemMonitor::initTitleWidget()
{
    m_titleWidget = new MonitorTitleWidget(proSettings, this);
    m_titleWidget->resize(width() - 2, MONITOR_TITLE_WIDGET_HEIGHT);
    m_titleWidget->move(1, 1);
}

void SystemMonitor::initConnections()
{
    connect(m_titleWidget, SIGNAL(changePage(int)), this, SLOT(onChangePage(int)));
    connect(m_titleWidget, SIGNAL(canelSearchEditFocus()), process_dialog, SLOT(focusProcessView()));
    connect(m_titleWidget, SIGNAL(searchSignal(QString)), process_dialog, SLOT(onSearch(QString)), Qt::QueuedConnection);
}

void SystemMonitor::onChangePage(int index)
{
    if (m_sysMonitorStack) {
        m_sysMonitorStack->setCurrentIndex(index);
        if (index == 1) {
            //start time
            resources_dialog->startCpuTimer();
        }
        else {
            //stop time
            resources_dialog->stopCpuTimer();
        }
    }
}

int SystemMonitor::getCurrentSortColumnIndex()
{
    proSettings->beginGroup("PROCESS");
    QString currentSortColumn = proSettings->value("CurrentSortColumn").toString();
    proSettings->endGroup();

    QList<QString> columnNames = {"name", "user", "status", "cpu", "pid", "command", "memory", "priority"};

    return columnNames.indexOf(currentSortColumn);
}

bool SystemMonitor::isSortOrNot()
{
    proSettings->beginGroup("PROCESS");
    bool value = proSettings->value("IsSort", true).toBool();
    proSettings->endGroup();

    return value;
}

QList<bool> SystemMonitor::getReadyDisplayProcessColumns()
{
    proSettings->beginGroup("PROCESS");
    QString displayedColumns = proSettings->value("DisplayedColumns", "name,user,status,cpu,pid,command,memory,priority").toString();
    proSettings->endGroup();

    if (displayedColumns.isEmpty()) {
        proSettings->beginGroup("PROCESS");
        displayedColumns = "name,user,status,cpu,pid,command,memory,priority";
        proSettings->setValue("DisplayedColumns", displayedColumns);
        proSettings->endGroup();
        proSettings->sync();
    }

    QList<bool> m_shows;
    m_shows << displayedColumns.contains("name");
    m_shows << displayedColumns.contains("user");
    m_shows << displayedColumns.contains("status");
    m_shows << displayedColumns.contains("cpu");
    m_shows << displayedColumns.contains("pid");
    m_shows << displayedColumns.contains("command");
    m_shows << displayedColumns.contains("memory");
    m_shows << displayedColumns.contains("priority");

    return m_shows;
}

QList<bool> SystemMonitor::getReadyDisplayFileSysColumns()
{
    proSettings->beginGroup("FileSystem");
    QString displayedColumns = proSettings->value("DisplayedColumns", "device,directory,type,total,free,available,used").toString();
    proSettings->endGroup();

    if (displayedColumns.isEmpty()) {
        proSettings->beginGroup("FileSystem");
        displayedColumns = "device,directory,type,total,free,available,used";
        proSettings->setValue("DisplayedColumns", displayedColumns);
        proSettings->endGroup();
        proSettings->sync();
    }

    QList<bool> m_shows;
    m_shows << displayedColumns.contains("device");
    m_shows << displayedColumns.contains("directory");
    m_shows << displayedColumns.contains("type");
    m_shows << displayedColumns.contains("total");
    m_shows << displayedColumns.contains("free");
    m_shows << displayedColumns.contains("available");
    m_shows << displayedColumns.contains("used");

    return m_shows;
}

void SystemMonitor::moveCenter()
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

void SystemMonitor::closeEvent(QCloseEvent *event)
{
    event->accept();
}

/*void SystemMonitor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //绘制背景色
//    QPainterPath path;
//    path.addRect(QRectF(rect()));
//    painter.setOpacity(1);
//    painter.fillPath(path, QColor("#FFFFFF"));


    painter.setPen(QPen(QColor("#0d87ca"), 0));//边框颜色 #3f96e4
    painter.setBrush(QColor("#e9eef0"));//背景色
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(1);
    QRectF r(0 / 2.0, 0 / 2.0, width() - 0, height() - 0);//左边 上边 右边 下边
    painter.drawRoundedRect(r, 4, 4);

    QFrame::paintEvent(event);
}*/

void SystemMonitor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QFrame::mousePressEvent(event);
}

void SystemMonitor::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }

    QFrame::mouseReleaseEvent(event);
}

void SystemMonitor::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }

    QFrame::mouseMoveEvent(event);
}
