

#ifndef QCOMBOBOXQMLADAPTER_H
#define QCOMBOBOXQMLADAPTER_H

#include
#include
#include
#include

//#include "entrylistmodel.h"

class CustomComboBox : public QComboBox {
    Q_OBJECT
public:
    explicit CustomComboBox(QWidget *parent = 0) : QComboBox(parent){}

protected:
    void focusInEvent(QFocusEvent *event){ QComboBox::focusInEvent(event); emit focusIn(); }
    void focusOutEvent(QFocusEvent *event){ QComboBox::focusOutEvent(event); emit focusOut(); }

signals:
    void focusIn();
    void focusOut();
};

class QComboBoxQmlAdapter : public QGraphicsProxyWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit QComboBoxQmlAdapter(QGraphicsItem *parent = 0);
    ~QComboBoxQmlAdapter();

    void setText(const QString text) { m_comboBox->setEditText(text); }
    QString text() { return m_comboBox->currentText(); }

    Q_INVOKABLE void setItems(const QStringList &items);

signals:
    void focusIn();
    void focusOut();

    void textChanged(QString text);

private:
    CustomComboBox *m_comboBox;

};
#endif // QCOMBOBOXQMLADAPTER_H
