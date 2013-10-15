#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class PushButton : public QPushButton
{
public:
    explicit PushButton(QWidget *parent = 0);
    ~PushButton();
    void loadPixmap(QString pic_name);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
private:
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus status;
    QPixmap pixmap;

    int btn_width;
    int btn_height;
    bool mouse_press;
};

#endif // PUSHBUTTON_H
