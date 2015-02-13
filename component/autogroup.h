#ifndef AUTOGROUP_H
#define AUTOGROUP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include "kylinswitcher.h"

class AutoGroup : public QWidget
{
    Q_OBJECT
public:
    explicit AutoGroup(QWidget *parent = 0);
    void setLanguage(QString key, QString value);
//    void pushMap(QString key, QString value);
    void initData(QMap<QString,QString> data);
    QString dekstopFile;

signals:
    void autoStatusChange();

public slots:

private:
//    QHBoxLayout *h_layout;
    QLabel *logo_label;
    QLabel *name_label;
    QLabel *comment_label;
    KylinSwitcher *switcher;
//    QMap<QString, QString> name;
};

#endif // AUTOGROUP_H
