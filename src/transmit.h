#ifndef TRANSMIT_H
#define TRANSMIT_H

#include <QObject>

class Transmit : public QObject
{
    Q_OBJECT
public:
    explicit Transmit(QObject *parent = 0);
    void start_to_tansmit(QString str);
signals:
    void sendToQml(QString str);
    
public slots:
    
};

#endif // TRANSMIT_H
