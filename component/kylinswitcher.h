#ifndef KYLINSWITCHER_H
#define KYLINSWITCHER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class KylinSwitcher : public QWidget
{
    Q_OBJECT
public:
    explicit KylinSwitcher(QWidget *parent = 0);
    bool switchedOn;
//    void setSwitchStatus(bool flag) {switchedOn = flag;}

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
//    void enterEvent(QEvent *);

signals:
    void clicked();

public slots:

private:
    QPixmap pixmap_on;
    QPixmap pixmap_off;
    bool mouse_press;
};

#endif // KYLINSWITCHER_H
