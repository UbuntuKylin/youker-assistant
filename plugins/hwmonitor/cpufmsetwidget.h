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

#ifndef CPUFMSETWIDGET_H
#define CPUFMSETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <qgsettings.h>
#include <QStringList>

#include "kainfotitle.h"
#include "kaslider.h"

class CpuFMSetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CpuFMSetWidget(QWidget *parent = nullptr);
    virtual ~CpuFMSetWidget();

    void initUI();
    void initConnections();

public slots:
    void onUpdateInfo(QString strInfoJson);
    void onButtonClicked(QAbstractButton* button);

signals:
    void updateCpuFreq(QString strFreq);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initStyleTheme();
    void updateUIStatus();

signals:
    void modelChanged(QString strModel, QString strFreq);

private:
    QVBoxLayout *m_layoutMain = nullptr;
    QHBoxLayout *m_layoutTitle = nullptr;
    QHBoxLayout *m_layoutSingleChk = nullptr;
    QHBoxLayout *m_layoutSlider = nullptr;

    KAInfoTitle *m_labelTitle = nullptr;
    QButtonGroup *m_bgRadio = nullptr;
    QRadioButton *m_radioPerformance = nullptr;
    QRadioButton *m_radioPowerSave = nullptr;
    QRadioButton *m_radioUserSpace = nullptr;
    QRadioButton *m_radioBalance = nullptr;
    QRadioButton *m_radioOndemand = nullptr;
    QRadioButton *m_radioConservative = nullptr;

    KASlider *m_sliderUserSpace = nullptr;

    QString m_strCurModel;
    QString m_strCurFreq;

    QGSettings *m_styleSettings = nullptr;
    QColor m_alternateBase;
    QStringList m_validFreqList;
    QStringList m_validModelList;
};

#endif // CPUFMSETWIDGET_H
