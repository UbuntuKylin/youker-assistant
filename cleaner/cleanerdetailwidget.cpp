#include "cleanerdetailwidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"
#include <QDebug>

CleanerDetailWidget::CleanerDetailWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(900, 403);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    colorFlag = false;
    changeFromUser = true; // 设置状态改变由用户触发
    tree_widget = new QTreeWidget();
    tree_widget->setHeaderHidden(true);

    tree_widget->setRootIsDecorated(false);
    tree_widget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    tree_widget->setRootIsDecorated( false );//去掉虚线边框
    tree_widget->setFrameStyle(QFrame::NoFrame);//去掉边框
//    tree_widget->setStyleSheet("QTreeWidget::branch {image:none;}");//去掉子节点的虚框
    root_item = tree_widget->invisibleRootItem();

    this->initTreeRoot();
    this->initConnect();

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(tree_widget);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(10, 10, 10, 10);
    setLayout(main_layout);

    this->setLanguage();
}

CleanerDetailWidget::~CleanerDetailWidget()
{
    if(tree_widget != NULL)
    {
        delete tree_widget;
        tree_widget = NULL;
    }
}

void CleanerDetailWidget::showReciveData(const QStringList &data)
{
    tree_widget->expandAll();
//    qDebug() << "detail page receive data---------" << data;
    //----------------------------------------------------------------Cache---------------------------
    if(data.at(0) == "Belong:Cache.apt" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(0, data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.software-center" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(1, data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.thumbnails" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(2, data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(3, data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(4, data.at(1).split(":").at(1));
        }
    }
    //----------------------------------------------------------------Package---------------------------
    else if(data.at(0) == "Belong:Packages.unneed" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(5, data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Packages.oldkernel" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(6, data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Packages.configfile" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            this->addSubItem(7, data.at(1).split(":").at(1));
        }
    }


    //----------------------------------------------------------------Cookies---------------------------
    else if(data.at(0) == "Belong:Cookies.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
        {
            this->addSubItem(8, data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cookies.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
        {
            this->addSubItem(9, data.at(1).split(":").at(1));
        }
    }

    //----------------------------------------------------------------History Trace---------------------------
    else if(data.at(0) == "Belong:History.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0)
                this->addSubItem(10, data.at(1));
        }
    }
    else if(data.at(0) == "Belong:History.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0)
                this->addSubItem(11, data.at(1));
        }
    }
    else if(data.at(0) == "Belong:History.system" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0)
                this->addSubItem(12, data.at(1));
        }
    }
}

void CleanerDetailWidget::setLanguage()
{
//    title_label->setText(tr("Cleaning up the system cache"));
//    description_label->setText(tr("Deep cleaning up the system cache, to save disk space"));
}

void CleanerDetailWidget::cleanSelectedItemCache()
{
    recursiveSelectedSubItems();
}

void CleanerDetailWidget::onTreeWidgetItemChanged(QTreeWidgetItem *item, int column)
{
    if(item == NULL) {
        return;
    }
//    qDebug() << item->checkState(column);
    if (column != 0)
        return;
    if (changeFromUser)
    {
        changeFromUser = false;
        changeToParent = true;
        changeParents(item, item->checkState(0));
        changeChildren(item, item->checkState(0));
        changeFromUser = true;
    }
    else
    {
        if (changeToParent)
            changeParents(item, item->checkState(0));
        else
            changeChildren(item, item->checkState(0));
    }
}

//setCheckState 触 itemChanged 信号
void CleanerDetailWidget::changeParents(QTreeWidgetItem *item, Qt::CheckState state)
{
    QTreeWidgetItem *iParent = item->parent();
    if (iParent == 0)
    {
        changeToParent = false;
        return;
    }
    else
    {
        int i;
        int k=iParent->childCount();
        for (i=0;i<k;i++)
        {
            if (iParent->child(i)->checkState(0) != state)
                break;
        }
        if (i==k)
            iParent->setCheckState(0, state);
        else
            iParent->setCheckState(0, Qt::PartiallyChecked);
    }
}

void CleanerDetailWidget::changeChildren(QTreeWidgetItem *item, Qt::CheckState state)
{
    int i;
    int k=item->childCount();
    for (i=0;i<k;i++)
    {
        item->child(i)->setCheckState(0, state);
    }
}

void CleanerDetailWidget::onTreeWidgetItemPressed(QTreeWidgetItem * item, int column )
{
////    qDebug() << item->childCount();
//   if (item->childCount () == 0) {
//       return;
//   }
}

void CleanerDetailWidget::onTreeItemDoubleClicked (QTreeWidgetItem *item, int column)
{
  QString text = item->text(column);
  qDebug() << "double clicked.....";
  qDebug() << text;
}


void CleanerDetailWidget::deleteTreeWidgetItem(QString item_text)
{
    QTreeWidgetItem *item = getItem(root_item, item_text);
    if (item)
    {
        QTreeWidgetItem* parent = item->parent();
        parent->removeChild(item);
    }
}

QTreeWidgetItem* CleanerDetailWidget::getItem(QTreeWidgetItem *cur_item ,QString item_text)
{
    QTreeWidgetItem* find_item = NULL;
    if (cur_item->data(1,0).toString() == item_text)
    {
        return cur_item;
    }
    if (cur_item->childCount() > 0)
    {
        int count = cur_item->childCount();
        for (int i = 0;i < count; ++i)
        {
            find_item = getItem(cur_item->child(i), item_text);
            if (NULL != find_item)
            {
                return find_item;
            }
        }
    }
    return NULL;
}

void CleanerDetailWidget::recursiveSelectedSubItems()
{
    /*0 = Qt::Unchecked, 1= Qt::PartiallyChecked, 2= Qt::Checked*/
    QTreeWidgetItem* parentitem = root_item->child(1);
    if(parentitem)
    {
        if(parentitem->checkState(0) == 2 || parentitem->checkState(0) == 1)
        {
            int k = parentitem->childCount();
            for (int i=0;i<k;i++)
            {
                if(parentitem->child(i)->checkState(0) == 2) {
                    qDebug() << parentitem->child(i)->text(0);
                }
            }
        }
    }
    this->deleteTreeWidgetItem("IE/QQ浏览器/360浏览器");
    this->deleteTreeWidgetItem("搜狗浏览器(sogo)");
    this->deleteTreeWidgetItem("火狐(firefox)");
    this->deleteTreeWidgetItem("谷歌(Chrome)");
}

void CleanerDetailWidget::initTreeRoot()
{
    cache_apt_root = new QTreeWidgetItem(QStringList()<<tr("包缓存"));
    cache_apt_root->setIcon(0, QIcon("://res/camera.png"));
    cache_apt_root->setCheckState(0, Qt::Checked);
    root_item->addChild(cache_apt_root);
    cache_software_root = new QTreeWidgetItem(QStringList()<<tr("软件中心缓存"));
    cache_software_root->setIcon(0, QIcon("://res/camera.png"));
    cache_software_root->setCheckState(0, Qt::Checked);
    root_item->addChild(cache_software_root);
    cache_thumbnails_root = new QTreeWidgetItem(QStringList()<<tr("缩略图缓存"));
    cache_thumbnails_root->setIcon(0, QIcon("://res/camera.png"));
    cache_thumbnails_root->setCheckState(0, Qt::Checked);
    root_item->addChild(cache_thumbnails_root);
    cache_firefox_root = new QTreeWidgetItem(QStringList()<<tr("Firefox缓存"));
    cache_firefox_root->setIcon(0, QIcon("://res/camera.png"));
    cache_firefox_root->setCheckState(0, Qt::Checked);
    root_item->addChild(cache_firefox_root);
    cache_chromium_root = new QTreeWidgetItem(QStringList()<<tr("Chromium缓存"));
    cache_chromium_root->setIcon(0, QIcon("://res/camera.png"));
    cache_chromium_root->setCheckState(0, Qt::Checked);
    root_item->addChild(cache_chromium_root);
    package_unneed_root = new QTreeWidgetItem(QStringList()<<tr("不必要的程序"));
    package_unneed_root->setIcon(0, QIcon("://res/camera.png"));
    package_unneed_root->setCheckState(0, Qt::Checked);
    root_item->addChild(package_unneed_root);
    package_oldkernel_root = new QTreeWidgetItem(QStringList()<<tr("旧内核包"));
    package_oldkernel_root->setIcon(0, QIcon("://res/camera.png"));
    package_oldkernel_root->setCheckState(0, Qt::Checked);
    root_item->addChild(package_oldkernel_root);
    package_configfile_root = new QTreeWidgetItem(QStringList()<<tr("软件配置文件"));
    package_configfile_root->setIcon(0, QIcon("://res/camera.png"));
    package_configfile_root->setCheckState(0, Qt::Checked);
    root_item->addChild(package_configfile_root);
    cookies_firefox_root = new QTreeWidgetItem(QStringList()<<tr("Firefox Cookies"));
    cookies_firefox_root->setIcon(0, QIcon("://res/camera.png"));
    cookies_firefox_root->setCheckState(0, Qt::Checked);
    root_item->addChild(cookies_firefox_root);
    cookies_chromium_root = new QTreeWidgetItem(QStringList()<<tr("Chromium Cookies"));
    cookies_chromium_root->setIcon(0, QIcon("://res/camera.png"));
    cookies_chromium_root->setCheckState(0, Qt::Checked);
    root_item->addChild(cookies_chromium_root);
    trace_firefox_root = new QTreeWidgetItem(QStringList()<<tr("Firefox上网记录"));
    trace_firefox_root->setIcon(0, QIcon("://res/camera.png"));
    trace_firefox_root->setCheckState(0, Qt::Checked);
    root_item->addChild(trace_firefox_root);
    trace_chromium_root = new QTreeWidgetItem(QStringList()<<tr("Chromium上网记录"));
    trace_chromium_root->setIcon(0, QIcon("://res/camera.png"));
    trace_chromium_root->setCheckState(0, Qt::Checked);
    root_item->addChild(trace_chromium_root);
    trace_system_root = new QTreeWidgetItem(QStringList()<<tr("最近打开文件记录"));
    trace_system_root->setIcon(0, QIcon("://res/camera.png"));
    trace_system_root->setCheckState(0, Qt::Checked);
    root_item->addChild(trace_system_root);
}

void CleanerDetailWidget::initConnect()
{
    connect(tree_widget, SIGNAL(itemClicked(QTreeWidgetItem *, int)),this, SLOT(onTreeWidgetItemChanged(QTreeWidgetItem *, int)));
    connect(tree_widget,SIGNAL(itemPressed( QTreeWidgetItem*, int)),this,SLOT(onTreeWidgetItemPressed(QTreeWidgetItem*, int)));
    connect(tree_widget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onTreeItemDoubleClicked(QTreeWidgetItem*,int)));
}

void CleanerDetailWidget::addSubItem(int rootIndex, QString content)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<content);
    item->setSelected(true);
    if(colorFlag)
    {
        item->setBackground(0,QBrush(QColor("#4f4f4f")));
    }
    else
    {
        item->setBackground(0,QBrush(QColor("#7d7d7d")));
    }
    colorFlag = !colorFlag;
    item->setIcon(0, QIcon("://res/folder.png"));
    item->setCheckState(0, Qt::Checked);
    item->setData(1,0, content); //设置该节点唯一名称
    QTreeWidgetItem* parentitem = root_item->child(rootIndex);
    if (parentitem)
    {
        parentitem->addChild(item);
    }
}
