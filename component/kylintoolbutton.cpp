#include "kylintoolbutton.h"

KylinToolButton::KylinToolButton(const QString &pic_name, const QString &text, QWidget *parent)
    :QToolButton(parent)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);

    this->setText(text);

//	QPalette text_palette = palette();
//	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
//	setPalette(text_palette);

//	QFont &text_font = const_cast<QFont &>(font());
//	text_font.setWeight(QFont::Bold);

    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    setPopupMode(QToolButton::InstantPopup);

    QPixmap pixmap(pic_name);
    normal_icon = QIcon(pic_name);
    hover_icon = QIcon(pic_name + "-hover");
    press_icon = QIcon(pic_name + "-press");
    setIcon(pixmap);
    setIconSize(pixmap.size());

//    setFixedSize(pixmap.width(), pixmap.height() + 10);
	setAutoRaise(true);
    this->setObjectName("transparentToolButton");
	mouse_over = false;
	mouse_press = false;
}

KylinToolButton::~KylinToolButton()
{

}

void KylinToolButton::enterEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = true;
    }
}

void KylinToolButton::leaveEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = false;
    }
}

void KylinToolButton::mousePressEvent(QMouseEvent *event)
{
    if(isEnabled() && event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QToolButton::mousePressEvent(event);
}

void KylinToolButton::setMousePress(bool is_press)
{
    this->mouse_press = is_press;
	update();
}

void KylinToolButton::paintEvent(QPaintEvent *event)
{
    if(this->mouse_over)
	{
        this->setIcon(QIcon(hover_icon));
	}
	else
	{
        if(this->mouse_press)
		{
            this->setIcon(QIcon(press_icon));
		}
        else
        {
            this->setIcon(QIcon(normal_icon));
        }
	}

	QToolButton::paintEvent(event);
}
