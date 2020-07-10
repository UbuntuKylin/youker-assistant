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
#include <QMap>
#include <QVariant>
#include <QTimer>

#include "../component/utils.h"

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

    void getAllSelectedItems();

    void animationForTip(int f);
    void timerUpDate(bool t);
signals:
    void hideThisWidget();
    void startOneKeyClean();
    void startCleanSystem(QMap<QString, QVariant> itemsMap);
private slots:
    void getScanResult(QString msg);
    void finishScanResult(QString msg);
    void getScanAllResult(QString flag, QString msg);

    void OnClikedCleanBtn();
    void showReciveData(const QStringList &data);
    void showReciveStatus(const QString &status);
    void getCleanResult(QString msg);
    void ShowDetailsPage();

    void showCleanerData(const QStringList &data);
    void showCleanerStatus(const QString &status, const QString &domain);
    void showCleanerError(const QString &status);

    void onRefreshSelectedItems(CleanerModuleID id, const QStringList &infos);

    void receiveCleanSignal();
    void receivePolicyKitSignal(bool status);
    void showCleanOverStatus();
private:
    QVBoxLayout *main_layout;
    QHBoxLayout *top_layout;
    QVBoxLayout *bottom_layout;

    QPushButton *cancel_btn;
    QPushButton *onkeyclean;
    QPushButton *return_btn;
    QPushButton *btn_return;

    QPushButton *cache_btn;
    QPushButton *cookie_btn;
    QPushButton *history_btn;

    QLabel *top_tip;
    QLabel *status_tip;

    QLabel *cache_tip;
    QLabel *cache_icon;

    QLabel *cookie_tip;
    QLabel *cookie_icon;

    QLabel *history_tip;
    QLabel *history_icon;

    QString trace;
    QString cookies;
    QString garbage;

    qreal cache_sum = 0;
    qreal cookie_sum = 0;
    qreal history_sum = 0;

    QString root_key;

    QMap<QString, QVariant> argsData;

    QStringList cache_apt_list;
    QStringList cache_software_list;
    QStringList cache_thumbnails_list;
    QStringList cache_firefox_list;
    QStringList cache_chromium_list;
    /*QStringList package_unneed_list;
    QStringList package_oldkernel_list;
    QStringList package_configfile_list;*/
    QStringList cookies_firefox_list;
    QStringList cookies_chromium_list;
    QString trace_firefox_count;
    QString trace_chromium_count;
    QString trace_system_count;
    QString trace_bash_size;
    QString trace_bash_path;
    QStringList trace_x11_list;

    QStringList m_selectedAptList;
    QStringList m_selectedSoftwareList;
    QStringList m_selectedThumbnailsList;
    QStringList m_selectedFirefoxCacheList;
    QStringList m_selectedChromiumCacheList;
    QStringList m_selectedFirefoxCookieList;
    QStringList m_selectedChromiumCookieList;
    QStringList m_selectedTraceX11List;
};

#endif // CLEANDETAILVEIW_H
