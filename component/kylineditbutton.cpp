#include "kylineditbutton.h"
#include <QHBoxLayout>
#include <QLineEdit>

KylinEditButton::KylinEditButton(QLineEdit *edit)
    : QPushButton(edit)
{
    QSize size = QSize(40, edit->sizeHint().height());
//    setMinimumSize(size);
//    setMaximumSize(size);
    this->setFocusPolicy(Qt::NoFocus);
    this->setFlat(true);
    this->setIcon(QIcon("://res/folder.png"));
    this->setIconSize(QSize(16, 16));
    this->setCursor(QCursor(Qt::PointingHandCursor));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch();
    layout->addWidget(this);
    edit->setLayout(layout);
    edit->setTextMargins(0, 1, size.width(), 1);
}
