/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#ifndef NORMALCARD_H
#define NORMALCARD_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMouseEvent>
#include <QTimer>

namespace Ui {
class NormalCard;
}

class NormalCard : public QWidget
{
    Q_OBJECT
    
public:
    explicit NormalCard(QString title = "", QWidget *parent = 0);
    ~NormalCard();
//    void switchAnimation();
    void showUsingLogo(bool flag);

public slots:
//    void slotShowDelayAnimation();
//    void slotSwitchAnimationStep();
//    void onDeleteBtnClicked();

signals:
    void sendSelectThemeName(QString name);
//    void sendEnterBackground(QString name);
//    void sendLeaveBackground();
//    void sendDelteSignal(QString name);

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::NormalCard *ui;
//    QTimer *switchTimer;
//    QTimer *delayTimer;
//    bool showDelay;
//    QString switchDirection;
//    int py;
//    QString iconDir;
    QString icon_name;
    QString iconpath;
};

#endif // NORMALCARD_H
