#include "agentlistitem.h"
#include <QHBoxLayout>
#include <QMouseEvent>

AgentListItem::AgentListItem(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    mouse_press = false;
    label = new QLabel();
    delede_button = new QPushButton();
    delede_button->setFocusPolicy(Qt::NoFocus);
    delede_button->setObjectName("transparentButton");

    QPixmap pixmap("://res/delete.png");
    delede_button->setIcon(pixmap);
    delede_button->setIconSize(pixmap.size());
    connect(delede_button, SIGNAL(clicked()), this, SLOT(onDeleteButtonClicked()));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(delede_button);
//    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(5);
    layout->setMargin(0);
    setLayout(layout);
}

AgentListItem::~AgentListItem()
{
}

void AgentListItem::setCurrentItemName(QString name)
{
    label->setText(name);
}

QString AgentListItem::getCurrentItemName()
{
    QString name = label->text();
    return name;
}

void AgentListItem::onDeleteButtonClicked()
{
    QString name = label->text();
    emit removeItem(name);
}

void AgentListItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
}

void AgentListItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        emit showItemName(label->text());
        mouse_press = false;
    }
}
