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
#include "qmlaudio.h"
#include <QObject>
#include <phonon>
#include <QDebug>
#include <QSound>

QString music_path;
QmlAudio::QmlAudio(QDeclarativeItem *parent) : QDeclarativeItem(parent)
{

}

void QmlAudio::setSong(const QUrl & songUrl) {
    audioObject->setCurrentSource(Phonon::MediaSource(songUrl));
}

void QmlAudio::play() {
    audioObject = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(music_path));
    audioObject->play();
//    QSound player(music_path);
//    player.play();
//    if (player.isFinished() == true) {
//        player.stop();
//    }
}

void QmlAudio::pause() {
    audioObject->pause();
}
void QmlAudio::stop() {
    audioObject->stop();
}
