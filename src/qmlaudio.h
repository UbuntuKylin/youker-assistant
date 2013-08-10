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
#ifndef QMLAUDIO_H
#define QMLAUDIO_H

#include <phonon>
#include <QDeclarativeItem>
#include <QUrl>
class QmlAudio : public QDeclarativeItem
{
    Q_OBJECT
public:
    QmlAudio(QDeclarativeItem *parent = 0);

public slots:
    void setSong(const QUrl & songUrl);
    void play();
    void pause();
    void stop();
private:
    Phonon::MediaObject *audioObject;

};

#endif // QMLAUDIO_H
