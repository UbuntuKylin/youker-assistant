/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  tang guang   tangguang@kylinos.cn
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

#include "cpufmwidget.h"
#include <QLabel>
#include <QDebug>
#include <QMovie>

#include "../component/generaldialog.h"

CpuFmwidget::CpuFmwidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(700,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                        border-bottom-right-radius:0px;\
                        border-bottom-left-radius:10px}");
}

CpuFmwidget::~CpuFmwidget()
{

}

void CpuFmwidget::InitUI()
{
    QLabel *icon_lable = new QLabel(this);
    cpu_lable = new QLabel(this);
    QLabel *cpu_tip = new QLabel(this);

    QMovie *movie = new QMovie(":/res/cpuFM.gif");
    movie->setSpeed(100);
    icon_lable->setMovie(movie);
    icon_lable->setFixedSize(68,68);
    icon_lable->setGeometry(QRect(60,39,68,68));
    movie->start();

    QFont font;
    font.setBold(QFont::Bold);
    font.setPixelSize(24);
//    cpu_lable->setFont(font);
    cpu_lable->setText(this->cpu_num+"Mhz");
    cpu_lable->setStyleSheet("QLabel{color:rgb(0,0,0,185);font-size:24px;font-weight:bold;}");
    cpu_lable->setGeometry(QRect(140,35,150,30));

    font.setBold(QFont::Normal);
    font.setPixelSize(16);
    cpu_tip->setFont(font);
    cpu_tip->setText(tr("Current average CPU core frequency"));
    cpu_tip->setStyleSheet("QLabel{color:rgb(0,0,0,185);font-size:16px;font-weight:bold;}");
    cpu_tip->setGeometry(QRect(140,78,400,20));

    QFrame *h = new QFrame(this);
    h->setStyleSheet("background:rgb(231,231,231);border-radius:4px;");
    h->setGeometry(QRect(62,120,580,75));
    QVBoxLayout *h_layout = new QVBoxLayout(h);
    h_layout->setSpacing(10);
    h_layout->setMargin(0);
    h_layout->setContentsMargins(10,10,0,10);

    QLabel *tip = new QLabel(h);
    tip->setFont(font);
    tip->setText(tr("CPU Management Strategy :"));
    tip->setStyleSheet("color:rgb(0,0,0,185)");
    h_layout->addWidget(tip);

    radioGroup = new QButtonGroup(h);
    QHBoxLayout *radio_layout = new QHBoxLayout(h);
    radioGroup->setExclusive(true);
//    qDebug() << Q_FUNC_INFO << governer_list;
    for(int i=0 ; i < governer_list.length() ; i++)
    {
        if(governer_list.at(i) == "performance")
        {
            QRadioButton *item = new QRadioButton(h);
            item->setText(tr("performance"));
            item->setStyleSheet("color:rgb(0,0,0,185)");
            item->setObjectName("performance");
            if(cur_governer == "performance")
            {
                item->setChecked(true);
            }
            radio_layout->addWidget(item);
            radioGroup->addButton(item);
        }
        else if(governer_list.at(i) == "powersave")
        {
            QRadioButton *item = new QRadioButton(h);
            item->setText(tr("powersave"));
            item->setStyleSheet("color:rgb(0,0,0,185)");
            item->setObjectName("powersave");
            if(cur_governer == "powersave")
            {
                item->setChecked(true);
            }
            radio_layout->addWidget(item);
            radioGroup->addButton(item);
        }
        else if(governer_list.at(i) == "userspace")
        {
            QRadioButton *item = new QRadioButton(h);
            item->setText(tr("userspace"));
            item->setStyleSheet("color:rgb(0,0,0,185)");
            item->setObjectName("userspace");
            if(cur_governer == "userspace")
            {
                item->setChecked(true);
            }
            radio_layout->addWidget(item);
            radioGroup->addButton(item);
        }
        else if(governer_list.at(i) == "schedutil")
        {
            QRadioButton *item = new QRadioButton(h);
            item->setText("Schedutil");
            item->setStyleSheet("color:rgb(0,0,0,185)");
            item->setObjectName("schedutil");
            if(cur_governer == "schedutil")
            {
                item->setChecked(true);
            }
            radio_layout->addWidget(item);
            radioGroup->addButton(item);
        }
        else
        {
            continue;
        }
    }
    radio_layout->setSpacing(10);
    radio_layout->addStretch(1);
    radio_layout->setContentsMargins(10, 0, 10, 0);

    h_layout->addLayout(radio_layout);

    connect(radioGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

    w = new QFrame(this);
    w->setAutoFillBackground(false);
    w->setStyleSheet("background:rgb(231,231,231);border-radius:4px;");
    w->setGeometry(QRect(62,200,580,50));

    QHBoxLayout *w_layout = new QHBoxLayout(w);
    w_layout->setSpacing(15);
    w_layout->setMargin(0);
    w_layout->setContentsMargins(10,0,10,0);

    QLabel *lable1 = new QLabel();
    lable1->setText(tr("Adjust the CPU frequency to:"));
    lable1->setStyleSheet("color:rgb(0,0,0,185)");
    w_layout->addWidget(lable1);

    FreqGroup = new QComboBox(w);
    FreqGroup->setFixedSize(300,40);
    FreqGroup->addItems(getComboxText(freq_list));
    FreqGroup->setCurrentIndex(0);
    FreqGroup->setStyleSheet("QComboBox{background:rgb(211,211,211);border-radius:4px;}");
    w_layout->addWidget(FreqGroup,1,Qt::AlignLeft);

    connect(FreqGroup,&QComboBox::currentTextChanged,this,[=]{
        freq_value = FreqGroup->currentText();
    });

    tip_lable = new QLabel(this);
    tip_lable->setText(tr("CPU FM Note: The CPU FM function has some risks, please use it carefully! After FM is completed, restarting will restore the default configuration!"));
    tip_lable->adjustSize();
    tip_lable->setStyleSheet("color:rgb(0,0,0,185);font-size:14px;");
    tip_lable->resize(570, 27);
    tip_lable->setWordWrap(true);
    tip_lable->setGeometry(QRect(62,205,580,50));

    if(QString::compare(cur_governer,"userspace") != 0)
        w->setVisible(false);

    apply_button = new QPushButton(this);
    apply_button->setFixedSize(120,36);
    apply_button->setText(tr("apply"));
    apply_button->setStyleSheet("QPushButton{width:120px;height:36px;\
                                 background:rgba(231,231,231,1);\
                                 border-radius:4px;color:black;}\
                                 QPushButton:hover{width:120px;height:36px;\
                                 background:rgba(67,127,240,1);\
                                 border-radius:4px;color:white;}");
    apply_button->setGeometry(QRect(60,310,120,36));

    connect(apply_button,SIGNAL(clicked()),this,SLOT(onClickedApply()));

    if(cur_governer == "userspace")
    {
        w->setVisible(true);
    }
    else
    {
        w->setVisible(false);
        apply_button->move(60,255);
    }

    initUserspaceFrameAnimation();

    dialog = new GeneralDialog(this,tr("Whether to apply?"),true,false);

    connect(dialog,&GeneralDialog::accepted,[this]{
        if(value == "userspace"){
//            qDebug() << Q_FUNC_INFO << freq_list.at(FreqGroup->currentIndex());
            emit this->setCpuGoverner(value+"<1_1>"+freq_list.at(FreqGroup->currentIndex()));
            cur_freq = freq_list.at(FreqGroup->currentIndex());
        }else
            emit this->setCpuGoverner(value);

        cur_governer = value;
    });

    connect(dialog,&GeneralDialog::rejected,[this]{
        FreqGroup->setCurrentIndex(freq_list.indexOf(cur_freq));

        QList<QAbstractButton*> list1 = radioGroup->buttons();
        foreach (QAbstractButton *pButton, list1)
        {
            if(QString::compare(cur_governer,pButton->objectName()) == 0)
            {
               pButton->setChecked(true);
//               qDebug() << Q_FUNC_INFO <<  __LINE__ <<pButton->objectName();
            }

            if(QString::compare("userspace",cur_governer) != 0)
            {
                if(w->isVisible())
                    showUserspaceFrame(false);

                value = cur_governer;
            }else if(QString::compare("userspace",cur_governer) == 0 && !w->isVisible()){

                if(!w->isVisible())
                    showUserspaceFrame(true);

                value = cur_governer;
            }
        }
    });

    QObject::connect(&qtimer, &QTimer::timeout, this, &CpuFmwidget::RequestCPUFrequencyData);
    qtimer.start(2000);
}

void CpuFmwidget::set_cpu_listAndCur(QStringList list, QStringList list1, QString string, QString cur)
{
    this->governer_list = list;
    this->freq_list = list1;

    if(this->governer_list.contains("userspace") && isHW990())
    {
        this->governer_list.removeAll("userspace");
    }
    this->cur_governer = string;
    this->cur_freq = cur;
    value = string;
    qDebug() << Q_FUNC_INFO <<this->governer_list << this->cur_governer;
}

void CpuFmwidget::getCpuRange(QMap<QString,QVariant> tmpMap, QStringList list)
{
    qDebug() << Q_FUNC_INFO << list;
//    slider->setRangeLable(tmpMap,list);
}

void CpuFmwidget::onButtonClicked(QAbstractButton *button)
{
    qDebug() << QString("Clicked Button : %1").arg(button->objectName());

    if(button->objectName() == "userspace" && value != "userspace")
    {
        if(!w->isVisible())
            showUserspaceFrame(true);
    }
    else if(button->objectName() != "userspace" && value == "userspace")
    {
        if(w->isVisible())
            showUserspaceFrame(false);
    }
    value = button->objectName();

}

void CpuFmwidget::onClickedApply()
{
    dialog->exec();
}

void CpuFmwidget::RefreshCheckStatus()
{
    if((cur_governer != "userspace")&&w->isVisible()){
        w->setVisible(false);
        apply_button->setGeometry(60,255,120,36);
        tip_lable->setGeometry(QRect(62,205,580,50));
        value = cur_governer;
    }
    if((cur_governer == "userspace")&&!w->isVisible())
        showUserspaceFrame(true);

    if(cur_freq != "0")
        FreqGroup->setCurrentIndex(freq_list.indexOf(cur_freq));

     QList<QAbstractButton*> list = radioGroup->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         if(QString::compare(cur_governer,pButton->objectName()) == 0)
         {
            pButton->setChecked(true);
//            qDebug() << Q_FUNC_INFO <<  __LINE__ <<pButton->objectName();
         }
     }
}

void CpuFmwidget::ProcessingCPUFrequencyData(QMap<QString, QVariant> TmpMap)
{
//    qDebug() << Q_FUNC_INFO <<TmpMap;
    QMap<QString, QVariant> cpu_info_map = TmpMap;
    if (!cpu_info_map.isEmpty()) {
        QMap<QString,QVariant>::iterator it;
        it = cpu_info_map.begin();
//        qDebug() << Q_FUNC_INFO <<TmpMap<<it.value().toString();
        cpu_lable->setText(it.value().toString());
        cpu_lable->update();
    }
}

bool CpuFmwidget::isHW990(){
    QFile file("/proc/cpuinfo");
    bool isHW990 = false;
    bool ret = file.open(QIODevice::ReadOnly|QIODevice::Text);
    if (ret){
        QString all = file.readAll();
        if(all.contains("HUAWEI Kirin 990") || all.contains("kirin990") || all.contains("HUAWEI Kirin 9006C") || all.contains("Kirin990")){
            isHW990 = true;
        }
    }
    return isHW990;
}

void CpuFmwidget::initUserspaceFrameAnimation()
{
    QPropertyAnimation *animation0 = new QPropertyAnimation(w,"geometry");
    animation0->setDuration(500);
    animation0->setStartValue(QRect(62,200,580,10));
    animation0->setEndValue(QRect(62,200,580,50));
    animation0->setEasingCurve(QEasingCurve::InQuad);

    QPropertyAnimation *animation1 = new QPropertyAnimation(apply_button,"geometry");
    animation1->setDuration(500);
    animation1->setStartValue(QRect(60,255,120,36));
    animation1->setEndValue(QRect(60,310,120,36));
    animation1->setEasingCurve(QEasingCurve::InQuad);

    QPropertyAnimation *animation2 = new QPropertyAnimation(tip_lable,"geometry");
    animation2->setDuration(500);
    animation2->setStartValue(QRect(62,205,580,50));
    animation2->setEndValue(QRect(60,260,580,50));
    animation2->setEasingCurve(QEasingCurve::InQuad);

    group = new QParallelAnimationGroup(this);
    group->setDirection(QAbstractAnimation::Forward);
    group->setLoopCount(1);
    group->addAnimation(animation0);
    group->addAnimation(animation1);
    group->addAnimation(animation2);


    QPropertyAnimation *animation3 = new QPropertyAnimation(w,"geometry");
    animation3->setDuration(200);
    animation3->setStartValue(QRect(62,200,580,50));
    animation3->setEndValue(QRect(62,200,580,10));
    animation3->setEasingCurve(QEasingCurve::InQuad);

    QPropertyAnimation *animation4 = new QPropertyAnimation(apply_button,"geometry");
    animation4->setDuration(200);
    animation4->setStartValue(QRect(60,310,120,36));
    animation4->setEndValue(QRect(60,255,120,36));
    animation4->setEasingCurve(QEasingCurve::InQuad);

    QPropertyAnimation *animation5 = new QPropertyAnimation(tip_lable,"geometry");
    animation5->setDuration(200);
    animation5->setEndValue(QRect(62,205,580,50));
    animation5->setStartValue(QRect(60,260,580,50));
    animation5->setEasingCurve(QEasingCurve::InQuad);

    group1 = new QParallelAnimationGroup(this);
    group1->setDirection(QAbstractAnimation::Forward);
    group1->setLoopCount(1);
    group1->addAnimation(animation3);
    group1->addAnimation(animation4);
    group1->addAnimation(animation5);
}

void CpuFmwidget::showUserspaceFrame(bool i)
{
    if(i){
        w->setVisible(true);
        group->start();
    }else{
        group1->start();
        w->setVisible(false);
    }
}

QString CpuFmwidget::conversion(QString str)
{
    float target = str.toFloat();
    qDebug() << Q_FUNC_INFO << str.toInt();
    int i = 0;
    QString unit;
    while (target >= 1000) {
        if (0 == i)
            unit = "Mhz";
        else if (1 == i)
            unit = "Ghz";
        i++;

        target = target/1000;
    }

    return QString::number(target,'f',1)+unit;
}

QStringList CpuFmwidget::getComboxText(QStringList list)
{
    QStringList comboxText;
    comboxText.clear();

    foreach (QString var, list) {
        comboxText.append(conversion(var));
    }

    return comboxText;
}

