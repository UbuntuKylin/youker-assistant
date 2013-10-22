#ifndef LOCATIONDIALOG_H
#define LOCATIONDIALOG_H

#include <QDialog>
#include <QMap>
namespace Ui {
class LocationDialog;
}

class LocationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LocationDialog(QWidget *parent = 0);
    ~LocationDialog();
    QStringList list_city_names(QString inputText);
    
private slots:
    void on_searchBtn_clicked();

    void on_quitBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::LocationDialog *ui;

    QMap<QString, QVariant> cityInfo;

signals:
    void sendCityInfo(QString cityName, QString cityId);
};

#endif // LOCATIONDIALOG_H
