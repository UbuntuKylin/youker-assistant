#ifndef QUIBO_H
#define QUIBO_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMouseEvent>

namespace Ui {
class QUIBO;
}

class QUIBO : public QWidget
{
    Q_OBJECT
    
public:
    explicit QUIBO(QWidget *parent = 0);
    ~QUIBO();
    
private:
    Ui::QUIBO *ui;

    int cindex;
    QStringList *colors;
    void mouseReleaseEvent(QMouseEvent *me);
    void changeColor();
};

#endif // QUIBO_H
