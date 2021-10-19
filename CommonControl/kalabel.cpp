#include "kalabel.h"

#include "utils.h"

KALabel::KALabel(QWidget *parent)
    : QLabel(parent)
{
    m_strText = "";
}

KALabel::KALabel(QString strText, QWidget *parent)
    : QLabel(strText, parent)
{
    m_strText = strText;
}

void KALabel::setText(const QString &strText)
{
    m_strText = strText;
    QLabel::setText(strText);
}

void KALabel::paintEvent(QPaintEvent *event)
{
    QString strEText = getElidedText(font(), m_strText, width());
    if (strEText != m_strText) {
        QLabel::setText(strEText);
        setToolTip(m_strText);
    } else {
        QLabel::setText(m_strText);
        setToolTip("");
    }
    QLabel::paintEvent(event);
}
