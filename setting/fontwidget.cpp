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

#include "fontwidget.h"
#include <QDebug>
#include "../component/kylinfontdialog.h"
#include "../dbusproxy/youkersessiondbus.h"
#include "../mainui/mainwindow.h"

FontWidget::FontWidget(QWidget *parent, SessionDispatcher *proxy, MainWindow *window) :
    QWidget(parent),
    sessionproxy(proxy),
    parentWindow(window)
{
//    splitter = new QSplitter();
//    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    splitter->setOrientation(Qt::Vertical);
//    splitter->setHandleWidth(1);

//    top_widget = new QWidget();
//    bottom_widget = new QWidget();

//    title_label = new QLabel();
//    title_label->setFixedHeight(20);
//    description_label = new QLabel();
//    description_label->setFixedHeight(20);
//    back_btn = new QPushButton();

//    QVBoxLayout *v_layout = new QVBoxLayout();
//    v_layout->addWidget(title_label);
//    v_layout->addWidget(description_label);
//    v_layout->setMargin(0);
//    v_layout->setSpacing(1);

//    QHBoxLayout *h_layout = new QHBoxLayout();
//    h_layout->addWidget(back_btn);
//    h_layout->addLayout(v_layout);
//    h_layout->addStretch();
//    top_widget->setLayout(h_layout);
//    top_widget->setFixedSize(900,60);
//    h_layout->setSpacing(20);
//    h_layout->setContentsMargins(20, 0, 0, 0);

    default_font_label = new QLabel();
    desktop_font_label = new QLabel();
    monospace_font_label = new QLabel();
    document_font_label = new QLabel();
    titlebar_font_label = new QLabel();
    scaling_label = new QLabel();
    hinting_label = new QLabel();
    antialiasing_label = new QLabel();

    default_font_btn = new QPushButton();
    desktop_font_btn = new QPushButton();
    monospace_font_btn = new QPushButton();
    document_font_btn = new QPushButton();
    titlebar_font_btn = new QPushButton();
    scaling_slider = new QDoubleSpinBox();
    scaling_slider->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    scaling_slider->setSingleStep(0.1);
    scaling_slider->setMinimum(0.5);
    scaling_slider->setMaximum(3.0);
    hinting_combo = new QComboBox();
    antialiasing_combo = new QComboBox();

    default_font_btn->setObjectName("transparentButton");
    desktop_font_btn->setObjectName("transparentButton");
    monospace_font_btn->setObjectName("transparentButton");
    document_font_btn->setObjectName("transparentButton");
    titlebar_font_btn->setObjectName("transparentButton");
    default_font_btn->setFocusPolicy(Qt::NoFocus);
    desktop_font_btn->setFocusPolicy(Qt::NoFocus);
    monospace_font_btn->setFocusPolicy(Qt::NoFocus);
    document_font_btn->setFocusPolicy(Qt::NoFocus);
    titlebar_font_btn->setFocusPolicy(Qt::NoFocus);
    default_font_btn->setToolTip(tr("Click here to change font"));
    desktop_font_btn->setToolTip(tr("Click here to change font"));
    monospace_font_btn->setToolTip(tr("Click here to change font"));
    document_font_btn->setToolTip(tr("Click here to change font"));
    titlebar_font_btn->setToolTip(tr("Click here to change font"));


    default_font_label->setFixedWidth(150);
    desktop_font_label->setFixedWidth(150);
    monospace_font_label->setFixedWidth(150);
    document_font_label->setFixedWidth(150);
    titlebar_font_label->setFixedWidth(150);
    scaling_label->setFixedWidth(150);
    hinting_label->setFixedWidth(150);
    antialiasing_label->setFixedWidth(150);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(default_font_label);
    layout1->addWidget(default_font_btn);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(desktop_font_label);
    layout2->addWidget(desktop_font_btn);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(monospace_font_label);
    layout3->addWidget(monospace_font_btn);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(document_font_label);
    layout4->addWidget(document_font_btn);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(titlebar_font_label);
    layout5->addWidget(titlebar_font_btn);
    layout5->addStretch();
    QHBoxLayout *layout6 = new QHBoxLayout();
    layout6->setSpacing(10);
    layout6->addWidget(scaling_label);
    layout6->addWidget(scaling_slider);
    layout6->addStretch();
    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->setSpacing(10);
    layout7->addWidget(hinting_label);
    layout7->addWidget(hinting_combo);
    layout7->addStretch();
    QHBoxLayout *layout8 = new QHBoxLayout();
    layout8->setSpacing(10);
    layout8->addWidget(antialiasing_label);
    layout8->addWidget(antialiasing_combo);
    layout8->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addLayout(layout6);
    layout->addLayout(layout7);
    layout->addLayout(layout8);
    layout->addStretch();
//    bottom_widget->setLayout(layout);
    setLayout(layout);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 0, 0);

//    splitter->addWidget(top_widget);
//    splitter->addWidget(bottom_widget);

//    QHBoxLayout *main_layout = new QHBoxLayout;
//    main_layout->addStretch();
//    main_layout->addWidget(splitter);
//    main_layout->setSpacing(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(main_layout);
    this->initData();
    this->setLanguage();
    this->initConnect();
}

FontWidget::~FontWidget()
{
//    if(label != NULL)
//    {
//        delete label;
//        label = NULL;
//    }
//    if(back_btn != NULL)
//    {
//        delete back_btn;
//        back_btn = NULL;
//    }
}

void FontWidget::setLanguage() {
//    title_label->setText(tr("Default font settings"));
//    description_label->setText(tr("According to personal preferences to set the system default font, click the  'Restore' button, can be restored to the state before the font settings."));
//    back_btn->setText(tr("Back"));
    default_font_label->setText(tr("Default Font") + ":");
    desktop_font_label->setText(tr("Desktop Font") + ":");
    monospace_font_label->setText(tr("Monospace Font") + ":");
    document_font_label->setText(tr("Document Font") + ":");
    titlebar_font_label->setText(tr("Titlebar Font") + ":");
    scaling_label->setText(tr("Global Font Scaling") + ":");
    hinting_label->setText(tr("Hinting") + ":");
    antialiasing_label->setText(tr("Antialiasing") + ":");
}

void FontWidget::initData()
{
    current_font = sessionproxy->get_font_qt();
    desktop_font = sessionproxy->get_desktop_font_qt();
    if(desktop_font.isEmpty())
        sessionproxy->set_desktop_font_qt_default();
        desktop_font = sessionproxy->get_desktop_font_qt();
    monospace_font = sessionproxy->get_monospace_font_qt();
    document_font = sessionproxy->get_document_font_qt();
    titlebar_font = sessionproxy->get_window_title_font_qt();
    default_font_btn->setText(current_font);
    desktop_font_btn->setText(desktop_font);
    monospace_font_btn->setText(monospace_font);
    document_font_btn->setText(document_font);
    titlebar_font_btn->setText(titlebar_font);
    scaling_slider->setValue(sessionproxy->get_font_zoom_qt());

    QString current_smooth = sessionproxy->get_smooth_style_qt();
    QStringList smoothlist  = sessionproxy->get_smooth_style_list_qt();
    hinting_combo->clear();
    hinting_combo->clearEditText();
    hinting_combo->addItems(smoothlist);
    QList<QString>::Iterator it = smoothlist.begin(), itend = smoothlist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == current_smooth)
            break;
    }
    hinting_combo->setCurrentIndex(initIndex);

    QString current_antialiasing = sessionproxy->get_antialiasing_style_qt();
    QStringList antialiasinglist  = sessionproxy->get_antialiasing_style_list_qt();
    antialiasing_combo->clear();
    antialiasing_combo->clearEditText();
    antialiasing_combo->addItems(antialiasinglist);
    QList<QString>::Iterator ite = antialiasinglist.begin(), iteend = antialiasinglist.end();
    int index = 0;
    for(;ite != iteend; ite++,index++)
    {
        if(*ite == current_antialiasing)
            break;
    }
    antialiasing_combo->setCurrentIndex(index);
}

void FontWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(default_font_btn, SIGNAL(clicked()), this, SLOT(setDefaultFont()));
    connect(desktop_font_btn, SIGNAL(clicked()), this, SLOT(setDesktopFont()));
    connect(monospace_font_btn, SIGNAL(clicked()), this, SLOT(setMonospaceFont()));
    connect(document_font_btn, SIGNAL(clicked()), this, SLOT(setDocumentFont()));
    connect(titlebar_font_btn, SIGNAL(clicked()), this, SLOT(setTitlebarFont()));
    connect(scaling_slider, SIGNAL(valueChanged(double)), this, SLOT(setScalingValue(double)));
    connect(hinting_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setFontHinting(QString)));
    connect(antialiasing_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setFontAntialiasing(QString)));
}

void FontWidget::setDefaultFont() {
//    KylinFontDialog *fontDialog = new KylinFontDialog(mSettings, flag, current_font, 0);
    KylinFontDialog *fontDialog = new KylinFontDialog(current_font, 0);
    connect(fontDialog, SIGNAL(rebackCurrentFont(QString)), this, SLOT(resetDefaultFont(QString)));
    int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (600  / 2);
    int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (500  / 2);
    fontDialog->move(w_x, w_y);
    fontDialog->exec();
}

void FontWidget::resetDefaultFont(QString cur_font)
{
    sessionproxy->set_font_qt(cur_font);
    default_font_btn->setText(cur_font);
}

void FontWidget::setDesktopFont() {
    KylinFontDialog *fontDialog = new KylinFontDialog(desktop_font, 0);
    connect(fontDialog, SIGNAL(rebackCurrentFont(QString)), this, SLOT(resetDesktopFont(QString)));
    int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (600  / 2);
    int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (500  / 2);
    fontDialog->move(w_x, w_y);
    fontDialog->exec();
}

void FontWidget::resetDesktopFont(QString cur_font)
{
    sessionproxy->set_desktop_font_qt(cur_font);
    desktop_font_btn->setText(cur_font);
}

void FontWidget::setMonospaceFont() {
    KylinFontDialog *fontDialog = new KylinFontDialog(monospace_font, 0);
    connect(fontDialog, SIGNAL(rebackCurrentFont(QString)), this, SLOT(resetMonospaceFont(QString)));
    int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (600  / 2);
    int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (500  / 2);
    fontDialog->move(w_x, w_y);
    fontDialog->exec();
}

void FontWidget::resetMonospaceFont(QString cur_font)
{
    sessionproxy->set_monospace_font_qt(cur_font);
//    qDebug() << cur_font;
    monospace_font_btn->setText(cur_font);
}

void FontWidget::setDocumentFont() {
    KylinFontDialog *fontDialog = new KylinFontDialog(document_font, 0);
    connect(fontDialog, SIGNAL(rebackCurrentFont(QString)), this, SLOT(resetDocumentFont(QString)));
    int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (600  / 2);
    int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (500  / 2);
    fontDialog->move(w_x, w_y);
    fontDialog->exec();
}

void FontWidget::resetDocumentFont(QString cur_font)
{
    sessionproxy->set_document_font_qt(cur_font);
//    qDebug() << cur_font;
    document_font_btn->setText(cur_font);
}

void FontWidget::setTitlebarFont() {
    KylinFontDialog *fontDialog = new KylinFontDialog(titlebar_font, 0);
    connect(fontDialog, SIGNAL(rebackCurrentFont(QString)), this, SLOT(resetTitlebarFont(QString)));
    int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (600  / 2);
    int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (500  / 2);
    fontDialog->move(w_x, w_y);
    fontDialog->exec();
}

void FontWidget::resetTitlebarFont(QString cur_font)
{
    sessionproxy->set_window_title_font_qt(cur_font);
//    qDebug() << cur_font;
    titlebar_font_btn->setText(cur_font);
}


void FontWidget::setScalingValue(double value)
{
    sessionproxy->set_font_zoom_qt(value);
}

void FontWidget::setFontHinting(QString selected)
{
    sessionproxy->set_smooth_style_qt(selected);
}

void FontWidget::setFontAntialiasing(QString selected)
{
    sessionproxy->set_antialiasing_style_qt(selected);
}
