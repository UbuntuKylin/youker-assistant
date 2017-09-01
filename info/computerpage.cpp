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

#include "computerpage.h"
#include "../component/utils.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QBitmap>
#include <QRadioButton>

ComputerPage::ComputerPage(QWidget *parent, QString title/*, QString manufacturer*/) :
    QWidget(parent), title_context(title)/*, vendor(manufacturer)*/
{
//    this->setWindowFlags(Qt::FramelessWindowHint);
    sensor = false;
    page_height = 0;
    title_label = NULL;
    time_label = NULL;
    logo_label = NULL;
    group_box = NULL;
    form_layout = NULL;
    ondemand_radio = NULL;
    powersave_radio = NULL;
    performance_radio = NULL;
    layout = NULL;

    in0_label = NULL;
    in2_label = NULL;
    in3_label = NULL;
    in5_label = NULL;
    in6_label = NULL;
    tr1_label = NULL;
    tr2_label = NULL;
    tr3_label = NULL;
    tr4_label = NULL;
    tr5_label = NULL;
    tr6_label = NULL;
    fanin1_label = NULL;
}

ComputerPage::~ComputerPage()
{
    for(int i=0; i<label_list.count(); i++)
    {
        QLabel *label = label_list.at(i);
        delete label;
        label = NULL;
    }
    label_list.clear();
    page_height = 0;
    if(title_label != NULL)
    {
        delete title_label;
        title_label = NULL;
    }
    if(time_label != NULL)
    {
        delete time_label;
        time_label = NULL;
    }
    if(logo_label != NULL)
    {
        delete logo_label;
        logo_label = NULL;
    }
    if(ondemand_radio != NULL)
    {
        delete ondemand_radio;
        ondemand_radio = NULL;
    }
    if(powersave_radio != NULL)
    {
        delete powersave_radio;
        powersave_radio = NULL;
    }
    if(performance_radio != NULL)
    {
        delete performance_radio;
        performance_radio = NULL;
    }
    if(layout != NULL)
    {
        delete layout;
        layout = NULL;
    }
    if(in0_label != NULL)
    {
        delete in0_label;
        in0_label = NULL;
    }
    if(in2_label != NULL)
    {
        delete in2_label;
        in2_label = NULL;
    }
    if(in3_label != NULL)
    {
        delete in3_label;
        in3_label = NULL;
    }
    if(in5_label != NULL)
    {
        delete in5_label;
        in5_label = NULL;
    }
    if(in6_label != NULL)
    {
        delete in6_label;
        in6_label = NULL;
    }
    if(tr1_label != NULL)
    {
        delete tr1_label;
        tr1_label = NULL;
    }
    if(tr2_label != NULL)
    {
        delete tr2_label;
        tr2_label = NULL;
    }
    if(tr3_label != NULL)
    {
        delete tr3_label;
        tr3_label = NULL;
    }
    if(tr4_label != NULL)
    {
        delete tr4_label;
        tr4_label = NULL;
    }
    if(tr5_label != NULL)
    {
        delete tr5_label;
        tr5_label = NULL;
    }
    if(tr6_label != NULL)
    {
        delete tr6_label;
        tr6_label = NULL;
    }
    if(fanin1_label != NULL)
    {
        delete fanin1_label;
        fanin1_label = NULL;
    }
    if(form_layout != NULL)
    {
        delete form_layout;
        form_layout = NULL;
    }
    if(group_box != NULL)
    {
        delete group_box;
        group_box = NULL;
    }
}

void ComputerPage::setLanguage() {
    group_box->setTitle(tr("%1").arg(title_context));
}

void ComputerPage::initUI(bool cpu)
{
    group_box = new QGroupBox();
    group_box->setStyleSheet("QGroupBox{border: 1px solid #e0e0e0;border-radius: 2px;margin-top: 15px;font-size:14px;}QGroupBox:title{subcontrol-origin: margin;subcontrol-position: top left;padding: 6px 3px;color: #00609a;font-family: 方正黑体_GBK;font-weight:bold;}");

    QFont group_box_font = group_box->font();
    group_box_font.setBold(true);
    group_box->setFont(group_box_font);
    group_box->setFixedWidth(720);

    form_layout = new QFormLayout();
//    form_layout->setSizeConstraint(QLayout::SetFixedSize);//frame will fixed with content's width
    form_layout->setSpacing(ITEMVSPACE);
    form_layout->setHorizontalSpacing(ITEMHSPACE);
    form_layout->setRowWrapPolicy(QFormLayout::DontWrapRows);
    form_layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    QMap<QString,QVariant>::iterator it; //遍历map
    if (sensor) {
        in0_label = new QLabel();
        in2_label = new QLabel();
        in3_label = new QLabel();
        in5_label = new QLabel();
        in6_label = new QLabel();
        tr1_label = new QLabel();
        tr2_label = new QLabel();
        tr3_label = new QLabel();
        tr4_label = new QLabel();
        tr5_label = new QLabel();
        tr6_label = new QLabel();
        fanin1_label = new QLabel();
        in0_label->setFixedHeight(ITEMHEIGHT);
        in2_label->setFixedHeight(ITEMHEIGHT);
        in3_label->setFixedHeight(ITEMHEIGHT);
        in5_label->setFixedHeight(ITEMHEIGHT);
        in6_label->setFixedHeight(ITEMHEIGHT);
        tr1_label->setFixedHeight(ITEMHEIGHT);
        tr2_label->setFixedHeight(ITEMHEIGHT);
        tr3_label->setFixedHeight(ITEMHEIGHT);
        tr4_label->setFixedHeight(ITEMHEIGHT);
        tr5_label->setFixedHeight(ITEMHEIGHT);
        tr6_label->setFixedHeight(ITEMHEIGHT);
        fanin1_label->setFixedHeight(ITEMHEIGHT);
        for (it = info_map.begin(); it != info_map.end(); ++it ) {
            if(it.key() == "IN0") {
                in0_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), in0_label);
                page_height += in0_label->height();
            }
            else if(it.key() == "IN2") {
                in2_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), in2_label);
                page_height += in2_label->height();
            }
            else if(it.key() == "IN3") {
                in3_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), in3_label);
                page_height += in3_label->height();
            }
            else if(it.key() == "IN5") {
                in5_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), in5_label);
                page_height += in5_label->height();
            }
            else if(it.key() == "IN6") {
                in6_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), in6_label);
                page_height += in6_label->height();
            }
            else if(it.key() == "TR1") {
                tr1_label->setText(it.value().toString());
                form_layout->addRow("ATX_3V3", tr1_label);
                page_height += tr1_label->height();
            }
            else if(it.key() == "TR2") {
                tr2_label->setText(it.value().toString());
                form_layout->addRow("ATX_5V", tr2_label);
                page_height += tr2_label->height();
            }
            else if(it.key() == "TR3") {
                tr3_label->setText(it.value().toString());
                form_layout->addRow("ATX_12V", tr3_label);
                page_height += tr3_label->height();
            }
            else if(it.key() == "TR4") {
                tr4_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), tr4_label);
                page_height += tr4_label->height();
            }
            else if(it.key() == "TR5") {
                tr5_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), tr5_label);
                page_height += tr5_label->height();
            }
            else if(it.key() == "TR6") {
                tr6_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), tr6_label);
                page_height += tr6_label->height();
            }
            else if(it.key() == "FANIN1") {
                fanin1_label->setText(it.value().toString());
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), fanin1_label);
                page_height += fanin1_label->height();
            }
            page_height += ITEMVSPACE;
        }
    }
    else {
        for (it = info_map.begin(); it != info_map.end(); ++it ) {
            if(it.key() == "uptime")
            {
                time_label = new QLabel();
                int time_value = it.value().toInt();
                int hour_value = time_value/60;
                int minutes_value =time_value%60;
                if(hour_value < 1)
                {
                    time_label->setText(QString::number(minutes_value) + tr(" Minutes"));//分钟
                }
                else
                {
                    time_label->setText(QString::number(hour_value) + tr(" Hours ") + QString::number(minutes_value) + tr(" Minutes"));//小时 分钟
                }
                time_label->setFixedHeight(ITEMHEIGHT);
                form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), time_label);
                page_height += time_label->height();
            }
            else {
                QString valueStr = it.value().toString().trimmed();
                if (QString::compare(valueStr, "UNKOWN", Qt::CaseInsensitive) == 0 || QString::compare(valueStr, "UNKNOWN", Qt::CaseInsensitive) == 0) {//for arm memory
                    //do nothing
                }
                else if (it.key().length() > 0 && valueStr.length() > 0) {//20161228
                    QLabel *label = new QLabel();
                    label_list.append(label);
                    if (it.key() == "cpu_cores") {
                        label->setText(tr("%1 cores").arg(valueStr));
                    }
                    else if (it.key() == "CpuVersion" && valueStr.contains("v1.0")) {
                        label->setText(tr("%1 64bit").arg(valueStr));
                    }
                    else {
                        if (QString::compare(valueStr, "1500a v1.0 64 bits", Qt::CaseInsensitive) == 0)//2017
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        else if (QString::compare(valueStr, "phytium", Qt::CaseInsensitive) == 0)//2017
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        else if (QString::compare(valueStr, "4 cores", Qt::CaseInsensitive) == 0)//2017
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        else if (QString::compare(valueStr, "4 thread/core", Qt::CaseInsensitive) == 0)//2017
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        else if (QString::compare(valueStr, "32bit", Qt::CaseInsensitive) == 0)//2017
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        else if (QString::compare(valueStr, "64bit", Qt::CaseInsensitive) == 0)//2017
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        else if (QString::compare(valueStr, "Ethernet interface", Qt::CaseInsensitive) == 0) {
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        }
                        else if (QString::compare(valueStr, "Wireless interface", Qt::CaseInsensitive)  == 0) {
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        }
                        else if (QString::compare(valueStr, "YHKylin community", Qt::CaseInsensitive)  == 0) {
                            label->setText(tr("%1").arg(this->translatorSwitch(valueStr)));
                        }
                        else
                        {
                            QFont ft;
                            QFontMetrics fm(ft);
                            QString elided_text = fm.elidedText(tr("%1").arg(valueStr), Qt::ElideRight, 400);
                            label->setText(elided_text);
                            if(elided_text.endsWith("…"))
                                label->setToolTip(tr("%1").arg(valueStr));
//                            label->setText(tr("%1").arg(valueStr));
                        }
                    }
                    label->setFixedHeight(ITEMHEIGHT); 
                    form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), label);
                    page_height += label->height();
                }
            }
            page_height += ITEMVSPACE;
        }
    }


    if (cpu) {
        if (systemProxy) {
            QStringList cpulist = systemProxy->get_cpufreq_scaling_governer_list_qt();
            if (cpulist.length() > 0) {
                ondemand_radio = new QRadioButton();
                ondemand_radio->setFocusPolicy(Qt::NoFocus);
                ondemand_radio->setFixedHeight(ITEMHEIGHT);
                ondemand_radio->setText(tr("Ondemand"));
                ondemand_radio->setObjectName("ondemandradio");
                ondemand_radio->setChecked(false);
                ondemand_radio->hide();
                powersave_radio = new QRadioButton();
                powersave_radio->setFixedHeight(ITEMHEIGHT);
                powersave_radio->setFocusPolicy(Qt::NoFocus);
                powersave_radio->setText(tr("Powersave"));
                powersave_radio->setObjectName("powersaveradio");
                powersave_radio->setChecked(false);
                powersave_radio->hide();
                performance_radio = new QRadioButton();
                performance_radio->setFixedHeight(ITEMHEIGHT);
                performance_radio->setFocusPolicy(Qt::NoFocus);
                performance_radio->setText(tr("Performance"));
                performance_radio->setObjectName("performanceradio");
                performance_radio->setChecked(false);
                performance_radio->hide();
                connect(ondemand_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
                connect(powersave_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
                connect(performance_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
                layout = new QHBoxLayout();
                layout->setSpacing(10);
                layout->addWidget(ondemand_radio);
                layout->addWidget(powersave_radio);
                layout->addWidget(performance_radio);
                layout->addStretch();

                QString cur_cpu = systemProxy->get_current_cpufreq_scaling_governer_qt();
                QList<QString>::Iterator it = cpulist.begin(), itend = cpulist.end();
                bool showed = false;
                for(;it != itend; it++)
                {
                    if(*it == "ondemand") {
                        if (cur_cpu == *it) {
                            ondemand_radio->setChecked(true);
                            powersave_radio->setChecked(false);
                            performance_radio->setChecked(false);
                        }
                        ondemand_radio->show();
                        showed = true;
                    }
                    else if(*it == "powersave") {
                        if (cur_cpu == *it) {
                            powersave_radio->setChecked(true);
                            ondemand_radio->setChecked(false);
                            performance_radio->setChecked(false);
                        }
                        powersave_radio->show();
                        showed = true;
                    }
                    else if(*it == "performance") {
                        if (cur_cpu == *it) {
                            performance_radio->setChecked(true);
                            ondemand_radio->setChecked(false);
                            powersave_radio->setChecked(false);
                        }
                        performance_radio->show();
                        showed = true;
                    }
                }
                if (showed) {
                    form_layout->addRow(tr("CPU FM mode"), layout);
                    page_height += ITEMHEIGHT;
                }
            }
        }
    }

    page_height += ITEMVSPACE*2;//every groupbox has tow separate line
    page_height += 30;
    page_height += ITEMHSPACE;//ContentsMargin's height
    info_map.clear(); //清空map

    group_box->setLayout(form_layout);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(group_box);
    layout->setMargin(0);
    layout->setContentsMargins(ITEMHSPACE, ITEMHSPACE, 0, 0);
    setLayout(layout);

    if(!vendor.isEmpty())
    {
        logo_label = new QLabel(this);
        logo_label->setAutoFillBackground(true);
        logo_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
        QPixmap label_pixmap(":/vendor/res/manufacturer/" + vendor + ".jpg");
        if (label_pixmap.isNull())
        {
//            label_pixmap = QPixmap(":/vendor/res/manufacturer/UBUNTUKYLIN.jpg");
            label_pixmap = QPixmap("");
        }
        logo_label->setPixmap(label_pixmap);
        logo_label->setFixedSize(label_pixmap.size());
        logo_label->setGeometry(QRect(720 - logo_label->width(), 40, logo_label->width(), logo_label->height()));
        logo_label->setMask(label_pixmap.mask());
//        QImage image(":/vendor/res/manufacturer/UBUNTUKYLIN.jpg");
//        if (!image.isNull()) {
//            image = image.scaled(logo_label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//            logo_label->setPixmap(QPixmap::fromImage(image));
//        }
//        logo_label->setGeometry(QRect(720 - logo_label->width(), 40, logo_label->width(), logo_label->height()));
    }

    this->setLanguage();
}

void ComputerPage::setRadioButtonRowStatus()
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "ondemandradio") {
        systemProxy->adjust_cpufreq_scaling_governer_qt("ondemand");
    }
    else if(obj_name == "powersaveradio") {
        systemProxy->adjust_cpufreq_scaling_governer_qt("powersave");
    }
    else if(obj_name == "performanceradio") {
        systemProxy->adjust_cpufreq_scaling_governer_qt("performance");
    }
}


void ComputerPage::resetTimeValue(QString value)
{
    time_label->setText(value);
}

void ComputerPage::resetSensor(QMap<QString, QVariant> sensormap)
{
    if (sensor) {
        QMap<QString,QVariant>::iterator it; //遍历map
        for (it = sensormap.begin(); it != sensormap.end(); ++it ) {
            if(it.key() == "IN0") {
                if (in0_label)
                    in0_label->setText(it.value().toString());
            }
            else if(it.key() == "IN2") {
                if (in2_label)
                    in2_label->setText(it.value().toString());
            }
            else if(it.key() == "IN3") {
                if (in3_label)
                    in3_label->setText(it.value().toString());
            }
            else if(it.key() == "IN5") {
                if (in5_label)
                    in5_label->setText(it.value().toString());
            }
            else if(it.key() == "IN6") {
                if (in6_label)
                    in6_label->setText(it.value().toString());
            }
            else if(it.key() == "TR1") {
                if (tr1_label)
                    tr1_label->setText(it.value().toString());
            }
            else if(it.key() == "TR2") {
                if (tr2_label)
                    tr2_label->setText(it.value().toString());
            }
            else if(it.key() == "TR3") {
                if (tr3_label)
                    tr3_label->setText(it.value().toString());
            }
            else if(it.key() == "TR4") {
                if (tr4_label)
                    tr4_label->setText(it.value().toString());
            }
            else if(it.key() == "TR5") {
                if (tr5_label)
                    tr5_label->setText(it.value().toString());
            }
            else if(it.key() == "TR6") {
                if (tr6_label)
                    tr6_label->setText(it.value().toString());
            }
            else if(it.key() == "FANIN1") {
                if (fanin1_label)
                    fanin1_label->setText(it.value().toString());
            }
        }
    }
}

QString ComputerPage::translatorSwitch(QString orgStr)
{
    if(orgStr == "MulProduct")//声卡型号
        return tr("Audio Model");
    else if(orgStr == "MulVendor")//制造商
        return tr("Vendor");
    else if(orgStr == "MulBusinfo")//总线地址
        return tr("Bus Address");
    else if(orgStr == "MulDrive")//声卡驱动
        return tr("Audio Driver");

    else if(orgStr == "POWER_SUPPLY_NAME")//设备名
        return tr("Device Name");
    else if(orgStr == "POWER_SUPPLY_MANUFACTURER")//发行商
        return tr("Manufacturer");
//    else if(orgStr == "POWER_SUPPLY_CAPACITY")//
//        return tr("POWER_SUPPLY_CAPACITY");
//    else if(orgStr == "POWER_SUPPLY_CYCLE_COUNT")//
//        return tr("POWER_SUPPLY_CYCLE_COUNT");
//    else if(orgStr == "POWER_SUPPLY_POWER_NOW")//
//        return tr("POWER_SUPPLY_POWER_NOW");
//    else if(orgStr == "POWER_SUPPLY_PRESENT")//
//        return tr("POWER_SUPPLY_PRESENT");
//    else if(orgStr == "POWER_SUPPLY_STATUS")//
//        return tr("POWER_SUPPLY_STATUS");
//    else if(orgStr == "POWER_SUPPLY_VOLTAGE_MIN_DESIGN")//
//        return tr("POWER_SUPPLY_VOLTAGE_MIN_DESIGN");
    //    POWER_SUPPLY_CAPACITY_LEVEL
    //    POWER_SUPPLY_CHARGE_FULL
    //    POWER_SUPPLY_CHARGE_FULL_DESIGN
    //    POWER_SUPPLY_CHARGE_NOW
    //    POWER_SUPPLY_CURRENT_NOW
    //    POWER_SUPPLY_PROP_STATUS
    //    POWER_SUPPLY_PROP_CHARGE_TYPE
    //    POWER_SUPPLY_PROP_HEALTH
    //    POWER_SUPPLY_PROP_PRESENT,
    //    POWER_SUPPLY_PROP_TECHNOLOGY,
    //    POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
    //    POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
    //    POWER_SUPPLY_PROP_VOLTAGE_NOW,
    //    POWER_SUPPLY_PROP_CAPACITY,
    //    POWER_SUPPLY_PROP_CURRENT_NOW,
    //    POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
    //    POWER_SUPPLY_PROP_TEMP,
    //    POWER_SUPPLY_PROP_SYSTEM_TEMP_LEVEL
    //    POWER_SUPPLY_ATTR
    //    POWER_SUPPLY_CURRENT_MAX
    //    SEQNUM
    //    POWER_SUPPLY_CHARGING_ENABLED
    //    POWER_SUPPLY_CHARGE_TYPE
    //    POWER_SUPPLY_HEALTH
    //    POWER_SUPPLY_VOLTAGE_MAX_DESIGN
    //    POWER_SUPPLY_TEMP
    //    POWER_SUPPLY_SYSTEM_TEMP_LEVEL
    else if(orgStr == "POWER_SUPPLY_MODEL_NAME")//型号
        return tr("Model");
    else if(orgStr == "POWER_SUPPLY_TECHNOLOGY")//技术
        return tr("Technology");
    else if(orgStr == "POWER_SUPPLY_VOLTAGE_NOW")//电压
        return tr("Voltage");
    else if(orgStr == "POWER_SUPPLY_ENERGY_FULL_DESIGN")//能量（设计）
        return tr("Energy Designed");
    else if(orgStr == "POWER_SUPPLY_ENERGY_FULL")//满时能量
        return tr("Energy Full");
    else if(orgStr == "POWER_SUPPLY_ENERGY_NOW")//能量
        return tr("Energy Now");
    else if(orgStr == "POWER_SUPPLY_SERIAL_NUMBER")//序列号
        return tr("Serial Number");

    else if(orgStr == "BoaVendor")//主板型号
        return tr("Motherboard Model");
    else if(orgStr == "BoaProduct")//主板产商
        return tr("Motherboard Vendor");
    else if(orgStr == "BoaSerial")//序列号
        return tr("Serial Number");
    else if(orgStr == "BioVendor")//BIOS产商
        return tr("BIOS Vendor");
    else if(orgStr == "BioVersion")//BIOS版本
        return tr("BIOS Version");
    else if(orgStr == "BioRelease")//发布日期
        return tr("Release Date");

    else if(orgStr == "DvdProduct")//光驱型号
        return tr("CD-ROM Model");
    else if(orgStr == "DvdVendor")//制造商
        return tr("Vendor");
    else if(orgStr == "DvdName")//设备名称
        return tr("Device Name");
    else if(orgStr == "DvdFw")//固件版本
        return tr("Firmware Version");
    else if(orgStr == "DvdSerial")//序列号
        return tr("Serial Number");



    else if(orgStr == "CpuVersion")//处理器：
        return tr("CPU");
    else if(orgStr == "CpuVendor")//制造商：
        return tr("Vendor");
    else if(orgStr == "CpuSerial")//序列号：
        return tr("Serial Number");
    else if(orgStr == "CpuSlot")//插座/插槽：
        return tr("Socket/Slot");
    else if(orgStr == "CpuCapacity")//最大主频：
        return tr("Maximum Frequency");
    else if(orgStr == "CpuSize")//当前主频：
        return tr("Current Frequency");
    else if(orgStr == "CpuClock")//前端总线：
        return tr("FSB");
    else if(orgStr == "cpu_cores")//核心数目：
        return tr("Core Number");
    else if(orgStr == "cpu_siblings")//线程
        return tr("Thread");
    else if(orgStr == "clflush_size")//一级缓存：
        return tr("L1 Cache");
    else if(orgStr == "cache_size")//二级缓存：
        return tr("L2 Cache");


//    else if(orgStr == "1500a v1.0 64 bits")//1500a v1.0 64位
//        return tr("1500a v1.0 64 bits");
    else if(orgStr == "phytium")//飞腾
        return tr("phytium");
    else if(orgStr == "4 cores")//4核
        return tr("4 cores");
    else if(orgStr == "4 thread/core")//4线程/核
        return tr("4 thread/core");


    else if(orgStr == "desktopenvironment")//桌面环境
        return tr("Desktop Environment");
    else if(orgStr == "cpu")
        return tr("CPU");
    else if(orgStr == "hostname")
        return tr("Host Name");
    else if(orgStr == "ram")
        return tr("Memery Capacity");
    else if(orgStr == "terminal")
        return tr("Terminal");
    else if(orgStr == "distribution")//发行版
        return tr("Distribution");
    else if(orgStr == "language")//语言
        return tr("Language");
    else if(orgStr == "currrent_user")//当前用户
        return tr("User");
    else if(orgStr == "home_path")//用户主目录
        return tr("Home Folder");

    else if(orgStr == "Host bridge")//主桥
        return tr("Host bridge");
    else if(orgStr == "VGA compatible controller")//VGA兼容控制器
        return tr("VGA Model");
    else if(orgStr == "USB controller")//USB控制器
        return tr("USB Model");
    else if(orgStr == "Communication controller")//通信控制器
        return tr("Communication Model");
    else if(orgStr == "Ethernet controller")//以太网控制器
        return tr("Ethernet Model");
    else if(orgStr == "Audio device")//音频设备
        return tr("Audio Model");
    else if(orgStr == "PCI bridge")//PCI桥
        return tr("PCI bridge");
    else if(orgStr == "ISA bridge")//ISA桥
        return tr("ISA bridge");
    else if(orgStr == "SATA controller")//SATA控制器
        return tr("SATA Model");
    else if(orgStr == "SMBus")//系统管理总线
        return tr("SMBus");
    else if(orgStr == "System peripheral")//系统外围
        return tr("System peripheral");
    else if(orgStr == "driver in use")//使用的驱动
        return tr("Driver in use");
    else if(orgStr == "existing drivers")//可选的驱动
        return tr("existing drivers");
    else if(orgStr == "IDE interface")//IDE接口
        return tr("IDE interface");
    else if(orgStr == "Signal processing controller")//信号处理控制器
        return tr("SP controller");
    else if(orgStr == "Network controller")//网络控制器
        return tr("Network controller");
    else if(orgStr == "Multimedia audio controller")//多媒体音频控制器
        return tr("Multimedia audio controller");


    else if(orgStr == "DiskProduct")//硬盘型号：
        return tr("HDD Model");
    else if(orgStr == "DiskVendor")//硬盘厂商：
        return tr("HDD Vendor");
    else if(orgStr == "DiskCapacity")//硬盘容量：
        return tr("HDD Capacity");
    else if(orgStr == "DiskName")//设备名称：
        return tr("Device Name");
    else if(orgStr == "DiskFw")//固件版本：
        return tr("Firmware Version");
    else if(orgStr == "DiskSerial")//序列号：
        return tr("Serial Number");

    else if(orgStr == "MemSlot")//插槽号：
        return tr("Slot Number");
    else if(orgStr == "MemProduct")//内存型号：
        return tr("Memory Model");
    else if(orgStr == "MemVendor")//制造商：
        return tr("Vendor");
    else if(orgStr == "MemSerial")//序列号：
        return tr("Serial Number");
    else if(orgStr == "MemSize")//内存大小：
        return tr("Memory Size");
    else if(orgStr == "MemWidth")//数据宽度：
        return tr("Data Width");
    else if(orgStr == "MemInfo")//内存条信息：
        return tr("Memory Info");

    else if(orgStr == "Vga_product")//显卡型号：
        return tr("Graphics Card Model");
    else if(orgStr == "Mon_chip")//当前显卡：
        return tr("Current Graphics Card");
    else if(orgStr == "Vga_vendor")//显卡制造商：
        return tr("Graphics Card Vendor");
    else if(orgStr == "Vga_Drive")//显卡驱动：
        return tr("Graphics Driver");
    else if(orgStr == "Vga_businfo")//显卡总线地址：
        return tr("Bus Address");
    else if(orgStr == "Mon_gamma")//伽马值
        return tr("Gamma");
    else if(orgStr == "Mon_in")//屏幕尺寸（英寸）
        return tr("Screen Size(inch)");
    else if(orgStr == "Mon_maxmode")//最大分辨率
        return tr("Max Resolution");
    else if(orgStr == "Mon_output")//当前接口
        return tr("Current Interface");
    else if(orgStr == "Mon_product")//显示器型号：
        return tr("Monitor Model");
    else if(orgStr == "Mon_size")//可视面积
        return tr("Visual Area");
    else if(orgStr == "Mon_support")//支持接口
        return tr("Support Interface");
    else if(orgStr == "Mon_vendor")//显示器制造商
        return tr("Monitor Manufacturers");
    else if(orgStr == "Mon_week")//生产日期_周
        return tr("Date of production/Week");
    else if(orgStr == "Mon_year")//生产日期_年
        return tr("Date of production/Year");


    else if(orgStr == "NetVendor")//制造商：
        return tr("Vendor");
    else if(orgStr == "NetProduct")//网卡型号：
        return tr("NIC Model");
    else if(orgStr == "NetDrive")//有线网卡驱动：
        return tr("NIC Driver");
    else if(orgStr == "NetBusinfo")//总线地址：
        return tr("Bus Address");
    else if(orgStr == "NetLogicalname")//设备名称：
        return tr("Device Name");
    else if(orgStr == "NetIp")//IP地址：
        return tr("IP Address");
    else if(orgStr == "NetSerial")//MAC地址：
        return tr("Mac Address");
    else if(orgStr == "NetLink")//连接状态：
        return tr("Connection Status");
    else if(orgStr == "NetCapacity")//最大带宽：
        return tr("Max Bandwidth");
    else if(orgStr == "WlanVendor")//制造商：
        return tr("Vendor");
    else if(orgStr == "WlanDrive")//无线网卡驱动：
        return tr("WLan NIC Driver");
    else if(orgStr == "WlanProduct")//网卡型号：
        return tr("WLan NIC Model");
    else if(orgStr == "WlanBusinfo")//总线地址：
        return tr("Bus Address");
    else if(orgStr == "WlanLogicalname")//设备名称：
        return tr("Device Name:");
    else if(orgStr == "WlanSerial")//序列号：
        return tr("Serial Number");
    else if(orgStr == "WlanIp")//IP地址：
        return tr("IP Address");
    else if (orgStr == "VNIC") {
        return tr("VNIC");
    }
    else if (orgStr == "NetType") {
        return tr("NetType");
    }
    else if (orgStr == "Ethernet interface") {
        return tr("Ethernet interface");
    }
    else if (orgStr == "Wireless interface") {
        return tr("Wireless interface");
    }

    else if(orgStr == "ComVendor")//制造商：
        return tr("Vendor");
    else if(orgStr == "ComProduct")//电脑型号：
        return tr("Model");
    else if(orgStr == "ComVersion")//电脑版本：
        return tr("Version");
    else if(orgStr == "ComSerial")//序列号：
        return tr("Serial Number");
    else if(orgStr == "node")//主机名：
        return tr("Hostname");
    else if(orgStr == "uptime")//持续运行时间：
        return tr("Running Time");
    else if(orgStr == "system")//操作系统类型：
        return tr("OS Types");
    else if(orgStr == "osname")//操作系统版本：
        return tr("OS Version");
    else if(orgStr == "architecture")//系统位数：
        return tr("Kernel Bit");
    else if(orgStr == "release")//内核版本：
        return tr("Kernel Version");
    else if(orgStr == "machine")//内核架构：
        return tr("Kernel Arch");
    else if (orgStr == "32bit")
        return tr("32bit");
    else if (orgStr == "64bit" || orgStr == "64 bits")
        return tr("64bit");
    else if (orgStr == "YHKylin community")
        return tr("YHKylin community");

    else if(orgStr == "IN0")//内存参考电压
        return tr("Memory reference voltage");
    else if(orgStr == "IN2")//SATA控制器电压
        return tr("SATA controller voltage");
    else if(orgStr == "IN3")//内存电压
        return tr("Memory voltage");
    else if(orgStr == "IN5")//CPU管脚电压
        return tr("CPU pin voltage");
    else if(orgStr == "IN6")//桥片电压
        return tr("Bridge voltage");
    else if(orgStr == "TR4")//CPU核电压
        return tr("CPU core voltage");
    else if(orgStr == "TR5")//CPU温度
        return tr("CPU temperature");
    else if(orgStr == "TR6")//主板温度
        return tr("Motherboard temperature");
    else if(orgStr == "FANIN1")//CPU风扇转速
        return tr("CPU fan speed");
    else
        return orgStr;
}

//void ComputerPage::resizeEvent(QResizeEvent *event)
//{
//    //获取当前窗口高度
////    this->resize(700, page_height);
////    page_height = height();
//    QWidget::resizeEvent(event);
//}


