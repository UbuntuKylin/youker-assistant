#ifndef SWITCHMENU_H
#define SWITCHMENU_H

#include <QWidget>

class SwitchMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchMenu(QWidget *parent = 0);

protected:
//    /*virtual */void paintEvent(QPaintEvent *);
//    virtual void mousePressEvent(QMouseEvent *);
//    virtual void mouseReleaseEvent(QMouseEvent *);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QPixmap     m_pixmapBk;
    QPixmap     m_pixmapFore;
    bool        m_bOn;
    bool        m_bLBtnDown;
};

#endif // SWITCHMENU_H
