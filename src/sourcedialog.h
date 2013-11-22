#ifndef __SOURCEDIALOG_H__
#define __SOURCEDIALOG_H__
#include <QDialog>
class QGridLayout;
class QVBoxLayout;
class QPushButton;
class QSpacerItem;
class QGroupBox;
class QLabel;
class QComboBox;

class SourceDialog:public QDialog
{

    Q_OBJECT
public:
    SourceDialog(QWidget *parent = 0);
};
#endif // __SOURCEDIALOG_H__
//class SortDialog:public QDialog
//{
     
//      Q_OBJECT
     
//      public:
//      SortDialog(QWidget *parent = 0);
//      void setColumnRange(QChar first,QChar last);
          
//      private:
  
//      QSpacerItem *spacerItem;
//      QGridLayout *gridLayout;
//      QVBoxLayout *vboxLayout;
//      QPushButton *okButton;
//      QPushButton *cancelButton;
//      QPushButton *moreButton;
     
//      QGroupBox   *primaryGroupBox;
//      QGridLayout *gridLayout1;
//      QLabel      *primaryColumnLabel;
//      QComboBox   *primaryColumnCombo;
//      QSpacerItem *spacerItem1;
//      QLabel      *primaryOrderLabel;
//      QComboBox   *primaryOrderCombo;
     
//      QSpacerItem *spacerItem2;
     
//      QGroupBox   *secondaryGroupBox;
//      QGridLayout *gridLayout2;
//      QLabel      *secondaryColumnLabel;
//      QComboBox   *secondaryColumnCombo;
//      QSpacerItem *spacerItem3;
//      QLabel      *secondaryOrderLabel;
//      QComboBox   *secondaryOrderCombo;
     
     
//      QGroupBox   *tertiaryGroupBox;
//      QGridLayout *gridLayout3;
//      QLabel      *tertiaryColumnLabel;
//      QComboBox   *tertiaryColumnCombo;
//      QSpacerItem *spacerItem4;
//      QLabel      *tertiaryOrderLabel;
//      QComboBox   *tertiaryOrderCombo;
           
//};

