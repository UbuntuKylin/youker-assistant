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

#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QComboBox>

class MainWindow;
class QLabel;
class QPushButton;
class QComboBox;
class QDoubleSpinBox;
#include "settingmodulelpage.h"

class FontWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit FontWidget(QWidget *parent = 0, MainWindow *window = 0, QString cur_desktop = "", QString skin = ":/background/res/skin/1.png");
    ~FontWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;
    void resetCurrentSkin(QString skin);

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
    void restore_default_font();
    void restore_desktop_font();
    void restore_monospace_font();
    void restore_document_font();
    void restore_titlebar_font();

    void fontwidget_notify_string(QString key, QString value);
    void fontwidget_notify_double(QString key, double value);

    void onSendFontValue(const QString &curFont);
    void onSendDesktopFontValue(const QString &curFont);
    void onSendMonospaceFontValue(const QString &curFont);
    void onSendDocumentFontValue(const QString &curFont);
    void onSendTitlebarFontValue(const QString &curFont);
    void onSendFontSmoothAndAntialiasingValue(double fontZoom, const QString &current_smooth, const QStringList &smoothlist, const QString &current_antialiasing, const QStringList &antialiasinglist);

signals:
    void requestFontData();
    void setDefaultFontByName(const QString &cur_font);
    void setDesktopFontByName(const QString &cur_font);
    void setMonospaceFontByName(const QString &cur_font);
    void setDocumentFontByName(const QString &cur_font);
    void setTitlebarFontByName(const QString &cur_font);
    void resetFontZoomScalingValue(double value);
    void resetFontHinting(const QString &selected);
    void resetFontAntialiasing(const QString &selected);
    void restoreDefaultFont(bool isMate);
    void restoreDesktopDefaultFont(bool isMate);
    void restoreMonospaceDefaultFont(bool isMate);
    void restoreDocumentDefaultFont(bool isMate);
    void restoreTitlebarDefaultFont(bool isMate);

private:
    QStringList m_smoothlist;
    QStringList m_antialiasinglist;
    MainWindow *parentWindow;
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

    QPushButton *restore_default_font_btn;
    QPushButton *restore_desktop_font_btn;
    QPushButton *restore_monospace_font_btn;
    QPushButton *restore_document_font_btn;
    QPushButton *restore_titlebar_font_btn;

    QString current_font;
    QString desktop_font;
    QString monospace_font;
    QString document_font;
    QString titlebar_font;
    QString desktop;
    QString cur_skin;
};

#endif // FONTWIDGET_H
