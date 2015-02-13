#ifndef SYSTEMBUTTON_H
#define SYSTEMBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class SystemButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SystemButton(QWidget *parent = 0);
    void loadPixmap(QString pic_name);



protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QPixmap pixmap;
    enum ButtonStatus{NORMAL, ENTER, PRESS};
    ButtonStatus status;
    bool mouse_press; //按钮左键是否按下
    int btn_width;
    int btn_height;
};

#endif // SYSTEMBUTTON_H
