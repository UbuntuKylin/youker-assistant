#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

class ComputerPage;

class ScrollWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollWidget(QWidget *parent = 0);
    void addScrollWidget(ComputerPage *widget);
    QWidget *zone;

private:
    QScrollArea *scroll_area;
    QVBoxLayout *v_layout;
    int widget_count;
    int zone_height;
};

#endif // SCROLLWIDGET_H
