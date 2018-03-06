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

#ifndef THEMEVIEW_H
#define THEMEVIEW_H

#include <QListView>
#include <QStandardItemModel>

class ThemeDelegate;

class ThemeView : public QListView
{
    Q_OBJECT
public:
    explicit ThemeView(QWidget *parent = 0);
    ~ThemeView();

    void loadOneTheme(const QString &name, bool isCurrrent = false);
    QModelIndex loadThemeData(const QString &name, bool isCurrrent = false);
    void clearData();
    int isExist(const QString &name) const;
    QSize itemSize() const;

public slots:
    void onItemClicked(const QModelIndex &index);

signals:
    void sendSelectThemeName(QString themeName);

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
//    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private:
    ThemeDelegate *m_delegate = nullptr;
    QStandardItemModel *m_model = nullptr;
    QSize m_itemSize;
    QModelIndex m_prevModelIndex;

};

#endif // THEMEVIEW_H
