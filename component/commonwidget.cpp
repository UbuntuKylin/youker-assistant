#include "commonwidget.h"

CommonWidget::CommonWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(110, 110);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(233,238,241));//#e9eef1
    this->setPalette(palette);
}
