/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef FCITXWARNDIALOG_H
#define FCITXWARNDIALOG_H

#include <QDialog>
#include <fcitxwarndialog.h>

namespace Ui {
class FcitxWarnDialog;
}

class FcitxWarnDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FcitxWarnDialog(QWidget *parent = 0);
    ~FcitxWarnDialog();
public:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void fcitxWarntest();
public slots:
    void on_okButton_clicked();
    void text();

private:
    Ui::FcitxWarnDialog *ui;
};

#endif // FCITXWARNDIALOG_H




