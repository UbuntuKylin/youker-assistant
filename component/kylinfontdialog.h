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

#ifndef KYLINFONTDIALOG_H
#define KYLINFONTDIALOG_H

#include <QDialog>
#include <qfontdatabase.h>
#include <QModelIndex>
#include <QStringListModel>
//#include "kylintitlebar.h"
#include "../component/mytitlebar.h"
#include <QListView>

class QSettings;
class QLabel;

class KylinFontDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit KylinFontDialog(/*QSettings *mSettings = 0, QString flag = "", */QString cur_font = "", QString skin = ":/background/res/skin/1.png", QWidget *parent = 0);
    ~KylinFontDialog();
    void initDialog();
    void setLanguage();
    void initConnect();
    void initTitleBar(QString skin);
    void updateSampleFont();
    void resetTitleSkin(QString skin);
    void moveCenter();

public slots:
    void onCacelButtonClicked();
//    void onMinButtonClicked();
    void onOKButtonClicked();

signals:
    void rebackCurrentFont(QString cur_font);

protected slots:
    void updateAll(QModelIndex index);
    void updateStyleandSize(QModelIndex index);
    void updateSize(QModelIndex index);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
//    Ui::KylinFontDialog *ui;
//    QSettings *pSettings;
    QFontDatabase fdb;
//    QString fontFlag;//字体标记
    QStringListModel *familymodel;
    QStringListModel *stylemodel;
    QStringListModel *sizemodel;
    QPoint dragPos;
    QString selectedFont;
//    KylinTitleBar *title_bar;
    MyTitleBar *title_bar;

    QLabel *cur_tip_label;
    QLabel *cur_font_label;
    QLabel *font_label;
    QLabel *style_label;
    QLabel *size_label;
    QLineEdit *font_edit;
    QLineEdit *style_edit;
    QLineEdit *size_edit;
    QListView *font_view;
    QListView *style_view;
    QListView *size_view;
    QLabel *sample_label;
    QLineEdit *sample_edit;
    QPushButton *ok_btn;
    QPushButton *cacel_btn;
};

#endif // KYLINFONTDIALOG_H
