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

#include "../../component/utils.h"
#include "../widgets/mydialog.h"
#include "../widgets/myactiongroup.h"
#include "../widgets/myactiongroupitem.h"
#include "../widgets/myaction.h"
#include "processworker.h"
#include "processlistitem.h"
#include "processlistwidget.h"

#include <QLabel>
#include <QMap>
#include <QMenu>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QDebug>
#include <QHeaderView>
#include <QSettings>

class ProcessManager;
class ProcessCategory;

class ProcessDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessDialog(QList<bool> toBeDisplayedColumns, int currentSortIndex, bool isSort, QSettings *settings, QWidget* parent = 0);
    ~ProcessDialog();

    ProcessListWidget* getProcessView();
    void displayAllProcess();
    void displayActiveProcess();
    void displayCurrentUserProcess();
    void clearOriginProcList();

signals:
    void changeColumnVisible(int index, bool visible, QList<bool> columnVisible);
    void changeSortStatus(int index, bool isSort);
    void activeWhoseProcessList(int index);

public slots:
    void focusProcessView();
    void onSearch(QString text);
    void stopProcesses();
    void continueProcesses();
    void endProcesses();
    void killProcesses();
    void popupMenu(QPoint pos, QList<ProcessListItem*> items);
    void showPropertiesDialog();
    void showEndProcessDialog();
    void showKillProcessDialog();
    void endDialogButtonClicked(int index, QString buttonText);
    void killDialogButtonClicked(int index, QString buttonText);
    void updateStatus(QList<ProcessListItem*> items);
    void onActiveWhoseProcess(int index);
    void changeProcPriority(int nice);
    void refreshProcessList();

protected:
//    void paintEvent(QPaintEvent *event);

private:
    QTimer *timer = nullptr;
    QSettings *proSettings = nullptr;
    guint64 cpu_total_time;
    guint64 cpu_total_time_last;
    MyDialog *killProcessDialog = nullptr;
    MyDialog *endProcessDialog = nullptr;
    ProcessListWidget *m_processListWidget = nullptr;
    QAction *m_propertiyAction = nullptr;
    QAction *m_stopAction = nullptr;//停止
    QAction *m_continueAction = nullptr;//继续进程
    QAction *m_endAction = nullptr;//结束
    QAction *m_killAction = nullptr;//杀死
    ProcessCategory *processCategory = nullptr;

  QMenu *m_priorityMenu;
  MyActionGroup * priorityGroup;
  MyAction *veryHighAction;
  MyAction *highAction;
  MyAction *normalAction;
  MyAction *lowAction;
  MyAction *veryLowAction;
  MyAction *customAction;

    QList<pid_t> *actionPids;
    QMenu *m_menu = nullptr;
    QString whose_processes;
    gint num_cpus;
    unsigned frequency;

    QVBoxLayout *m_layout = nullptr;
    QHBoxLayout *m_categoryLayout = nullptr;
};
