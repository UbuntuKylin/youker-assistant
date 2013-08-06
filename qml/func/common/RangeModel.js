/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserveD.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributeD.
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

function RangeModel()
{
    this.value = 0;
    this.min = 0;
    this.max = 99;
    this.stepSize = 0;

    this.position = 0;
    this.posAtMin = 0;
    this.posAtMax = 1;

    this.inverted = false;

    this.recursionBlocked = false;
}

RangeModel.prototype = {

setRange: function(newMin, newMax)
{
    if (this.recursionBlocked)
        return;
    this.recursionBlocked = true;
    var oldValue = this.value;
    var oldPos = this.position;

    this.min = newMin;
    this.max = newMax;

    this.updateValueAndPosition(oldValue, oldPos);
    this.recursionBlocked = false;
},

setStepSize: function(ss)
{
    if (this.recursionBlocked)
        return;
    this.recursionBlocked = true;
    var oldValue = this.value;
    var oldPos = this.position;

    this.stepSize = ss;

    this.updateValueAndPosition(oldValue, oldPos);
    this.recursionBlocked = false;
},

setPositionRange: function(newMin, newMax)
{
    if (this.recursionBlocked)
        return;
    this.recursionBlocked = true;
    var oldValue = this.value;
    var oldPos = this.position;

    this.posAtMin = newMin;
    this.posAtMax = newMax;
    this.position = this.positionForValue(this.value);

    this.updateValueAndPosition(oldValue, oldPos);
    this.recursionBlocked = false;
},

setInverted: function(i)
{
    if (this.recursionBlocked)
        return;
    this.recursionBlocked = true;
    var oldValue = this.value;
    var oldPos = this.position;

    this.inverted = i;

    this.updateValueAndPosition(oldValue, oldPos);
    this.recursionBlocked = false;
},

setValue: function(v)
{
    if (this.recursionBlocked)
        return;
    this.recursionBlocked = true;
    var oldValue = this.value;
    var oldPos = this.position;

    this.value = v;
    this.position = this.positionForValue(v);

    this.updateValueAndPosition(oldValue, oldPos);
    this.recursionBlocked = false;
},

setPosition: function(p)
{
    if (this.recursionBlocked)
        return;
    this.recursionBlocked = true;
    var oldValue = this.value;
    var oldPos = this.position;

    this.position = p;
    this.value = this.valueForPosition(p);

    this.updateValueAndPosition(oldValue, oldPos);
    this.recursionBlocked = false;
},

effectivePosAtMin: function()
{
    return this.inverted ? this.posAtMax : this.posAtMin;
},

effectivePosAtMax: function()
{
    return this.inverted ? this.posAtMin : this.posAtMax;
},

updateValueAndPosition: function(oldValue, oldPosition)
{
    var newValue = this.publicValue(this.value);
    if (newValue != oldValue)
        model.value = newValue;

    var newPos = this.publicPosition(this.position);
    if (newPos != oldPosition)
        model.position = newPos;
},

publicValue: function(v)
{
    if (this.stepSize == 0)
        return v < this.min ? this.min : v > this.max ? this.max : v;

    var stepSizeMultiplier = Math.floor((v - this.min) / this.stepSize);
    if (stepSizeMultiplier < 0)
        return this.min;

    var leftEdge = Math.min(this.max, stepSizeMultiplier * this.stepSize + this.min);
    var rightEdge = Math.min(this.max, (stepSizeMultiplier + 1) * this.stepSize + this.min);
    var middle = (leftEdge + rightEdge) / 2;

    return v <= middle ? leftEdge : rightEdge;
},

publicPosition: function(p)
{
    var minPos = this.effectivePosAtMin();
    var maxPos = this.effectivePosAtMax();
    var valueRange = this.max - this.min;
    var positionValueRatio = valueRange != 0 ? (maxPos - minPos) / valueRange : 0;
    var positionStep = this.stepSize * positionValueRatio;

    if (positionStep == 0) {
        if (this.inverted) {
            var tmp = maxPos;
            maxPos = minPos;
            minPos = tmp;
        }
        return p < minPos ? minPos : p > maxPos ? maxPos : p;
    }

    var stepSizeMultiplier = Math.floor((p - minPos) / positionStep);
    if (stepSizeMultiplier < 0)
        return minPos;

    var leftEdge = stepSizeMultiplier * positionStep + minPos;
    var rightEdge = leftEdge + positionStep;

    if (minPos < maxPos) {
        leftEdge = Math.min(leftEdge, maxPos);
        rightEdge = Math.min(rightEdge, maxPos);
    } else {
        leftEdge = Math.max(leftEdge, maxPos);
        rightEdge = Math.max(rightEdge, maxPos);
    }

    return Math.abs(leftEdge - p) <= Math.abs(rightEdge - p) ? leftEdge : rightEdge;
},

valueForPosition: function(p) {
    return this.publicValue(this.equivalentValue(p));
},

positionForValue: function(v) {
    return this.publicPosition(this.equivalentPosition(v));
},

equivalentValue: function(p)
{
    var ePAM = this.effectivePosAtMin();
    var posRange = this.effectivePosAtMax() - ePAM;

    if (posRange == 0)
        return this.min;

    var scale = (this.max - this.min) / posRange;
    return (p - ePAM) * scale + this.min;
},

equivalentPosition: function(v)
{
    var valueRange = this.max - this.min;
    var ePAM = this.effectivePosAtMin();
    if (valueRange == 0)
        return ePAM;

    var scale = (this.effectivePosAtMax() - ePAM) / valueRange;
    return (v - this.min) * scale + ePAM;
}

} // RangeModel.prototype

var ate = new RangeModel();
