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

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
//sudo apt-get install libcv-dev libopencv-highgui-dev libopencv-dev libhighgui-dev
#include <QDialog>
#include "../component/kylintitlebar.h"
#include <QImage>
#include <QTimer>// 设置采集数据的间隔时间
#include <highgui.h>  //包含opencv库头文件
#include <cv.h>
//#include <opencv2/highgui.hpp> //1710opencv库
//#include <cvaux.h>
//#include <ml.h>
#include <QDateTime>
#include <QDir>
#include <stdio.h>
#include <ctype.h>
#include  <time.h>

class SessionDispatcher;
class MainWindow;
class ToolButton;

class CameraManager :public QDialog
{
  Q_OBJECT
public:
    CameraManager(QWidget *parent = 0, SessionDispatcher *proxy = 0, QString skin = ":/background/res/skin/1.png");
//    ~CameraManager();
    void setParentWindow(MainWindow *From) { mainwindow = From;}
    void initConnect();
    void setOKButtonEnable(bool enable);
    void resetTitleSkin(QString skin);
    void initCamera();
    IplImage* DoPyrDown(IplImage* image, int filter);
    QString getCurrentDateTime();
    QString getHomePath();
    int countCamaras();

public slots:
    void readFarme();//读取当前帧信息
    void onCloseButtonClicked();
    void onOKButtonClicked();
    void onViewButtonClicked();
    void refreshCamera();

//protected:
//    void keyPressEvent( QKeyEvent *k );

private:
    void initTitleBar(QString skin);

private:
    MainWindow *mainwindow;
    SessionDispatcher *sessionproxy;
    QTimer *timer;
    QImage *imag;
    CvCapture *cam;// 视频获取结构， 用来作为视频获取函数的一个参数
    IplImage  *frame;//申请IplImage类型指针，就是申请内存空间来存放每一帧图像
    KylinTitleBar *title_bar;
    QLabel *camera_label;
    QWidget *baseWidget;
    QLabel *catch_label;
    QLabel *disable_icon;
    QPushButton *okBtn;
    ToolButton *viewBtn;
    QLabel *error_icon;
    QLabel *error_label;
};

#endif // CAMERAMANAGER_H
