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
#include <QGroupBox>
#include <QFormLayout>

ComputerPage::ComputerPage(QWidget *parent, QString title/*, QString manufacturer*/) :
    QWidget(parent), title_context(title)/*, vendor(manufacturer)*/
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    page_height = 0;
    title_label = NULL;
    time_label =NULL;
    logo_label = NULL;
    group_box = NULL;
    form_layout = NULL;
}

ComputerPage::~ComputerPage()
{
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
}

void ComputerPage::setLanguage() {
    group_box->setTitle(tr("%1").arg(title_context));
}

void ComputerPage::initUI()
{
    group_box = new QGroupBox();

    if(!vendor.isEmpty())
    {
        logo_label = new QLabel(this);
        logo_label->setAutoFillBackground(true);
        logo_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
        QPixmap label_pixmap(":/vendor/res/manufacturer/" + vendor + ".jpg");
        if (label_pixmap.isNull())
        {
            label_pixmap = QPixmap(":/vendor/res/manufacturer/UBUNTUKYLIN.jpg");
        }
        logo_label->setPixmap(label_pixmap);
        logo_label->setFixedSize(label_pixmap.size());
        logo_label->setGeometry(QRect(720 - logo_label->width(), 40, logo_label->width(), logo_label->height()));
//        logo_label->show();
////        logo_label->move(720 - logo_label->width(), 40);
    }

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
    for ( it = info_map.begin(); it != info_map.end(); ++it ) {
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
        else{
            QLabel *label = new QLabel();
            label->setText(tr("%1").arg(it.value().toString()));
            label->setFixedHeight(ITEMHEIGHT);
            form_layout->addRow(tr("%1").arg(this->translatorSwitch(it.key())), label);
            page_height += label->height();
        }
        page_height += ITEMVSPACE;
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

    this->setLanguage();
}

void ComputerPage::resetTimeValue(QString value)
{
    time_label->setText(value);
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


    else if(orgStr == "desktopenvironment")//桌面环境
        return tr("Desktop Environment");
    else if(orgStr == "cpu")
        return tr("CPU");
    else if(orgStr == "hostname")
        return tr("Host Name");
    else if(orgStr == "ram")
        return tr("Memery Capacity");
    else if(orgStr == "shell")
        return tr("Shell");
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


    else if(orgStr == "NetVendor")//有线网卡型号：
        return tr("NIC Model");
    else if(orgStr == "NetProduct")//制造商：
        return tr("Vendor");
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
    else if(orgStr == "platform")//操作系统版本：
        return tr("OS Version");
    else if(orgStr == "architecture")//系统位数：
        return tr("Kernel Bit");
    else if(orgStr == "release")//内核版本：
        return tr("Kernel Version");
    else if(orgStr == "machine")//内核架构：
        return tr("Kernel Arch");
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


