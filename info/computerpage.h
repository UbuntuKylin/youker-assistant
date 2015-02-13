#ifndef COMPUTERPAGE_H
#define COMPUTERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPen>
#include <QEvent>
#include "../component/separatorline.h"
#include <QMap>
#include <QGroupBox>
#include <QFormLayout>
#include <QVariant>
#include "../dbusproxy/youkersessiondbus.h"
#include "../dbusproxy/youkersystemdbus.h"

class ComputerPage : public QWidget
{
    Q_OBJECT
public:
    explicit ComputerPage(QWidget *parent = 0, QString title = "computer"/*, QString manufacturer = "UbuntuKylin"*/);
    ~ComputerPage();
    void setLanguage();
    int page_height;
    void initUI();
    void setMap(QMap<QString ,QVariant> tmp, const QString &manufacturer) {
        info_map = tmp;
        vendor = manufacturer;
    }
    QString translatorSwitch(QString orgStr);


protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

public slots:

private:
    QString title_context;
    QLabel *title_label;
    QString vendor;
//    QLabel *line;
    QHBoxLayout *h_layout;
    QVBoxLayout *v_layout;
    SeparatorLine *separ;

    void resizeEvent(QResizeEvent *);

    QMap<QString ,QVariant> info_map;
    QLabel *logo_label;

    QGroupBox *group_box;
    QFormLayout *form_layout;
};

#endif // COMPUTERPAGE_H
