#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QVBoxLayout>

class MemoryCircle;

class MemoryWidget : public QWidget
{
    Q_OBJECT

public:
    MemoryWidget(QWidget *parent = 0);
    ~MemoryWidget();

public slots:
    void onUpdateMemoryStatus();

signals:
    void rebackMemoryInfo(const QString &info, double percent);

private:
    QLabel *m_title = nullptr;
    MemoryCircle *m_memoryCircle = nullptr;
    QVBoxLayout *m_widgetLayout = nullptr;
    QHBoxLayout *mainLayout = nullptr;
};

#endif // MEMORYWIDGET_H
