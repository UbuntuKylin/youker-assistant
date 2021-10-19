/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "aboutwidget.h"
#include "xatom-helper.h"
#include "commondef.h"

#include <QPainter>
#include <QPainterPath>

AboutWidget::AboutWidget(QWidget *parent):
    QDialog(parent)
{
    this->setFixedSize(420,560);
//    this->setAttribute(Qt::WA_DeleteOnClose);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    initUI();
}

AboutWidget::~AboutWidget()
{
    if (qtSettings) {
        delete qtSettings;
        qtSettings = nullptr;
    }
}

void AboutWidget::initUI()
{
    title_icon = new QLabel(this);
    title_icon->setGeometry(8,8,24,24);

    title_name = new QLabel(this);
    title_name->setGeometry(40,8,300,25);
    title_name->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    close_btn = new QPushButton(this);
    close_btn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    close_btn->setProperty("isWindowButton", 0x2);
    close_btn->setProperty("useIconHighlightEffect", 0x8);
    close_btn->setFlat(true);
    close_btn->setToolTip(tr("Close"));
    close_btn->setCheckable(false);
    close_btn->setCursor(QCursor(Qt::ArrowCursor));
    close_btn->setGeometry(386,4,30,30);
    connect(close_btn,&QPushButton::released,this,[=]{
        this->close();
    });

    app_icon = new QLabel(this);
    app_icon->setGeometry(162,72,96,96);

    QFont font;
    font.setPixelSize(18);

    app_name = new QLabel(this);
    app_name->setGeometry(10,184,400,28);
    app_name->setAlignment(Qt::AlignCenter);
    app_name->setFont(font);

    font.setPixelSize(14);
    app_version = new QLabel(this);
    app_version->setGeometry(10,224,400,24);
    app_version->setAlignment(Qt::AlignCenter);
    app_version->setFont(font);

    app_description = new QTextBrowser();
    app_description->setOpenLinks(true);
    app_description->setOpenExternalLinks(true);
    app_description->setReadOnly(true);
    app_description->setContextMenuPolicy (Qt::NoContextMenu);
    app_description->setStyleSheet("QTextBrowser{border:none;}");

    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setWidgetResizable(true);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollarea->setWidget(app_description);
    scrollarea->setGeometry(32,260,356,260);
    scrollarea->setStyleSheet("QScrollArea{border:none;}");

    initThemeMode();
}

void AboutWidget::setAppIcon(const QString &text)
{
    if(text.isEmpty() || text == ""){
        qDebug() << Q_FUNC_INFO << "arg is empty!!!";
        return;
    }else{
        if(QIcon::hasThemeIcon(text)){
            title_icon->setPixmap(QIcon::fromTheme(text).pixmap(24,24));
            app_icon->setPixmap(QIcon::fromTheme(text).pixmap(96,96));
        }else{
            qDebug() << Q_FUNC_INFO << "No icon exists: " << text << " !!!";
        }
    }
}

void AboutWidget::setAppName(const QString &text)
{
    if(text.isEmpty() || text == ""){
        qDebug() << Q_FUNC_INFO << "APP name should not be empty!!!";
        return;
    }else{
        title_name->setText(text);
        this->setWindowTitle(text);
        title_name->update();
        app_name->setText(text);
    }
}

void AboutWidget::setAppVersion(const QString &text)
{
    if(text.isEmpty() || text == ""){
        qDebug() << Q_FUNC_INFO << "APP version should not be empty!!!";
        return;
    }else{
        app_version->setText(tr("VERSION")+":  "+text);
    }
}

void AboutWidget::setAppDescription(const QString &text)
{
    app_description->append(text);
}

//void AboutWidget::closeEvent(QCloseEvent *event)
//{
//    Q_UNUSED(event);
//    qDebug() << Q_FUNC_INFO;
//}

void AboutWidget::initThemeMode()
{
    const QByteArray idd(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(idd)) {
        qtSettings = new QGSettings(idd);
    }
    if (qtSettings) {
        //监听主题改变
        connect(qtSettings, &QGSettings::changed, this, [=](const QString &key)
        {
            if (key == "styleName") {
            } else if ("iconThemeName" == key) {
                setAppIcon("kylin-assistant");
            }
        });
    }
}

void AboutWidget::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    QPainter painter(this);

    path.addRect(this->rect());
    path.setFillRule(Qt::WindingFill);
    painter.setBrush(this->palette().base());
    painter.setPen(Qt::transparent);
    painter.drawPath(path);
    QDialog::paintEvent(event);
}
