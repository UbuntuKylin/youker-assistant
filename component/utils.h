/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef UTILS_H
#define UTILS_H

#include <QString>

#define ITEMHEIGHT 30
#define ITEMHSPACE 10
#define ITEMVSPACE 5
#define PAGESPACE 20
#define ITEMWIDTH 650
#define SHADOW_LEFT_TOP_PADDING 2
#define SHADOW_RIGHT_BOTTOM_PADDING 4
#define MAIN_WINDOW_WIDTH 900
#define MAIN_WINDOW_HEIGHT 600
#define TITLE_BAR_HEIGHT 39
#define ITEM_LEFT_RIGHT_PADDING 5
//const int windowShadowPadding = 10;

//#define VERSION "2.4.1"

const QString KYLIN_COMPANY_SETTING = "kylin/kylin-assistant";
const QString KYLIN_SETTING_FILE_NAME_SETTING = "kylin-assistant";

enum CleanerModuleID {
    CacheApt = 0,
    CacheSoftware,
    CacheThumbnail,
    CacheFirefox,
    CacheChromium,
    CookieFirefox,
    CookieChromium,
    TraceX11,
    InvalidID,
};

enum CleanerCategoryID {
    CacheCategory = 0,
    CookieCategory,
    TraceCategory,
    InvalidCategory,
};

typedef enum{
    YOUKER_EN,
    YOUKER_ZH_CN,
    YOUKER_ES,
} LANGUAGE;

typedef enum{
    CACHE,
    PACAKAGE,
    COOKIES,
    BROWSER,
    TRACE,
    BIGFILE,
} CLEANERTAB;

struct AutoData
{
    QString appPath;
    QString appName;
    QString appComment;
    QString iconName;
    QString appStatus;
};

typedef enum{
    BUTTON_ENTER,
    BUTTON_LEAVE,
    BUTTON_PRESSED,
    BUTTON_DISABLE,
    BUTTON_FIRST,
    BUTTON_SCALED,
}BUTTONSTATUS;

typedef enum{
    HOMEPAGE,
    CLEANPAGE,
    INFOPAGE,
    SETTINGPAGE,
    BOXPAGE,
}PAGESTATUS;

#endif // UTILS_H
