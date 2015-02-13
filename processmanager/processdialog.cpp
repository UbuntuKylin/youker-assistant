#include <QStringList>
#include <QCloseEvent>
#include <QBitmap>
#include <QPainter>
#include "processmanager.h"
#include <QFileDialog>
#include <QDir>
#include <QProcess>

QPoint widgetPosition;//界面中心位置的全局变量

ProcessDialog::ProcessDialog(ProcessManager *plugin, QDialog *parent)
:QDialog(parent)
//,m_EraseFile(this)
{
  setWindowFlags(Qt::FramelessWindowHint);
//  ui.setupUi(this);

    title_bar = new KylinTitleBar();
    initTitleBar();

    this->setFixedSize(850, 476);
    process_plugin = plugin;

    toolkits = new Toolkits();
    tip_label = new QLabel();
    kill_btn = new QPushButton();
    kill_btn->setFixedSize(91, 25);
    kill_btn->setObjectName("blackButton");
    kill_btn->setFocusPolicy(Qt::NoFocus);
    tableWidget = new QTableWidget();

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
//    qDebug() << row;
//    qDebug() << column;
    QList<QTableWidgetItem*>items=tableWidget->selectedItems();
    QTableWidgetItem*item=items.at(2);
    QString name=item->text();//获取内容
//    qDebug() << name;
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
        toolkits->alertMSG(tr("kill process success"));
    }
    else {
        toolkits->alertMSG(tr("kill process failed"));
    }
//    int count=items.count();
//   for(int i=0;i<count;i++) {
//          int row = tableWidget->row(items.at(i));//获取选中的行
//          QTableWidgetItem* item = items.at(i);
//          QString name=item->text();//获取内容
//          qDebug() << name;
//    }
}

void ProcessDialog::paintEvent(QPaintEvent *event)
{
     widgetPosition = this->pos();
//    QBitmap objBitmap(size());
//    //QPainter用于在位图上绘画
//    QPainter painter(&objBitmap);
//    //填充位图矩形框(用白色填充)
//    painter.fillRect(rect(),Qt::white);
//    painter.setBrush(QColor(0,0,0));
//    //在位图上画圆角矩形(用黑色填充)
//    painter.drawRoundedRect(this->rect(),5,5);
//    ////使用setmask过滤即可
//    setMask(objBitmap);
}
