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

#ifndef CLEANLISTWIDGET_H
#define CLEANLISTWIDGET_H

#include <QWidget>
#include <QDialog>
#include "../component/kylintitlebar.h"

class SessionDispatcher;
class QCheckBox;

namespace Ui {
class CleanListWidget;
}

class CleanListWidget : public QDialog
{
    Q_OBJECT

public:
//    explicit CleanListWidget(QStringList &arglist, const QString title_text = "UbuntuKylin", QWidget *parent = 0/*, SessionDispatcher *proxy = 0*/);
    explicit CleanListWidget(QStringList &arglist, QString skin = ":/background/res/skin/1.png", const QString title_text = "UbuntuKylin", QDialog *parent = 0/*, SessionDispatcher *proxy = 0*/);
    ~CleanListWidget();
    void setLanguage();
    void initConnect();
    QStringList getSelectedItems();
    void resetTitleSkin(QString skin);

public slots:
    void resetSubCheckbox(int status);
    void scanAllSubCheckbox();
    void onCloseButtonClicked();

signals:
    void notifyMainCheckBox(int status);

private:
    void initTitleBar(QString skin);

private:
    Ui::CleanListWidget *ui;
    QList<QCheckBox *> checkbox_list;
    KylinTitleBar *title_bar;
    QString titleName;
    QLabel *tip_label;
    QLabel *num_label;
};

#endif // CLEANLISTWIDGET_H
