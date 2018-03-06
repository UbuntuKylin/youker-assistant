#ifndef MYUNDERLINEBUTTON_H
#define MYUNDERLINEBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

class QVBoxLayout;

class MyUnderLineButton : public QWidget
{
    Q_OBJECT

    enum UnderLineButtonState {Normal, Hover, Press, Checked};

public:
    MyUnderLineButton(QWidget * parent=0);
    ~MyUnderLineButton();

    void setChecked(bool flag);
    bool isChecked();
    void setName(const QString &name);
    UnderLineButtonState getButtonState() const;

signals:
    void clicked();

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void updateStyleSheet();
    void setState(UnderLineButtonState state);

private:
    UnderLineButtonState m_state;
    bool m_isChecked;
    QLabel *m_textLabel = nullptr;
    QLabel *m_underlineLabel = nullptr;
    QVBoxLayout *m_layout = nullptr;
};

#endif // MYUNDERLINEBUTTON_H
