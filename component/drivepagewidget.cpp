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
    main_layout->setContentsMargins(60,0,40,15);

    scrollarea = new QScrollArea(this);
    scrollarea->setWidgetResizable(true);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollarea->setStyleSheet("QScrollArea{border: none;background-color: #ffffff;}");
    scrollarea->setFixedSize(this->width(),this->height()-50);
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

    for(it = map.begin(); it!= map.end() ; ++it){
//        qDebug() << it.key() << it.value().toString();
        QFrame *item = new QFrame();
        item->setFixedSize(600,80);
//        QVBoxLayout *m_Hlayout = new QHBoxLayout(item);
//        QHBoxLayout *m_Vlayout = new QVBoxLayout(item);
        QLabel *icon = new QLabel(item);
        QLabel *whichDrive = new QLabel(item);
        QLabel *name = new QLabel(item);

        QString k = this->getWhichDrive(it.key());

        QPixmap pixmap(":/res/drive/"+k+".png");
        icon->setPixmap(pixmap);
        icon->setFixedSize(pixmap.size());
        icon->setGeometry(QRect(3,16,44,44));

        QFont font;
        font.setPixelSize(16);
        font.setWeight(QFont::Bold);
        whichDrive->setFont(font);
        whichDrive->setText(k);
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

QString DrivePageWidget::getWhichDrive(QString p)
{
    if(p == "Host bridge"){
        return "motherboard";
    }
    else if(p == "VGA compatible controller"){
        return "graphics-card";
    }
    else if(p == "Signal processing controller"){
        return "motherboard";
    }
    else if(p == "USB controller"){
        return "motherboard";
    }
    else if(p == "RAM memory"){
        return "other";
    }
    else if(p == "Communication controller"){
        return "wired-network-card";
    }
    else if(p == "SATA controller"){
        return "other";
    }
    else if(p == "PCI bridge"){
        return "motherboard";
    }
    else if(p == "ISA bridge"){
        return "motherboard";
    }
    else if(p == "Audio device"){
        return "sound-card";
    }
    else if(p == "SMBus"){
        return "other";
    }
    else if(p == "Ethernet controller"){
        return "wired-network-card";
    }
    else
    {
        return "other";
    }
}
