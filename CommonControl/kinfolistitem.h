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

#ifndef KINFOLISTITEM_H
#define KINFOLISTITEM_H

#include <QObject>
#include <QFrame>
#include <QColor>
#include <qgsettings.h>
#include <QMenu>
#include "kalabel.h"
class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class KInfoListItem : public QFrame
{
    Q_OBJECT
public:
    explicit KInfoListItem(QString strTitle, QString strIcon, QString strDetail, bool isOdd, QWidget *parent = nullptr);
    virtual ~KInfoListItem();

    void initUI();
    void updateDetailInfo(QString strDetail);

public slots:
    void onCopyContent();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void initStyleTheme();

private:
    QHBoxLayout *m_mainLayout = nullptr;

    QLabel *m_labelIcon = nullptr;
    KALabel *m_labelTitle = nullptr;
    KALabel *m_labelDetail = nullptr;

    QString m_strTitle;
    QString m_strIcon;
    QString m_strDetail;

    bool m_isOdd = false;
    QGSettings *m_styleSettings = nullptr;
    QColor m_alternateBase;
    QMenu *m_rkeyMenu = nullptr;
};

#endif // KINFOLISTITEM_H
