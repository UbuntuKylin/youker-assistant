#include "networkindicator.h"
#include "smoothcurvegenerator.h"

#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

NetworkIndicator::NetworkIndicator(QWidget *parent)
    : QWidget(parent)
    ,m_state(Normal)
    ,m_isChecked(false)
    ,m_rectTopPadding(9)
    ,m_rectTotalHeight(38)
    ,m_rectTotalWidth(58)
    ,m_outsideBorderColor(Qt::transparent)
    ,m_bgColor(QColor("#ffffff"))
{
    this->setFixedSize(188, 56);
    m_netMaxHeight = 30;
    m_pointSpace = 5;

    m_pointsCount = int((this->width() -2) / m_pointSpace);
    m_downloadSpeedList = new QList<long>();
    for (int i = 0; i < m_pointsCount; i++) {
        m_downloadSpeedList->append(0);
    }

    m_uploadSpeedList = new QList<long>();
    for (int i = 0; i < m_pointsCount; i++) {
        m_uploadSpeedList->append(0);
    }

    m_gridY = new QList<int>();

    setNetworkState(Normal);
}

NetworkIndicator::~NetworkIndicator()
{
    delete m_downloadSpeedList;
    delete m_uploadSpeedList;
    delete m_gridY;
}

void NetworkIndicator::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);

    if (!m_isChecked) {
        setNetworkState(Hover);
    }

    event->accept();
    //QWidget::enterEvent(event);
}

void NetworkIndicator::leaveEvent(QEvent *event)
{
    if (!m_isChecked) {
        setNetworkState(Normal);
    }

    event->accept();
    //QWidget::leaveEvent(event);
}

void NetworkIndicator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    setNetworkState(Press);

    event->accept();
    //QWidget::mousePressEvent(event);
}

void NetworkIndicator::mouseReleaseEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos()))
        return;

    m_isChecked = !m_isChecked;
    if (m_isChecked) {
        setNetworkState(Checked);
    } else {
        setNetworkState(Normal);
    }

    event->accept();
    //QWidget::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void NetworkIndicator::mouseMoveEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos())) {
        setNetworkState(Normal);
    }
}

void NetworkIndicator::updateBgColor()
{
    switch (m_state) {
    case Hover:
        this->m_outsideBorderColor = Qt::transparent;
        this->m_bgColor = QColor("#f6fcfe");
        break;
    case Press:
        this->m_outsideBorderColor = Qt::transparent;
        this->m_bgColor = QColor("#f6fcfe");
        break;
    case Checked:
        this->m_outsideBorderColor = QColor("#009944");
        this->m_bgColor = QColor("#e9f8fd");
        break;
    default:
        this->m_outsideBorderColor = Qt::transparent;
        this->m_bgColor = QColor("#ffffff");
        break;
    }
    repaint();
}

void NetworkIndicator::setNetworkState(NetworkIndicator::NetworkState state)
{
    if (m_state == state)
        return;

    m_state = state;
    updateBgColor();
}

void NetworkIndicator::setChecked(bool flag)
{
    m_isChecked = flag;
    if (m_isChecked){
        setNetworkState(Checked);
    } else {
        setNetworkState(Normal);
    }
}

bool NetworkIndicator::isChecked()
{
    return m_isChecked;
}

void NetworkIndicator::setTitle(const QString &title)
{
    this->m_title = title;
}

//void NetworkIndicator::updateNetworkPainterPath(QPainterPath downloadPath, QPainterPath uploadPath)
//{
//    this->m_downloadPath = downloadPath;
//    this->m_uploadPath = uploadPath;
//    repaint();
//}

NetworkIndicator::NetworkState NetworkIndicator::getNetworkState() const
{
    return m_state;
}

void NetworkIndicator::onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateBytes, long sentRateBytes)
{
    m_recvTotalBytes = recvTotalBytes;
    m_sentTotalBytes = sentTotalBytes;
    m_recvRateBytes = recvRateBytes;
    m_sentRateBytes = sentRateBytes;

    //download
    QList<QPointF> downloadPoints;
    m_downloadSpeedList->append(m_recvRateBytes);
    if (m_downloadSpeedList->size() > m_pointsCount) {
        m_downloadSpeedList->pop_front();
    }
    //计算出下载速度中最大的值
    long downloadMaxHeight = 0;
    for (int i = 0; i < m_downloadSpeedList->size(); i++) {
        if (m_downloadSpeedList->at(i) > downloadMaxHeight) {
            downloadMaxHeight = m_downloadSpeedList->at(i);
        }
    }
    for (int i = 0; i < m_downloadSpeedList->size(); i++) {
        if (downloadMaxHeight < m_netMaxHeight) {
            downloadPoints.append(QPointF(i * m_pointSpace, m_downloadSpeedList->at(i)));
        }
        else {
            downloadPoints.append(QPointF(i * m_pointSpace, m_downloadSpeedList->at(i) * m_netMaxHeight / downloadMaxHeight));
        }
    }
    m_downloadPath = SmoothCurveGenerator::generateSmoothCurve(downloadPoints);

    //upload
    QList<QPointF> uploadPoints;
    m_uploadSpeedList->append(m_sentRateBytes);
    if (m_uploadSpeedList->size() > m_pointsCount) {
        m_uploadSpeedList->pop_front();
    }
    //计算出上传速度中最大的值
    long uploadMaxHeight = 0;
    for (int i = 0; i < m_uploadSpeedList->size(); i++) {
        if (m_uploadSpeedList->at(i) > uploadMaxHeight) {
            uploadMaxHeight = m_uploadSpeedList->at(i);
        }
    }

    for (int i = 0; i < m_uploadSpeedList->size(); i++) {
        if (uploadMaxHeight < m_netMaxHeight) {
            uploadPoints.append(QPointF(i * m_pointSpace, m_uploadSpeedList->at(i)));
        }
        else {
            uploadPoints.append(QPointF(i * m_pointSpace, m_uploadSpeedList->at(i) * m_netMaxHeight / uploadMaxHeight));
        }
    }
    m_uploadPath = SmoothCurveGenerator::generateSmoothCurve(uploadPoints);

    repaint();
}

void NetworkIndicator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //border of rect
    QPainterPath borderPath;
    borderPath.addRoundedRect(this->rect(), 0, 0);
    QPen pen(this->m_outsideBorderColor, 1);
    painter.setPen(pen);
    painter.drawPath(borderPath);

    //background of rect
    painter.setOpacity(1);
    QPainterPath path;
    path.addRect(QRectF(1, 1, width()-2, height()-2));
    painter.fillPath(path, this->m_bgColor);

    painter.translate((rect().width() - m_pointsCount * m_pointSpace) / 2 + 2, 40);//将坐标第原点移动到该点
    painter.scale(1, -1);//将横坐标扩大1倍,将纵坐标缩小1倍
    //使用QPainterPath画贝塞尔曲线
    painter.setPen(QPen(QColor("#009944"), 1));
    painter.setBrush(QBrush());
    painter.drawPath(m_downloadPath);//绘制前面创建的path:m_downloadPath
    painter.translate(0, -8);//将点（0，-8）设为原点
    painter.setPen(QPen(QColor("#e60012"), 1));
    painter.setBrush(QBrush());
    painter.drawPath(m_uploadPath);

    QWidget::paintEvent(event);
}

