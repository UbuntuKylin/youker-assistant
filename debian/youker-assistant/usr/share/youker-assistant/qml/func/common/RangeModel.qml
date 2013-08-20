/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reservePriv.ate.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributePriv.ate.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

import QtQuick 1.1
import "RangeModel.js" as Priv

QtObject {
    id: model
    property real value: Priv.ate.publicValue(Priv.ate.value)
    property real minimumValue: Priv.ate.minimumValue
    property real maximumValue: Priv.ate.maximumValue
    property real stepSize: Priv.ate.stepSize
    property real position: Priv.ate.publicPosition(Priv.ate.position)
    property real positionAtMinimum: Priv.ate.posAtMin
    property real positionAtMaximum: Priv.ate.posAtMax
    property bool inverted: Priv.ate.inverted

    function valueForPosition(p) {
        return Priv.ate.valueForPosition(p);
    }

    function positionForValue(v) {
        return Priv.ate.positionForValue(v);
    }

    onValueChanged: Priv.ate.setValue(value)
    onMinimumValueChanged: Priv.ate.setRange(minimumValue, Math.max(minimumValue, Priv.ate.max))
    onMaximumValueChanged: Priv.ate.setRange(Math.min(Priv.ate.min, maximumValue), maximumValue)
    onStepSizeChanged: Priv.ate.setStepSize(stepSize)
    onPositionChanged: Priv.ate.setPosition(position)
    onPositionAtMinimumChanged:
        Priv.ate.setPositionRange(positionAtMinimum, Math.max(positionAtMinimum, positionAtMaximum))
    onPositionAtMaximumChanged:
        Priv.ate.setPositionRange(Math.min(positionAtMinimum, positionAtMaximum), positionAtMaximum)
    onInvertedChanged: Priv.ate.setInverted(inverted)
}
