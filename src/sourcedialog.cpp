#include <QtGui>
#include "sourcedialog.h"

SourceDialog::SourceDialog(QWidget *parent)
       :QDialog(parent)
{

}

//SortDialog::SortDialog(QWidget *parent)
//       :QDialog(parent)
//{

//       okButton = new QPushButton(tr("OK"));
//       okButton->setDefault(true);
//       cancelButton = new QPushButton(tr("Cancel"));
//       moreButton = new QPushButton(tr("&More"));
//       moreButton->setCheckable(true);
//       spacerItem = new QSpacerItem(20, 0, QSizePolicy::Minimum,
//QSizePolicy::Expanding);

//       vboxLayout = new QVBoxLayout;
//       vboxLayout->addWidget(okButton);
//       vboxLayout->addWidget(cancelButton);
//       vboxLayout->addItem(spacerItem);
//       vboxLayout->addWidget(moreButton);



//       primaryGroupBox = new QGroupBox(tr("&Primary Key"));
//       primaryColumnLabel = new QLabel(tr("Column:"));
//       primaryColumnCombo = new QComboBox;
//       primaryColumnCombo->addItem(tr("None"));
//       spacerItem1 = new QSpacerItem(20,20,QSizePolicy::Minimum,
//       QSizePolicy::Expanding);
//       primaryOrderLabel = new QLabel(tr("Order:"));
//       primaryOrderCombo = new QComboBox;
//       primaryOrderCombo->addItem(tr("Ascending"));
//       primaryOrderCombo->addItem(tr("Descending"));

//       gridLayout1 = new QGridLayout;
//       gridLayout1->addWidget(primaryColumnLabel,0,0,1,1);
//       gridLayout1->addWidget(primaryColumnCombo,0,1,1,1);
//       gridLayout1->addItem(spacerItem1,0,2,1,1);
//       gridLayout1->addWidget(primaryOrderLabel,1,0,1,1);
//       gridLayout1->addWidget(primaryOrderCombo,1,1,1,2);
//       primaryGroupBox->setLayout(gridLayout1);


//       spacerItem2 = new QSpacerItem(20, 0, QSizePolicy::Minimum,
//QSizePolicy::Expanding);


//       secondaryGroupBox = new QGroupBox(tr("&Secondary Key"));
//       secondaryColumnLabel = new QLabel(tr("Column:"));
//       secondaryColumnCombo = new QComboBox;
//       secondaryColumnCombo->addItem(tr("None"));
//       spacerItem3 = new QSpacerItem(20,20,QSizePolicy::Minimum,
//       QSizePolicy::Expanding);
//       secondaryOrderLabel = new QLabel(tr("Order:"));
//       secondaryOrderCombo = new QComboBox;
//       secondaryOrderCombo->addItem(tr("Ascending"));
//       secondaryOrderCombo->addItem(tr("Descending"));

//       gridLayout2 = new QGridLayout;
//       gridLayout2->addWidget(secondaryColumnLabel,0,0,1,1);
//       gridLayout2->addWidget(secondaryColumnCombo,0,1,1,1);
//       gridLayout2->addItem(spacerItem3,0,2,1,1);
//       gridLayout2->addWidget(secondaryOrderLabel,1,0,1,1);
//       gridLayout2->addWidget(secondaryOrderCombo,1,1,1,2);
//       secondaryGroupBox->setLayout(gridLayout2);


//       tertiaryGroupBox = new QGroupBox(tr("&Tertiary Key"));
//       tertiaryColumnLabel = new QLabel(tr("Column:"));
//       tertiaryColumnCombo = new QComboBox;
//       tertiaryColumnCombo->addItem(tr("None"));
//       spacerItem4 = new QSpacerItem(20,20,QSizePolicy::Minimum,
//       QSizePolicy::Expanding);
//       tertiaryOrderLabel = new QLabel(tr("Order:"));
//       tertiaryOrderCombo = new QComboBox;
//       tertiaryOrderCombo->addItem(tr("Ascending"));
//       tertiaryOrderCombo->addItem(tr("Descending"));

//       gridLayout3 = new QGridLayout;
//       gridLayout3->addWidget(tertiaryColumnLabel,0,0,1,1);
//       gridLayout3->addWidget(tertiaryColumnCombo,0,1,1,1);
//       gridLayout3->addItem(spacerItem4,0,2,1,1);
//       gridLayout3->addWidget(tertiaryOrderLabel,1,0,1,1);
//       gridLayout3->addWidget(tertiaryOrderCombo,1,1,1,2);
//       tertiaryGroupBox->setLayout(gridLayout3);



//       gridLayout = new QGridLayout;
//       gridLayout->addLayout(vboxLayout,0,1,2,1);
//       gridLayout->addWidget(primaryGroupBox,0,0,1,1);
//       gridLayout->addItem(spacerItem2, 1, 0, 1, 1);
//       gridLayout->addWidget(secondaryGroupBox, 2, 0, 1, 1);
//       gridLayout->addWidget(tertiaryGroupBox, 3, 0, 1, 1);
//       setLayout(gridLayout);

//       QWidget::setTabOrder(primaryColumnCombo, primaryOrderCombo);
//       QWidget::setTabOrder(primaryOrderCombo, secondaryColumnCombo);
//       QWidget::setTabOrder(secondaryColumnCombo, secondaryOrderCombo);
//       QWidget::setTabOrder(secondaryOrderCombo, tertiaryColumnCombo);
//       QWidget::setTabOrder(tertiaryColumnCombo, tertiaryOrderCombo);
//       QWidget::setTabOrder(tertiaryOrderCombo, okButton);
//       QWidget::setTabOrder(okButton, cancelButton);
//       QWidget::setTabOrder(cancelButton, moreButton);

//       QObject::connect(moreButton, SIGNAL(toggled(bool)), secondaryGroupBox, SLOT(setVisible(bool)));
//       QObject::connect(moreButton, SIGNAL(toggled(bool)), tertiaryGroupBox, SLOT(setVisible(bool)));

//       QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
//       QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));

//       QMetaObject::connectSlotsByName(this);

//       secondaryGroupBox->hide();
//       tertiaryGroupBox->hide();
//       layout()->setSizeConstraint(QLayout::SetFixedSize);
//       setColumnRange('A','Z');

//}
//void SortDialog::setColumnRange(QChar first,QChar last)
//{
//       primaryColumnCombo->clear();
//       secondaryColumnCombo->clear();
//       tertiaryColumnCombo->clear();
//       secondaryColumnCombo->addItem(tr("None"));
//       tertiaryColumnCombo->addItem(tr("None"));
//       primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());

//       QChar ch = first;
//       while(ch <= last)
//       {
//               primaryColumnCombo->addItem(QString(ch));
//               secondaryColumnCombo->addItem(QString(ch));
//               tertiaryColumnCombo->addItem(QString(ch));
//               ch = ch.unicode() + 1;
//       }
//}
