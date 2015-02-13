#include "kylinbutton.h"

KylinButton::KylinButton(QWidget *parent)
	:QPushButton(parent)
{	
	status = NORMAL;
	mouse_press = false;
}

KylinButton::~KylinButton()
{

}

void KylinButton::setPicName(QString pic_name)
{
	this->pic_name = pic_name;
	setFixedSize(QPixmap(pic_name).size());
}

void KylinButton::enterEvent(QEvent *)
{
	status = ENTER;
	update();
}

void KylinButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		status = PRESS;
		update();
	}
}

void KylinButton::mouseReleaseEvent(QMouseEvent *event)
{
	if(mouse_press  && this->rect().contains(event->pos()))
	{
		mouse_press = false;
		status = ENTER;
		update();
		emit clicked();
	}
}

void KylinButton::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();
}

void KylinButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QPixmap pixmap;
	switch(status)
	{
	case NORMAL:
		{
			pixmap.load(pic_name);
			break;
		}    
	case ENTER:
		{
			pixmap.load(pic_name + QString("_hover"));
			break;
		} 
	case PRESS:
		{
			pixmap.load(pic_name + QString("_pressed"));	
			break;
		}   
	case NOSTATUS:
		{
			pixmap.load(pic_name);	
			break;
		}   
	default:
		pixmap.load(pic_name);
	}
	
	painter.drawPixmap(rect(), pixmap);
}
