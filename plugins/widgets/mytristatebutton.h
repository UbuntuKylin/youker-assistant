#ifndef MYTRISTATEBUTTON_H
#define MYTRISTATEBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

class MyTristateButton : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QString normalPic READ getNormalPic WRITE setNormalPic DESIGNABLE true)
    Q_PROPERTY(QString hoverPic READ getHoverPic WRITE setHoverPic DESIGNABLE true)
    Q_PROPERTY(QString pressPic READ getPressPic WRITE setPressPic DESIGNABLE true)
    Q_PROPERTY(QString checkedPic READ getCheckedPic WRITE setCheckedPic DESIGNABLE true)

public:
    MyTristateButton(QWidget * parent=0);

    ~MyTristateButton();

    void setChecked(bool flag);
    void setCheckable(bool flag);
    bool isChecked();
    bool isCheckable();

    void setNormalPic(const QString & normalPic);
    void setHoverPic(const QString & hoverPic);
    void setPressPic(const QString & pressPic);
    void setCheckedPic(const QString & checkedPic);

    inline const QString getNormalPic() const {return m_normalPic;}
    inline const QString getHoverPic() const {return m_hoverPic;}
    inline const QString getPressPic() const {return m_pressPic;}
    inline const QString getCheckedPic() const {return m_checkedPic;}

    enum ButtonState {Normal, Hover, Press, Checked};

    ButtonState getButtonState() const;

signals:
//Q_SIGNALS:
    void clicked();
    void stateChanged();

protected:
    void enterEvent(QEvent * event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent * event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void updateIcon();
    void setState(ButtonState state);

private:
    ButtonState m_state = Normal;
    bool m_isChecked = false;
    bool m_isCheckable = false;
    QString m_normalPic;
    QString m_hoverPic;
    QString m_pressPic;
    QString m_checkedPic;
};

#endif // MYTRISTATEBUTTON_H
