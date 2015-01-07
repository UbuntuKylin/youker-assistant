/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef ACCOUNTCACHE_H
#define ACCOUNTCACHE_H

#include <QStringList>
#include <QDomElement>
#include <QDir>
#include <QFile>
#include <QDesktopServices>
#include <QTextStream>
#include <qmath.h>

class AccountCache
{
public:
    AccountCache();
    QString getPassword(const QString& bareJid);
    void addAccount(const QString& bareJid, const QString& passwd);
    void loadFromFile();
    QStringList getUserName();
private:
    void saveToFile();
    QDomDocument accountsDocument;
    QString dir ;
    QByteArray calculateXor(const QByteArray &data, const QByteArray &key);
};

#endif // ACCOUNTCACHE_H
