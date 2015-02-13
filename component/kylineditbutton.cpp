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






    // 设置style sheet

    /*.SearchButton {

        background: gray; color: white; border: 1 solid gray;

        min-width: 40px;

    }


    .SearchButton:hover {

        background: black; color: white; border: 1 solid black;

    }


    .SearchButton:pressed {

        background: white;

        color: black;

    }*/


    // 为了方便起见, 帮把 style sheet 写到代码里, 实际工作中应该放到专用的style sheet里, 方便修改

//    QString qss = QString(".SearchButton {background: gray; color: white; border: 1 solid gray;min-width: 40px;}")

//            + QString(".SearchButton:hover {background: black; color: white; border: 1 solid black;}")

//            + QString(".SearchButton:pressed {background: white;color: black;}");

//    setStyleSheet(qss);
