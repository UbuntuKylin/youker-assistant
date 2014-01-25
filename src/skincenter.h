#ifndef SKINCENTER_H
#define SKINCENTER_H

#include <QDialog>
#include <QtGui>
namespace Ui {
class SkinCenter;
}

class SkinCenter : public QDialog
{
    Q_OBJECT
    
public:
    explicit SkinCenter(QWidget *parent = 0);
    ~SkinCenter();
    QString get_locale_version();
private:
    Ui::SkinCenter *ui;
    QString locale_Lan;



//protected:
//    bool eventFilter(QObject *obj, QEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void paintEvent(QPaintEvent *event);
//    void resizeEvent(QResizeEvent *event);

//signals:
//    void skinSignalToQML(QString skinName);

//private slots:
//    void showSkin(QString page_count);
//    void verifyToUseSkin(QString skinName);

//private:
//    void initTitleBar();//标题栏
//    void initSkinsCenter();//皮肤列表区域
//    void initBottomBar();//上一页下一页按钮区域
//    QSettings *pSettings;
//    QString skinName;
//    bool is_change;
//    QPoint move_point;
//    bool mouse_press;
};

#endif // SKINCENTER_H
