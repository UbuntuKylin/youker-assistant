#ifndef KYLINEDITBUTTON_H
#define KYLINEDITBUTTON_H

#include <QPushButton>
class QLineEdit;

class KylinEditButton : public QPushButton
{
    Q_OBJECT
public:
    KylinEditButton(QLineEdit *edit);
};

#endif // KYLINEDITBUTTON_H
