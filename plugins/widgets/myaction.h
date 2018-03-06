#ifndef _MYACTION_H_
#define _MYACTION_H_

#include <QAction>
#include <QString>
#include <QIcon>
#include <QKeySequence>

class MyAction : public QAction
{

public:

    MyAction (QObject * parent, const char * name, bool autoadd = true );
    MyAction (QObject * parent, bool autoadd = true );
    MyAction (const QString & text, QKeySequence accel,
               QObject * parent, const char * name = "",
               bool autoadd = true );
    MyAction (QKeySequence accel, QObject * parent,
               const char * name = "", bool autoadd = true );
    ~MyAction();
    void addShortcut(QKeySequence key);
    void change(const QIcon & icon, const QString & text );
    void change(const QString & text);

protected:
    void addActionToParent();
};

#endif

