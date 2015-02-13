#include "commontoolbutton.h"

CommonToolButton::CommonToolButton(const QString &pic_name, const QString &text, QWidget *parent)
    :QToolButton(parent)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);

    this->setText(text);

//	QPalette text_palette = palette();
//	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
//	setPalette(text_palette);

    setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    setPopupMode(QToolButton::InstantPopup);

    QPixmap pixmap(pic_name);
    normal_icon = QIcon(pic_name);

    setIcon(pixmap);
    setIconSize(pixmap.size());

//    setFixedSize(pixmap.width(), pixmap.height() + 10);
	setAutoRaise(true);
    this->setObjectName("commonToolButton");
	mouse_over = false;
	mouse_press = false;
}

CommonToolButton::~CommonToolButton()
{

}

void CommonToolButton::enterEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = true;
    }
}

void CommonToolButton::leaveEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = false;
    }
}

void CommonToolButton::mousePressEvent(QMouseEvent *event)
{
    if(isEnabled() && event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QToolButton::mousePressEvent(event);
}

void CommonToolButton::setMousePress(bool is_press)
{
    this->mouse_press = is_press;
	update();
}

void CommonToolButton::paintEvent(QPaintEvent *event)
{
    if(this->mouse_over)
	{
        this->setIcon(QIcon(press_icon));
	}
	else
	{
        if(this->mouse_press)
		{
            this->setIcon(QIcon(hover_icon));
		}
        else
        {
            this->setIcon(QIcon(normal_icon));
        }
	}

	QToolButton::paintEvent(event);
}
