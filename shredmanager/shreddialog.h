//#include "ui_shreddialog.h"
#include <QDialog>
//#include "EraseFile.h"
#include "../component/kylineditbutton.h"
#include "../component/kylintitlebar.h"
#include "../component/toolkits.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
class ShredManager;

class ShredDialog : public QDialog
{
    Q_OBJECT
public:
  ShredDialog(ShredManager *plugin, QDialog *parent = 0);
  ~ShredDialog();
  virtual void paintEvent (QPaintEvent *event);
  void setLanguage();
  void initConnect();
  void initTitleBar();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void onSelectButtonClicked();
    void onShredButtonClicked();
    void onCacelButtonClicked();
    void onSelecteComboActivated(int index);
    void onCloseButtonClicked();
//    void onMinButtonClicked();

private:
    //  Ui::ShredDialog  ui;
    ShredManager *process_plugin;
    //  CEraseFile  m_EraseFile;
    KylinTitleBar *title_bar;
    KylinEditButton *select_btn;
    QLineEdit *select_edit;
    QPushButton *shred_btn;
    QPushButton *cacel_btn;
    Toolkits *toolkits;
};
