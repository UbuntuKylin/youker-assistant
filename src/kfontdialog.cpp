#include "kfontdialog.h"
#include "ui_kfontdialog.h"
#include <QMouseEvent>
#include <QListView>
#include <QStringListModel>
#include <QDebug>
/*
 *http://www.vision.ee.ethz.ch/computing/sepp-irix/qt-3.0-mo/qfontdatabase.html
 *https://qt.gitorious.org/qt/qt/source/c48eb6d5d0a299449330dea8a6a59514942c8781:src/gui/dialogs/qfontdialog_p.h#L73
 *http://blog.163.com/shaohj_1999@126/blog/static/63406851201252043139502/
 *http://www.cnblogs.com/venow/archive/2012/10/17/2728299.html
*/

KFontDialog::KFontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KFontDialog)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    ui->okBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
//                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
//    ui->quitBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
//                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");
    getInitFont();//得到初始字体
    familymodel = new QStringListModel;
    stylemodel = new QStringListModel;
    sizemodel = new QStringListModel;
    initDialog();//初始化字体对话框
    connect(ui->familyList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateAll(QModelIndex)));
    connect(ui->styleList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateStyleandSize(QModelIndex)));
    connect(ui->sizeList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateSize(QModelIndex)));
}

KFontDialog::~KFontDialog()
{
    delete ui;
}

void KFontDialog::getInitFont() {
    //如果font为空，赋予默认值"Ubuntu"
    //如果style为空，赋予默认值"Regular"
    //如果size为空，赋予默认值"11"
    initfont ="Ubuntu";
    initstyle = "Regular";
    initsize = "11";
}

void KFontDialog::initDialog() {
    bool flag = false;//默认配置是否在当前系统字体列表中存在
    /*----------------------字体名字初始化----------------------*/
    //列出所有字体的名字
    QStringList familyNames = fdb.families();
    familymodel->setStringList(familyNames);
    ui->familyList->setModel(familymodel);
    //定位默认字体名字
    ui->familyEdit->setText(initfont);
    int row = -1;
    QModelIndex index;
    for(QStringList::Iterator f = familyNames.begin(); f != familyNames.end(); ++f) {
        row++;
        QString family = *f;
        if(initfont == family) {//默认字体名字存在列表中
            index = familymodel->index(row);
            ui->familyList->setCurrentIndex(index);
            flag = true;
            break;
        }
    }
    if(flag == false) {//默认字体名字不存在列表中，此时让光标定位在第一个字体名字上面
        index = familymodel->index(0);
        ui->familyList->setCurrentIndex(index);
    }

    /*----------------------字体风格初始化----------------------*/
    if(flag) {
        flag = false;
    }
    //列出系统对应的所有风格
    QStringList familystyles = fdb.styles(initfont);
    stylemodel->setStringList(familystyles);
    ui->styleList->setModel(stylemodel);
    //定位默认的字体风格
    ui->styleEdit->setText(initstyle);
    row = -1;
    for(QStringList::Iterator s = familystyles.begin(); s != familystyles.end(); ++s) {
        row++;
        QString style = *s;
        if(initstyle == style) {//默认字体风格存在列表中
            index = stylemodel->index(row);
            ui->styleList->setCurrentIndex(index);
            flag = true;
            break;
        }
    }
    if(flag == false) {//默认字体风格不存在列表中，此时让光标定位在第一个风格上面
        index = stylemodel->index(0);
        ui->styleList->setCurrentIndex(index);
    }

    /*----------------------字体大小初始化----------------------*/
    if(flag) {
        flag = false;
    }
    //列出所有字体及其风格对应的所有大小
    QList<int> sizes = fdb.pointSizes(initfont, initstyle);
    QStringList str_sizes;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        str_sizes.append(QString::number(*it));
    }
    sizemodel->setStringList(str_sizes);
    ui->sizeList->setModel(sizemodel);
    //定位默认的字体大小
    ui->sizeEdit->setText(initsize);
    row = -1;
    for(QStringList::Iterator m = str_sizes.begin(); m != str_sizes.end(); ++m) {
        row++;
        QString size = *m;
        if(initsize == size) {//默认字体大小存在列表中
            index = sizemodel->index(row);
            ui->sizeList->setCurrentIndex(index);
            flag = true;
            break;
        }
    }
    if(flag == false) {//默认字体大小不存在列表中，此时让光标定位在第一个大小上面
        index = sizemodel->index(0);
        ui->sizeList->setCurrentIndex(index);
    }

    /*----------------------字体视图显示----------------------*/
    updateSampleFont();
//    QVariant variant = model->data(index, Qt::DisplayRole);  //获取当前选择的项的文本
//    QString name = variant.toString();
}


void KFontDialog::updateSampleFont()
{
    int pSize = ui->sizeEdit->text().toInt();
    QFont newFont(fdb.font(ui->familyEdit->text(), ui->styleEdit->text(), pSize));
    if (newFont != ui->sampleEdit->font()) {
        ui->sampleEdit->setFont(newFont);
    }
//    if (ui->familyList->currentText().isEmpty())
//        ui->sampleEdit->clear();
//    updateSampleFont(newFont);
}

void KFontDialog::updateAll(QModelIndex index) {
    ui->familyEdit->setText(index.data().toString());
    QModelIndex styleindex = stylemodel->index(0);

    //更新stylemodel
    QStringList familystyles = fdb.styles(ui->familyEdit->text());
    stylemodel->setStringList(familystyles);
    ui->styleList->setModel(stylemodel);
    //设置光标默认值
    ui->styleList->setCurrentIndex(styleindex);
    ui->styleEdit->setText(ui->styleList->currentIndex().data().toString());


    //列出所有字体及其风格对应的所有大小
    //更新sizemodel
    bool sizeFlag = false;
    int num = 0;
    QList<int> sizes = fdb.pointSizes(ui->familyEdit->text(), ui->styleEdit->text());
    QStringList str_sizes;
    int row = -1;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        row++;
        str_sizes.append(QString::number(*it));
        if(*it == 11) {
            sizeFlag = true;
            num = row;
        }
    }
    sizemodel->setStringList(str_sizes);
    ui->sizeList->setModel(sizemodel);
    QModelIndex sizeindex;
    //更新时如果大小列表中存在11,则大小的默认值设为11
    if(sizeFlag == false) {
        sizeindex = sizemodel->index(0);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }
    else {
        sizeFlag = false;
        sizeindex = sizemodel->index(num);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }



//    QModelIndex sizeindex;
////    bool sizeFlag = false;
//    int row = -1;
//    QList<int> sizes = fdb.pointSizes(ui->familyEdit->text(), ui->styleEdit->text());
//    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
//        row++;
//        if(*it == 11) {
//            sizeindex = sizemodel->index(row);
//            ui->sizeList->setCurrentIndex(sizeindex);
//            ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
//            sizeFlag = true;
//            break;
//        }
//    }
//    if(sizeFlag == false) {
//        sizeindex = sizemodel->index(0);
//        ui->sizeList->setCurrentIndex(sizeindex);
//        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
//    }
    updateSampleFont();
}

void KFontDialog::updateStyleandSize(QModelIndex index) {
    ui->styleEdit->setText(index.data().toString());

    //列出所有字体及其风格对应的所有大小
    //更新sizemodel
    bool sizeFlag = false;
    int num = 0;
    QList<int> sizes = fdb.pointSizes(ui->familyEdit->text(), ui->styleEdit->text());
    QStringList str_sizes;
    int row = -1;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        row++;
        str_sizes.append(QString::number(*it));
        if(*it == 11) {
            sizeFlag = true;
            num = row;
        }
    }
    sizemodel->setStringList(str_sizes);
    ui->sizeList->setModel(sizemodel);
    //更新时如果大小列表中存在11,则大小的默认值设为11
    QModelIndex sizeindex;
    if(sizeFlag == false) {
        sizeindex = sizemodel->index(0);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }
    else {
        sizeFlag = false;
        sizeindex = sizemodel->index(num);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }


    updateSampleFont();
}

void KFontDialog::updateSize(QModelIndex index) {
    ui->sizeEdit->setText(index.data().toString());
    updateSampleFont();
}


//void KFontDialog::showStyles(QModelIndex index) {
//    QString font = index.data().toString();
////    qDebug() << ui->familyList->currentIndex().data().toString();
//    QStringList familystyles = fdb.styles(font);
//    QStringListModel *model = new QStringListModel;
//    model->setStringList(familystyles);
//    ui->styleList->setModel(model);

//    //定位选择的字体风格
//    ui->styleEdit->setText(initstyle);
//    int row = -1;
//    for(QStringList::Iterator s = familystyles.begin(); s != familystyles.end(); ++s) {
//        row++;
//        QString style = *s;
//        if(initstyle == style) {
////            QString strValue;
////            strValue = tr("%1").arg(row);
////            qDebug() << "5555";
////            qDebug() << QString(strValue);
//            QModelIndex index = model->index(row);
//            ui->styleList->setCurrentIndex(index);
//            break;
//        }
//    }
//}
