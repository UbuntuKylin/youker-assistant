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
#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QDialog>

class QGridLayout;
class QHBoxLayout;
class QPushButton;
class QSpacerItem;
class QLabel;
class WarningDialog : public QDialog
{
      Q_OBJECT
    public:
    WarningDialog(QString message = "", QWidget *parent = 0);
    private:
      QSpacerItem *spacerItem;
      QGridLayout *gridLayout;
      QHBoxLayout *hboxLayout;
      QPushButton *okButton;
      QPushButton *cancelButton;
      QLabel      *textlabel;
      QLabel      *titlelabel;

};
#endif // WARNINGDIALOG_H
