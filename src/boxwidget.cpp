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

#include "boxwidget.h"
#include "../component/plugininterface.h"
#include "pluginmanager.h"

#include <QDebug>
#include <QGridLayout>
#include <QStackedLayout>
#include <QProcess>
#include <QFileInfo>

BoxWidget::BoxWidget(QWidget *parent, QString arch, QString os, QString path) :
    QWidget(parent), osarch(arch), osname(os), plugin_path(path)
//  ,m_pluginsLayout(new QStackedLayout)
//  ,m_pluginsManager(new PluginManager(this))
{
    this->setFixedSize(900, 403);
    this->setStyleSheet("QWidget{border: none;}");
    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    list_view = new QListView(this);
//    list_view = new KylinListView(this);
    list_view->setFocusPolicy(Qt::NoFocus);
    list_view->setAutoFillBackground(true);
    list_view->setIconSize(QSize(48, 48));
    list_view->setResizeMode(QListView::Adjust);
    list_view->setModel(&pluginModel);
    list_view->setViewMode(QListView::IconMode);
//    list_view->setMovement(QListView::Static);
    list_view->setSpacing(26);
//    list_view->setLineWidth(110);

    this->loadPlugins();
    this->initPluginWidget();
    connect(list_view,SIGNAL(clicked(const QModelIndex&)),this,SLOT(OnClickListView(const QModelIndex &)));


//    stacked_widget = new QStackedWidget(this);//stacked_widget will delete when InfoWidget delete
//    stacked_widget->setFocusPolicy(Qt::NoFocus);
//    stacked_widget->setAutoFillBackground(true);
//    stacked_widget->addWidget(list_view);
//    stacked_widget->addWidget(test_widget);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(list_view,0,0);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);



    /*m_pluginLayoutWidget = new QWidget;
    m_pluginLayoutWidget->setLayout(m_pluginsLayout);
    QVBoxLayout *pluginWidgetLayout = new QVBoxLayout;
    pluginWidgetLayout->addWidget(m_pluginLayoutWidget);
    pluginWidgetLayout->setSpacing(0);
    pluginWidgetLayout->setMargin(0);
    m_pluginWidget = new QWidget;
    m_pluginWidget->setLayout(pluginWidgetLayout);

    QVBoxLayout *centralLayout = new QVBoxLayout(this);
    centralLayout->addWidget(list_view);
    centralLayout->addWidget(m_pluginWidget);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    connect(m_pluginsManager, &PluginManager::pluginAdded, this, &BoxWidget::pluginAdded, Qt::QueuedConnection);
    m_pluginsManager->loadPlugin(plugin_path);*/
}

BoxWidget::~BoxWidget()
{
}

//void BoxWidget::pluginAdded(QWidget * const w)
//{
//    qDebug() << "BoxWidget::pluginAdded............";
//    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    const int idx = m_pluginsLayout->addWidget(w);
//    m_pluginsLayout->setCurrentIndex(idx);
//}


void BoxWidget::displayBoxHomePage() {
//    stacked_widget->setCurrentIndex(0);
}

void BoxWidget::displayBoxSubPage(QString plugin_id) {
//    QObject *object = QObject::sender();
//    QPushButton *btn = qobject_cast<QPushButton *>(object);
//    QString object_name = btn->statusTip();
//    if (object_name == "theme") {
//        stacked_widget->setCurrentIndex(1);
//    }
}

void BoxWidget::loadPlugins()
{
    PluginManager::Instance()->loadPlugin(plugin_path);
}

void BoxWidget::initPluginWidget()
{
    QStringList title;
    title << tr("");
    pluginModel.setTitle(title);
//    pluginModel.insertRows(0,1,QModelIndex());
//    QModelIndex qindex = pluginModel.index(0,0,QModelIndex());
//    pluginModel.setData(qindex,tr("      "));
    pluginModel.insertRows(0,1,QModelIndex());
    QModelIndex qindex = pluginModel.index(0,0,QModelIndex());

//    if(this->osarch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin") {
//        //set text
//        pluginModel.setData(qindex, tr("Kylin Software Center"));
//        //set tooltip
//        pluginModel.setData(qindex, tr("Kylin Software Center"),Qt::WhatsThisRole);
//    }
//    else {
//        //set text
//        pluginModel.setData(qindex, tr("UbuntuKylin Software Center"));
//        //set tooltip
//        pluginModel.setData(qindex, tr("UbuntuKylin Software Center"),Qt::WhatsThisRole);
//    }

    //set text
    pluginModel.setData(qindex, tr("Kylin Software Center"));
    //set tooltip
    pluginModel.setData(qindex, tr("Kylin Software Center"),Qt::WhatsThisRole);

    //set icon
    pluginModel.setData(qindex,QIcon(QPixmap("://res/ubuntukylin-software-center.png")),Qt::DecorationRole);

//    QStringList icon_list;
//    //icon_list<<"://res/boot"<<"://res/camera";
//    icon_list<<"://res/boot";
//    QStringList text_list;
//    //text_list << tr("Boot Manager") << tr("Camera");
//    text_list << tr("Boot Manager");
//    for (int index = 0;index < 1;++index)
//    {
//        pluginModel.insertRows(index + 1,1,QModelIndex());
//        qindex = pluginModel.index(index + 1,0,QModelIndex());
//        pluginModel.setData(qindex, text_list.at(index));
//        //set icon
//        pluginModel.setData(qindex,QIcon(QPixmap(icon_list.at(index))),Qt::DecorationRole);
//        //set tooltip
//        pluginModel.setData(qindex, text_list.at(index),Qt::WhatsThisRole);
//    }

    int count = PluginManager::Instance()->count();
    for (int i = 0;i < count;++i)
    {
        PluginInterface* ICommon = PluginManager::Instance()->getInterfaceByindex<PluginInterface>(i);
        QString picture = ICommon->getPicture();
        QString  pacture_path = QString(":/model/res/plugin/%1").arg(picture);
        pluginModel.setGuid(ICommon->getGuid());
//        pluginModel.insertRows(i + 1,1,QModelIndex());
//        qindex = pluginModel.index(i + 1,0,QModelIndex());
        pluginModel.insertRows(i + 1,1,QModelIndex());
        qindex = pluginModel.index(i + 1,0,QModelIndex());
        pluginModel.setData(qindex,ICommon->getName());
        pluginModel.setData(qindex,QIcon(QPixmap(pacture_path)),Qt::DecorationRole);
        pluginModel.setData(qindex,ICommon->getName(),Qt::WhatsThisRole);
    }
}

void BoxWidget::OnClickListView(const QModelIndex & index)
{
    if(index.row() == 0) {
        if (QFileInfo("/usr/bin/kylin-software-center").exists()) {
            QProcess process;
            process.start("/usr/bin/kylin-software-center");
            process.waitForStarted(1000);
            process.waitForFinished(20*1000);
        }
        else if (QFileInfo("/usr/bin/ubuntu-kylin-software-center").exists()) {
            QProcess process;
            process.start("/usr/bin/ubuntu-kylin-software-center");
            process.waitForStarted(1000);
            process.waitForFinished(20*1000);
        }
        else {
            emit this->pluginModuleError(tr("No software center was found!"));
        }
        /*if(this->osarch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin")
            sessionProxy->runApp("kylin-software-center");
        else
            sessionProxy->runApp("ubuntu-kylin-software-center");*/
    }
//    else if(index.row() == 1) {
//        emit this->sendSubIndex(0);
//    }
//    else if(index.row() == -1) {
//        if(this->osarch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin")
//            sessionProxy->runApp("cheese");
//        else
//            emit this->sendSubIndex(1);
//    }
    else {
//        QString guid = pluginModel.getGuid(index.row() - 1);
        QString guid = pluginModel.getGuid(index.row() - 1);
        PluginInterface* interface = PluginManager::Instance()->getInterfaceByGuid<PluginInterface>(guid);
        interface->doAction();
    }
}
