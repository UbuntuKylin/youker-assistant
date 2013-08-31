#ifndef TRANSMIT_H
#define TRANSMIT_H

#include <QObject>
#include <QStringList>

class Transmit : public QObject
{
    Q_OBJECT
public:
    explicit Transmit(QObject *parent = 0);
    void start_to_tansmit(QStringList str);
    Q_INVOKABLE QStringList getMyString();
signals:
    void sendToQml(QStringList str);
    
public slots:
private:
    QStringList list;
};

#endif // TRANSMIT_H
