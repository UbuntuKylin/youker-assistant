#include "myunderlinebutton.h"

#include <QMouseEvent>
#include <QEvent>
#include <QVBoxLayout>


MyUnderLineButton::MyUnderLineButton(QWidget *parent)
    : QWidget(parent)
    ,m_state(Normal)
    ,m_isChecked(false)
{
    this->setFixedSize(80, 30);

    m_textLabel = new QLabel;
    m_textLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;text-align:center;}");

    m_underlineLabel = new QLabel;
    m_underlineLabel->setFixedSize(52, 2);
    m_underlineLabel->setStyleSheet("QLabel{background-color:#ffffff;}");
    m_underlineLabel->hide();

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0,5,0,5);

    m_layout->addWidget(m_textLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    m_layout->addWidget(m_underlineLabel, 0, Qt::AlignBottom | Qt::AlignHCenter);
}

MyUnderLineButton::~MyUnderLineButton()
{
    delete m_textLabel;
    delete m_underlineLabel;
}

void MyUnderLineButton::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);

    if (!m_isChecked){
        setState(Hover);
    }

    event->accept();
    //QWidget::enterEvent(event);
}

void MyUnderLineButton::leaveEvent(QEvent *event)
{
    if (!m_isChecked){
        setState(Normal);
    }

    event->accept();
    //QWidget::leaveEvent(event);
}

void MyUnderLineButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    setState(Press);

    event->accept();
    //QWidget::mousePressEvent(event);
}

void MyUnderLineButton::mouseReleaseEvent(QMouseEvent *event)
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
    //QWidget::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void MyUnderLineButton::mouseMoveEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos())) {
        setState(Normal);
    }
}

void MyUnderLineButton::updateStyleSheet()
{
    switch (m_state) {
    case Hover:
        m_textLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;text-align:center;font-weight:bold;}");
        m_underlineLabel->hide();
        break;
    case Press:
        m_textLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;text-align:center;font-weight:bold;}");
        m_underlineLabel->hide();
        break;
    case Checked:
        m_textLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;text-align:center;font-weight:bold;}");
        m_underlineLabel->show();
        break;
    default:
        m_textLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;text-align:center;}");
        m_underlineLabel->hide();
        break;
    }
}

void MyUnderLineButton::setState(MyUnderLineButton::UnderLineButtonState state)
{
    if (m_state == state)
        return;

    m_state = state;

    updateStyleSheet();
}

void MyUnderLineButton::setChecked(bool flag)
{
    m_isChecked = flag;
    if (m_isChecked){
        setState(Checked);
    } else {
        setState(Normal);
    }
}

bool MyUnderLineButton::isChecked()
{
    return m_isChecked;
}

void MyUnderLineButton::setName(const QString &name)
{
    this->m_textLabel->setText(name);
}

MyUnderLineButton::UnderLineButtonState MyUnderLineButton::getButtonState() const
{
    return m_state;
}
