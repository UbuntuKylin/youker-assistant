/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#ifndef MONITORTITLEWIDGET_H
#define MONITORTITLEWIDGET_H

#include <QFrame>
#include <QTimer>
#include <QSettings>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class MySearchEdit;
class MyTristateButton;

class MonitorTitleWidget : public QFrame
{
    Q_OBJECT
public:
    MonitorTitleWidget(QSettings *settings, QWidget *parent);
    ~MonitorTitleWidget();
    void initTitlebarLeftContent();
    void initTitlebarMiddleContent();
    void initTitlebarRightContent();
    void initToolbarLeftContent();
    void initToolbarRightContent();
    void initWidgets();
    void setSearchEditFocus();

public slots:
    void onRefreshSearchResult();
    void handleSearchTextChanged();
    void onCancelSearchBtnClicked(bool b);

    void onMinBtnClicked();
    void onMaxBtnClicked();
    void onCloseBtnClicked();
    void onUpdateMaxBtnStatusChanged();

signals:
    void updateMaxBtn();
    void changePage(int index);
    void searchSignal(QString searchContent);
    void canelSearchEditFocus();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
//    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *, QEvent *event) override;

private:
    QSettings *proSettings;
    MySearchEdit *m_searchEdit = nullptr;
    QPushButton *m_cancelSearchBtn = nullptr;
    QString searchTextCache;
    QTimer *m_searchTimer = nullptr;
    QLabel *emptyLabel = nullptr;
    QVBoxLayout *m_layout = nullptr;
    QHBoxLayout *m_topLayout = nullptr;
    QHBoxLayout *m_titleMiddleLayout = nullptr;
    QHBoxLayout *m_titleRightLayout = nullptr;
    QHBoxLayout *m_bottomLayout = nullptr;
    QHBoxLayout *m_titleLeftLayout = nullptr;
    QHBoxLayout *m_toolLeftLayout = nullptr;
    QHBoxLayout *m_toolRightLayout = nullptr;
    MyTristateButton *maxBtn = nullptr;
};

#endif // MONITORTITLEWIDGET_H
