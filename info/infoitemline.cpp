/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#include "infoitemline.h"

#include <QHBoxLayout>
#include <QObject>
#include <QDebug>

inline const QString covertKeyName(const QString &key)
{
    if(key == "MulProduct")//声卡型号
        return QString(QObject::tr("Audio Model"));
    else if(key == "MulVendor")//制造商
        return QString(QObject::tr("Vendor"));
    else if(key == "MulBusinfo")//总线地址
        return QString(QObject::tr("Bus Address"));
    else if(key == "MulDrive")//声卡驱动
        return QString(QObject::tr("Audio Driver"));

    else if(key == "POWER_SUPPLY_NAME")//设备名
        return QString(QObject::tr("Device Name"));
    else if(key == "POWER_SUPPLY_MANUFACTURER")//发行商
        return QString(QObject::tr("Manufacturer"));
//    else if(key == "POWER_SUPPLY_CAPACITY")//
//        return QString(QObject::tr("POWER_SUPPLY_CAPACITY");
//    else if(key == "POWER_SUPPLY_CYCLE_COUNT")//
//        return QString(QObject::tr("POWER_SUPPLY_CYCLE_COUNT");
//    else if(key == "POWER_SUPPLY_POWER_NOW")//
//        return QString(QObject::tr("POWER_SUPPLY_POWER_NOW");
//    else if(key == "POWER_SUPPLY_PRESENT")//
//        return QString(QObject::tr("POWER_SUPPLY_PRESENT");
//    else if(key == "POWER_SUPPLY_STATUS")//
//        return QString(QObject::tr("POWER_SUPPLY_STATUS");
//    else if(key == "POWER_SUPPLY_VOLTAGE_MIN_DESIGN")//
//        return QString(QObject::tr("POWER_SUPPLY_VOLTAGE_MIN_DESIGN");
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
    else if(key == "POWER_SUPPLY_MODEL_NAME")//型号
        return QString(QObject::tr("Model"));
    else if(key == "POWER_SUPPLY_TECHNOLOGY")//技术
        return QString(QObject::tr("Technology"));
    else if(key == "POWER_SUPPLY_VOLTAGE_NOW")//电压
        return QString(QObject::tr("Voltage"));
    else if(key == "POWER_SUPPLY_ENERGY_FULL_DESIGN")//能量（设计）
        return QString(QObject::tr("Energy Designed"));
    else if(key == "POWER_SUPPLY_ENERGY_FULL")//满时能量
        return QString(QObject::tr("Energy Full"));
    else if(key == "POWER_SUPPLY_ENERGY_NOW")//能量
        return QString(QObject::tr("Energy Now"));
    else if(key == "POWER_SUPPLY_SERIAL_NUMBER")//序列号
        return QString(QObject::tr("Serial Number"));

    else if(key == "BoaVendor")//主板型号
        return QString(QObject::tr("Motherboard Model"));
    else if(key == "BoaProduct")//主板产商
        return QString(QObject::tr("Motherboard Vendor"));
    else if(key == "BoaSerial")//序列号
        return QString(QObject::tr("Serial Number"));
    else if(key == "BioVendor")//BIOS产商
        return QString(QObject::tr("BIOS Vendor"));
    else if(key == "BioVersion")//BIOS版本
        return QString(QObject::tr("BIOS Version"));
    else if(key == "BioRelease")//发布日期
        return QString(QObject::tr("Release Date"));

    else if(key == "DvdProduct")//光驱型号
        return QString(QObject::tr("CD-ROM Model"));
    else if(key == "DvdVendor")//制造商
        return QString(QObject::tr("Vendor"));
    else if(key == "DvdName")//设备名称
        return QString(QObject::tr("Device Name"));
    else if(key == "DvdFw")//固件版本
        return QString(QObject::tr("Firmware Version"));
    else if(key == "DvdSerial")//序列号
        return QString(QObject::tr("Serial Number"));

    else if(key == "CpuVersion")//处理器：
        return QString(QObject::tr("CPU"));
    else if(key == "CpuVendor")//制造商：
        return QString(QObject::tr("Vendor"));
    else if(key == "CpuSerial")//序列号：
        return QString(QObject::tr("Serial Number"));
    else if(key == "CpuSlot")//插座/插槽：
        return QString(QObject::tr("Socket/Slot"));
    else if(key == "CpuCapacity")//最大主频：
        return QString(QObject::tr("Maximum Frequency"));
    else if(key == "CpuSize")//当前主频：
        return QString(QObject::tr("Current Frequency"));
    else if(key == "CpuClock")//前端总线：
        return QString(QObject::tr("FSB"));
    else if(key == "cpu_cores")//核心数目：
        return QString(QObject::tr("Core Number"));
    else if(key == "cpu_siblings")//线程
        return QString(QObject::tr("Thread"));
    else if(key == "clflush_size")//一级缓存：
        return QString(QObject::tr("L1 Cache"));
    else if(key == "cache_size")//二级缓存：
        return QString(QObject::tr("L2 Cache"));


//    else if(key == "1500a v1.0 64 bits")//1500a v1.0 64位
//        return QString(QObject::tr("1500a v1.0 64 bits");
    else if(key == "phytium")//飞腾
        return QString(QObject::tr("phytium"));
    else if(key == "4 cores")//4核
        return QString(QObject::tr("4 cores"));
    else if(key == "4 thread/core")//4线程/核
        return QString(QObject::tr("4 thread/core"));


    else if(key == "desktopenvironment")//桌面环境
        return QString(QObject::tr("Desktop Environment"));
    else if(key == "cpu")
        return QString(QObject::tr("CPU"));
    else if(key == "hostname")
        return QString(QObject::tr("Host Name"));
    else if(key == "ram")
        return QString(QObject::tr("Memery Capacity"));
    else if(key == "terminal")
        return QString(QObject::tr("Terminal"));
    else if(key == "distribution")//发行版
        return QString(QObject::tr("Distribution"));
    else if(key == "language")//语言
        return QString(QObject::tr("Language"));
    else if(key == "currrent_user")//当前用户
        return QString(QObject::tr("User"));
    else if(key == "home_path")//用户主目录
        return QString(QObject::tr("Home Folder"));

    else if(key == "Host bridge")//主桥
        return QString(QObject::tr("Host bridge"));
    else if(key == "VGA compatible controller")//VGA兼容控制器
        return QString(QObject::tr("VGA Model"));
    else if(key == "USB controller")//USB控制器
        return QString(QObject::tr("USB Model"));
    else if(key == "Communication controller")//通信控制器
        return QString(QObject::tr("Communication Model"));
    else if(key == "Ethernet controller")//以太网控制器
        return QString(QObject::tr("Ethernet Model"));
    else if(key == "Audio device")//音频设备
        return QString(QObject::tr("Audio Model"));
    else if(key == "PCI bridge")//PCI桥
        return QString(QObject::tr("PCI bridge"));
    else if(key == "ISA bridge")//ISA桥
        return QString(QObject::tr("ISA bridge"));
    else if(key == "SATA controller")//SATA控制器
        return QString(QObject::tr("SATA Model"));
    else if(key == "SMBus")//系统管理总线
        return QString(QObject::tr("SMBus"));
    else if(key == "System peripheral")//系统外围
        return QString(QObject::tr("System peripheral"));
    else if(key == "driver in use")//使用的驱动
        return QString(QObject::tr("Driver in use"));
    else if(key == "existing drivers")//可选的驱动
        return QString(QObject::tr("existing drivers"));
    else if(key == "IDE interface")//IDE接口
        return QString(QObject::tr("IDE interface"));
    else if(key == "Signal processing controller")//信号处理控制器
        return QString(QObject::tr("SP controller"));
    else if(key == "Network controller")//网络控制器
        return QString(QObject::tr("Network controller"));
    else if(key == "Multimedia audio controller")//多媒体音频控制器
        return QString(QObject::tr("Multimedia audio controller"));


    else if(key == "DiskProduct")//硬盘型号：
        return QString(QObject::tr("HDD Model"));
    else if(key == "DiskVendor")//硬盘厂商：
        return QString(QObject::tr("HDD Vendor"));
    else if(key == "DiskCapacity")//硬盘容量：
        return QString(QObject::tr("HDD Capacity"));
    else if(key == "DiskName")//设备名称：
        return QString(QObject::tr("Device Name"));
    else if(key == "DiskFw")//固件版本：
        return QString(QObject::tr("Firmware Version"));
    else if(key == "DiskSerial")//序列号：
        return QString(QObject::tr("Serial Number"));

    else if(key == "MemSlot")//插槽号：
        return QString(QObject::tr("Slot Number"));
    else if(key == "MemProduct")//内存型号：
        return QString(QObject::tr("Memory Model"));
    else if(key == "MemVendor")//制造商：
        return QString(QObject::tr("Vendor"));
    else if(key == "MemSerial")//序列号：
        return QString(QObject::tr("Serial Number"));
    else if(key == "MemSize")//内存大小：
        return QString(QObject::tr("Memory Size"));
    else if(key == "MemWidth")//数据宽度：
        return QString(QObject::tr("Data Width"));
    else if(key == "MemInfo")//内存条信息：
        return QString(QObject::tr("Memory Info"));

    else if(key == "Vga_product")//显卡型号：
        return QString(QObject::tr("Graphics Card Model"));
    else if(key == "Mon_chip")//当前显卡：
        return QString(QObject::tr("Current Graphics Card"));
    else if(key == "Vga_vendor")//显卡制造商：
        return QString(QObject::tr("Graphics Card Vendor"));
    else if(key == "Vga_Drive")//显卡驱动：
        return QString(QObject::tr("Graphics Driver"));
    else if(key == "Vga_businfo")//显卡总线地址：
        return QString(QObject::tr("Bus Address"));
    else if(key == "Mon_gamma")//伽马值
        return QString(QObject::tr("Gamma"));
    else if(key == "Mon_in")//屏幕尺寸（英寸）
        return QString(QObject::tr("Screen Size(inch)"));
    else if(key == "Mon_maxmode")//最大分辨率
        return QString(QObject::tr("Max Resolution"));
    else if(key == "Mon_output")//当前接口
        return QString(QObject::tr("Current Interface"));
    else if(key == "Mon_product")//显示器型号：
        return QString(QObject::tr("Monitor Model"));
    else if(key == "Mon_size")//可视面积
        return QString(QObject::tr("Visual Area"));
    else if(key == "Mon_support")//支持接口
        return QString(QObject::tr("Support Interface"));
    else if(key == "Mon_vendor")//显示器制造商
        return QString(QObject::tr("Monitor Manufacturers"));
    else if(key == "Mon_week")//生产日期_周
        return QString(QObject::tr("Date of production/Week"));
    else if(key == "Mon_year")//生产日期_年
        return QString(QObject::tr("Date of production/Year"));


    else if(key == "NetVendor")//制造商：
        return QString(QObject::tr("Vendor"));
    else if(key == "NetProduct")//网卡型号：
        return QString(QObject::tr("NIC Model"));
    else if(key == "NetDrive")//有线网卡驱动：
        return QString(QObject::tr("NIC Driver"));
    else if(key == "NetBusinfo")//总线地址：
        return QString(QObject::tr("Bus Address"));
    else if(key == "NetLogicalname")//设备名称：
        return QString(QObject::tr("Device Name"));
    else if(key == "NetIp")//IP地址：
        return QString(QObject::tr("IP Address"));
    else if(key == "NetSerial")//MAC地址：
        return QString(QObject::tr("Mac Address"));
    else if(key == "NetLink")//连接状态：
        return QString(QObject::tr("Connection Status"));
    else if(key == "NetCapacity")//最大带宽：
        return QString(QObject::tr("Max Bandwidth"));
    else if(key == "WlanVendor")//制造商：
        return QString(QObject::tr("Vendor"));
    else if(key == "WlanDrive")//无线网卡驱动：
        return QString(QObject::tr("WLan NIC Driver"));
    else if(key == "WlanProduct")//网卡型号：
        return QString(QObject::tr("WLan NIC Model"));
    else if(key == "WlanBusinfo")//总线地址：
        return QString(QObject::tr("Bus Address"));
    else if(key == "WlanLogicalname")//设备名称：
        return QString(QObject::tr("Device Name:"));
    else if(key == "WlanSerial")//序列号：
        return QString(QObject::tr("Serial Number"));
    else if(key == "WlanIp")//IP地址：
        return QString(QObject::tr("IP Address"));
    else if (key == "VNIC") {
        return QString(QObject::tr("VNIC"));
    }
    else if (key == "NetType") {
        return QString(QObject::tr("NetType"));
    }
    else if (key == "Ethernet interface") {
        return QString(QObject::tr("Ethernet interface"));
    }
    else if (key == "Wireless interface") {
        return QString(QObject::tr("Wireless interface"));
    }

    else if(key == "ComVendor")//制造商：
        return QString(QObject::tr("Vendor"));
    else if(key == "ComProduct")//电脑型号：
        return QString(QObject::tr("Model"));
    else if(key == "ComVersion")//电脑版本：
        return QString(QObject::tr("Version"));
    else if(key == "ComSerial")//序列号：
        return QString(QObject::tr("Serial Number"));
    else if(key == "node")//主机名：
        return QString(QObject::tr("Hostname"));
    else if(key == "uptime")//持续运行时间：
        return QString(QObject::tr("Running Time"));
    else if(key == "system")//操作系统类型：
        return QString(QObject::tr("OS Types"));
    else if(key == "osname")//操作系统版本：
        return QString(QObject::tr("OS Version"));
    else if(key == "architecture")//系统位数：
        return QString(QObject::tr("Kernel Bit"));
    else if(key == "release")//内核版本：
        return QString(QObject::tr("Kernel Version"));
    else if(key == "machine")//内核架构：
        return QString(QObject::tr("Kernel Arch"));
    else if (key == "32bit")
        return QString(QObject::tr("32bit"));
    else if (key == "64bit" || key == "64 bits")
        return QString(QObject::tr("64bit"));
    else if (key == "YHKylin community")
        return QString(QObject::tr("YHKylin community"));

    else if(key == "IN0")//内存参考电压
        return QString(QObject::tr("Memory reference voltage"));
    else if(key == "IN2")//SATA控制器电压
        return QString(QObject::tr("SATA controller voltage"));
    else if(key == "IN3")//内存电压
        return QString(QObject::tr("Memory voltage"));
    else if(key == "IN5")//CPU管脚电压
        return QString(QObject::tr("CPU pin voltage"));
    else if(key == "IN6")//桥片电压
        return QString(QObject::tr("Bridge voltage"));
    else if(key == "TR4")//CPU核电压
        return QString(QObject::tr("CPU core voltage"));
    else if(key == "TR5")//CPU温度
        return QString(QObject::tr("CPU temperature"));
    else if(key == "TR6")//主板温度
        return QString(QObject::tr("Motherboard temperature"));
    else if(key == "FANIN1")//CPU风扇转速
        return QString(QObject::tr("CPU fan speed"));
    else
        return key;
}


InfoItemLine::InfoItemLine(QFrame *parent)
    : QFrame(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(36);

    m_key = "";
    m_keyLabel = new QLabel;
    m_valueLabel = new QLabel;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(20, 0, 10, 0);
    mainLayout->addWidget(m_keyLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_valueLabel);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

InfoItemLine::~InfoItemLine()
{
    delete m_keyLabel;
    delete m_valueLabel;
}

void InfoItemLine::setInfoKey(const QString &key)
{
    const QString name = covertKeyName(key);
    m_keyLabel->setText(name);
    m_key = key;

    QFont ft;
    QFontMetrics fm(ft);
    this->keyWidth = fm.width(key);
}

void InfoItemLine::setInfoValue(const QString &value)
{
    int maxWidth = this->width() - keyWidth - 40;

    QFont ft;
    QFontMetrics fm(ft);
    QString elided_text = fm.elidedText(value, Qt::ElideRight, maxWidth);
    m_valueLabel->setText(elided_text);
    if(elided_text.endsWith("…"))
        m_valueLabel->setToolTip(value);
}

QString InfoItemLine::getLineKey()
{
    return m_key;
}
