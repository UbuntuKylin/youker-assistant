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
