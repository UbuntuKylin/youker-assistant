#include "myactiongroup.h"
#include <QAction>
#include <QList>
#include <QWidget>

MyActionGroup::MyActionGroup( QObject * parent ) : QActionGroup(parent)
{
    setExclusive(true);
    connect(this, SIGNAL(triggered(QAction *)), this, SLOT(itemTriggered(QAction *)) );
}

void MyActionGroup::setChecked(int ID) {
    QList <QAction *> l = actions();
    for (int n=0; n < l.count(); n++) {
        if ( (!l[n]->isSeparator()) && (l[n]->data().toInt() == ID) ) {
            l[n]->setChecked(true);
            return;
        }
    }
}

int MyActionGroup::checked() {
    QAction * a = checkedAction();
    if (a)
        return a->data().toInt();
    else
        return -1;
}

void MyActionGroup::uncheckAll() {
    QList <QAction *> l = actions();
    for (int n=0; n < l.count(); n++) {
        l[n]->setChecked(false);
    }
}

void MyActionGroup::setActionsEnabled(bool b) {
    QList <QAction *> l = actions();
    for (int n=0; n < l.count(); n++) {
        l[n]->setEnabled(b);
    }
}

void MyActionGroup::clear(bool remove) {
    while (actions().count() > 0) {
        QAction * a = actions()[0];
        if (a) {
            removeAction(a);
            if (remove) a->deleteLater();
        }
    }
}

void MyActionGroup::itemTriggered(QAction *a) {
    int value = a->data().toInt();

    emit activated(value);
}

void MyActionGroup::addTo(QWidget *w) {
    w->addActions( actions() );
}

void MyActionGroup::removeFrom(QWidget *w) {
    for (int n=0; n < actions().count(); n++) {
        w->removeAction( actions()[n] );
    }
}
