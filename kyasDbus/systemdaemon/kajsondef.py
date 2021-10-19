#!/usr/bin/python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
 # Copyright (C) 2021 KylinSoft Co., Ltd.
 #
 # Authors:
 #  Yang Min yangmin@kylinos.cn
 #
 # This program is free software; you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
### END LICENSE

from kacmdtool import KACmdTool

###Machine Outline
MI_MANUFACTURER = "Manufacturer"  #整机制造商
MI_MACHINEMODEL = "MachineModel"  #整机型号
MI_SERIALNUM = "SerialNum"        #SN
MI_VERSION = "Version"            #整机版本
MI_SYSTEMBITS = "SystemBits"      #系统位数
MI_KERNELARCH = "KernelArch"      #内核架构
MI_KERNELVERSION = "KernelVersion"  #内核版本
MI_HOSTNAME = "HostName"          #主机名
MI_OSVERSION = "OSVersion"        #操作系统版本
MI_OSTYPES = "OS Types"           #操作系统类型
MI_RUNINGTIME = "Running Time"    #系统持续运行时间
MI_PROCESSOR = "Processor"        #处理器
MI_MEMORY = "Memory"              #内存
MI_MAINBOARD = "MainBoard"        #主板
MI_HARDDISK = "HardDisk"          #硬盘
MI_GRAPHICSCARD = "GraphicsCard"  #显卡
MI_MONITOR = "Monitor"            #显示器
MI_NETWORKCARD = "NetworkCard"    #网卡
MI_SOUNDCARD = "SoundCard"        #声卡

##PROCESSOR
Pro_Manufacturer=    "manufacturer"
Pro_Product=         "processor"
Pro_Architecture=    "architecture"
Pro_Frequency=       "fref"
Pro_Frequency_Max=   "fref_max"
Pro_Threads=         "threads_num"
Pro_Family=          "Family"
Pro_Model=           "Model"
Pro_Stepping=        "Stepping"
Pro_L1dCache=        "L1d_cache"
Pro_L1iCache=        "L1i_cache"
Pro_L2Cache=         "L2_cache"
Pro_L3Cache=         "L3_cache"
Pro_Cores=           "cores_num"
Pro_Cores_Online=    "cores_num_online"
Pro_Ext_Instruction_Set="ext_instruction_set"
PSI_ROOT =           "processor"            #处理器根

##MEMORY
Mem_Manufacturer=    "Manufacturer"
Mem_BankLocator=     "Bank Locator"
Mem_Type=            "Type"
Mem_TypeDetail=      "Type Detail"
Mem_TotalWidth=      "Total Width"
Mem_DataWidth=       "Data Width"
Mem_SerialNumber=    "Serial Number"
Mem_MinVoltage=      "Minimum Voltage"
Mem_MaxVoltage=      "Maximum Voltage"
Mem_ConfVoltage=     "Configured Voltage"
Mem_Rank=            "Rank"
Mem_FormFactor=      "Form Factor"
Mem_Product=         "Product"

MMI_ROOT = "memory"               #内存
MMI_SLOT = "slot"                 #插槽
MMI_NAME = "name"                 #名称
MMI_FREQ = "freq"                 #当前频率
MMI_BUSWIDTH = "bus_width"        #总线位宽
MMI_DATAWIDTH = "data_width"        #数据位宽
MMI_TYPE = "type"                 #类型
MMI_TOTALCAPACITY = "total_capacity" #总容量
MMI_USEDCAPACITY = "used_capacity"   #已用容量
MMI_SERIALNUM = "serail_num"        #序列号
MMI_MANUFACTURER = "manufacturer"   #制造商
MMI_MODEL = "model"               #型号
MMI_SPEED = "speed"               #速率
MMI_CONFIGSPEED = "config_speed"   #配置速率
MMI_PIPE = "pipe"   #通道
MMI_ARRAYHANDLE = "array_handle"   #数组程序
MMI_PARTNUMBER = "partnum"   #部件号码
MMI_PHYSICALID = "physicalid"   #物理ID

###HARD DISK
HDI_ROOT = "harddisk"             #硬盘
HDI_MANUFACTURER = "manufacturer" #硬盘品牌
HDI_NAME = "name"                 #名称
HDI_CAPACITY = "capacity"         #容量
HDI_USEDTIMES = "used_times"      #已使用次数
HDI_INTERFACE = "interface"       #接口
HDI_ISMAINDISK = "is_maindisk"    #主硬盘（是否）
HDI_ISSSD = "is_ssd"              #硬盘类型（固态/机械）
HDI_SERIALNUM = "serial_num"      #序列号
HDI_MODEL = "model"               #型号
HDI_TRANSRATE = "trans_rate"      #数据传输率
HDI_READSPEED = "read_speed"      #磁盘读取速度
HDI_WRITESPEED = "write_speed"    #磁盘写入速度
HDI_FIRMWAREVER = "firmware_ver"  #固件版本
HDI_ROTA = "rota"                 #机械转速

###DEV MONITOR
DEVMONITOR_ROOT             = "device_monitor" #设备监测
DEVMONITOR_DEVTEMP          = "device_temp" #设备温度
DEVMONITOR_DEVTEMPS         = "device_temps" #设备温度列表
DEVMONITOR_DEVTEMP_HIGH     = "device_temp_high" #设备高温
DEVMONITOR_DEVTEMP_CRIT     = "device_temp_crit" #设备异常温
DEVMONITOR_DEVTEMP_NAME     = "device_name" #设备名称
DEVMONITOR_DEVTEMP_VALUE    = "device_temp_value" #设备温度值
DEVMONITOR_DEVUSAGE         = "device_usage" #设备使用率
DEVMONITOR_DEVUSAGE_NAME    = "device_name" #设备名称
DEVMONITOR_DEVUSAGE_USED    = "device_usage_used" #设备使用率
DEVMONITOR_DEVUSAGE_TOTAL   = "device_usage_total" #使用总值

###CPU FM
Cpufm_Root              = "cpu_fm" # cpu调频
Cpufm_Average_Corefreq  = "cpu_corefreq" #当前cpu核心平均主频
Cpufm_Models            = "cpu_model_list" #cpu调频模式列表
Cpufm_Current_Model     = "cpu_curmodel" #cpu当前模式
Cpufm_Model_Performance = "performance" #性能模式
Cpufm_Model_Powersave   = "powersave" #省电模式
Cpufm_Model_Userspace   = "userspace" #自定义
Cpufm_Model_Schedutil   = "schedutil" #均衡模式
Cpufm_Freqs             = "cpu_freq_list" #cpu频率列表
Cpufm_CurFreq           = "cur_freq" #cpu调频

###NETWORK CARD
NWI_ROOT = "network_card"         #网卡

###VOICE CARD
VCI_ROOT = "voice_card"           #声卡

###MOTHER BOARD
MBI_ROOT= "mother_board"                 #主板
MBI_NAME= "name"                         #主板名称
MBI_CHIPSET= "chipset"                   #芯片组
MBI_SERIALNUM= "serial_num"              #序列号
MBI_PUBDATE= "publish_date"              #发布日期
MBI_VERSION= "version"                   #主板版本
MBI_MANUFACTURER= "manufacturer"           #主板制造商
MBI_BIOSMANUFACTURER= "bios_manufacturer"  #BIOS制造商
MBI_BIOSVERSION= "bios_version"            #BIOS版本

###GRAPHICS CARD
GSI_ROOT= "graphics_card"           #显卡
GSI_MANUFACTURER= "manufacturer"    #厂商
GSI_SUBSYSTEM= "subsystem"          #子制造商
GSI_NAME= "name"                    #名称
GSI_ISDISCRETE= "is_discrete"       #是否为独显
GSI_CAPCITY= "capcity"              #显存
GSI_MEMTYPE= "mem_type"             #显存类型
GSI_MODEL= "model"                  #型号
GSI_VERSION= "version"              #版本
GSI_BITWIDTH= "bit_width"           #位宽
GSI_IRQ= "irq"                      #中断
GSI_FUNCTION= "function"            #功能
GSI_CLOCK= "clock"                  #时钟频率
GSI_DESC= "description"             #描述
GSI_DRIVER= "driver"                #驱动
GSI_DBUSINFO= "dbusinfo"            #总线信息
GSI_IOPORT= "io_port"               #I/O端口
GSI_MEMORY= "memory"                #内存
GSI_PHYSICS= "physics_id"           #物理ID
GSI_DELAY= "delay"                  #延迟
GSI_DEVICE= "device"                #设备
GSI_CONFSTATUS= "config_status"     #配置状态
GSI_DRIVERMODULE= "driver_module"   #驱动模块
GSI_GDDRCAPACITY= "gddr_capacity"   #GDDR容量
GSI_EGLVERSION= "egl_version"       #EGL版本
GSI_EGLAPIS= "egl_apis"             #EGL接口
GSI_GLVERSION= "gl_version"         #GL版本
GSI_GLSLVERSION= "glsl_version"     #GLSL版本

###MONITOR
MNI_ROOT= "monitor"              #显示器
MNI_MANUFACTURER= "manufacturer" #显示器厂商
MNI_NAME= "name"                 #名称
MNI_SIZE= "size"                 #屏幕尺寸
MNI_RATIO= "ratio"               #图像高宽比
MNI_RESOLUTION= "resolution"     #分辨率
MNI_MAXAVARES= "max_resolution"  #最大分辨率
MNI_ISMAIN= "is_main"            #主显示器（是/否）
MNI_GAMMA= "gamma"               #伽马值
MNI_INTERFACE= "interface"       #当前接口
MNI_MODEL= "model"               #型号
MNI_VISIBLEAREA= "visible_area"  #可视面积
MNI_YEAR= "year"                 #生产年
MNI_WEEK= "week"                 #生产周
MNI_SERIALNUM= "serailnum"       #序列号

###KEYBOARD
KBI_ROOT= "key_board"            #键盘
KBI_DEVTYPE= "dev_type"          #设备类型
KBI_NAME= "name"                 #设备名称
KBI_DEVMODEL= "dev_model"        #设备型号
KBI_MANUFACTURER= "manufacturer" #制造商
KBI_INTERFACE= "interface"       #接口
KBI_DRIVER= "driver"       #驱动

###MOUSE
MSI_ROOT= "mouse"                #鼠标
MSI_DEVTYPE= "dev_type"          #设备类型
MSI_NAME= "name"                 #设备名称
MSI_DEVMODEL= "dev_model"        #设备型号
MSI_MANUFACTURER= "manufacturer" #制造商
MSI_INTERFACE= "interface"       #接口
MSI_DRIVER= "driver"             #驱动

###BATTERY
BTI_ROOT= "battery"              #电池
BTI_SERAILNUM= "serailnum"       #序列号
BTI_MODEL= "model"               #型号
BTI_MANUFACTURER= "manufacturer" #制造商
BTI_TTE= "time_to_empty"         #预计使用时间
BTI_USEDTIMES= "used_times"      #使用次数
BTI_ENERGYFULL= "energy_full"    #满电容量
BTI_ENERGY= "energy"             #当前容量
BTI_STATE= "state"               #状态
BTI_PERCENTAGE= "percentage"     #电量

###CDDRIVE
CDI_ROOT= "cddrive"              #光驱
CDI_NAME= "name"                 #名称
CDI_MANUFACTURER= "manufacturer" #制造商
CDI_VERSION= "version"           #版本
CDI_MODEL= "model"               #型号
CDI_BUSINFO= "businfo"           #总线信息
CDI_DRIVER= "driver"             #驱动
CDI_SPEED= "speed"               #速度
CDI_SERAILNUM= "serailnum"       #序列号
CDI_DEVICENUM= "devicenum"       #设备编号

CAI_ROOT= "camera"               #摄像头
CAI_NAME= "name"                 #设备名称
CAI_RESOLUTION= "resolution"     #分辨率
CAI_MANUFACTURER= "manufacturer" #制造商
CAI_MODEL= "model"               #型号
CAI_INTERFACE= "interface"       #接口
CAI_DRIVER= "driver"             #驱动
CAI_TYPE= "type"                 #类型
CAI_VERSION= "version"           #版本
CAI_BUSINFO= "businfo"           #总线信息
CAI_SPEED= "speed"               #速度

###BLUETOOTH
BLI_ROOT= "bluetooth"            #蓝牙
BLI_BUSADDR= "bus_addr"          #总线地址
BLI_FUNCTION= "function"         #功能
BLI_FREQ= "freq"                 #频率
BLI_CONF= "configuration"        #配置
BLI_DEVTYPE= "dev_type"          #设备类型
BLI_ID= "id"                     #ID号
BLI_DEVMODEL= "dev_model"        #设备型号
BLI_RESOURCE= "resource"         #资源
BLI_MANUFACTURER= "manufacturer" #制造商
BLI_DEVVERSION= "dev_version"    #设备版本
BLI_DATAWIDTH= "data_width"      #数据宽度
BLI_NAME= "name"                 #名称
BLI_DRIVER= "driver"             #驱动
BLI_SPEED= "speed"               #速度
BLI_SERIALNUM= "serial_num"      #序列号
BLI_ADDRESS= "address"           #蓝牙地址
BLI_LINKMODE= "link_mode"        #连接模式
BLI_LINKPOLICY= "link_policy"    #连接策略
BLI_PRODUCT= "product"           #产品
BLI_CAPABILITIES= "capabilities" #功能
BLI_BUS= "bus" #总线
BLI_SCOMTU= "scomtu" #SCO MTU
BLI_ALCMTU= "alcmtu" #ALC MTU
BLI_PACKETTYPE= "packettype" #数据包类型
BLI_FEATURES= "features" #特征

###FAN
FAI_ROOT= "fan"                  #风扇
FAI_NAME= "name"                 #名称
FAI_SPEED= "speed"               #转速