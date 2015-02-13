#ifndef AGENTLISTITEM_H
#define AGENTLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class AgentListItem : public QWidget
{
    Q_OBJECT
public:
    explicit AgentListItem(QWidget *parent = 0);
    ~AgentListItem();
    void setCurrentItemName(QString name);
    QString getCurrentItemName();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void showItemName(QString name);
    void removeItem(QString name);

public slots:
    void onDeleteButtonClicked();

private:
    bool mouse_press;
    QLabel *label;
    QPushButton *delede_button;

};


#endif // AGENTLISTITEM_H
