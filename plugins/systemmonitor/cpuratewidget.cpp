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

#include "cpuratewidget.h"
#include "cpuballwidget.h"

#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QFile>

inline QString convertTimeToString(long seconds)
{
    //test script: cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf("已运行：%d天%d时%d分%d秒",run_days,run_hour,run_minute,run_second)}'
    int run_day = seconds / 86400;
    int run_hour = (seconds % 86400)/3600;
    int run_minute = (seconds % 3600)/60;
    int run_second = seconds % 60;

    QString hourStr;
    QString minuteStr;
    QString secondStr;

    if (run_hour >1)
        hourStr = QString(QObject::tr("%1hours")).arg(run_hour);
    else
        hourStr = QString(QObject::tr("%1hour")).arg(run_hour);
    if (run_minute > 1)
        minuteStr = QString(QObject::tr("%1minutes")).arg(run_minute);
    else
        minuteStr = QString(QObject::tr("%1minute")).arg(run_minute);
    if (run_second > 1)
        secondStr = QString(QObject::tr("%1seconds")).arg(run_second);
    else
        secondStr = QString(QObject::tr("%1second")).arg(run_second);

    QString run_time;
    if (run_day > 0) {
        if (run_day == 1)
            return QString("%1 %2 %3 %4").arg(QString(QObject::tr("%1day"))).arg(run_day).arg(hourStr).arg(minuteStr).arg(secondStr);
        else
            return QString("%1 %2 %3 %4").arg(QString(QObject::tr("%1days"))).arg(run_day).arg(hourStr).arg(minuteStr).arg(secondStr);
    }
    else {
        return QString("%1 %2 %3").arg(hourStr).arg(minuteStr).arg(secondStr);
    }

    return run_time;
}

inline int getCoreCounts()
{
    int cpuCounts = 0;

    QFile file("/proc/cpuinfo");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString content = file.readLine().trimmed();
        while (!content.isEmpty() && content.contains(QChar(':'))) {
            const QStringList tokens = content.split(QChar(':'));
            if (tokens.size() == 2) {
                if (tokens[0] == "processor")
                    cpuCounts ++;
            }
            content = file.readLine().trimmed();
        }
        file.close();
    }

    if (cpuCounts == 0)
        cpuCounts = 4;

    return cpuCounts;
}

inline QString getIdelRate(unsigned long &runSeconds, unsigned long &idleSeconds)
{
    int cpuNumber = getCoreCounts();

    QString rate;
    QFile file("/proc/uptime");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString content = file.readLine();
        while (!content.isEmpty() && content.contains(" ")) {
            QStringList tokens = content.split(" ");//content.split(QChar(' '))
            QString runStr = tokens.at(0);//从系统启动到现在的时间(以秒为单位)
            if (runStr.contains(QChar('.'))) {
                QString senconds = runStr.split(QChar('.')).at(0);
                runSeconds = senconds.toLong();
            }
            else
                runSeconds = runStr.toLong();

            QString idleStr = tokens.at(1);//系统空闲的时间(以秒为单位)
            if (idleStr.contains(QChar('.'))) {
                QString senconds = idleStr.split(QChar('.')).at(0);
                idleSeconds = senconds.toLong();
            }
            else
                idleSeconds = idleStr.toLong();
            rate = QString::number((idleSeconds * 1.0) /(runSeconds *1.0 * cpuNumber) * 100, 'f', 0) + "%";
            break;
        }
        file.close();
    }
    return rate;
}

inline long readUpdatetimeFile(bool isRunTime)
{
    QFile file("/proc/uptime");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString result;
        QString content = file.readLine();
        while (!content.isEmpty() && content.contains(" ")) {
            QStringList tokens = content.split(" ");//content.split(QChar(' '))
            if (isRunTime) {
                result = tokens.at(0);//从系统启动到现在的时间(以秒为单位)
            }
            else {
                result = tokens.at(1);//系统空闲的时间(以秒为单位)
            }
            break;
            //content = file.readLine();//continue read
        }
        file.close();
        if (result.contains(QChar('.'))) {
            QString senconds = result.split(QChar('.')).at(0);
            return senconds.toLong();
        }
        else
            return result.toLong();
    }
    return 0;
}

//系统平均负载
inline QString readLoadAvg()
{
    /*cat /proc/loadavg
    0.10 0.06 0.01 1/72 29632
    前3个数字表示平均进程数量外，后面的1个分数，分母表示系统进程总数，分子表示正在运行的进程数；最后一个数字表示最近运行的进程ID*/
    return QString();
}

inline void readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        qCritical() << QString("open %1 failed").arg(fileName);
        return;
    }

    QByteArray content = file.readAll();
    file.close();
    QTextStream stream(&content, QIODevice::ReadOnly);
    while (!stream.atEnd()) {
        const QString aline = stream.readLine();
        qDebug() << "aline="<<aline;
//        const QStringList items = line.split(QChar(':'));
//        if (items.size() == 2) {
//            qDebug() << "items[0]="<<items[0]<<",items[1]="<<items[0];
//        }
    }
//    while (!file.atEnd()) {
//       QString line = file.readLine();
//       QString trimmedLine = line.trimmed();
//       qDebug() << "line="<<line;
//       qDebug() << "trimmedLine="<<trimmedLine;
//       if (line.isEmpty() || trimmedLine.isEmpty())
//           continue;
//    }
//    file.close();
}

CpuRateWidget::CpuRateWidget(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);

    QWidget *w = new QWidget;
    m_contentLayout = new QHBoxLayout(w);
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentLayout->setSpacing(50);
    m_layout->addWidget(w, 0, Qt::AlignCenter);

    initWidgets();

    m_cpuBall->startTimer();

    /*unsigned long runtime;
    unsigned long idletime;
    QString rate = getIdelRate(runtime, idletime);
    qDebug() << "rate="<<rate;
    qDebug() << convertTimeToString(runtime);
    qDebug() << convertTimeToString(idletime);*/


    /*sudo dmidecode -t processor
    u32 len;
    u8 *buf;
    size_t size = len;
    buf = read_file(&size, devmem);
    len = size;
//    dmi_table_decode(buf, len, num, ver, flags);
//    dmi_decode(&h, ver);*/
}

CpuRateWidget::~CpuRateWidget()
{
    delete m_cpuRateTitle;
    delete m_cpuRateText;
    delete m_cpuIdleRateTitle;
    delete m_cpuIdleRateText;
    delete m_cpuRunTimeTitle;
    delete m_cpuRunTimeText;
    delete m_cpuIdleTimeTitle;
    delete m_cpuIdleTimeText;

    delete m_cpuBall;
    QLayoutItem *child;
    while ((child = m_labelLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_contentLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    delete m_layout;
}

void CpuRateWidget::initWidgets()
{
    QWidget *w = new QWidget;
//    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_labelLayout = new QVBoxLayout(w);
    m_labelLayout->setContentsMargins(0, 0, 0, 0);
    m_labelLayout->setSpacing(0);

    QLabel *m_title = new QLabel(tr("CPU"));
    m_title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_title->setStyleSheet("background:transparent;font-size:24px;color:#000000");

    m_cpuRateTitle = new QLabel;
    m_cpuRateTitle->setStyleSheet("QLabel{background:transparent;font-size:12px;color:#999999;}");
    m_cpuRateTitle->setText(tr("Occupancy rate"));
    m_cpuRateText = new QLabel;
    m_cpuRateText->setStyleSheet("QLabel{background:transparent;font-size:20px;color:#000000;}");

    m_cpuIdleRateTitle = new QLabel;
    m_cpuIdleRateTitle->setStyleSheet("QLabel{background:transparent;font-size:12px;color:#999999;}");
    m_cpuIdleRateTitle->setText(tr("Idle rate"));
    m_cpuIdleRateText = new QLabel;
    m_cpuIdleRateText->setStyleSheet("QLabel{background:transparent;font-size:20px;color:#000000;}");

    m_cpuRunTimeTitle = new QLabel;
    m_cpuRunTimeTitle->setStyleSheet("QLabel{background:transparent;font-size:12px;color:#999999;}");
    m_cpuRunTimeTitle->setText(tr("The running time of system"));
    m_cpuRunTimeText = new QLabel;
    m_cpuRunTimeText->setStyleSheet("QLabel{background:transparent;font-size:20px;color:#000000;}");

    m_cpuIdleTimeTitle = new QLabel;
    m_cpuIdleTimeTitle->setStyleSheet("QLabel{background:transparent;font-size:12px;color:#999999;}");
    m_cpuIdleTimeTitle->setText(tr("The idle time of system"));
    m_cpuIdleTimeText = new QLabel;
    m_cpuIdleTimeText->setStyleSheet("QLabel{background:transparent;font-size:20px;color:#000000;}");

    QVBoxLayout *cpuRateLayout = new QVBoxLayout;
    cpuRateLayout->setSpacing(10);
    cpuRateLayout->addWidget(m_cpuRateTitle);
    cpuRateLayout->addWidget(m_cpuRateText);

    QVBoxLayout *cpuIdleRateLayout = new QVBoxLayout;
    cpuIdleRateLayout->setSpacing(10);
    cpuIdleRateLayout->addWidget(m_cpuIdleRateTitle);
    cpuIdleRateLayout->addWidget(m_cpuIdleRateText);

    QHBoxLayout *rateLayout = new QHBoxLayout;
    rateLayout->setSpacing(30);
    rateLayout->addLayout(cpuRateLayout);
    rateLayout->addLayout(cpuIdleRateLayout);

    QVBoxLayout *cpuRunTimeLayout = new QVBoxLayout;
    cpuRunTimeLayout->setSpacing(10);
    cpuRunTimeLayout->addWidget(m_cpuRunTimeTitle);
    cpuRunTimeLayout->addWidget(m_cpuRunTimeText);

    QVBoxLayout *cpuIdleTimeLayout = new QVBoxLayout;
    cpuIdleTimeLayout->setSpacing(10);
    cpuIdleTimeLayout->addWidget(m_cpuIdleTimeTitle);
    cpuIdleTimeLayout->addWidget(m_cpuIdleTimeText);



    m_labelLayout->setContentsMargins(0, 0, 0, 0);
    m_labelLayout->setSpacing(10);
    m_labelLayout->addWidget(m_title);
    m_labelLayout->addLayout(rateLayout);
    m_labelLayout->addLayout(cpuRunTimeLayout);
    m_labelLayout->addLayout(cpuIdleTimeLayout);
    m_contentLayout->addWidget(w, 1, Qt::AlignLeft);

    m_cpuBall = new CpuBallWidget;
    m_contentLayout->addWidget(m_cpuBall);
}

void CpuRateWidget::refreshData(double cpu)
{
    m_cpuRateText->setText(QString::number(cpu, 'f', 1) + "%");

    unsigned long runtime;
    unsigned long idletime;
    QString rate = getIdelRate(runtime, idletime);
    m_cpuIdleRateText->setText(rate);
    m_cpuRunTimeText->setText(convertTimeToString(runtime));
    m_cpuIdleTimeText->setText(convertTimeToString(idletime));
}

void CpuRateWidget::onUpdateCpuPercent(double value)
{
    this->refreshData(value);
    m_cpuBall->updateCpuPercent(value);
}

void CpuRateWidget::startTimer()
{
    m_cpuBall->startTimer();
}

void CpuRateWidget::stopTimer()
{
    m_cpuBall->stopTimer();
}
