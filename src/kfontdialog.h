#ifndef KFONTDIALOG_H
#define KFONTDIALOG_H

#include <QDialog>
#include <qfontdatabase.h>
#include <QModelIndex>
#include <QStringListModel>

namespace Ui {
class KFontDialog;
}

class KFontDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit KFontDialog(QWidget *parent = 0);
    ~KFontDialog();
    void getInitFont();
    void initDialog();
    
private:
    Ui::KFontDialog *ui;

    QFontDatabase fdb;
    QString initfont;
    QString initstyle;
    QString initsize;
    void updateSampleFont();
//    void updateSampleFont(const QFont &newFont);

    QStringListModel *familymodel;
    QStringListModel *stylemodel;
    QStringListModel *sizemodel;
protected slots:
    void updateAll(QModelIndex index);
    void updateStyleandSize(QModelIndex index);
    void updateSize(QModelIndex index);

signals:
    void updateSizeList();
};

#endif // KFONTDIALOG_H
