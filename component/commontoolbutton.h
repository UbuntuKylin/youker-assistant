#ifndef COMMONOOlBUTTON_H
#define COMMONOOlBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class CommonToolButton : public QToolButton
{

public:
    explicit CommonToolButton(const QString &pic_name, const QString &text , QWidget *parent = 0);
    ~CommonToolButton();
    void setMousePress(bool is_press);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public:
	bool mouse_over; //鼠标是否移过
	bool mouse_press; //鼠标是否按下
    QIcon normal_icon;
    QIcon hover_icon;
    QIcon press_icon;
};

#endif //COMMONOOlBUTTON_H
