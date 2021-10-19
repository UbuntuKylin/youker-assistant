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

#ifndef KAUSAGEITEM_H
#define KAUSAGEITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <qgsettings.h>

#include "kaprogressbar.h"

class KAUsageItem : public QWidget
{
    Q_OBJECT
public:
    explicit KAUsageItem(QString strTitle, QWidget *parent = nullptr);
    virtual ~KAUsageItem();

    void initUI();
    void setTitle(QString strTitle);
    void setMaxValue(qreal rMaxValue);
    void setThresholdValue(qreal rHigh, qreal rVHigh);
    qreal getMaxValue();
    qreal getCurValue();
    KAProgressBar::PROG_STATUS getCurStatus() {
        return m_progressBar->getCurStatus();
    }

public slots:
    void onUpdateValue(qreal rCurValue);

private:
    void initStyleTheme();

private:
    QString m_strTitle;
    QLabel *m_labelTitle = nullptr;
    QLabel *m_labelUsed = nullptr;
    QLabel *m_labelLeft = nullptr;
    KAProgressBar *m_progressBar = nullptr;
    QVBoxLayout *m_mainLayout = nullptr;
    QHBoxLayout *m_topLayout = nullptr;
    QHBoxLayout *m_midLayout = nullptr;
    QHBoxLayout *m_buttomLayout = nullptr;

    QGSettings *m_styleSettings = nullptr;
};

#endif // KAUSAGEITEM_H
