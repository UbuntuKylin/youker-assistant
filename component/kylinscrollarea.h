#ifndef KYLINSCROLLAREA_H
#define KYLINSCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

class AutoGroup;

class KylinScrollArea : public QWidget
{
    Q_OBJECT
public:
    explicit KylinScrollArea(QWidget *parent = 0/*, int width = 0, int height = 0, int spacing = 0*/);
    void calculate_data();
    void add_card(AutoGroup *card);
    QWidget *cardPanel;

private:
    QScrollArea *scroll_area;
    int cardcount;
    int number_per_row;
    int itemwidth;
    int itemheight;
    int cardspacing;
};

#endif // KYLINSCROLLAREA_H
