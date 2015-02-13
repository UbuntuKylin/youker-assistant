#ifndef KYLINTITLEBAR_H
#define KYLINTITLEBAR_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include "systembutton.h"

class KylinTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit KylinTitleBar(QWidget *parent = 0);
    virtual ~KylinTitleBar();
    void setTitleWidth(int width) { title_width = width;}
    void setTitleName(QString title) { title_content = title;}
    void setTitleBackgound(QString img) { backgroud_image = img;}

protected:
    virtual void resizeEvent (QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
//    void showMinDialog();
    void closeDialog();

private:
    QPoint  press_point;
    QPoint  move_point;
    bool left_btn_pressed;
    QLabel *logo_label;
    QLabel *title_label;
    int title_width;
    QString title_content;
    QString backgroud_image;
//    SystemButton *min_btn;
    SystemButton *close_btn;
};

#endif // KYLINTITLEBAR_H
