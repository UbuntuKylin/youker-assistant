#include "memorywidget.h"
#include "memorycircle.h"

#include <QDebug>
#include <QObject>

MemoryWidget::MemoryWidget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *w = new QWidget;
    m_widgetLayout = new QVBoxLayout(w);
    m_widgetLayout->setContentsMargins(0, 0, 0, 0);
    m_widgetLayout->setSpacing(0);

    m_title = new QLabel(tr("Memory"));
    m_title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_title->setStyleSheet("background:transparent;font-size:24px;color:#000000");
    /*QFont font = m_title->font();
    font.setPointSize(24);
    font.setWeight(QFont::Light);
    m_title->setFont(font);*/

    m_memoryCircle = new MemoryCircle;
    connect(m_memoryCircle, SIGNAL(rebackMemoryInfo(QString,double)), this, SIGNAL(rebackMemoryInfo(QString,double)));

    m_widgetLayout->addWidget(m_title);
    m_widgetLayout->addWidget(m_memoryCircle);

    mainLayout->addWidget(w, 0, Qt::AlignCenter);
}

MemoryWidget::~MemoryWidget()
{
    delete m_title;
    delete m_memoryCircle;
    QLayoutItem *child;
    while ((child = m_widgetLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    delete mainLayout;
}

void MemoryWidget::onUpdateMemoryStatus()
{
    m_memoryCircle->onUpdateMemoryStatus();
}
