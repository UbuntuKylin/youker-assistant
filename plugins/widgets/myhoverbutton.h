#ifndef MYHOVERBUTTON_H
#define MYHOVERBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

class MyHoverButton : public QLabel
{
    Q_OBJECT

    enum HoverButtonState {Normal, Hover, Press, Checked};

public:
    MyHoverButton(QWidget * parent=0);
    ~MyHoverButton();

    void setChecked(bool flag);
    bool isChecked();
    void setPicture(const QString &picture);
    HoverButtonState getButtonState() const;

signals:
    void clicked();
    void stateChanged();

protected:
    void enterEvent(QEvent * event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent * event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void updateBackgroundColor();
    void setState(HoverButtonState state);

private:
    HoverButtonState m_state;
    bool m_isChecked;
};

#endif // MYHOVERBUTTON_H
