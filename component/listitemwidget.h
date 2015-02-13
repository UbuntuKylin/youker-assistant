#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class ListItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListItemWidget(QWidget *parent = 0);

signals:

private:
    QLabel *title_label;
    QLabel *msg_label;
};

#endif // LISTITEMWIDGET_H
