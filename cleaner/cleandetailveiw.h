#ifndef CLEANDETAILVEIW_H
#define CLEANDETAILVEIW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QFont>
#include <QVBoxLayout>
#include <QLine>
#include <QPixmap>
#include <QString>
#include <QMovie>

class CleandetailVeiw : public QWidget
{
    Q_OBJECT
public:
    explicit CleandetailVeiw(QWidget *parent = nullptr);
    ~CleandetailVeiw();

    void InitWidget();
    void InitTopWidget();
    void InitBottomWidget();
    void ResetUI();
signals:
    void hideThisWidget();
    void startOneKeyClean();

private slots:
    void getScanResult(QString msg);
    void finishScanResult(QString msg);
    void getScanAllResult(QString flag, QString msg);

    void OnClikedCleanBtn();

    void getCleanResult(QString msg);
private:
    QVBoxLayout *main_layout;
    QHBoxLayout *top_layout;
    QVBoxLayout *bottom_layout;

    QPushButton *cancel_btn;
    QPushButton *onkeyclean;
    QPushButton *return_btn;

    QLabel *top_tip;

    QLabel *cache_tip;
    QLabel *cache_icon;

    QLabel *cookie_tip;
    QLabel *cookie_icon;

    QLabel *history_tip;
    QLabel *history_icon;

    QString trace;
    QString cookies;
    QString garbage;

    QString root_key;
};

#endif // CLEANDETAILVEIW_H
