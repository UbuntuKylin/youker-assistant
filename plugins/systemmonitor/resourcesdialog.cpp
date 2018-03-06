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

#include "resourcesdialog.h"
#include "cpuratewidget.h"
#include "memorywidget.h"
#include "networkwidget.h"
#include "resourcescategory.h"

#include <glibtop/netload.h>
#include <glibtop/netlist.h>

#include <QDebug>
#include <QTimer>

typedef struct _net
{
    guint64 last_in, last_out;
    GTimeVal time;
} net;
net netinfo;

inline void getNetworkBytesData(unsigned long long int &receiveBytes, unsigned long long int &sendBytes, unsigned long long int &receiveRateBytes, unsigned long long int &sendRateBytes)
{
    glibtop_netlist netlist;
    char **ifnames;
    guint32 i;
    guint64 in = 0, out = 0;
    GTimeVal time;
    guint64 din, dout;
    ifnames = glibtop_get_netlist(&netlist);

    for (i = 0; i < netlist.number; ++i) {
        glibtop_netload netload;
        glibtop_get_netload(&netload, ifnames[i]);

        if (netload.if_flags & (1 << GLIBTOP_IF_FLAGS_LOOPBACK))
            continue;

        /* Skip interfaces without any IPv4/IPv6 address (or
           those with only a LINK ipv6 addr) However we need to
           be able to exclude these while still keeping the
           value so when they get online (with NetworkManager
           for example) we don't get a suddent peak.  Once we're
           able to get this, ignoring down interfaces will be
           possible too.  */
        if (not (netload.flags & (1 << GLIBTOP_NETLOAD_ADDRESS6)
                 and netload.scope6 != GLIBTOP_IF_IN6_SCOPE_LINK)
            and not (netload.flags & (1 << GLIBTOP_NETLOAD_ADDRESS)))
            continue;

        /* Don't skip interfaces that are down (GLIBTOP_IF_FLAGS_UP)
           to avoid spikes when they are brought up */

        in  += netload.bytes_in;
        out += netload.bytes_out;
    }

    g_strfreev(ifnames);

    g_get_current_time(&time);

    if (in >= netinfo.last_in && out >= netinfo.last_out && netinfo.time.tv_sec != 0) {
        float dtime;
        dtime = time.tv_sec - netinfo.time.tv_sec +
                (double) (time.tv_usec - netinfo.time.tv_usec) / G_USEC_PER_SEC;
        din   = static_cast<guint64>((in  - netinfo.last_in)  / dtime);
        dout  = static_cast<guint64>((out - netinfo.last_out) / dtime);
    } else {
        /* Don't calc anything if new data is less than old (interface
           removed, counters reset, ...) or if it is the first time */
        din  = 0;
        dout = 0;
    }

    netinfo.last_in  = in;
    netinfo.last_out = out;
    netinfo.time     = time;

    receiveBytes = in;
    sendBytes = out;
    receiveRateBytes = din;
    sendRateBytes = dout;
}

unsigned long long getCpuTimeData(unsigned long long &workTime)
{
    FILE *file = fopen("/proc/stat", "r");
    if (file == NULL) {
        return 0;
    }

    char buffer[1024] = {0};
    unsigned long long user = 0, nice = 0, system = 0, idle = 0;
    unsigned long long iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0, guestnice = 0;

    char* ret = fgets(buffer, sizeof(buffer) - 1, file);
    if (ret == NULL) {
        fclose(file);
        return 0;
    }
    fclose(file);

    sscanf(buffer, "cpu  %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu %16llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guestnice);
    workTime = user + nice + system;

    return user + nice + system + idle + iowait + irq + softirq + steal;
}

ResouresDialog::ResouresDialog(QWidget *parent)
    :QWidget(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setAcceptDrops(true);
    setAttribute(Qt::WA_NoMousePropagation);
    this->setObjectName("ResouresDialog");

    //cpu
    m_cpuTotalTime = 0;
    m_cpuworkTime = 0;
    m_prevCpuTotalTime = 0;
    m_prevCpuWorkTime = 0;

    m_hlayout = new QHBoxLayout(this);
    m_hlayout->setContentsMargins(0, 0, 0, 0);

    splitter = new QSplitter(this);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setHandleWidth(1);

    m_stack = new QStackedWidget(this);
    m_stack->setStyleSheet("QStackedWidget{background: rgb(255, 255, 255);}");
//    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_resourcesCategory = new ResourcesCategory(0);
    connect(m_resourcesCategory, SIGNAL(switchResoucesPage(int)), this, SLOT(onSwitchResoucesPage(int)));

//    m_vlayout = new QVBoxLayout;
    m_cpuWidget = new CpuRateWidget();
    m_memoryWidget = new MemoryWidget();
    m_networkWidget = new NetworkWidget();
//    m_vlayout->addWidget(m_cpuWidget, 0, Qt::AlignHCenter);
//    m_vlayout->addWidget(m_memoryWidget, 0, Qt::AlignHCenter);
//    m_vlayout->addWidget(m_networkWidget, 0, Qt::AlignHCenter);
    m_stack->addWidget(m_cpuWidget);
    m_stack->addWidget(m_memoryWidget);
    m_stack->addWidget(m_networkWidget);
    m_stack->setCurrentWidget(m_cpuWidget);

    /*m_hlayout->addWidget(m_resourcesCategory);
//    m_hlayout->addLayout(m_vlayout);
    m_hlayout->addWidget(m_stack);*/
    splitter->addWidget(m_resourcesCategory);
    splitter->addWidget(m_stack);
    m_hlayout->addWidget(splitter);

    connect(this, SIGNAL(updateNetworkStatus(long,long,long,long)), m_networkWidget, SLOT(onUpdateNetworkStatus(long,long,long,long)), Qt::QueuedConnection);
    connect(this, SIGNAL(updateMemoryStatus()), m_memoryWidget, SLOT(onUpdateMemoryStatus()));
    connect(this, SIGNAL(updateCpuStatus(double)), m_cpuWidget, SLOT(onUpdateCpuPercent(double)), Qt::QueuedConnection);

    connect(m_memoryWidget, &MemoryWidget::rebackMemoryInfo, this, [=] (const QString &info, double percent) {
        m_resourcesCategory->onUpdateMemoryPercent(info, percent);
    });

    connect(this, SIGNAL(updateCpuStatus(double)), m_resourcesCategory, SLOT(onUpdateCpuPercent(double)), Qt::QueuedConnection);
    connect(this, SIGNAL(updateNetworkStatus(long,long,long,long)), m_resourcesCategory, SLOT(onUpdateNetworkStatus(long,long,long,long)), Qt::QueuedConnection);

    updateStatusTimer = new QTimer(this);
    connect(updateStatusTimer, SIGNAL(timeout()), this, SLOT(updateResourceStatus()));
    updateStatusTimer->start(2000);
}

ResouresDialog::~ResouresDialog()
{
    delete m_resourcesCategory;
    if (m_stack) {
        foreach (QObject *child, m_stack->children()) {
            QWidget *widget = static_cast<QWidget *>(child);
            widget->deleteLater();
        }
        delete m_stack;
    }
    /*
//    if (m_vlayout) {
//        foreach (QObject *child, m_vlayout->children()) {
//            QWidget *widget = static_cast<QWidget *>(child);
//            widget->deleteLater();
//        }
//    }

    QLayoutItem *child;
    while ((child = m_vlayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }*/

    delete m_hlayout;
}

void ResouresDialog::onSwitchResoucesPage(int index)
{
    if (index < 3 && index >= 0)
        m_stack->setCurrentIndex(index);
}

void ResouresDialog::startCpuTimer()
{
    m_cpuWidget->startTimer();
}

void ResouresDialog::stopCpuTimer()
{
    m_cpuWidget->stopTimer();
}

void ResouresDialog::updateResourceStatus()
{
    //cpu
    m_prevCpuWorkTime = m_cpuworkTime;
    m_prevCpuTotalTime = m_cpuTotalTime;
    m_cpuTotalTime = getCpuTimeData(m_cpuworkTime);
    if (m_prevCpuWorkTime != 0 && m_prevCpuTotalTime != 0) {
        emit updateCpuStatus((m_cpuworkTime - m_prevCpuWorkTime) * 100.0 / (m_cpuTotalTime - m_prevCpuTotalTime));
    }
    else {
        emit updateCpuStatus(0);
    }

    //memory
    emit this->updateMemoryStatus();

    //network
    getNetworkBytesData(m_totalRecvBytes, m_totalSentBytes, m_rateRecvBytes, m_rateSentBytes);
    emit this->updateNetworkStatus(m_totalRecvBytes, m_totalSentBytes, m_rateRecvBytes, m_rateSentBytes);
}
