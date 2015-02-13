//#include "ui_processdialog.h"
#include <QDialog>
//#include "EraseFile.h"



#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QDebug>
#include <QHeaderView>

#include "procman.h"
#include "procapp.h"
#include "filelist.h"
#include "../component/toolkits.h"
#include "../component/kylintitlebar.h"

#include <QTimer>
#define COLUMN_NUM 9


class ProcessManager;

class ProcessDialog : public QDialog
{
    Q_OBJECT
public:
  ProcessDialog(ProcessManager *plugin, QDialog *parent = 0);
  ~ProcessDialog();
  virtual void paintEvent ( QPaintEvent *event);
  void setLanguage();
  void initConnect();
  void initTitleBar();
  void showProList();
  ProcApp *app;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void refresh_prolist();
    void handlercellClicked(int row, int column);
    void killSelectedProcess();
    void onCloseButtonClicked();
//    void onMinButtonClicked();

//Q_SIGNALS:
//    void SignalClose();
private:
//  Ui::ProcessDialog  ui;
  ProcessManager *process_plugin;
  QLabel *tip_label;
  QPushButton *kill_btn;
  QTableWidget *tableWidget;
  QString selected_pid;
  QTimer *timer;
  Toolkits *toolkits;
//  CEraseFile  m_EraseFile;
  KylinTitleBar *title_bar;
};
