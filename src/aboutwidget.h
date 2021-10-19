/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QFont>
#include <QPalette>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QDebug>
#include <qgsettings.h>

class AboutWidget : public QDialog
{
    Q_OBJECT
public:
    explicit AboutWidget(QWidget *parent = nullptr);
    ~AboutWidget();

    void initUI();
    void setAppIcon(const QString &text);
    void setAppName(const QString &text);
    void setAppVersion(const QString &text);
    void setAppDescription(const QString &text);
protected:
//    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void initThemeMode();

private:
    QVBoxLayout *main_layout = nullptr;

    QLabel *title_icon = nullptr;
    QLabel *title_name = nullptr;
    QPushButton *close_btn = nullptr;

    QLabel *app_icon = nullptr;
    QLabel *app_name = nullptr;
    QLabel *app_version = nullptr;
    QTextBrowser *app_description = nullptr;

    QGSettings *qtSettings = nullptr;
};

#endif // ABOUTWIDGET_H
