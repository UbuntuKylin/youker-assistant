#ifndef NETWORKINDICATOR_H
#define NETWORKINDICATOR_H

#include <QObject>
#include <QWidget>
#include <QPixmap>

class NetworkIndicator : public QWidget
{
    Q_OBJECT

    enum NetworkState {Normal, Hover, Press, Checked};

public:
    NetworkIndicator(QWidget * parent=0);
    ~NetworkIndicator();

    void setChecked(bool flag);
    bool isChecked();
    void setTitle(const QString &title);
//    void updateNetworkPainterPath(QPainterPath downloadPath, QPainterPath uploadPath);

    NetworkState getNetworkState() const;

public slots:
    void onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateKbs, long sentRateKbs);

signals:
    void clicked();

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void updateBgColor();
    void setNetworkState(NetworkState state);

private:
    NetworkState m_state;
    bool m_isChecked;
    QString m_title;
    int m_rectTopPadding;
    int m_rectTotalHeight;
    int m_rectTotalWidth;
    QColor m_outsideBorderColor;
    QColor m_bgColor;


    QList<long> *m_downloadSpeedList;
    QList<long> *m_uploadSpeedList;
    QPainterPath m_downloadPath;
    QPainterPath m_uploadPath;

    int m_netMaxHeight;
    int m_pointsCount;
    QList<int> *m_gridY;
    int m_pointSpace;

    long m_recvTotalBytes;
    long m_sentTotalBytes;
    long m_recvRateBytes;
    long m_sentRateBytes;
};

#endif // NETWORKINDICATOR_H
