/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

ListModel {
    id: model
    ListElement {
        itemTitle: "Item title 1"
        attributes: [
            ListElement { subItemTitle: "kobe 1/1" },
            ListElement { subItemTitle: "kobe 2/1" }
        ]
    }
    ListElement {
        itemTitle: "Item title 2"
        attributes: [
            ListElement { subItemTitle: "kobe 1/3" },
            ListElement { subItemTitle: "kobe 2/3" },
            ListElement { subItemTitle: "kobe 3/3" }
        ]
    }
    ListElement {
        itemTitle: "Item title 3"
        attributes: [
            ListElement { subItemTitle: "kobe 1/4" },
            ListElement { subItemTitle: "kobe 2/4" },
            ListElement { subItemTitle: "kobe 3/4" },
            ListElement { subItemTitle: "kobe 4/4" }
        ]
    }
}

