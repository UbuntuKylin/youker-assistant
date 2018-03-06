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


#ifndef RESOURCESINDICATOR_H
#define RESOURCESINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QPixmap>

class ResourcesIndicator : public QWidget
{
    Q_OBJECT

    enum ResourcesState {Normal, Hover, Press, Checked};

public:
    ResourcesIndicator(int flag, QWidget * parent=0);
    ~ResourcesIndicator();

    void setChecked(bool flag);
    bool isChecked();
    void setTitle(const QString &title);
    void updatePercentAndInfo(double percent, const QString &info);
    ResourcesState getResourcesState() const;

signals:
    void clicked();

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void updateBgColor();
    void setResourcesState(ResourcesState state);

private:
    ResourcesState m_state;
    bool m_isChecked;
    int m_currentPercent;
    QString m_title;
    QString m_info;
    int m_posX;
    int m_rectTopPadding;
    int m_rectTotalHeight;
    int m_rectTotalWidth;
    QColor m_outsideBorderColor;
    QColor m_bgColor;
    QColor m_borderColor;
};

#endif // RESOURCESINDICATOR_H
