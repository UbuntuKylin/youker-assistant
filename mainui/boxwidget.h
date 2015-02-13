#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include "../component/kylinlistmodel.h"

class BoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoxWidget(QWidget *parent = 0, QString path = "");
    ~BoxWidget();
    void loadPlugins();
    void initPluginWidget();

signals:

public slots:
  void OnClickListView(const QModelIndex & index);
  void displayBoxHomePage();
  void displayBoxSubPage(QString plugin_id);

private:
    QListView *list_view;
    CFetureListModel m_feture_Model;
    QString plugin_path;
};

#endif // BOXWIDGET_H
