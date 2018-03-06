#ifndef MYSEARCHEDIT_H
#define MYSEARCHEDIT_H

#include <QFrame>
#include <QSize>
#include <QLineEdit>
#include <QPropertyAnimation>
#include <QLabel>

#include "mytristatebutton.h"

class MySearchEdit : public QFrame
{
    Q_OBJECT
public:
    explicit MySearchEdit(QWidget *parent = 0);
    ~MySearchEdit();

    void setPlaceHolder(const QString &text);
    const QString searchedText() const;
    QLineEdit *getLineEdit() const;

public slots:
    void clearEdit();
    void setEditFocus();
    void setText(const QString & text);
    void clearAndFocusEdit();

signals:
    void textChanged();

protected:
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

private:
    QPropertyAnimation *m_animation = nullptr;
    QEasingCurve m_showCurve;
    QEasingCurve m_hideCurve;
    QSize m_size;
    QLineEdit *m_edit = nullptr;
    QLabel *m_searchBtn = nullptr;
    QLabel *m_placeHolder = nullptr;
    MyTristateButton *m_clearBtn = nullptr;
};

#endif // MYSEARCHEDIT_H
