#ifndef CPUFMWIDGET_H
#define CPUFMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QFont>
#include <QSlider>
#include <QPushButton>
#include <QString>
#include <QVariant>
#include <QStringList>
#include <QString>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDialog>
#include <QTimer>

#include "../component/myslider.h"
#include "../component/generaldialog.h"

class mySlider;
class GeneralDialog;

class CpuFmwidget : public QWidget
{
    Q_OBJECT
public:
    explicit CpuFmwidget(QWidget *parent = nullptr);
    ~CpuFmwidget();

    void InitUI();
    void InitTopUI();
    void InitBottomUI();

    void set_cpu_listAndCur(QStringList list,QString string);
    void RefreshCheckStatus();
    void getCpuRange(QMap<QString,QVariant>);
    bool isHW990();
    void initUserspaceFrameAnimation();
    void showUserspaceFrame(bool);
signals:
    void setCpuGoverner(QString);
    void RequestCPUFrequencyData();
private slots:
    void ProcessingCPUFrequencyData(QMap<QString,QVariant>);

    void onButtonClicked(QAbstractButton *button);
    void onClickedApply();
private:
    QFrame *w;
    QPushButton *apply_button;
    QLabel *cpu_lable;
//    QSlider *slider;
    QString cpu_num = "3.52";

    mySlider *slider;

    QStringList governer_list;
    QString cur_governer;

    QString governer;
    QString cpuValue="";

    QString value = "";

    QButtonGroup *radioGroup;
    GeneralDialog *dialog;

    QParallelAnimationGroup *group;
    QParallelAnimationGroup *group1;

    QTimer qtimer;
};

#endif // CPUFMWIDGET_H
