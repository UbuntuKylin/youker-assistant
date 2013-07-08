#include "modaldialog.h"
#include <QtGui>
ModalDialog::ModalDialog(QWidget *parent)
    :QDialog(parent)
{

//       okButton = new QPushButton(tr("确定"));
//       okButton->setDefault(true);
//       cancelButton = new QPushButton(tr("取消"));
//       spacerItem = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

//       hboxLayout = new QHBoxLayout;
//       hboxLayout->addWidget(okButton);
//       hboxLayout->addWidget(cancelButton);

//       gridLayout = new QGridLayout;
//       gridLayout->addLayout(hboxLayout,0,0,1,1);
//       setLayout(gridLayout);
//       QWidget::setTabOrder(okButton, cancelButton);
//       QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
//       QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
//       QMetaObject::connectSlotsByName(this);
//       layout()->setSizeConstraint(QLayout::SetFixedSize);
//       setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
//       setWindowFlags(Qt::FramelessWindowHint);//因隐藏默认titlebar


    okButton = new QPushButton(tr("确定"));
    okButton->setDefault(true);
    cancelButton = new QPushButton(tr("取消"));
    spacerItem = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    hboxLayout = new QHBoxLayout;
//    hboxLayout->addWidget(okButton);
//    hboxLayout->addWidget(cancelButton);
    gridLayout = new QGridLayout;
    label = new QLabel(tr("测试过程中点击鼠标左键更换颜色,点击鼠标右键退出."));
    gridLayout->addWidget(label,0,0);
    gridLayout->addWidget(okButton,1,0);
    gridLayout->addWidget(cancelButton,1,1);
    gridLayout->setMargin(15);
    gridLayout->setSpacing(10);
//    gridLayout->addLayout(hboxLayout,0,0,1,1);
    setLayout(gridLayout);
    QWidget::setTabOrder(okButton, cancelButton);
    QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    QMetaObject::connectSlotsByName(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    setWindowFlags(Qt::FramelessWindowHint);//因隐藏默认titlebar

}
