
#include "qmlaudio.h"
#include <QObject>
#include <phonon>
#include <QDebug>
QString music_path;
QmlAudio::QmlAudio(QDeclarativeItem *parent) : QDeclarativeItem(parent)
{

//    qDebug() << music_path;
//    audioObject = Phonon::createPlayer(Phonon::MusicCategory,
//                                       Phonon::MediaSource(music_path));
}

 void QmlAudio::setSong(const QUrl & songUrl)
{
    audioObject->setCurrentSource(Phonon::MediaSource(songUrl));
}

void QmlAudio::play()
{
    qDebug() << "test for playing.....";
    qDebug() << music_path;
    audioObject = Phonon::createPlayer(Phonon::MusicCategory,
                                       Phonon::MediaSource(music_path));
    qDebug() << "test for playing111.....";
    audioObject->play();
    qDebug() << "test for playing222.....";

}

void QmlAudio::pause()
{
//    audioObject = Phonon::createPlayer(Phonon::MusicCategory,
//                                       Phonon::MediaSource(music_path));
    audioObject->pause();
}
void QmlAudio::stop()
{
//    audioObject = Phonon::createPlayer(Phonon::MusicCategory,
//                                       Phonon::MediaSource(music_path));
    audioObject->stop();
}
