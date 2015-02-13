#ifndef LABELGROUP_H
#define LABELGROUP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>

class LabelGroup : public QWidget
{
    Q_OBJECT
public:
    explicit LabelGroup(QWidget *parent = 0);
    void setLanguage(QString key, QString value);
//    void pushMap(QString key, QString value);

signals:

public slots:

private:
    QHBoxLayout *h_layout;
    QLabel *key_info;
    QLabel *value_info;
//    QMap<QString, QString> name;
};

#endif // LABELGROUP_H
