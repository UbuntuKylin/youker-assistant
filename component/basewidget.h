#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
class QVBoxLayout;

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = 0);
    void insertWidget(QWidget *widget);
    void insertLayout(QLayout *layout);
    void initUI();
    void initConnect();

signals:

public slots:

private:
    QVBoxLayout *m_vLayout;
};

#endif // BASEWIDGET_H
