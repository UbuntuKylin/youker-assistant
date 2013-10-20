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

#ifndef WIZARDCONTROLLER_H
#define WIZARDCONTROLLER_H

#include <QWizard>
#include <QPoint>

namespace Ui {
class WizardController;
}

class WizardController : public QWizard
{
    Q_OBJECT
    
public:
    explicit WizardController(QWidget *parent = 0);
    ~WizardController();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected slots:
    void addLocation();
    void delLocation();
    void ChangedBackGround();

private:
    Ui::WizardController *ui;
    QPoint dragPos;
    QAbstractButton *backButton;
    QAbstractButton *nextButton;
    QAbstractButton *finishButton;
};

#endif // WIZARDCONTROLLER_H
