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

#include <QDialog>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QDebug>
#include <QHeaderView>
#include <QSettings>

#include "procman.h"
#include "procapp.h"
#include "filelist.h"
#include "../component/utils.h"
#include "../component/toolkits.h"
#include "../component/kylintitlebar.h"

#include <QTimer>
#define COLUMN_NUM 9

class ProcessManager;

class ProcessDialog : public QDialog
{
    Q_OBJECT
public:
  ProcessDialog(ProcessManager *plugin, QDialog *parent = 0);
  ~ProcessDialog();
  void setLanguage();
  void initConnect();
  void initTitleBar();
  void showProList();
  QString getCurrrentSkinName();
  void resetSkin();
  ProcApp *app;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void refresh_prolist();
    void handlercellClicked(int row, int column);
    void killSelectedProcess();
    void onCloseButtonClicked();
//    void onMinButtonClicked();

private:
  ProcessManager *process_plugin;
  QLabel *tip_label;
  QPushButton *kill_btn;
  QTableWidget *tableWidget;
  QString selected_pid;
  QTimer *timer;
  Toolkits *toolkits;
  KylinTitleBar *title_bar;
  QSettings *proSettings;
};
