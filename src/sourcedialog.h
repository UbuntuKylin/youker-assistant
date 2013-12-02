#ifndef SOURCEDIALOG_H
#define SOURCEDIALOG_H

#include <QDialog>

namespace Ui {
class SourceDialog;
}

class SourceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SourceDialog(QWidget *parent = 0);
    ~SourceDialog();
    
private:
    Ui::SourceDialog *ui;
    QPoint dragPos;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void handler_OK();
signals:
    void addList();

};

#endif // SOURCEDIALOG_H
