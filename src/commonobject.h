#ifndef COMMONOBJECT_H
#define COMMONOBJECT_H

#include <QObject>
#include <QLocale>

class CommonObject : public QObject
{
    Q_OBJECT
public:
    explicit CommonObject(QObject *parent = 0);
    //得到安装操作系统的语言版本
    Q_INVOKABLE QString get_locale_version();

signals:

public slots:

};

#endif // COMMONOBJECT_H
