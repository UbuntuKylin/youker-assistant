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

    dialog = new GeneralDialog(this,tr("Whether to apply?"),true,false);

    connect(dialog,&GeneralDialog::accepted,[this]{
        if(value == "userspace")
            emit this->setCpuGoverner(value+"<1_1>"+QString::number(slider->value()*1000));
        else
            emit this->setCpuGoverner(value);

        cur_governer = value;
    });

    connect(dialog,&GeneralDialog::rejected,[this]{
        QList<QAbstractButton*> list = radioGroup->buttons();
        foreach (QAbstractButton *pButton, list)
        {
            if(QString::compare(cur_governer,pButton->objectName()) == 0)
            {
               pButton->setChecked(true);
//               qDebug() << Q_FUNC_INFO <<  __LINE__ <<pButton->objectName();
            }

            if(QString::compare("userspace",pButton->objectName()) == 0 && QString::compare("userspace",value) == 0 )
            {
                w->setVisible(false);

                QPropertyAnimation *animation = new QPropertyAnimation(w,"geometry");
                animation->setDuration(200);
                animation->setStartValue(QRect(62,200,580,155));
                animation->setEndValue(QRect(62,200,580,10));
                animation->setEasingCurve(QEasingCurve::InQuad);

                QPropertyAnimation *animation1 = new QPropertyAnimation(apply_button,"geometry");
                animation1->setDuration(200);
                animation1->setStartValue(QRect(60,360,120,36));
                animation1->setEndValue(QRect(60,200,120,36));
                animation1->setEasingCurve(QEasingCurve::InQuad);

                group1 = new QParallelAnimationGroup(this);
                group1->setDirection(QAbstractAnimation::Forward);
                group1->setLoopCount(1);
                group1->addAnimation(animation);
                group1->addAnimation(animation1);

                group1->start();

                value = cur_governer;
            }
        }
    });

    QObject::connect(&qtimer, &QTimer::timeout, this, &CpuFmwidget::RequestCPUFrequencyData);
    qtimer.start(2000);
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
    w->setGeometry(QRect(62,200,580,155));

    QVBoxLayout *v_layout = new QVBoxLayout(w);
    v_layout->setSpacing(0);
    v_layout->setMargin(0);
    v_layout->setContentsMargins(10,10,0,0);

    QLabel *lable1 = new QLabel();
//    QLabel *lable2 = new QLabel();
    slider = new mySlider(w);

    lable1->setText(tr("Current Frequency Adjustable Range:"));
    lable1->setStyleSheet("color:rgb(0,0,0,185)");
    v_layout->addWidget(lable1);

    slider->setFixedSize(560,80);
    slider->setOrientation(Qt::Horizontal);
    slider->setStyleSheet("QSlider{background:white;"
                          "margin: 40px;"
                          "border-radius: 3px;}");
    v_layout->addWidget(slider);

//    lable2->setText(tr("CPU FM Note: There are some risks associated with the CPU FM function,please use caution! The computer needs to be restarted when the FM is complete."));
//    lable2->adjustSize();
//    lable2->setStyleSheet("color:rgb(0,0,0,185)");
//    lable2->setFixedSize(580, 27*2);
//    lable2->setWordWrap(true);
//    v_layout->addWidget(lable2);
//    v_layout->addStretch(1);

    w->setVisible(false);

    apply_button = new QPushButton(this);
    apply_button->setFixedSize(120,36);
    apply_button->setText(tr("apply"));
    apply_button->setStyleSheet("QPushButton{width:120px;height:36px;\
                                 background:rgba(231,231,231,1);\
                                 border-radius:4px;font-size:14px;color:black;}\
                                 QPushButton:hover{width:120px;height:36px;\
                                 background:rgba(67,127,240,1);\
                                 border-radius:4px;font-size:14px;color:white;}");
    apply_button->setGeometry(QRect(60,360,120,36));

    connect(apply_button,SIGNAL(clicked()),this,SLOT(onClickedApply()));

    if(cur_governer == "userspace")
    {
        w->setVisible(true);
    }
    else
    {
        w->setVisible(false);
        apply_button->move(60,200);
    }
}

void CpuFmwidget::set_cpu_listAndCur(QStringList list, QString string)
{
    this->governer_list = list;
    if(!this->governer_list.contains("userspace"))
    {
        this->governer_list.append("userspace");
    }
    this->cur_governer = string;
    value = string;
    qDebug() << Q_FUNC_INFO <<this->governer_list << this->cur_governer;
}

void CpuFmwidget::getCpuRange(QMap<QString,QVariant> tmpMap)
{
    slider->setRangeLable(tmpMap);
}

void CpuFmwidget::onButtonClicked(QAbstractButton *button)
{
    qDebug() << QString("Clicked Button : %1").arg(button->objectName());

//     QList<QAbstractButton*> list = radioGroup->buttons();
//     foreach (QAbstractButton *pButton, list)
//     {
//         QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
//         qDebug() << QString("Button : %1 is %2").arg(button->text()).arg(strStatus);
//     }

    if(button->objectName() == "userspace" && value != "userspace")
    {
        w->setVisible(true);
        QPropertyAnimation *animation = new QPropertyAnimation(w,"geometry");
        animation->setDuration(500);
        animation->setStartValue(QRect(62,200,580,10));
        animation->setEndValue(QRect(62,200,580,155));
        animation->setEasingCurve(QEasingCurve::InQuad);

        QPropertyAnimation *animation1 = new QPropertyAnimation(apply_button,"geometry");
        animation1->setDuration(500);
        animation1->setStartValue(QRect(60,200,120,36));
        animation1->setEndValue(QRect(60,360,120,36));
        animation1->setEasingCurve(QEasingCurve::InQuad);

        group = new QParallelAnimationGroup(this);
        group->setDirection(QAbstractAnimation::Forward);
        group->setLoopCount(1);
        group->addAnimation(animation);
        group->addAnimation(animation1);

        group->start();

    }
    else if(button->objectName() != "userspace" && value == "userspace")
    {
        w->setVisible(false);
        QPropertyAnimation *animation = new QPropertyAnimation(w,"geometry");
        animation->setDuration(200);
        animation->setStartValue(QRect(62,200,580,155));
        animation->setEndValue(QRect(62,200,580,10));
        animation->setEasingCurve(QEasingCurve::InQuad);

        QPropertyAnimation *animation1 = new QPropertyAnimation(apply_button,"geometry");
        animation1->setDuration(200);
        animation1->setStartValue(QRect(60,360,120,36));
        animation1->setEndValue(QRect(60,200,120,36));
        animation1->setEasingCurve(QEasingCurve::InQuad);

        group1 = new QParallelAnimationGroup(this);
        group1->setDirection(QAbstractAnimation::Forward);
        group1->setLoopCount(1);
        group1->addAnimation(animation);
        group1->addAnimation(animation1);

        group1->start();
    }
    value = button->objectName();

}

void CpuFmwidget::onClickedApply()
{
//    qDebug() << Q_FUNC_INFO << value << slider->value() << value+"<1_1>"+QString::number(slider->value()*1000);
    dialog->exec();

}

void CpuFmwidget::RefreshCheckStatus()
{
    if((cur_governer != "userspace")&&w->isVisible()){
        w->setVisible(false);
        apply_button->setGeometry(60,200,120,36);
        value = cur_governer;
    }

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
