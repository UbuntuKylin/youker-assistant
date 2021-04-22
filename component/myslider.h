#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>
#include <QLabel>
#include <QStringList>
#include <QMap>
#include <QString>
#include <QMouseEvent>
#include <QVariant>

class mySlider : public QSlider
{
public:
    mySlider(QWidget *parent=0);
    ~mySlider();
    void setRangeLable(QMap<QString,QVariant>,QStringList);
    void setCurValue(int);
    int getCurValue();
    void updateTipLabel();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
private:
    QLabel *tiplable;
    QLabel *minlable;
    QLabel *maxlable;

    qreal max;
    qreal min;

    int cur_value;
};

#endif // MYSLIDER_H
