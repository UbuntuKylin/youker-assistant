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

#ifndef KFONTDIALOG_H
#define KFONTDIALOG_H

#include <QDialog>
#include <qfontdatabase.h>
#include <QModelIndex>
#include <QStringListModel>
class QSettings;
namespace Ui {
class KFontDialog;
}

class KFontDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit KFontDialog(QSettings *mSettings = 0, QString flag = "", QWidget *parent = 0);
    ~KFontDialog();
    void getInitFont();
    void initDialog();
    
private:
    Ui::KFontDialog *ui;
    QSettings *pSettings;
    QFontDatabase fdb;
    QString fontFlag;//字体标记
    void updateSampleFont();
    QStringListModel *familymodel;
    QStringListModel *stylemodel;
    QStringListModel *sizemodel;
    QPoint dragPos;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

protected slots:
    void updateAll(QModelIndex index);
    void updateStyleandSize(QModelIndex index);
    void updateSize(QModelIndex index);

private slots:
    void on_quitBtn_clicked();
    void on_okBtn_clicked();
};

#endif // KFONTDIALOG_H
