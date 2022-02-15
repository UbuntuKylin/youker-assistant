/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "commondef.h"
#include "dataworker.h"

#include <unistd.h>
#include <QDebug>
#include <QProcess>
#include <QApplication>
#include <QStyleOption>
#include <QPainterPath>
#include <QPainter>
#include <QPluginLoader>
#include <interface.h>
#include <QTimer>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QMouseEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    this->setMouseTracking(true);
    this->setWindowTitle(tr("ToolKit"));
    //this->setWindowIcon(QIcon::fromTheme("kylin-assistant"));
    this->setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    this->installEventFilter(this);
    initOpacityGSettings();
    initUI();
    initConnections();
}

MainWindow::~MainWindow()
{
    if (m_gsTransOpacity) {
        delete m_gsTransOpacity;
        m_gsTransOpacity = nullptr;
    }
    //DataWorker::getInstance()->exitDaemonDbus();
}

void MainWindow::handleMessage(const QString &msg)
{
    qDebug() << Q_FUNC_INFO << msg;
    this->hide();
    this->show();
    this->showNormal();
}

void MainWindow::initUI()
{
    // 初始化布局
    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);

    // 加载插件
    loadPlugins();

    // 初始控件
    initLeftSideBar();
    initRightPanel();

    this->setLayout(m_mainLayout);
    int nDefautPage = 0;
    QTimer::singleShot(0, this, [&,this,nDefautPage](){
        this->switchPage(nDefautPage);
    });
}

void MainWindow::initOpacityGSettings()
{
    const QByteArray idtrans(THEME_QT_TRANS);
    if(QGSettings::isSchemaInstalled(idtrans)) {
        m_gsTransOpacity = new QGSettings(idtrans);
    }

    if (!m_gsTransOpacity) {
        m_curTransOpacity = 1;
        return;
    }

    connect(m_gsTransOpacity, &QGSettings::changed, this, [=](const QString &key) {
        if (key == "transparency") {
            QStringList keys = m_gsTransOpacity->keys();
            if (keys.contains("transparency")) {
                m_curTransOpacity = m_gsTransOpacity->get("transparency").toString().toDouble();
                repaint();
            }
        }
    });

    QStringList keys = m_gsTransOpacity->keys();
    if(keys.contains("transparency")) {
        m_curTransOpacity = m_gsTransOpacity->get("transparency").toString().toDouble();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainterPath path;

    QPainter painter(this);
    painter.setOpacity(m_curTransOpacity);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setClipping(true);
    painter.setPen(Qt::transparent);

    path.addRect(this->rect());
    path.setFillRule(Qt::WindingFill);
    painter.setBrush(this->palette().base());
    painter.setPen(Qt::transparent);

    painter.drawPath(path);
    QWidget::paintEvent(event);
}

void MainWindow::initConnections()
{
    connect(m_leftWidget, SIGNAL(switchPage(int)), this, SLOT(onSwitchPage(int)));
    connect(m_rightWidget, SIGNAL(maximizeWindow()), this, SLOT(onMaximizeWindow()));
    connect(m_rightWidget, SIGNAL(minimizeWindow()), this, SLOT(onMinimizeWindow()));
}

void MainWindow::onSwitchPage(int nIndex)
{
    qDebug()<<"SwitchPage:"<<nIndex;
    switchPage(nIndex);
}

void MainWindow::onMinimizeWindow()
{
    this->showMinimized();
}

void MainWindow::onMaximizeWindow()
{
    if (this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}

void MainWindow::loadPlugins()
{
    for (int index = 0; index < FUNCTYPE_MAX; index++){
        QObject *plugin = nullptr;
        m_pluginsList.append(plugin);
    }
    static bool installed = (QCoreApplication::applicationDirPath() == QDir(("/usr/bin")).canonicalPath());

    if (installed)
        m_pluginsDir = QDir(PLUGIN_INSTALL_DIRS);
    else {
        m_pluginsDir = QDir(qApp->applicationDirPath() + "/plugins");
    }

    foreach (QString fileName, m_pluginsDir.entryList(QDir::Files)) {
        if (!fileName.endsWith(".so"))
            continue;

        qDebug() << "Scan Plugin: " << fileName;
        QPluginLoader loader(m_pluginsDir.absoluteFilePath(fileName));
        QObject * plugin = loader.instance();
        if (plugin) {
            PluginInterface * pluginInstance = qobject_cast<PluginInterface *>(plugin);
            m_pluginsList[pluginInstance->getPluginType()] = plugin;
            QTimer::singleShot(100, this, [&,pluginInstance](){
                pluginInstance->pluginDelayControl();
            });
            qDebug() << "Load Plugin :" << pluginInstance->getPluginType() << "->" << pluginInstance->getPluginName();
        } else {
            //如果加载错误且文件后缀为so，输出错误
            if (fileName.endsWith(".so"))
                qWarning() << fileName << "Load Failed: " << loader.errorString() << "\n";
        }
    }
}

void MainWindow::initLeftSideBar()
{
    // 初始化左侧列表
    m_leftWidget = new KLeftWidget(this);
    for (int n = 0; n < m_pluginsList.size(); n++) {
        if (m_pluginsList[n] != nullptr) {
            PluginInterface *pluginInstance = qobject_cast<PluginInterface *>(m_pluginsList[n]);
            m_leftWidget->addItems(pluginInstance->getPluginName(), pluginInstance->getPluginName(),
                                   QString(":/imgres/img_res/%1.svg").arg(pluginInstance->name()));
        }
    }
    m_mainLayout->addWidget(m_leftWidget, 1, Qt::AlignLeft);
}

void MainWindow::initRightPanel()
{
    //初始化右侧窗口
    m_rightWidget = new KRightWidget(this);
    for (int n = 0; n < m_pluginsList.size(); n++) {
        if (m_pluginsList[n] != nullptr) {
            PluginInterface *pluginInstance = qobject_cast<PluginInterface *>(m_pluginsList[n]);
            m_rightWidget->addPanel(pluginInstance->getPluginMainWnd(), pluginInstance->getPluginName(),
                                    QString(":/imgres/img_res/%1.svg").arg(pluginInstance->name()));
        }
    }
    m_mainLayout->addWidget(m_rightWidget, 0, Qt::AlignRight);
}

int MainWindow::panelIndex2ListIndex(int nPanelIndex)
{
    int nListIndex = -1;
    for (int n = 0; n < m_pluginsList.size(); n++) {
        if (m_pluginsList[n] != nullptr) {
            nListIndex ++;
            if (nListIndex == nPanelIndex)
                return n;
        }
    }
    return -1;
}

void MainWindow::switchPage(int nIndex)
{
    if (nIndex < 0)
        return;
    if (m_leftWidget->currentIndex() != nIndex)
        m_leftWidget->onSwichPanel(nIndex);
    if (m_rightWidget->currentIndex() != nIndex) {
        int nListIndex = panelIndex2ListIndex(nIndex);
        if (nListIndex >= 0 && nListIndex < m_pluginsList.size()) {
            PluginInterface *pluginInstance = qobject_cast<PluginInterface *>(m_pluginsList[nListIndex]);
            pluginInstance->updatePluginContent();
        }
        m_rightWidget->onSwichPanel(nIndex);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QFrame::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }

    QFrame::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }

    QFrame::mouseMoveEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if (event->key() == Qt::Key_F1){
        QString serviceName = KYLIN_USER_GUIDE_SERVICE + QString("%1%2").arg("_").arg(QString::number(getuid()));

        QDBusInterface *  iface = new QDBusInterface(serviceName,
                                                         KYLIN_USER_GUIDE_PATH,
                                                         KYLIN_USER_GUIDE_INTERFACE,
                                                         QDBusConnection::sessionBus(),
                                                         this);
        QDBusMessage msg = iface->call(QString("showGuide"), "toolkit");

        delete iface;
    }
}
