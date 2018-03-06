#include "myhoverbutton.h"

#include <QMouseEvent>
#include <QEvent>

MyHoverButton::MyHoverButton(QWidget *parent)
    : QLabel(parent)
    ,m_state(Normal)
    ,m_isChecked(false)
{
    this->setStyleSheet("QLabel{background-color:transparent;}");
}

MyHoverButton::~MyHoverButton()
{
}

void MyHoverButton::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);

    if (!m_isChecked){
        setState(Hover);
    }

    event->accept();
    //QLabel::enterEvent(event);
}

void MyHoverButton::leaveEvent(QEvent *event)
{
    if (!m_isChecked){
        setState(Normal);
    }

    event->accept();
    //QLabel::leaveEvent(event);
}

void MyHoverButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    setState(Press);

    event->accept();
    //QLabel::mousePressEvent(event);
}

void MyHoverButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos()))
        return;

    m_isChecked = !m_isChecked;
    if (m_isChecked){
        setState(Checked);
    } else {
        setState(Normal);
    }

    event->accept();
    //QLabel::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void MyHoverButton::mouseMoveEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos())) {
        setState(Normal);
    }
}

void MyHoverButton::updateBackgroundColor()
{
    switch (m_state) {
    case Hover:
        this->setStyleSheet("QLabel{background-color:#e0f4f9;}");
        break;
    case Press:
        this->setStyleSheet("QLabel{background-color:#e0f4f9;}");
        break;
    case Checked:
        this->setStyleSheet("QLabel{background-color:#e0f4f9;}");
        break;
    default:
        this->setStyleSheet("QLabel{background-color:transparent;}");
        break;
    }
    setAlignment(Qt::AlignCenter);
}

void MyHoverButton::setState(MyHoverButton::HoverButtonState state)
{
    if (m_state == state)
        return;

    m_state = state;

    updateBackgroundColor();
}

void MyHoverButton::setChecked(bool flag)
{
    m_isChecked = flag;
    if (m_isChecked){
        setState(Checked);
    } else {
        setState(Normal);
    }
}

bool MyHoverButton::isChecked()
{
    return m_isChecked;
}

void MyHoverButton::setPicture(const QString &picture)
{
    setPixmap(QPixmap(picture));
}

MyHoverButton::HoverButtonState MyHoverButton::getButtonState() const
{
    return m_state;
}
