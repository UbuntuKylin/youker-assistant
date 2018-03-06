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


#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QSplitter>

class ResourcesCategory;
class CpuRateWidget;
class MemoryWidget;
class NetworkWidget;

class ResouresDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ResouresDialog(QWidget* parent = 0);
    ~ResouresDialog();

    void startCpuTimer();
    void stopCpuTimer();

public slots:
    void updateResourceStatus();
    void onSwitchResoucesPage(int index);

signals:
    void updateCpuStatus(double percent);
    void updateMemoryStatus();
    void updateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateBytes, long sentRateBytes);

private:
    //cpu
    unsigned long long m_prevCpuTotalTime;
    unsigned long long m_prevCpuWorkTime;
    unsigned long long m_cpuTotalTime;
    unsigned long long m_cpuworkTime;

    //network
    unsigned long long int m_totalRecvBytes;
    unsigned long long int m_totalSentBytes;
    unsigned long long int m_rateRecvBytes;
    unsigned long long int m_rateSentBytes;

    QTimer *updateStatusTimer = nullptr;
    QHBoxLayout *m_hlayout = nullptr;
//    QVBoxLayout *m_vlayout = nullptr;
    ResourcesCategory * m_resourcesCategory = nullptr;
    CpuRateWidget *m_cpuWidget = nullptr;
    MemoryWidget *m_memoryWidget = nullptr;
    NetworkWidget *m_networkWidget = nullptr;

    QSplitter *splitter = nullptr;
    QStackedWidget *m_stack = nullptr;
};
