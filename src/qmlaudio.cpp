
#include "qmlaudio.h"
#include <QObject>
#include <phonon>

QmlAudio::QmlAudio(QDeclarativeItem *parent) : QDeclarativeItem(parent)
{

    audioObject = Phonon::createPlayer(Phonon::MusicCategory,
                                       Phonon::MediaSource("/home/wenbo/youker-assistant/qml/img/qc.mp3"));
}

 void QmlAudio::setSong(const QUrl & songUrl)
{
    audioObject->setCurrentSource(Phonon::MediaSource(songUrl));
}

void QmlAudio::play()
{
    audioObject->play();
}

void QmlAudio::pause()
{
    audioObject->pause();
}
void QmlAudio::stop()
{
    audioObject->stop();
}
