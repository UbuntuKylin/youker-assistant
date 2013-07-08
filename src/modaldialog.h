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
#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>
#include "quibo.h"

class QGridLayout;
class QHBoxLayout;
class QPushButton;
class QSpacerItem;
class QLabel;
class ModalDialog : public QDialog
{
      Q_OBJECT
    public:
      ModalDialog(QWidget *parent = 0);
    private:
      QSpacerItem *spacerItem;
      QGridLayout *gridLayout;
      QHBoxLayout *hboxLayout;
      QPushButton *okButton;
      QPushButton *cancelButton;
      QLabel      *textlabel;
      QLabel      *titlelabel;

      QUIBO *qtui;

public slots:
      void monitor_check();
};
#endif // MODALDIALOG_H
