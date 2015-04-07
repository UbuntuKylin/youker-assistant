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

#include <QStringList>
#include <QCloseEvent>
#include <QBitmap>
#include <QPainter>
#include "processmanager.h"
#include <QFileDialog>
#include <QDir>
#include <QProcess>

ProcessDialog::ProcessDialog(ProcessManager *plugin, QDialog *parent)
:QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog{border: 1px solid gray;border-radius:2px}");//设定边框宽度以及颜色
    this->setWindowIcon(QIcon(":/res/youker-assistant.png"));
    title_bar = new KylinTitleBar();
    initTitleBar();

    this->setFixedSize(850, 476);
    process_plugin = plugin;

    toolkits = new Toolkits(0, this->width(), this->height());
    tip_label = new QLabel();
    kill_btn = new QPushButton();
    kill_btn->setFixedSize(91, 25);
    kill_btn->setObjectName("blackButton");
    kill_btn->setFocusPolicy(Qt::NoFocus);
    tableWidget = new QTableWidget();
    tableWidget->setStyleSheet("QTableWidget{border: none}");

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(tip_label);
    h_layout->addStretch();
    h_layout->addWidget(kill_btn);
    h_layout->setMargin(0);
    h_layout->setContentsMargins(10, 2, 10, 0);

    QVBoxLayout *v_layout  = new QVBoxLayout();
    v_layout->addWidget(tableWidget);
    v_layout->setContentsMargins(10, 0, 10, 10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(h_layout);
    main_layout->addLayout(v_layout);
    main_layout->setSpacing(20);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);

    app = new ProcApp();
    selected_pid = "";
    this->refresh_prolist();
    timer=new QTimer(this);
    timer->start(3000);

    this->setLanguage();
    this->initConnect();
}

ProcessDialog::~ProcessDialog()
{
    if (app) {
        delete app;
    }
    disconnect(timer,SIGNAL(timeout()),this,SLOT(refresh_prolist()));
    if(timer->isActive()) {
        timer->stop();
    }
}

void ProcessDialog::setLanguage()
{
    this->setWindowTitle(tr("Process Manager"));
    tip_label->setText(tr("Help you learn more about the program running on the system."));
    kill_btn->setText(tr("Kill Process"));
}

void ProcessDialog::initConnect()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(refresh_prolist()));
    connect(tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(handlercellClicked(int,int)));
    connect(kill_btn, SIGNAL(clicked()), this, SLOT(killSelectedProcess()));
//    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void ProcessDialog::onCloseButtonClicked()
{
    this->close();
}

//void ProcessDialog::onMinButtonClicked()
//{
//    this->showMinimized();
////    this->hide();
//}

void ProcessDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
//  emit SignalClose();
}

void ProcessDialog::initTitleBar()
{
    title_bar->setTitleWidth(850);
    title_bar->setTitleName(tr("Process Manager"));
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}

void ProcessDialog::showProList() {
    tableWidget->clearContents();//只清除表中数据，不清除表头内容
    tableWidget->setRowCount(0);//连行也清除掉

    int num = filelist_length(app->filelist);
//    printf("num=%s\n",g_strdup_printf("%d", num));

    tableWidget->setColumnCount(COLUMN_NUM);
    tableWidget->setRowCount(num);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setMouseTracking(true);
    tableWidget->setSelectionMode(QTableWidget::SingleSelection);
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->horizontalHeader()->setHighlightSections(false);
    tableWidget->setShowGrid(false);
    QStringList headers;
    headers << "命令行" << "用户" << "ID" << "优先级" << "状态" << "% 内存" << "% CPU" << "CPU时间" << "开始于";//<< "等候频道";
    tableWidget->setHorizontalHeaderLabels(headers);
    QTableWidgetItem *columnHeaderItem0 = tableWidget->horizontalHeaderItem(0); //获得水平方向表头的Item对象
    QTableWidgetItem *columnHeaderItem1 = tableWidget->horizontalHeaderItem(1);
    QTableWidgetItem *columnHeaderItem2 = tableWidget->horizontalHeaderItem(2);
    QTableWidgetItem *columnHeaderItem3 = tableWidget->horizontalHeaderItem(3);
    QTableWidgetItem *columnHeaderItem4 = tableWidget->horizontalHeaderItem(4);
    QTableWidgetItem *columnHeaderItem5 = tableWidget->horizontalHeaderItem(5);
    QTableWidgetItem *columnHeaderItem6 = tableWidget->horizontalHeaderItem(6);
    QTableWidgetItem *columnHeaderItem7 = tableWidget->horizontalHeaderItem(7);
    QTableWidgetItem *columnHeaderItem8 = tableWidget->horizontalHeaderItem(8);
    columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
    columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
    columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色
    columnHeaderItem1->setFont(QFont("Helvetica"));
    columnHeaderItem1->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem1->setTextColor(QColor(200,111,30));
    columnHeaderItem2->setFont(QFont("Helvetica"));
    columnHeaderItem2->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem2->setTextColor(QColor(200,111,30));
    columnHeaderItem3->setFont(QFont("Helvetica"));
    columnHeaderItem3->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem3->setTextColor(QColor(200,111,30));
    columnHeaderItem4->setFont(QFont("Helvetica"));
    columnHeaderItem4->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem4->setTextColor(QColor(200,111,30));
    columnHeaderItem5->setFont(QFont("Helvetica"));
    columnHeaderItem5->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem5->setTextColor(QColor(200,111,30));
    columnHeaderItem6->setFont(QFont("Helvetica"));
    columnHeaderItem6->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem6->setTextColor(QColor(200,111,30));
    columnHeaderItem7->setFont(QFont("Helvetica"));
    columnHeaderItem7->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem7->setTextColor(QColor(200,111,30));
    columnHeaderItem8->setFont(QFont("Helvetica"));
    columnHeaderItem8->setBackgroundColor(QColor(0,60,10));
    columnHeaderItem8->setTextColor(QColor(200,111,30));

    //表头设置
    tableWidget->horizontalHeader()->setClickable(false);
    tableWidget->horizontalHeader()->resizeSection(0,150);
    tableWidget->horizontalHeader()->resizeSection(1,80);
    tableWidget->horizontalHeader()->resizeSection(2,50);
    tableWidget->horizontalHeader()->resizeSection(3,80);
    tableWidget->horizontalHeader()->resizeSection(4,80);
    tableWidget->horizontalHeader()->resizeSection(5,60);
    tableWidget->horizontalHeader()->resizeSection(6,80);
    tableWidget->horizontalHeader()->resizeSection(7,80);
    tableWidget->horizontalHeader()->setFixedHeight(25);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    int index = 0;
    char * checkpath = NULL;
    for( ; index<num ; index++) {
        checkpath = filelist_index(app->filelist, index);
        QString pro_line = QString::fromLocal8Bit(checkpath);
        QStringList tmp = pro_line.split(";");
        if(tmp.length() == COLUMN_NUM) {
            if(selected_pid ==  tmp[2]) {
//                tableWidget->selectRow(index);//set current selected row
                tableWidget->setCurrentCell(index, QItemSelectionModel::Select);
            }
            if(index == 0 && selected_pid == "") {
                tableWidget->selectRow(0);//set current selected row
                selected_pid = tmp[2];
            }
            for(int i=0;i<COLUMN_NUM;i++) {
                if (i == 0 || i == 8) {
                    tableWidget->setItem(index, i, new QTableWidgetItem(tmp[i]));
                }
                else {
                    QTableWidgetItem *newItem = new QTableWidgetItem(tmp[i]);
                    newItem->setTextAlignment(Qt::AlignCenter);
                    tableWidget->setItem(index,i,newItem);
                }
            }
        }
    }

    tableWidget->setFocus(Qt::MouseFocusReason);
    filelist_destroy(app->filelist);
    app->filelist=NULL;
}

void ProcessDialog::refresh_prolist() {
    list_whose_proc_info(app);
    this->showProList();
}

void ProcessDialog::handlercellClicked(int row, int column) {
    QList<QTableWidgetItem*>items=tableWidget->selectedItems();
    QTableWidgetItem*item=items.at(2);
    QString name=item->text();//获取内容
    selected_pid = name;
}

void ProcessDialog::killSelectedProcess(){
    QString pid;
    QList<QTableWidgetItem*>items = tableWidget->selectedItems();
    QTableWidgetItem* item = items.at(2);
    pid = item->text();
    QProcess *p = new QProcess();
    p->start("kill -9 " + pid);
    bool result = p->waitForFinished();
    if (result) {
        toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("kill process success"));
    }
    else {
        toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("kill process failed"));
    }
//    int count=items.count();
//   for(int i=0;i<count;i++) {
//          int row = tableWidget->row(items.at(i));//获取选中的行
//          QTableWidgetItem* item = items.at(i);
//          QString name=item->text();//获取内容
//    }
}
