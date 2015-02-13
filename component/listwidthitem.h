#include <QListWidgetItem>
#include <QPainter>
class MainWindow;

class ListWidthItem :public QListWidgetItem
{
public:
    ListWidthItem(const QIcon &icon, const QString &text, QListWidget *view = 0, int type = Type);
    ~ListWidthItem();
    void SetPress(bool bEnable);
    void SetOver(bool bEnable);
    void painter();
    void setMainWindow(MainWindow* MainFrom) {m_MainFrom = MainFrom;}
    void setPicture(QString picture) {m_sPicture = picture;}
    QString getPicture() {return m_sPicture;}

private:
    bool m_bOver;
    bool m_bPress;
    MainWindow *m_MainFrom;
    QString m_sPicture;
};
