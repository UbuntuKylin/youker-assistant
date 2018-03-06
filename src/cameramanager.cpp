/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cameramanager.h"
#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include "../dbusproxy/youkersessiondbus.h"
#include "../component/toolbutton.h"

//#include <QKeyEvent>
#include <QDesktopServices>
#include <QUrl>

CameraManager::CameraManager(QWidget *parent, SessionDispatcher *proxy, QString skin)
:QDialog(parent),sessionproxy(proxy)
{
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:2px}");
    this->setFixedSize(622, 480);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    timer = NULL;
    imag = NULL;
    cam = NULL;
    frame = NULL;

    title_bar = new KylinTitleBar(this);
    initTitleBar(skin);

    camera_label = new QLabel(this);
    camera_label->setGeometry(QRect(0,32,622,340));
    camera_label->hide();
    baseWidget = new QWidget(this);
    baseWidget->setStyleSheet("QWidget{border: none;background-color: #a6b6c1;}");//background:transparent;
    baseWidget->setGeometry(QRect(0,372,622,108));
    catch_label = new QLabel(baseWidget);
    catch_label->setStyleSheet("QLabel{border: 1px solid white;}");
    catch_label->setGeometry(QRect(10,11,145,86));
    QImage image("://res/camera-default.png");
    if (!image.isNull()) {
        catch_label->setPixmap(QPixmap::fromImage(image).scaled(145, 86, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    disable_icon = new QLabel(baseWidget);
    disable_icon->setGeometry(QRect(263,7,93,93));
    disable_icon->setStyleSheet("QLabel{background-image:url(':/res/catch-disable.png')}");
    disable_icon->hide();

    okBtn = new QPushButton(baseWidget);
    okBtn->setGeometry(QRect(263,7,93,93));
    okBtn->hide();
    okBtn->setCursor(Qt::PointingHandCursor);
    okBtn->setFocusPolicy(Qt::NoFocus);
    okBtn->setIconSize(QSize(93, 93));
    okBtn->setFlat(true);
    okBtn->setStyleSheet("QPushButton{background:transparent;background-image:url('://res/catch.png');}QPushButton:hover{background:url('://res/catch-hover.png');}");
    viewBtn = new ToolButton(baseWidget, true);
    viewBtn->setFocusPolicy(Qt::NoFocus);
    viewBtn->setCursor(Qt::PointingHandCursor);
    viewBtn->setIcon("://res/view.png");
    viewBtn->setText(tr("View Photos"));
    viewBtn->setGeometry(QRect(500,16,50,60));

    error_icon = new QLabel(this);
    error_icon->setGeometry(QRect(0,32,622,340));
    error_icon->setStyleSheet("QLabel{background-image:url('://res/camera-error.png')}");
    error_label = new QLabel(this);
    error_label->setGeometry(QRect(10, 280, 600, 20));
    error_label->setWordWrap(true);
    error_label->setStyleSheet("QLabel{color:#90a5b1;font-family: 方正黑体_GBK;font-size: 14px;text-align: center;}");
    error_label->setAlignment(Qt::AlignCenter);
    error_label->setText(tr("The camera is out of question, <a style='color: #3f96e4;' href = http://www.ubuntukylin.com> Refresh</a> to call it out ~"));

    this->initCamera();
    this->initConnect();

}

//CameraManager::~CameraManager()
//{
//    if (timer != NULL) {
//            disconnect(timer,SIGNAL(timeout()),this,SLOT(readFarme()));
//            if(timer->isActive())
//                timer->stop();
//            delete timer;
//            timer = NULL;
//    }
//    if (imag != NULL) {
//        delete imag;
//        imag = NULL;
//    }
//    if (cam != NULL) {
//        delete cam;
//        cam = NULL;
//    }
//}

void CameraManager::initCamera()
{
    timer  = new QTimer(this);
    imag = new QImage();
    int number = this->countCamaras();//获取摄像头的个数
//    qDebug()  << "camara number:" << number;
//    if (cam != NULL)
//        return;
    if(number < 1) {
        this->setOKButtonEnable(false);
        return;
    }
    else {
        this->setOKButtonEnable(true);
    }
    //0表示内置摄像头 1表示外界摄像头
   cam = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频
//   assert(NULL != cam);
   if(cam == NULL) {
       this->setOKButtonEnable(false);
       return;
   }
   cvSetCaptureProperty(cam, CV_CAP_PROP_FPS, 30);//帧率（只对摄像头有效）
   //default :640*480
//   cvSetCaptureProperty(cam, CV_CAP_PROP_FRAME_WIDTH, 1280);//视频流的帧宽度（只对摄像头有效）
//   cvSetCaptureProperty(cam, CV_CAP_PROP_FRAME_HEIGHT, 720);//视频流的帧高度（只对摄像头有效）
   timer->start(33);// 开始计时，超时则发出timeout()信号
}

QString CameraManager::getCurrentDateTime() {
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd"); //设置显示格式
    return str;
}

QString CameraManager::getHomePath() {
    QString homepath = QDir::homePath();
    return homepath;
}

int CameraManager::countCamaras() {
    cv::VideoCapture temp_camera;
    int maxTested = 10;
    for (int i = 0; i < maxTested; i++) {
//        try {
//            cv::VideoCapture temp_camera(i);
//        }
//        catch(cv::Exception& e) {
//            qDebug() << e.what();
//        }
        cv::VideoCapture temp_camera(i);
        bool res = (!temp_camera.isOpened());
        temp_camera.release();
        if (res)
        {
            return i;
        }
    }
    return maxTested;
}

void CameraManager::setOKButtonEnable(bool enable)
{
    if(enable)
    {
        error_icon->hide();
        error_label->hide();
        disable_icon->hide();
        camera_label->show();
        okBtn->show();
//        okBtn->setEnabled(true);
    }
    else
    {
        camera_label->hide();
//        okBtn->setEnabled(false);
        okBtn->hide();
        error_icon->show();
        error_label->show();
        disable_icon->show();
    }
}

void CameraManager::onOKButtonClicked()
{
    frame = cvQueryFrame(cam);
//    QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();
    QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();
    catch_label->setPixmap(QPixmap::fromImage(image).scaled(145, 86, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    IplImage* outImage = cvCreateImage(cvGetSize(frame),frame->depth,frame->nChannels);
    cvCopy(frame,outImage,NULL);
 //    outImage = this->DoPyrDown(outImage);//图片缩放
    QString outImageName = this->getHomePath() + "/" + this->getCurrentDateTime() + ".jpg";
    char* ch;
    QByteArray ba = outImageName.toUtf8();
    ch=ba.data();
    cvSaveImage(ch,outImage);
    cvReleaseImage(&outImage);
}

void CameraManager::readFarme()
{
    frame = cvQueryFrame(cam);
    if(!frame)
        return;
   QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();
   camera_label->setPixmap(QPixmap::fromImage(image));
}


// 实现将拍下来的图片缩放一倍
IplImage* CameraManager::DoPyrDown(IplImage* image, int filter = IPL_GAUSSIAN_5x5)
//IplImage* CameraManager::DoPyrDown(IplImage* image, int filter = CV_GAUSSIAN_5x5)
{
    CvSize size = cvSize(image->width / 2,image->height / 2);
    IplImage* outImage = cvCreateImage(size,image->depth,image->nChannels);
    cvPyrDown(image,outImage);
    cvReleaseImage(&image);
    return outImage;
}

void CameraManager::onViewButtonClicked()
{
//    sessionproxy->open_folder_qt(sessionproxy->getHomePath());
    QDesktopServices::openUrl(QUrl(QString("file:%1").arg(this->getHomePath()), QUrl::TolerantMode));
}

void CameraManager::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
    connect(okBtn,SIGNAL(clicked()), this, SLOT(onOKButtonClicked()));
    connect(viewBtn, SIGNAL(clicked()), this, SLOT(onViewButtonClicked()));
    connect(error_label,SIGNAL(linkActivated(QString)),this,SLOT(refreshCamera()));
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
}

void CameraManager::refreshCamera()
{
    int number = this->countCamaras();//获取摄像头的个数
    if(number < 1) {
        this->setOKButtonEnable(false);
        return;
    }
    else {
        this->setOKButtonEnable(true);
    }
    //0表示内置摄像头 1表示外界摄像头
   cam = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频
   if(cam == NULL) {
       this->setOKButtonEnable(false);
       return;
   }
   cvSetCaptureProperty(cam, CV_CAP_PROP_FPS, 30);//帧率（只对摄像头有效）
   if(timer != NULL) {
       if(timer->isActive())
        timer->stop();
       timer->start(33);// 开始计时，超时则发出timeout()信号
   }
}

void CameraManager::onCloseButtonClicked()
{
    cvReleaseCapture(&cam);
    if (timer != NULL) {
            disconnect(timer,SIGNAL(timeout()),this,SLOT(readFarme()));
            if(timer->isActive())
                timer->stop();
            delete timer;
            timer = NULL;
    }
    if (imag != NULL) {
        delete imag;
        imag = NULL;
    }
    if (cam != NULL) {
        delete cam;
        cam = NULL;
    }
    this->close();
}

void CameraManager::initTitleBar(QString skin)
{
    title_bar->setTitleWidth(622);
    title_bar->setTitleName(tr("Camera"));
    title_bar->setTitleBackgound(skin);
}

void CameraManager::resetTitleSkin(QString skin)
{
    title_bar->resetBackground(skin);
}

//void CameraManager::keyPressEvent(QKeyEvent *k)
//{
//    if (k->key() == Qt::Key_Escape) {
//        qDebug() << "prssss. esc.....";
//        if (cam != NULL) {
//            qDebug() << "cam not null";
//            this->onCloseButtonClicked();
//        }
//        else
//            qDebug() << "cam null";
//    }
//    else if (k->key() == Qt::Key_Enter || k->key() == Qt::Key_Return)
//    {
//        qDebug() << "prssss. enter.....";
//        if (cam != NULL)
//            this->onPicButtonClicked();
//    }
//}
