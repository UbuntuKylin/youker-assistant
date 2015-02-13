#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QPainter>
#include <QPen>
#include <QHBoxLayout>
#include <QEvent>
#include <QVBoxLayout>
#include <QSignalMapper>

class ContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = 0);
    ~ContentWidget();
    void setLanguage();

private:
protected:

public slots:

signals:

private:


};

#endif // CONTENTWIDGET_H
