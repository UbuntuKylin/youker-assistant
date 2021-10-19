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

#ifndef KDRIVEINFOITEM_H
#define KDRIVEINFOITEM_H

#include <QObject>
#include <QFrame>
#include <QColor>
#include <qgsettings.h>
#include <QMenu>
class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class KDriveInfoItem : public QFrame
{
    Q_OBJECT
public:
    explicit KDriveInfoItem(QString strTitle, QString strIcon, QString strDriveName, QString strDriveVer, bool isOdd, QWidget *parent = nullptr);
    virtual ~KDriveInfoItem();

    void initUI();
    void updateDriveInfo(QString strDriveName, QString strDriveVer);

public slots:
    void onCopyContent();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void initStyleTheme();

private:
    QHBoxLayout *m_mainLayout = nullptr;
    QVBoxLayout *m_driveInfoLayout = nullptr;

    QLabel *m_labelIcon = nullptr;
    QLabel *m_labelTitle = nullptr;
    QLabel *m_labelDriveName = nullptr;
    QLabel *m_labelDriveVersion = nullptr;

    QString m_strTitle;
    QString m_strIcon;
    QString m_strDriveName;
    QString m_strDriveVersion;

    bool m_isOdd = false;
    QGSettings *m_styleSettings = nullptr;
    QColor m_alternateBase;
    QMenu *m_rkeyMenu = nullptr;
};

#endif // KDRIVEINFOITEM_H
