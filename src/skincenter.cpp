#include "skincenter.h"
#include "ui_skincenter.h"

SkinCenter::SkinCenter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkinCenter)
{
    ui->setupUi(this);

    locale_Lan = this->get_locale_version();
    QPixmap pixmap(":/pixmap/image/clothes.png");
    ui->iconLabel->setPixmap(pixmap);
    if(locale_Lan == "zh_CN") {
        ui->preBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/pre-zh.png)}");
        ui->nextBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/next-zh.png)}");
    }
    else {
        ui->preBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/pre-en.png)}");
        ui->nextBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/next-en.png)}");
    }
    QPixmap pixmap1(":/skin/image/0.png");
    ui->label1->setPixmap(pixmap1);
    ui->label2->setPixmap(pixmap1);
    ui->label3->setPixmap(pixmap1);
    ui->label4->setPixmap(pixmap1);
    ui->label5->setPixmap(pixmap1);
    ui->label6->setPixmap(pixmap1);
    ui->label7->setPixmap(pixmap1);
    ui->label8->setPixmap(pixmap1);

//    ui->descBtn->setStyleSheet("QPushButton {border:0px;color:#1790c9}");
//    ui->descBtn->setText(tr("Details"));//详细
//    ui->descBtn->setFlat(true);
//    ui->descBtn->setFocusPolicy(Qt::NoFocus);


//    this->setCursor(Qt::PointingHandCursor);
//    skin_icon->setScaledContents(true);
//    skin_icon->setFixedSize(100, 65);
//    QVBoxLayout *background_layout = new QVBoxLayout();
//    background_layout->addWidget(skin_icon, 0, Qt::AlignCenter);
//    background_layout->addWidget(skin_title, 0, Qt::AlignCenter);
//    background_layout->setSpacing(5);
//    background_layout->setContentsMargins(0, 10, 0, 10);
//    this->setLayout(background_layout);



//    this->setWindowOpacity(1.0);
//    this->setAttribute(Qt::WA_DeleteOnClose);
//    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    this->setAttribute(Qt::WA_TranslucentBackground);

//    pSettings = mSettings;
//    skinName = QString("");

//    mouse_press = false;
//    is_change = false;
//    current_page = 1;
//    //皮肤 1   皮肤 2
//    tip_list<<tr("skin 1")<<tr("skin 2")<<tr("skin 3")<<tr("skin 4")<<tr("skin 5")<<
//           tr("skin 6")<<tr("skin 7")<<tr("skin 8")<<tr("skin 9")<<tr("skin 10")<<
//           tr("skin 11")<<tr("skin 12")<<tr("skin 13")<<tr("skin 14")<<tr("skin 15")<<
//           tr("skin 16")<<tr("skin 17")<<tr("skin 18")<<tr("skin 19")<<tr("skin 20") <<
//           tr("skin 21")<<tr("skin 22")<<tr("skin 23")<<tr("skin 24");
//    this->initTitleBar();
//    this->initSkinsCenter();
//    this->initBottomBar();

//    QVBoxLayout *mainLayout = new QVBoxLayout();
//    mainLayout->addLayout(titleLayout);
//    mainLayout->addLayout(centerLayout);
//    mainLayout->addLayout(bottomLayout);
//    mainLayout->addStretch();
//    mainLayout->setSpacing(0);
//    mainLayout->setContentsMargins(0, 0, 0, 0);
//    setLayout(mainLayout);
//    this->showSkin(QString::number(current_page, 10));

//    QDesktopWidget* desktop = QApplication::desktop();
//    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

//    this->resize(620, 445);
}

SkinCenter::~SkinCenter()
{
    delete ui;
}

QString SkinCenter::get_locale_version() {
    QString locale = QLocale::system().name();
    return locale;
}

//void SkinCenter::paintEvent(QPaintEvent *) {
//    QString skinName = QString(":/skin/image/0");
//    QPainter painter(this);
//    painter.drawPixmap(rect(), QPixmap(skinName));

//    QPainter painter2(this);
//    QLinearGradient linear2(rect().topLeft(), rect().bottomLeft());
//    linear2.setColorAt(0, Qt::white);
//    linear2.setColorAt(0.5, Qt::white);
//    linear2.setColorAt(1, Qt::white);
//    painter2.setPen(Qt::white);
//    painter2.setBrush(linear2);
//    painter2.drawRect(QRect(0, 30, this->width(), this->height()-30));

//    QPainter painter3(this);
//    painter3.setPen(Qt::gray);
//    static const QPointF points[4] = {QPointF(0, 30), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 30)};
//    painter3.drawPolyline(points, 4);
//}

//void SkinsWidget::resizeEvent(QResizeEvent *event) {
//    wheel=QImage(event->size(),QImage::Format_ARGB32_Premultiplied);
//    wheel.fill(palette().background().color());
//    update();
//}

//bool SkinCenter::eventFilter(QObject *obj, QEvent *event) {
//    if(obj == close_button) {
//            if(event->type() == QEvent::Enter){
//                close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
//            }else if(event->type() == QEvent::Leave){
//                close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
//            }else if(event->type() == QEvent::MouseButtonPress){
//                close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
//            }else if(event->type() == QEvent::MouseButtonRelease){
//                QMouseEvent *me = (QMouseEvent *)event;
//                QLabel *lb = (QLabel *)obj;
//                if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
//                    this->hide();
//                }else{
//                    close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
//                }
//            } else {
//                return QObject::eventFilter(obj, event);
//            }
//        }
//        return QObject::eventFilter(obj, event);
//}

//void SkinCenter::mousePressEvent( QMouseEvent * event ) {
//    if(event->button() == Qt::LeftButton) {
//        mouse_press = true;
//    }
//    move_point = event->globalPos() - pos();
//}

//void SkinCenter::mouseReleaseEvent(QMouseEvent *) {
//    mouse_press = false;
//}

//void SkinCenter::mouseMoveEvent(QMouseEvent *event) {
//    if(mouse_press) {
//        QPoint move_pos = event->globalPos();
//        move(move_pos - move_point);
//    }
//}
