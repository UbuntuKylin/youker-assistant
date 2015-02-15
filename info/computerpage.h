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

#ifndef COMPUTERPAGE_H
#define COMPUTERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPen>
#include <QEvent>
#include <QMap>
#include <QGroupBox>
#include <QFormLayout>
#include <QVariant>
#include "../dbusproxy/youkersessiondbus.h"
#include "../dbusproxy/youkersystemdbus.h"

class ComputerPage : public QWidget
{
    Q_OBJECT
public:
    explicit ComputerPage(QWidget *parent = 0, QString title = "computer"/*, QString manufacturer = "UbuntuKylin"*/);
    ~ComputerPage();
    void setLanguage();
    int page_height;
    void initUI();
    void setMap(QMap<QString ,QVariant> tmp, const QString &manufacturer) {
        info_map = tmp;
        vendor = manufacturer;
    }
    QString translatorSwitch(QString orgStr);
    void resetTimeValue(QString value);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

public slots:

private:
    QString title_context;
    QLabel *title_label;
    QString vendor;

    void resizeEvent(QResizeEvent *);

    QMap<QString ,QVariant> info_map;
    QLabel *logo_label;
    QLabel *time_label;
    QGroupBox *group_box;
    QFormLayout *form_layout;
};

#endif // COMPUTERPAGE_H
