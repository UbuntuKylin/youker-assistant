#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>

class QGridLayout;
class QHBoxLayout;
class QPushButton;
class QSpacerItem;
class QLabel;
class ModalDialog : public QDialog
{

      Q_OBJECT

    public:
      ModalDialog(QWidget *parent = 0);

    private:

//      QSpacerItem *spacerItem;
//      QGridLayout *gridLayout;
//      QHBoxLayout *hboxLayout;
////      QHBoxLayout *hboxLayout1;
//      QPushButton *okButton;
//      QPushButton *cancelButton;
//      QLabel      *label;

      QSpacerItem *spacerItem;
      QGridLayout *gridLayout;
      QHBoxLayout *hboxLayout;
      QPushButton *okButton;
      QPushButton *cancelButton;
      QLabel      *label;


};
#endif // MODALDIALOG_H
