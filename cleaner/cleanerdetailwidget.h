#ifndef CLEANERDETAILWIDGET_H
#define CLEANERDETAILWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"
#include "../component/systembutton.h"
#include "../component/loadinglabel.h"
#include <QTreeWidget>
#include <QTableWidgetItem>

//class MainWindow;
class CleanerDetailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerDetailWidget(QWidget *parent = 0);
    ~CleanerDetailWidget();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage();
    void initTreeRoot();
    void initConnect();
    void addSubItem(int rootIndex, QString content);
    QTreeWidgetItem* getItem(QTreeWidgetItem *cur_item, QString item_text);
    void deleteTreeWidgetItem(QString item_text);
    void recursiveSelectedSubItems();

public slots:
    void cleanSelectedItemCache();
    void onTreeWidgetItemChanged(QTreeWidgetItem* item, int column);
    void onTreeWidgetItemPressed(QTreeWidgetItem * item, int column );
    void onTreeItemDoubleClicked (QTreeWidgetItem * item, int column);
    void showReciveData(const QStringList &data);


private:
    QTreeWidget *tree_widget;
    QTreeWidgetItem*  root_item;
    bool changeFromUser; // true：这个状态变化是由用户触发的；false：由程序调用 setCheckState 函数触发的
    bool changeToParent; // 某个节点 checkState 变化后，同步更新其它节点的方向，true：向父节点方向；false：向子节点方向
    void changeParents(QTreeWidgetItem *item, Qt::CheckState state); //朝父节点方向刷新 CheckState
    void changeChildren(QTreeWidgetItem *item, Qt::CheckState state); //朝子节点方向刷新 CheckState
//    QLabel *img_label;
//    QLabel *title_label;
//    QLabel *description_label;

//    MainWindow *p_mainwindow;
    QTreeWidgetItem *cache_apt_root;
    QTreeWidgetItem *cache_software_root;
    QTreeWidgetItem *cache_thumbnails_root;
    QTreeWidgetItem *cache_firefox_root;
    QTreeWidgetItem *cache_chromium_root;
    QTreeWidgetItem *package_unneed_root;
    QTreeWidgetItem *package_oldkernel_root;
    QTreeWidgetItem *package_configfile_root;
    QTreeWidgetItem *cookies_firefox_root;
    QTreeWidgetItem *cookies_chromium_root;
    QTreeWidgetItem *trace_firefox_root;
    QTreeWidgetItem *trace_chromium_root;
    QTreeWidgetItem *trace_system_root;

    bool colorFlag;
};

#endif // CLEANERDETAILWIDGET_H




