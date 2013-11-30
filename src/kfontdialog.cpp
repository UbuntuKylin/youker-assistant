#include "kfontdialog.h"
#include "ui_kfontdialog.h"
#include <QMouseEvent>
#include <QListView>
#include <QStringListModel>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

extern QString selectedFont;
/*
 *http://www.vision.ee.ethz.ch/computing/sepp-irix/qt-3.0-mo/qfontdatabase.html
 *https://qt.gitorious.org/qt/qt/source/c48eb6d5d0a299449330dea8a6a59514942c8781:src/gui/dialogs/qfontdialog_p.h#L73
 *http://blog.163.com/shaohj_1999@126/blog/static/63406851201252043139502/
 *http://www.cnblogs.com/venow/archive/2012/10/17/2728299.html
 *
 *
 *
 *families:
 ("Abyssinica SIL", "AR PL UKai CN", "AR PL UKai HK", "AR PL UKai TW", "AR PL UKai TW MBE", "AR PL UMing CN",
"AR PL UMing HK", "AR PL UMing TW", "AR PL UMing TW MBE", "Bitstream Charter", "Century Schoolbook L",
"Courier 10 Pitch", "DejaVu Sans", "DejaVu Sans Mono", "DejaVu Serif", "Dingbats", "gargi", "Garuda", "Kedage",
"Khmer OS", "Khmer OS System", "Liberation Mono", "Liberation Sans", "Liberation Sans Narrow", "Liberation Serif",
"LKLUG", "Lohit Bengali", "Lohit Gujarati", "Lohit Hindi", "Lohit Punjabi", "Lohit Tamil", "Mallige", "Meera",
"Monospace", "Mukti Narrow", "Nimbus Mono L", "Nimbus Roman No9 L", "Nimbus Sans L", "OpenSymbol", "ori1Uni",
"Padauk", "Padauk Book", "Pothana2000", "Rachana", "Rekha", "Saab", "Sans Serif", "Serif", "Standard Symbols L",
"Symbol", "Tibetan Machine Uni", "Ubuntu", "Ubuntu Condensed", "Ubuntu Mono", "URW Bookman L", "URW Chancery L",
"URW Gothic L", "URW Palladio L", "Vemana2000", "文泉驿微米黑", "文泉驿正黑", "文泉驿点阵正黑", "文泉驿等宽微米黑",
"文泉驿等宽正黑")

 *styles:
"Regular","Roman", "Light", "Bold","Medium", "Book", "BoldOblique","Oblique","Normal", "Regular Oblique",
"斜体", "半粗体 斜体", "轻体 斜体", "粗体 斜体", "意大利体", "普通", "粗体 意大利体", "粗体"
"Bold Italic",  "Italic", "Regular Italic", "Medium Italic","Light Italic",
"Bold Condensed", "Regular Condensed Italic", "Bold Condensed Italic", "Regular Condensed",
"Demi Bold", "Demi Bold Italic","Demi", "Demi Oblique", Book Oblique"
sizes:
("6", "7", "8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72")
*/

KFontDialog::KFontDialog(QSettings *mSettings, QString flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KFontDialog)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->okBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
    ui->quitBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");
//    families << "Abyssinica SIL" << "AR PL UKai CN" << "AR PL UKai HK" << "AR PL UKai TW" << "AR PL UKai TW MBE" << "AR PL UMing CN" \
//             << "AR PL UMing HK" << "AR PL UMing TW" << "AR PL UMing TW MBE" << "Bitstream Charter" << "Century Schoolbook L" \
//             << "Courier 10 Pitch" << "DejaVu Sans" << "DejaVu Sans Mono" << "DejaVu Serif" << "Dingbats" << "gargi" << "Garuda" << "Kedage" \
//             << "Khmer OS" << "Khmer OS System" << "Liberation Mono" << "Liberation Sans" << "Liberation Sans Narrow" << "Liberation Serif" \
//             << "LKLUG" << "Lohit Bengali" << "Lohit Gujarati" << "Lohit Hindi" << "Lohit Punjabi" << "Lohit Tamil" << "Mallige" << "Meera" \
//             << "Monospace" << "Mukti Narrow" << "Nimbus Mono L" << "Nimbus Roman No9 L" << "Nimbus Sans L" << "OpenSymbol" << "ori1Uni" \
//             << "Padauk" << "Padauk Book" << "Pothana2000" << "Rachana" << "Rekha" << "Saab" << "Sans Serif" << "Serif" << "Standard Symbols L" \
//             << "Symbol" << "Tibetan Machine Uni" << "Ubuntu" << "Ubuntu Condensed" << "Ubuntu Mono" << "URW Bookman L" << "URW Chancery L" \
//             << "URW Gothic L" << "URW Palladio L" << "Vemana2000" << "文泉驿微米黑" << "文泉驿正黑" << "文泉驿点阵正黑" << "文泉驿等宽微米黑" << "文泉驿等宽正黑";
//    styles << "Regular" << "Light" << "Bold" << "Medium" << "Normal" << "Roman" << "Book" << "BoldOblique" \
//           << "Oblique" << "Regular Oblique" << "Bold Italic" << "Italic" << "Regular Italic" << "Medium Italic" \
//           << "Light Italic" << "Bold Condensed" << "Regular Condensed Italic" << "Bold Condensed Italic" \
//           << "Regular Condensed" << "Demi Bold" << "Demi Bold Italic" << "Demi" << "Demi Oblique" << "Book Oblique" \
//           << "斜体" << "半粗体 斜体" << "轻体 斜体" << "粗体 斜体" << "意大利体" << "普通" << "粗体 意大利体" << "粗体";
//    sizes << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "14" << "16" << "18" << "20" \
//          << "22" << "24" << "26" << "28" << "36" << "48" << "72";
    pSettings = mSettings;
    fontFlag = flag;
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
    pSettings->beginGroup("font");
    QString fontStr;
    if(fontFlag == "font") {
        //font
        fontStr = pSettings->value("currentfont").toString();
    }
    else if(fontFlag == "desktopfont") {
        //desktopfont
        fontStr = pSettings->value("desktopfont").toString();
    }
    else if(fontFlag == "monospacefont") {
        //monospacefont
        fontStr = pSettings->value("monospacefont").toString();
    }
    else if(fontFlag == "documentfont") {
        //documentfont
        fontStr = pSettings->value("documentfont").toString();
    }
    else if(fontFlag == "titlebarfont") {
        //titlebarfont
        fontStr = pSettings->value("titlebarfont").toString();
    }
    pSettings->endGroup();
    pSettings->sync();
    ui->curFontText->setText(fontStr);
//    initfont ="Ubuntu";
//    initstyle = "Regular";
//    initsize = "11";
}

//void KFontDialog::initDialog() {
//    bool flag = false;//默认配置是否在当前系统字体列表中存在
//    /*----------------------字体名字初始化----------------------*/
//    //列出所有字体的名字
//    QStringList familyNames = fdb.families();
//    familymodel->setStringList(familyNames);
//    ui->familyList->setModel(familymodel);
//    //定位默认字体名字
//    ui->familyEdit->setText(initfont);
//    int row = -1;
//    QModelIndex index;
//    for(QStringList::Iterator f = familyNames.begin(); f != familyNames.end(); ++f) {
//        row++;
//        QString family = *f;
//        if(initfont == family) {//默认字体名字存在列表中
//            index = familymodel->index(row);
//            ui->familyList->setCurrentIndex(index);
//            flag = true;
//            break;
//        }
//    }
//    if(flag == false) {//默认字体名字不存在列表中，此时让光标定位在第一个字体名字上面
//        index = familymodel->index(0);
//        ui->familyList->setCurrentIndex(index);
//    }

//    /*----------------------字体风格初始化----------------------*/
//    if(flag) {
//        flag = false;
//    }
//    //列出系统对应的所有风格
//    QStringList familystyles = fdb.styles(initfont);
//    stylemodel->setStringList(familystyles);
//    ui->styleList->setModel(stylemodel);
//    //定位默认的字体风格
//    ui->styleEdit->setText(initstyle);
//    row = -1;
//    for(QStringList::Iterator s = familystyles.begin(); s != familystyles.end(); ++s) {
//        row++;
//        QString style = *s;
//        if(initstyle == style) {//默认字体风格存在列表中
//            index = stylemodel->index(row);
//            ui->styleList->setCurrentIndex(index);
//            flag = true;
//            break;
//        }
//    }
//    if(flag == false) {//默认字体风格不存在列表中，此时让光标定位在第一个风格上面
//        index = stylemodel->index(0);
//        ui->styleList->setCurrentIndex(index);
//    }

//    /*----------------------字体大小初始化----------------------*/
//    if(flag) {
//        flag = false;
//    }
//    //列出所有字体及其风格对应的所有大小
//    QList<int> sizes = fdb.pointSizes(initfont, initstyle);
//    QStringList str_sizes;
//    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
//        str_sizes.append(QString::number(*it));
//    }
//    sizemodel->setStringList(str_sizes);
//    ui->sizeList->setModel(sizemodel);
//    //定位默认的字体大小
//    ui->sizeEdit->setText(initsize);
//    row = -1;
//    for(QStringList::Iterator m = str_sizes.begin(); m != str_sizes.end(); ++m) {
//        row++;
//        QString size = *m;
//        if(initsize == size) {//默认字体大小存在列表中
//            index = sizemodel->index(row);
//            ui->sizeList->setCurrentIndex(index);
//            flag = true;
//            break;
//        }
//    }
//    if(flag == false) {//默认字体大小不存在列表中，此时让光标定位在第一个大小上面
//        index = sizemodel->index(0);
//        ui->sizeList->setCurrentIndex(index);
//    }

//    /*----------------------字体视图显示----------------------*/
//    updateSampleFont();
////    QVariant variant = model->data(index, Qt::DisplayRole);  //获取当前选择的项的文本
////    QString name = variant.toString();
//}


void KFontDialog::initDialog() {
    //列出所有字体的名字
    QStringList familyNames = fdb.families();
    familymodel->setStringList(familyNames);
    ui->familyList->setModel(familymodel);
    QModelIndex index;
    index = familymodel->index(0);
    ui->familyList->setCurrentIndex(index);

    //列出系统对应的所有风格
    QStringList familystyles = fdb.styles(ui->familyList->currentIndex().data().toString());
    stylemodel->setStringList(familystyles);
    ui->styleList->setModel(stylemodel);
    index = stylemodel->index(0);
    ui->styleList->setCurrentIndex(index);

    //列出所有字体及其风格对应的所有大小
    QList<int> sizes = fdb.pointSizes(ui->familyList->currentIndex().data().toString(), ui->styleList->currentIndex().data().toString());
    QStringList str_sizes;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        str_sizes.append(QString::number(*it));
    }
    sizemodel->setStringList(str_sizes);
    ui->sizeList->setModel(sizemodel);
    //默认的字体大小显示为11
    bool flag = false;
    int row = -1;
    for(QStringList::Iterator m = str_sizes.begin(); m != str_sizes.end(); ++m) {
        row++;
        QString size = *m;
        if("11" == size) {//默认字体大小存在列表中
            index = sizemodel->index(row);
            ui->sizeList->setCurrentIndex(index);
            flag = true;
            break;
        }
    }
    if(flag == false) {//11不存在列表中，此时让光标定位在第一个大小上面
        index = sizemodel->index(0);
        ui->sizeList->setCurrentIndex(index);
    }

    /*----------------------字体视图显示----------------------*/
//    updateSampleFont();
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
    QString curStr = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
    ui->curFontText->setText(curStr);

    ui->sampleEdit->setText("UbuntuKylin:做最有中国位的操作系统！");
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

    QString curfont = ui->familyEdit->text();
    if(!curfont.isEmpty()) {
        QString curStr = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
        ui->curFontText->setText(curStr);
        updateSampleFont();
    }


}

void KFontDialog::updateSize(QModelIndex index) {
    ui->sizeEdit->setText(index.data().toString());
    QString curfont = ui->familyEdit->text();
    if(!curfont.isEmpty()) {
        QString curStr = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
        ui->curFontText->setText(curStr);
        updateSampleFont();
    }
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

void KFontDialog::on_quitBtn_clicked()
{
    this->close();
}

void KFontDialog::on_okBtn_clicked()
{
    if(ui->familyEdit->text().isEmpty()) {
        //提示      你还没有更换字体，请选择字体进行更换！
        QMessageBox::warning(NULL,
                             tr("Tips"),
                             tr("You haven't change the font, please select a font to change it!"),
                             QMessageBox::Ok);
    }
    else {
        selectedFont = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
//        if(fontFlag == "font") {
//            //font
//            fontStr = pSettings->value("currentfont").toString();
//        }
//        else if(fontFlag == "desktopfont") {
//            //desktopfont
//            fontStr = pSettings->value("desktopfont").toString();
//        }
//        else if(fontFlag == "monospacefont") {
//            //monospacefont
//            fontStr = pSettings->value("monospacefont").toString();
//        }
//        else if(fontFlag == "documentfont") {
//            //documentfont
//            fontStr = pSettings->value("documentfont").toString();
//        }
//        else if(fontFlag == "titlebarfont") {
//            //titlebarfont
//            fontStr = pSettings->value("titlebarfont").toString();
//        }
        this->accept();
    }
}


bool KFontDialog::eventFilter(QObject *obj, QEvent *event) {
    if(obj == ui->btn_close) {
            if(event->type() == QEvent::Enter){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
            }else if(event->type() == QEvent::Leave){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
            }else if(event->type() == QEvent::MouseButtonPress){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
            }else if(event->type() == QEvent::MouseButtonRelease){
                QMouseEvent *me = (QMouseEvent *)event;
                QLabel *lb = (QLabel *)obj;
                if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                    this->close();
                }else{
                    ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
                }
            } else {
                return QObject::eventFilter(obj, event);
            }
        }
    return QObject::eventFilter(obj, event);
}

void KFontDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void KFontDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();
}

void KFontDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
