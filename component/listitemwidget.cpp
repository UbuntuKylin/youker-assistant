#include "listitemwidget.h"

ListItemWidget::ListItemWidget(QWidget *parent) :
    QWidget(parent)
{
    title_label = new QLabel();
    title_label->setFixedWidth(150);
    title_label->setText(tr("Audio"));
    msg_label = new QLabel();
    msg_label->setText(tr("1.0.3"));
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(title_label);
    mainLayout->addWidget(msg_label);
    mainLayout->addStretch();
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
}
