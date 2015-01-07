/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

import QtQuick 1.1

Rectangle {
    id:widget
    width:parent.width
    height:parent.height
    color:"white"
    state:"hide"

    property int index: 0

    states:
    [
        State
        {
            name:"active"
            PropertyChanges
            {
                target: widget
                visible: true
//                x:parent.x
            }

        },
        State
        {
            name:"hide"
            PropertyChanges
            {
                target: widget
//                x:parent.x - width
                visible: false
            }
        }
    ]

    transitions:
    [
        Transition
        {
            PropertyAnimation
            {
                property:"x"
                duration: 500
                easing.type: Easing.OutBounce
                easing.amplitude: 0.1
            }
        }
    ]
}
