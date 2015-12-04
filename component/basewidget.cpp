#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

BaseWidget::BaseWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->initConnect();
}

void BaseWidget::initUI()
{
    m_vLayout = new QVBoxLayout;
}

void BaseWidget::initConnect()
{
}

void BaseWidget::insertWidget(QWidget *widget)
{
    m_vLayout->addWidget(widget);
    m_vLayout->setContentsMargins(0, 0, 0, 0);
    m_vLayout->setSpacing(0);

    this->setLayout(m_vLayout);
}

void BaseWidget::insertLayout(QLayout *layout)
{
    m_vLayout->addLayout(layout);
    m_vLayout->setContentsMargins(0, 0, 0, 0);
    m_vLayout->setSpacing(0);

    this->setLayout(m_vLayout);
}
