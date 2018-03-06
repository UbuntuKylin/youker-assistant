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

#include <glib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <QString>
#include <QSet>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QPainter>

#define MONITOR_TITLE_WIDGET_HEIGHT 77
#define TITLE_WIDGET_HEIGHT 39
#define DEVICE_MOUNT_PONINT_RECORD_FILE "/proc/mounts"

using std::string;

std::string getDesktopFileAccordProcName(QString procName, QString cmdline);
QPixmap getAppIconFromDesktopFile(std::string desktopFile, int iconSize = 24);
QString getDisplayNameAccordProcName(QString procName, std::string desktopFile);
std::string make_string(char *c_str);
QString formatProcessState(guint state);
QString getNiceLevel(int nice);
QString getNiceLevelWithPriority(int nice);
QString formatUnitSize(double v, const char** orders, int nb_orders);
QString formatByteCount(double v);
void setFontSize(QPainter &painter, int textSize);
QString formatDurationForDisplay(unsigned centiseconds);
QString getDeviceMountedPointPath(const QString &line);
QString getFileContent(const QString &filePath);
QSet<QString> getFileContentsLineByLine(const QString &filePath);
