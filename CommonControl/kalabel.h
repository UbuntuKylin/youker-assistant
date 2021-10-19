#ifndef KALABEL_H
#define KALABEL_H

#include <QLabel>

class KALabel : public QLabel
{
    Q_OBJECT
public:
    KALabel(QWidget *parent = nullptr);
    KALabel(QString strText, QWidget *parent = nullptr);

public slots:
    void setText(const QString &);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_strText;
};

#endif // KALABEL_H
