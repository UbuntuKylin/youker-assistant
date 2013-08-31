#include "transmit.h"
#include <QDebug>
QStringList speedlist;
Transmit::Transmit(QObject *parent) :
    QObject(parent)
{

}

void Transmit::start_to_tansmit(QStringList str) {
    speedlist = str;
//    emit sendToQml(str);
}

QStringList Transmit::getMyString()
{
    return list;
}
