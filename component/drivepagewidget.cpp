#include "drivepagewidget.h"
#include <QDebug>


DrivePageWidget::DrivePageWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << Q_FUNC_INFO <<__LINE__;
    this->setFixedSize(700,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                        border-bottom-right-radius:0px;\
                        border-bottom-left-radius:10px}");


    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(60,24,40,15);

    scrollarea = new QScrollArea(this);
    scrollarea->setWidgetResizable(true);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollarea->setStyleSheet("QScrollArea{border: none;background-color: #ffffff;}");
    scrollarea->setFixedSize(this->width(),this->height()-70);
    main_layout->addWidget(scrollarea);

    main_frame = new QFrame();
    v_layout = new QVBoxLayout(main_frame);
    v_layout->setSpacing(0);
    v_layout->setMargin(0);
    v_layout->setContentsMargins(0,0,0,0);

    scrollarea->setWidget(main_frame);

    this->setLayout(main_layout);
}

DrivePageWidget::~DrivePageWidget()
{

}

void DrivePageWidget::InitPageUI(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << Q_FUNC_INFO <<"______________________________"<< tmpMap;
    QMap<QString, QVariant> map = tmpMap;
    QMap<QString, QVariant>::iterator it;

    QFrame *spilterLine = new QFrame(this);
    spilterLine->setFixedSize(600, 1);
    spilterLine->setStyleSheet("QFrame{background:rgba(238,238,238,1);}");
    spilterLine->setFrameShape(QFrame::HLine);
    spilterLine->setFrameShadow(QFrame::Plain);
    v_layout->addWidget(spilterLine);

    for(it = map.begin(); it!= map.end() ; ++it){
//        qDebug() << it.key() << it.value().toString();
        QFrame *item = new QFrame();
        item->setFixedSize(600,80);
//        QVBoxLayout *m_Hlayout = new QHBoxLayout(item);
//        QHBoxLayout *m_Vlayout = new QVBoxLayout(item);
        QLabel *icon = new QLabel(item);
        QLabel *whichDrive = new QLabel(item);
        QLabel *name = new QLabel(item);

        QStringList k = this->getWhichDrive(it.key());

        QPixmap pixmap(":/res/drive/"+k.at(0)+".png");
        icon->setPixmap(pixmap);
        icon->setFixedSize(pixmap.size());
        icon->setGeometry(QRect(3,16,44,44));

        QFont font;
        font.setPixelSize(16);
        font.setWeight(QFont::Bold);
        whichDrive->setStyleSheet("color:rgba(0,0,0,195)");
        whichDrive->setFont(font);
        whichDrive->setText(k.at(1));
        whichDrive->setGeometry(QRect(65,16,200,18));

        name->setText(it.value().toString());
        name->setWordWrap(true);
        name->setStyleSheet("color:rgb(173,173,173);}");
        name->setGeometry(QRect(65,40,500,18));

        v_layout->addWidget(item);

        QFrame *spilterLine = new QFrame(this);
        spilterLine->setFixedSize(600, 1);
        spilterLine->setStyleSheet("QFrame{background:rgba(238,238,238,1);}");
        spilterLine->setFrameShape(QFrame::HLine);
        spilterLine->setFrameShadow(QFrame::Plain);
        v_layout->addWidget(spilterLine);
    }
    QLabel *drive_num = new QLabel(this);
    drive_num->setText(tr("Total, section ")+QString::number(map.size())+tr(" drivers"));
    drive_num->setStyleSheet("color:rgb(173,173,173);}");
    main_layout->addWidget(drive_num);
}

QStringList DrivePageWidget::getWhichDrive(QString p)
{
    QStringList v;
    v.clear();
    if(p == "Host bridge"){
        v << "MotherBoard" << tr("MotherBoard");
        return v;
    }
    else if(p == "VGA compatible controller"){
        v << "Graphics-Card" << tr("Graphics-Card");
        return v;
    }
    else if(p == "Signal processing controller"){
        v << "MotherBoard" << tr("MotherBoard");
        return v;
    }
    else if(p == "USB controller"){
        v << "MotherBoard" << tr("MotherBoard");
        return v;
    }
    else if(p == "RAM memory"){
        v << "Other" << tr("Other");
        return v;
    }
    else if(p == "Communication controller"){
        v << "Wired-Network-Card" << tr("Wired-Network-Card");
        return v;
    }
    else if(p == "SATA controller"){
        v << "Other" << tr("Other");
        return v;
    }
    else if(p == "PCI bridge"){
        v << "MotherBoard" << tr("MotherBoard");
        return v;
    }
    else if(p == "ISA bridge"){
        v << "MotherBoard" << tr("MotherBoard");
        return v;
    }
    else if(p == "Audio device"){
        v << "Sound-Card" << tr("Sound-Card");
        return v;
    }
    else if(p == "SMBus"){
        v << "Other" << tr("Other");
        return v;
    }
    else if(p == "Ethernet controller"){
        v << "Wired-Network-Card" << tr("Wired-Network-Card");
        return v;
    }
    else
    {
        v << "Other" << tr("Other");
        return v;
    }
}
