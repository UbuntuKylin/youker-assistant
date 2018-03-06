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
#include <QSettings>
#include "../../component/kylineditbutton.h"
#include "../../component/mytitlebar.h"
#include "../../component/toolkits.h"
#include "../../component/utils.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
//class ShredManager;

class ShredDialog : public QWidget
//class ShredDialog : public QDialog
{
    Q_OBJECT
public:
//  ShredDialog(ShredManager *plugin, QDialog *parent = 0);
    explicit ShredDialog(QWidget *parent = 0);
  ~ShredDialog();
  void setLanguage();
  void initConnect();
//  void initTitleBar();
//  QString getCurrrentSkinName();
//  void resetSkin();

  void moveCenter();

protected:
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

public slots:
    void onSelectButtonClicked();
    void onShredButtonClicked();
    void onCacelButtonClicked();
//    void onSelecteComboActivated(int index);
    void onCloseButtonClicked();
//    void onMinButtonClicked();

private:
//    ShredManager *process_plugin;
    MyTitleBar *title_bar;
    KylinEditButton *select_btn;
    QLineEdit *select_edit;
    QPushButton *shred_btn;
    QPushButton *cacel_btn;
    Toolkits *toolkits;
    QPoint dragPosition;
    bool mousePressed;
//    QSettings *shredSettings;
};
