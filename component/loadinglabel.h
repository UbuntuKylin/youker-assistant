#ifndef LOADINLABEL_H
#define LOADINLABEL_H

#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QPixmap>

class LoadingLabel : public QLabel
{
    Q_OBJECT
public:
    explicit LoadingLabel(QWidget *parent = 0, bool flag = true);//flag=ture:big picture;flag=false:small picture
    ~LoadingLabel();
    void loadAllPictures();
    void startLoading();
    void stopLoading();

public slots:
    void changeAnimationStep();

private:
    QTimer *timer;
    QVector<QPixmap> png_vector;
    int currentpage;
    int bigFlag;
};

#endif // LOADINLABEL_H
