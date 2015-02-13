#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSplitter>
#include <QDoubleSpinBox>
class SessionDispatcher;
class MainWindow;

class FontWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FontWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, MainWindow *window = 0);
    ~FontWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setDefaultFont();
    void setDesktopFont();
    void setMonospaceFont();
    void setDocumentFont();
    void setTitlebarFont();
    void setScalingValue(double value);
    void setFontHinting(QString selected);
    void setFontAntialiasing(QString selected);
    void resetDefaultFont(QString cur_font);
    void resetDesktopFont(QString cur_font);
    void resetMonospaceFont(QString cur_font);
    void resetDocumentFont(QString cur_font);
    void resetTitlebarFont(QString cur_font);

private:
    SessionDispatcher *sessionproxy;
    MainWindow *parentWindow;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *default_font_label;
    QLabel *desktop_font_label;
    QLabel *monospace_font_label;
    QLabel *document_font_label;
    QLabel *titlebar_font_label;
    QLabel *scaling_label;
    QLabel *hinting_label;
    QLabel *antialiasing_label;
    QPushButton *default_font_btn;
    QPushButton *desktop_font_btn;
    QPushButton *monospace_font_btn;
    QPushButton *document_font_btn;
    QPushButton *titlebar_font_btn;
    QDoubleSpinBox *scaling_slider;
    QComboBox *hinting_combo;
    QComboBox *antialiasing_combo;

    QString current_font;
    QString desktop_font;
    QString monospace_font;
    QString document_font;
    QString titlebar_font;
};

#endif // FONTWIDGET_H
