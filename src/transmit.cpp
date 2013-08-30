#include "transmit.h"
#include <QDebug>
Transmit::Transmit(QObject *parent) :
    QObject(parent)
{

}

void Transmit::start_to_tansmit(QString str) {
    emit sendToQml(str);
}
