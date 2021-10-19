/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KAJSONDEF_H
#define KAJSONDEF_H

#define MI_MANUFACTURER "Manufacturer"  //整机制造商
#define MI_MACHINEMODEL "MachineModel"  //整机型号
#define MI_SERIALNUM "SerialNum"        //SN
#define MI_SYSTEMBITS "SystemBits"      //系统位数
#define MI_KERNELARCH "KernelArch"      //内核架构
#define MI_HOSTNAME "HostName"          //主机名
#define MI_OSVERSION "OSVersion"        //操作系统版本
#define MI_KERNELVERSION "KernelVersion"    //内核版本
#define MI_PROCESSOR "Processor"        //处理器
#define MI_MEMORY "Memory"              //内存
#define MI_MAINBOARD "MainBoard"        //主板
#define MI_HARDDISK "HardDisk"          //硬盘
#define MI_GRAPHICSCARD "GraphicsCard"  //显卡
#define MI_MONITOR "Monitor"            //显示器
#define MI_NETWORKCARD "NetworkCard"    //网卡
#define MI_SOUNDCARD "SoundCard"        //声卡

#define PSI_ROOT "processor"            //处理器根
#define PSI_PROCESSOR "processor"       //处理器
#define PSI_MANUFACTURER "manufacturer" //厂商
#define PSI_ARCH "architecture"         //架构
#define PSI_CORESNUM "cores_num"        //核心数目
#define PSI_CORESONLINE "cores_num_online"  //在线核心数目
#define PSI_THREADSNUM "threads_num"    //线程数
#define PSI_SLOT "slot"                 //插槽
#define PSI_FREQ "fref"                 //基准频率
#define PSI_FREQ_MAX "fref_max"         //最大核心主频
#define PSI_L1CACHE "L1_cache"          //一级缓存
#define PSI_L1DCACHE "L1d_cache"        //一级数据缓存
#define PSI_L1ICACHE "L1i_cache"        //一级指令缓存
#define PSI_L2CACHE "L2_cache"          //二级缓存
#define PSI_L3CACHE "L3_cache"          //三级缓存
#define PSI_INSTSET "instruction_set"   //指令集
#define PSI_USED "used"                 //占用率
#define PSI_EXTINSTSET "ext_instruction_set"   //扩展指令集

#define MMI_ROOT "memory"               //内存
#define MMI_SLOT "slot"                 //插槽
#define MMI_NAME "name"                 //名称
#define MMI_FREQ "freq"                 //当前频率
#define MMI_BUSWIDTH "bus_width"        //总线位宽
#define MMI_TYPE "type"                 //类型
#define MMI_DATAWIDTH "data_width"        //数据位宽
#define MMI_TOTALCAPACITY "total_capacity" //总容量
#define MMI_USEDCAPACITY "used_capacity"   //已用容量
#define MMI_SERIALNUM "serail_num"        //序列号
#define MMI_MANUFACTURER "manufacturer"   //制造商
#define MMI_MODEL "model"               //型号
#define MMI_SPEED "speed"               //速率
#define MMI_CONFIGSPEED "config_speed"  //配置速率
#define MMI_PIPE "pipe"                 //通道
#define MMI_ARRAYHANDLE "array_handle"  //数组程序
#define MMI_PARTNUMBER "partnum"        //部件号码
#define MMI_PHYSICALID "physicalid"     //物理ID

#define GSI_ROOT "graphics_card"           //显卡
#define GSI_MANUFACTURER "manufacturer"    //厂商
#define GSI_SUBSYSTEM "subsystem"          //子制造商
#define GSI_NAME "name"                    //名称
#define GSI_ISDISCRETE "is_discrete"       //是否为独显
#define GSI_CAPCITY "capcity"              //显存
#define GSI_MEMTYPE "mem_type"             //显存类型
#define GSI_MODEL "model"                  //型号
#define GSI_VERSION "version"              //版本
#define GSI_BITWIDTH "bit_width"           //位宽
#define GSI_IRQ "irq"                      //中断
#define GSI_FUNCTION "function"            //功能
#define GSI_CLOCK "clock"                  //时钟频率
#define GSI_DESC "description"             //描述
#define GSI_DRIVER "driver"                //驱动
#define GSI_DBUSINFO "dbusinfo"            //总线信息
#define GSI_IOPORT "io_port"               //I/O端口
#define GSI_MEMORY "memory"                //内存
#define GSI_PHYSICSID "physics_id"         //物理ID
#define GSI_DELAY "delay"                  //延迟
#define GSI_DEVICE "device"                //设备
#define GSI_CONFSTATUS "config_status"     //配置状态
#define GSI_DRIVERMODULE "driver_module"   //驱动模块
#define GSI_GDDRCAPACITY "gddr_capacity"   //GDDR容量
#define GSI_EGLVERSION "egl_version"       //EGL版本
#define GSI_EGLAPIS "egl_apis"             //EGL接口
#define GSI_GLVERSION "gl_version"         //GL版本
#define GSI_GLSLVERSION "glsl_version"     //GLSL版本

#define MBI_ROOT "mother_board"                 //主板
#define MBI_NAME "name"                         //主板名称
#define MBI_CHIPSET "chipset"                   //芯片组
#define MBI_SERIALNUM "serial_num"              //序列号
#define MBI_PUBDATE "publish_date"              //主板版本
#define MBI_VERSION "version"                   //主板版本
#define MBI_MANUFACTURER "manufacturer"         //主板制造商
#define MBI_BIOSMANUFACTURER "bios_manufacturer"  //BIOS制造商
#define MBI_BIOSVERSION "bios_version"            //BIOS版本

#define NWI_ROOT "network_card"         //网卡
#define NWI_NAME "Logical Name"         //网卡名称
#define NWI_TYPE "Description"          //类型（有线/无线）
#define NWI_MACADDR "Serial"            //MAC地址
#define NWI_CONNSPEED "Size"            //连接速度
#define NWI_MTU "mtu"                   //MTU
#define NWI_IPADDR "IP"                 //IP地址
#define NWI_SUBNETMASK "subnet_mask"    //子网掩码
#define NWI_GATEWAY "gateway"           //网关地址
#define NWI_DNSSERVER "dns_server"      //DNS服务器
#define NWI_RECVBYTES "recv_bytes"      //已接收字节
#define NWI_SENDBYTES "send_bytes"      //已发送字节
#define NWI_MANUFACTURER "Vendor"       //制造商
#define NWI_BUSADDR "Bus Info"          //总线地址
#define NWI_DRIVER "Driver"             //驱动
#define NWI_MODEL "Product"             //型号

#define HDI_ROOT "harddisk"             //硬盘
#define HDI_MANUFACTURER "manufacturer" //硬盘品牌
#define HDI_NAME "name"                 //名称
#define HDI_CAPACITY "capacity"         //容量
#define HDI_USEDTIMES "used_times"      //已使用次数
#define HDI_INTERFACE "interface"       //接口
#define HDI_ISMAINDISK "is_maindisk"    //主硬盘（是否）
#define HDI_ISSSD "is_ssd"              //硬盘类型（固态/机械）
#define HDI_SERIALNUM "serial_num"      //序列号
#define HDI_MODEL "model"               //型号
#define HDI_TRANSRATE "trans_rate"      //数据传输率
#define HDI_READSPEED "read_speed"      //磁盘读取速度
#define HDI_WRITESPEED "write_speed"    //磁盘写入速度
#define HDI_FIRMWAREVER "firmware_ver"  //固件版本

#define MNI_ROOT "monitor"              //显示器
#define MNI_MANUFACTURER "manufacturer" //显示器厂商
#define MNI_NAME "name"                 //名称
#define MNI_SIZE "size"                 //屏幕尺寸
#define MNI_RATIO "ratio"               //图像高宽比
#define MNI_RESOLUTION "resolution"     //分辨率
#define MNI_MAXAVARES "max_resolution"  //最大可用分辨率
#define MNI_ISMAIN "is_main"            //主显示器（是/否）
#define MNI_GAMMA "gamma"               //伽马值
#define MNI_INTERFACE "interface"       //当前接口
#define MNI_MODEL "model"               //型号
#define MNI_VISIBLEAREA "visible_area"  //可视面积
#define MNI_YEAR "year"                 //生产年
#define MNI_WEEK "week"                 //生产周

#define VCI_ROOT "voice_card"           //声卡
#define VCI_BUSADDR "Bus Info"          //总线地址
#define VCI_DRIVE "Driver"              //声卡驱动
#define VCI_MODEL "Model"               //声卡型号
#define VCI_MANUFACTURER "Vendor"       //制造商
#define VCI_NAME "Product"              //名称
#define VCI_CLOCK "Clock"               //时钟频率
#define VCI_BITWIDTH "Width"            //位宽

#define KBI_ROOT "key_board"            //键盘
#define KBI_DEVTYPE "dev_type"          //设备类型
#define KBI_NAME "name"                 //设备名称
#define KBI_DEVMODEL "dev_model"        //设备型号
#define KBI_MANUFACTURER "manufacturer" //制造商
#define KBI_DEVADDR "dev_addr"          //硬件地址
#define KBI_INTERFACE "interface"       //接口
#define KBI_DRIVER "driver"             //驱动

#define MSI_ROOT "mouse"                //鼠标
#define MSI_DEVTYPE "dev_type"          //设备类型
#define MSI_NAME "name"                 //设备名称
#define MSI_DEVMODEL "dev_model"        //设备型号
#define MSI_MANUFACTURER "manufacturer" //制造商
#define MSI_DEVADDR "dev_addr"          //硬件地址
#define MSI_INTERFACE "interface"       //接口
#define MSI_DRIVER "driver"             //驱动

#define BTI_ROOT "battery"              //电池
#define BTI_MANUFACTURER "manufacturer" //制造商
#define BTI_MODEL "model"               //型号
#define BTI_SERAILNUM "serailnum"       //序列号
#define BTI_TTE "time_to_empty"         //预计使用时间
#define BTI_USEDTIMES "used_times"      //使用次数
#define BTI_ENERGYFULL "energy_full"    //满电容量
#define BTI_ENERGY "energy"             //当前容量
#define BTI_STATE "state"               //状态
#define BTI_PERCENTAGE "percentage"     //电量

#define CDI_ROOT "cddrive"              //光驱
#define CDI_NAME "name"                 //名称
#define CDI_MANUFACTURER "manufacturer" //制造商
#define CDI_VERSION "version"           //版本
#define CDI_MODEL "model"               //型号
#define CDI_BUSINFO "businfo"           //总线信息
#define CDI_DRIVER "driver"             //驱动
#define CDI_SPEED "speed"               //速度
#define CDI_SERAILNUM "serailnum"       //序列号
#define CDI_DEVICENUM "devicenum"       //设备编号

#define CAI_ROOT "camera"               //摄像头
#define CAI_NAME "name"                 //设备名称
#define CAI_RESOLUTION "resolution"     //分辨率
#define CAI_MANUFACTURER "manufacturer" //制造商
#define CAI_MODEL "model"               //型号
#define CAI_INTERFACE "interface"       //接口
#define CAI_DRIVER "driver"             //驱动
#define CAI_TYPE "type"                 //类型
#define CAI_VERSION "version"           //版本
#define CAI_BUSINFO "businfo"           //总线信息
#define CAI_SPEED "speed"               //速度

#define BLI_ROOT "bluetooth"            //蓝牙
#define BLI_BUSADDR "bus_addr"          //总线地址
#define BLI_FUNCTION "function"         //功能
#define BLI_FREQ "freq"                 //频率
#define BLI_CONF "configuration"        //配置
#define BLI_DEVTYPE "dev_type"          //设备类型
#define BLI_ID "id"                     //ID号
#define BLI_DEVMODEL "dev_model"        //设备型号
#define BLI_RESOURCE "resource"         //资源
#define BLI_MANUFACTURER "manufacturer" //制造商
#define BLI_DEVVERSION "dev_version"    //设备版本
#define BLI_DATAWIDTH "data_width"      //数据宽度
#define BLI_NAME "name"                 //名称
#define BLI_DRIVER "driver"             //驱动
#define BLI_SPEED "speed"               //速度
#define BLI_SERIALNUM "serial_num"      //序列号
#define BLI_ADDRESS "address"           //蓝牙地址
#define BLI_LINKMODE "link_mode"        //连接模式
#define BLI_LINKPOLICY "link_policy"    //连接策略
#define BLI_PRODUCT "product"           //产品
#define BLI_CAPABILITIES "capabilities" //功能
#define BLI_BUS "bus"                   //总线
#define BLI_SCOMTU "scomtu"             // SCO MTU
#define BLI_ALCMTU "alcmtu"             //ALC MTU
#define BLI_PACKETTYPE "packettype"     //数据包类型
#define BLI_FEATURES "features"         //特征

#define FAI_ROOT "fan"                  //风扇
#define FAI_SPEED "speed"               //转速

#define DRIVE_INFO "drive_info"         //驱动信息
#define DRIVE_INFO_TYPE "drive_type"    //驱动类型
#define DRIVE_INFO_NAME "drive_name"    //驱动名称
#define DRIVE_INFO_VERSION "drive_version"    //驱动版本

#define DEVMONITOR_ROOT "device_monitor" //设备监测
#define DEVMONITOR_DEVTEMP "device_temps" //设备温度
#define DEVMONITOR_DEVTEMP_NAME "device_name" //设备名称
#define DEVMONITOR_DEVTEMP_VALUE "device_temp" //设备温度值
#define DEVMONITOR_DEVTEMP_HIGH "device_temp_high" //设备高温
#define DEVMONITOR_DEVTEMP_CRIT "device_temp_crit" //设备异常温
#define DEVMONITOR_DEVUSAGE "device_usage" //设备使用率
#define DEVMONITOR_DEVUSAGE_NAME "device_name" //设备名称
#define DEVMONITOR_DEVUSAGE_USED "device_usage_used" //设备使用率
#define DEVMONITOR_DEVUSAGE_TOTAL "device_usage_total" //使用总值

#define CPUFM_ROOT "cpu_fm" // cpu调频
#define CPUFM_AVERAGE_COREFREQ "cpu_corefreq" //当前cpu核心平均主频
#define CPUFM_MODELS "cpu_model_list" //cpu调频模式列表
#define CPUFM_MODEL_PERFORMANCE "performance" //性能模式
#define CPUFM_MODEL_POWERSAVE "powersave" //省电模式
#define CPUFM_MODEL_USERSPACE "userspace" //自定义
#define CPUFM_MODEL_SCHEDUTIL "schedutil" //均衡模式
#define CPUFM_MODEL_ONDEMAND "ondemand" //随需应变
#define CPUFM_MODEL_CONSERVATIVE "conservative" //保守模式
#define CPUFM_FREQS "cpu_freq_list" //cpu频率列表
#define CPUFM_CURFREQ "cur_freq" //cpu调频
#define CPUFM_CURFREQMODEL "cpu_curmodel" //cpu调频模式

#endif // KAJSONDEF_H
