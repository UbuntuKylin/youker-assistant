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

#include "accountcache.h"

AccountCache::AccountCache()
{
    dir = QDesktopServices::storageLocation(QDesktopServices::HomeLocation)+"/.config/ubuntukylin/youker-assistant/";
}

QStringList AccountCache::getUserName()
{
    QStringList list;
    QDomElement element = accountsDocument.documentElement().firstChildElement("account");
    while(!element.isNull())
    {
        list << element.firstChildElement("username").text();
        element = element.nextSiblingElement("account");
    }

    return list;
}


QString AccountCache::getPassword(const QString &username)
{
    QDomElement element = accountsDocument.documentElement().firstChildElement("account");
    while(!element.isNull())
    {
        if(element.firstChildElement("username").text() == username)
        {
            QByteArray passwdEncryptedBa = QByteArray::fromBase64(
                    element.firstChildElement("password").text().toUtf8());
            QString passwd = calculateXor(passwdEncryptedBa, username.toUtf8());
            return passwd;
        }
        element = element.nextSiblingElement("account");
    }

    return "";
}

void AccountCache::addAccount(const QString &username, const QString &passwd)
{
    if(accountsDocument.documentElement().isNull())
    {
        accountsDocument.appendChild(accountsDocument.createElement("accounts"));
    }

    QDomElement element = accountsDocument.documentElement().firstChildElement("account");
    while(!element.isNull())
    {
        if(element.firstChildElement("username").text() == username)
        {
            accountsDocument.documentElement().removeChild(element);
            break;
        }
        element = element.nextSiblingElement("account");
    }

    QDomElement newElement = accountsDocument.createElement("account");

    QDomElement newElementAccount = accountsDocument.createElement("username");
    newElementAccount.appendChild(accountsDocument.createTextNode(username));
    newElement.appendChild(newElementAccount);

    QDomElement newElementPasswd = accountsDocument.createElement("password");
    newElementPasswd.appendChild(accountsDocument.createTextNode(
            calculateXor(passwd.toUtf8(), username.toUtf8()).toBase64()));
    newElement.appendChild(newElementPasswd);

    accountsDocument.documentElement().appendChild(newElement);

    saveToFile();
}

void AccountCache::loadFromFile()
{
    QDir cacheDir(dir);
    if(cacheDir.exists())
    {
        QFile file(dir+ "accountCache");
        if(file.open(QIODevice::ReadOnly))
        {
            accountsDocument.setContent(&file, true);
        }
    }
}

void AccountCache::saveToFile()
{
    QDir cacheDir;
    if(!cacheDir.exists(dir))
        cacheDir.mkpath(dir);

    QString fileAccounts =dir + "accountCache";
    QFile file(fileAccounts);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream textStream(&file);
        accountsDocument.save(textStream, 2);
        file.close();
    }
}

QByteArray AccountCache::calculateXor(const QByteArray& data, const QByteArray& key)
{
    if(key.isEmpty())
        return data;

    QByteArray result;
    for(int i = 0 , j = 0; i < data.length(); ++i , ++j)
    {
        if(j == key.length())
            j = 0;
        result.append(data.at(i) ^ key.at(j));
    }
    return result;
}
