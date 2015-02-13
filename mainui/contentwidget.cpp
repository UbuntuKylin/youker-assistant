#include "contentwidget.h"
#include <QDebug>

ContentWidget::ContentWidget(QWidget *parent)
	: QWidget(parent)
{
//    this->resize(900, 326);
    this->setFixedSize(900, 326);

}

ContentWidget::~ContentWidget()
{
}
