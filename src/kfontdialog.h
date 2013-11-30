#ifndef KFONTDIALOG_H
#define KFONTDIALOG_H

#include <QDialog>
#include <qfontdatabase.h>
#include <QModelIndex>
#include <QStringListModel>
class QSettings;
namespace Ui {
class KFontDialog;
}

class KFontDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit KFontDialog(QSettings *mSettings = 0, QString flag = "", QWidget *parent = 0);
    ~KFontDialog();
    void getInitFont();
    void initDialog();
    
private:
    Ui::KFontDialog *ui;
    QSettings *pSettings;
    QFontDatabase fdb;
//    QString initfont;
//    QString initstyle;
//    QString initsize;
//    QStringList families;//所有字体名字
//    QStringList styles;//所有字体风格列表
//    QStringList sizes;//所有字体大小
    QString fontFlag;//字体标记
    void updateSampleFont();
//    void updateSampleFont(const QFont &newFont);

    QStringListModel *familymodel;
    QStringListModel *stylemodel;
    QStringListModel *sizemodel;
    QPoint dragPos;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

protected slots:
    void updateAll(QModelIndex index);
    void updateStyleandSize(QModelIndex index);
    void updateSize(QModelIndex index);

signals:
    void updateSizeList();
private slots:
    void on_quitBtn_clicked();
    void on_okBtn_clicked();
};

#endif // KFONTDIALOG_H
