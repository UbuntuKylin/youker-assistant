#ifndef KYLINTOOlBUTTON_H
#define KYLINTOOlBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class KylinToolButton : public QToolButton
{

public:
    explicit KylinToolButton(const QString &pic_name, const QString &text , QWidget *parent = 0);
    ~KylinToolButton();
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

#endif //KYLINTOOlBUTTON_H
