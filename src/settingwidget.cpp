/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#include "settingwidget.h"
#include <QDebug>
#include <QStackedLayout>

#include "../setting/settinglistview.h"
#include "../setting/settingmodel.h"
#include "../setting/settingdelegate.h"

SettingWidget::SettingWidget(/*QStringList cpulist, QString cpu, */QString cur_desktop, /*bool has_battery, */QWidget *parent) :
    QWidget(parent)
//    ,m_cpuList(cpulist)
//    ,m_currentCpu(cpu)
    ,desktop(cur_desktop)
//    ,battery(has_battery)
{
    this->setFixedSize(900, 403);
//    setStyleSheet("background-color: rgba(155, 255, 255, .238);");

    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    itemSpace = 20;
    m_settingModel = new SettingModel;
    m_settingListView = new SettingListView;

    m_settingListView->setItemDelegate(new SettingDelegate);
    m_settingListView->setModel(m_settingModel);
    m_settingListView->setFixedSize(120 * 6 + (6+1)*itemSpace + 2, 400);//每行放6个item，间隔为20，每个item的宽度为120

    QVBoxLayout *navLayout = new QVBoxLayout(this);
    navLayout->addWidget(m_settingListView);
    navLayout->setSpacing(0);
    navLayout->setMargin(0);
    navLayout->setContentsMargins(20, 1, 20, 1);

    connect(m_settingListView, SIGNAL(entered(QModelIndex)), this, SLOT(onSettingItemEntered(QModelIndex)));
    connect(m_settingListView, SIGNAL(entered(QModelIndex)), m_settingModel, SLOT(setCurrentItem(QModelIndex)));
    connect(m_settingListView, SIGNAL(clicked(QModelIndex)), this, SLOT(onSettingItemClicked(QModelIndex)), Qt::QueuedConnection);

    m_settingModel->addItem("ThemePage");
    m_settingModel->addItem("IconPage");
    m_settingModel->addItem("MousePage");
    m_settingModel->addItem("SoundPage");
    m_settingModel->addItem("PanelPage");
    m_settingModel->addItem("MenuPage");
    m_settingModel->addItem("WindowPage");
    m_settingModel->addItem("FontPage");
    m_settingModel->addItem("TouchPadPage");
    m_settingModel->addItem("EnergyPage");
    m_settingModel->addItem("FMPage");

    stacked_widget = new QStackedWidget(this);
    stacked_widget->setFixedSize(900, 403);
//    stacked_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    stacked_widget->setVisible(false);

    //this->qtui = NULL;
}

SettingWidget::~SettingWidget()
{
    /*if(qtui != NULL)
    {
        delete qtui;
        qtui = NULL;
    }*/
}

void SettingWidget::onSettingItemClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QString m_currentModuleName = index.data().toString();
    if (m_currentModuleName.isEmpty() || m_currentModuleName.isNull())
        return;

    //qDebug() << "onSettingItemClicked:" << m_currentModuleName;

    for (int i = 0; i < stacked_widget->count(); i++) {
        if (SettingModulePage *page = static_cast<SettingModulePage *>(stacked_widget->widget(i))) {
            if (page->settingModuleName() == m_currentModuleName) {
                QPointer<SettingModulePage> panel(page);
                if (panel.isNull()) {
                    continue;
                }
                page->initSettingData();
                if (m_settingListView->isVisible())
                    m_settingListView->setVisible(false);
                if (!stacked_widget->isVisible())
                    stacked_widget->setVisible(true);

                emit changeActionPage(m_currentModuleName);
                stacked_widget->setCurrentWidget(page);
                break;
            }
        }
    }
}

void SettingWidget::onSettingItemEntered(const QModelIndex &index)
{
    /*if (!index.isValid())
        return;

    qDebug() << "onSettingItemEntered:" << index.data().toString();*/
}

void SettingWidget::initSettingsUI(QStringList cpulist, QString cpu, bool has_battery/*, QString skin*/)
{
    m_cpuList = cpulist;
    m_currentCpu = cpu;
    battery = has_battery;

    theme_widget = new ThemeWidget(this);
    icon_widget = new IconWidget(this, desktop);
    mouse_widget = new MouseWidget(this, desktop);
    sound_widget = new SoundWidget(this, desktop);
//    animation_widget = new AnimationWidget(this, systemProxy, p_mainwindow);
    launcher_widget = new MenuWidget(this, desktop);
    panel_widget = new PanelWidget(this, desktop, battery);
    window_widget = new WindowWidget(this, desktop);
    font_widget = new FontWidget(this, p_mainwindow, desktop, "");//TODO:read skin from ini file
    touchpad_widget = new TouchpadWidget(this, desktop);
//    deadpixel_widget = new DeadpixelWidget(this);
    conserve_widget = new EnergyWidget(m_cpuList, m_currentCpu, desktop, battery, this);
    nautilus_widget = new FileManagerWidget(this);
    stacked_widget->addWidget(theme_widget);
    stacked_widget->addWidget(icon_widget);
    stacked_widget->addWidget(mouse_widget);
    stacked_widget->addWidget(sound_widget);
//    stacked_widget->addWidget(animation_widget);
    stacked_widget->addWidget(launcher_widget);
    stacked_widget->addWidget(panel_widget);
    stacked_widget->addWidget(window_widget);
    stacked_widget->addWidget(font_widget);
    stacked_widget->addWidget(touchpad_widget);
    stacked_widget->addWidget(conserve_widget);
    stacked_widget->addWidget(nautilus_widget);

    //theme
//    connect(this, SIGNAL(string_value_notify(QString,QString)), theme_widget, SLOT(themewidget_notify_string(QString,QString)));
    connect(this, SIGNAL(sendThemeList(QString,QStringList)), theme_widget, SLOT(onReceiveThemeList(QString,QStringList)));
    connect(theme_widget, SIGNAL(changeSystemTheme(QString)), this, SIGNAL(changeSystemTheme(QString)));
    connect(theme_widget, SIGNAL(requestThemeData()), this, SIGNAL(requestThemeData()));

    //icon
//    connect(this, SIGNAL(string_value_notify(QString,QString)), icon_widget, SLOT(iconwidget_notify_string(QString,QString)));
//    connect(this, SIGNAL(bool_value_notify(QString,bool)), icon_widget, SLOT(iconwidget_notify_bool(QString,bool)));
    connect(this, SIGNAL(sendIconThemeList(QString,QStringList)), icon_widget, SLOT(onReceiveIconThemeList(QString,QStringList)));
    connect(this, SIGNAL(sendDisplayIconValue(bool,bool,bool,bool,bool)), icon_widget, SLOT(onReceiveDisplayIconValue(bool,bool,bool,bool,bool)));
    connect(icon_widget, SIGNAL(resetIconTheme(QString)), this, SIGNAL(resetIconTheme(QString)));
    connect(icon_widget, SIGNAL(displayComputerIcon(bool)), this, SIGNAL(displayComputerIcon(bool)));
    connect(icon_widget, SIGNAL(displayFolderIcon(bool)), this, SIGNAL(displayFolderIcon(bool)));
    connect(icon_widget, SIGNAL(displayNetworkIcon(bool)), this, SIGNAL(displayNetworkIcon(bool)));
    connect(icon_widget, SIGNAL(displayRecycleBinIcon(bool)), this, SIGNAL(displayRecycleBinIcon(bool)));
    connect(icon_widget, SIGNAL(displayDiskIcon(bool)), this, SIGNAL(displayDiskIcon(bool)));
    connect(icon_widget, SIGNAL(requestIconData()), this, SIGNAL(requestIconData()));

    //mouse
//    connect(this, SIGNAL(string_value_notify(QString,QString)), mouse_widget, SLOT(mousewidget_notify_string(QString,QString)));
//    connect(this, SIGNAL(int_value_notify(QString,int)), mouse_widget, SLOT(mousewidget_notify_int(QString,int)));
    connect(mouse_widget, SIGNAL(requestMouseData()), this, SIGNAL(requestMouseData()));
    connect(this, SIGNAL(sendMouseThemeAndCusorSize(QString,QStringList,int)), mouse_widget, SLOT(onReceiveMouseThemeAndCusorSize(QString,QStringList,int)));
    connect(mouse_widget, SIGNAL(resetMouseCursorTheme(QString)), this, SIGNAL(resetMouseCursorTheme(QString)));
    connect(mouse_widget, SIGNAL(resetMouseCursorSize(int)), this, SIGNAL(resetMouseCursorSize(int)));


    //voice
//    connect(this, SIGNAL(string_value_notify(QString,QString)), sound_widget, SLOT(voicewidget_notify_string(QString,QString)));
//    connect(this, SIGNAL(bool_value_notify(QString,bool)), sound_widget, SLOT(voicewidget_notify_bool(QString,bool)));
    connect(sound_widget, SIGNAL(requestSoundData()), this, SIGNAL(requestSoundData()));
    connect(this, SIGNAL(sendSoundList(QString,QStringList)), sound_widget, SLOT(onSendSoundList(QString,QStringList)));
    connect(this, SIGNAL(sendEnableSoundValue(bool,bool,bool)), sound_widget, SLOT(onSendEnableSoundValue(bool,bool,bool)));
    connect(sound_widget, SIGNAL(resetVoiceTheme(QString)), this, SIGNAL(resetVoiceTheme(QString)));
    connect(sound_widget, SIGNAL(resetLoginTipVoice(bool)), this, SIGNAL(resetLoginTipVoice(bool)));
    connect(sound_widget, SIGNAL(resetEventVoice(bool)), this, SIGNAL(resetEventVoice(bool)));
    connect(sound_widget, SIGNAL(resetInputFeedbackVoice(bool)), this, SIGNAL(resetInputFeedbackVoice(bool)));


    //panel
//    connect(this, SIGNAL(string_value_notify(QString,QString)), panel_widget, SLOT(panelwidget_notify_string(QString,QString)));
//    connect(this, SIGNAL(bool_value_notify(QString,bool)), panel_widget, SLOT(panelwidget_notify_bool(QString,bool)));
    connect(panel_widget, SIGNAL(requestMateOrUnityPanelData(bool)), this, SIGNAL(requestMateOrUnityPanelData(bool)));
    connect(this, SIGNAL(sendMatePanelValue(bool,bool,bool,bool)), panel_widget, SLOT(onSendMatePanelValue(bool,bool,bool,bool)));
    connect(this, SIGNAL(sendUnityBlurAndTransparencyValue(int,double)), panel_widget, SLOT(onSendUnityBlurAndTransparencyValue(int,double)));
    connect(this, SIGNAL(sendUnityTimeValue(QString,QStringList,bool,bool,bool)), panel_widget, SLOT(onSendUnityTimeValue(QString,QStringList,bool,bool,bool)));
    connect(this, SIGNAL(sendUnityPanelPowerValue(QString,QStringList,bool,bool)), panel_widget, SLOT(onSendUnityPanelPowerValue(QString,QStringList,bool,bool)));
    connect(panel_widget, SIGNAL(resetPanelTransparencyValue(double)), this, SIGNAL(resetPanelTransparencyValue(double)));
    connect(panel_widget, SIGNAL(resetDateFormat(QString)), this, SIGNAL(resetDateFormat(QString)));
    connect(panel_widget, SIGNAL(resetShowBatteryIcon(QString)), this, SIGNAL(resetShowBatteryIcon(QString)));
    connect(panel_widget, SIGNAL(resetDashBlurExperimental(int)), this, SIGNAL(resetDashBlurExperimental(int)));
    connect(panel_widget, SIGNAL(resetDisplaySeconds(bool)), this, SIGNAL(resetDisplaySeconds(bool)));
    connect(panel_widget, SIGNAL(resetDisplayWeek(bool)), this, SIGNAL(resetDisplayWeek(bool)));
    connect(panel_widget, SIGNAL(resetDisplayDate(bool)), this, SIGNAL(resetDisplayDate(bool)));
    connect(panel_widget, SIGNAL(resetDisplayBatteryPercentage(bool)), this, SIGNAL(resetDisplayBatteryPercentage(bool)));
    connect(panel_widget, SIGNAL(resetDisplayBatteryTime(bool)), this, SIGNAL(resetDisplayBatteryTime(bool)));
    connect(panel_widget, SIGNAL(resetShowApplications(bool)), this, SIGNAL(resetShowApplications(bool)));
    connect(panel_widget, SIGNAL(resetShowDesktop(bool)), this, SIGNAL(resetShowDesktop(bool)));
    connect(panel_widget, SIGNAL(resetShowIcon(bool)), this, SIGNAL(resetShowIcon(bool)));
    connect(panel_widget, SIGNAL(resetShowPlaces(bool)), this, SIGNAL(resetShowPlaces(bool)));

    //launcher menu
//    connect(this, SIGNAL(string_value_notify(QString,QString)), launcher_widget, SLOT(launcherwidget_notify_string(QString,QString)));
//    connect(this, SIGNAL(bool_value_notify(QString,bool)), launcher_widget, SLOT(launcherwidget_notify_bool(QString,bool)));
//    connect(this, SIGNAL(int_value_notify(QString,int)), launcher_widget, SLOT(launcherwidget_notify_int(QString,int)));
//    connect(this, SIGNAL(double_value_notify(QString,double)), launcher_widget, SLOT(launcherwidget_notify_double(QString,double)));
    connect(launcher_widget, SIGNAL(requestMateOrUnityMenuData(bool)), this, SIGNAL(requestMateOrUnityMenuData(bool)));
    connect(this, SIGNAL(sendMatePanelIconValue(int,int,bool,bool)), launcher_widget, SLOT(onSendMatePanelIconValue(int,int,bool,bool)));
    connect(this, SIGNAL(sendUnityIconValue(int,bool,bool,double,int,QStringList)), launcher_widget, SLOT(onSendUnityIconValue(int,bool,bool,double,int,QStringList)));
    connect(this, SIGNAL(sendUnityLauncherPosition(QString,QStringList)), launcher_widget, SLOT(onSendUnityLauncherPosition(QString,QStringList)));

    connect(launcher_widget, SIGNAL(resetIconSizeValue(int)), this, SIGNAL(resetIconSizeValue(int)));
    connect(launcher_widget, SIGNAL(resetTransparencyValue(int)), this, SIGNAL(resetTransparencyValue(int)));
    connect(launcher_widget, SIGNAL(resetIconColouring(int)), this, SIGNAL(resetIconColouring(int)));
    connect(launcher_widget, SIGNAL(resetAutoHide(bool)), this, SIGNAL(resetAutoHide(bool)));
    connect(launcher_widget, SIGNAL(resetDisplayDesktopIcon(bool)), this, SIGNAL(resetDisplayDesktopIcon(bool)));
    connect(launcher_widget, SIGNAL(resetTopIconSizeValue(int)), this, SIGNAL(resetTopIconSizeValue(int)));
    connect(launcher_widget, SIGNAL(resetBottomIconSizeValue(int)), this, SIGNAL(resetBottomIconSizeValue(int)));
    connect(launcher_widget, SIGNAL(resetTopAutoHide(bool)), this, SIGNAL(resetTopAutoHide(bool)));
    connect(launcher_widget, SIGNAL(resetBottomAutoHide(bool)), this, SIGNAL(resetBottomAutoHide(bool)));
    connect(launcher_widget, SIGNAL(resetLauncherPosition(QString)), this, SIGNAL(resetLauncherPosition(QString)));


    //window
    connect(window_widget, SIGNAL(requesetWindowButtonAlign()), this, SIGNAL(requesetWindowButtonAlign()));
    connect(window_widget, SIGNAL(requesetMenusHaveIcons()), this, SIGNAL(requesetMenusHaveIcons()));
    connect(window_widget, SIGNAL(requesetWindowTitileTags()), this, SIGNAL(requesetWindowTitileTags()));
    connect(this, SIGNAL(sendWindowButtonAlign(QString)), window_widget, SLOT(onSendWindowButtonAlign(QString)));
    connect(this, SIGNAL(sendMenusHaveIcons(bool)), window_widget, SLOT(onSendMenusHaveIcons(bool)));
    connect(this, SIGNAL(sendWindowTitileTags(QString,QStringList,QStringList,QString,QString,QString)), window_widget, SLOT(onSendWindowTitileTags(QString,QStringList,QStringList,QString,QString,QString)));
    connect(window_widget, SIGNAL(resetMenusHaveIcon(bool)), this, SIGNAL(resetMenusHaveIcon(bool)));
    connect(window_widget, SIGNAL(resetTitlebarWheel(QString)), this, SIGNAL(resetTitlebarWheel(QString)));
    connect(window_widget, SIGNAL(resetTitlebarDoubleClick(QString)), this, SIGNAL(resetTitlebarDoubleClick(QString)));
    connect(window_widget, SIGNAL(resetMouseMiddleClick(QString)), this, SIGNAL(resetMouseMiddleClick(QString)));
    connect(window_widget, SIGNAL(resetMouseRightClick(QString)), this, SIGNAL(resetMouseRightClick(QString)));
    connect(window_widget, SIGNAL(resetWindowButtonLeftOrRightAlign(bool)), this, SIGNAL(resetWindowButtonLeftOrRightAlign(bool)));


    //font
    connect(font_widget, SIGNAL(requestFontData()), this, SIGNAL(requestFontData()));

    connect(this, SIGNAL(sendFontValue(QString)), font_widget, SLOT(onSendFontValue(QString)));
    connect(this, SIGNAL(sendDesktopFontValue(QString)), font_widget, SLOT(onSendDesktopFontValue(QString)));
    connect(this, SIGNAL(sendMonospaceFontValue(QString)), font_widget, SLOT(onSendMonospaceFontValue(QString)));
    connect(this, SIGNAL(sendDocumentFontValue(QString)), font_widget, SLOT(onSendDocumentFontValue(QString)));
    connect(this, SIGNAL(sendTitlebarFontValue(QString)), font_widget, SLOT(onSendTitlebarFontValue(QString)));
    connect(this, SIGNAL(sendFontSmoothAndAntialiasingValue(double,QString,QStringList,QString,QStringList)), font_widget, SLOT(onSendFontSmoothAndAntialiasingValue(double,QString,QStringList,QString,QStringList)));

    connect(font_widget, SIGNAL(setDefaultFontByName(QString)), this, SIGNAL(setDefaultFontByName(QString)));
    connect(font_widget, SIGNAL(setDesktopFontByName(QString)), this, SIGNAL(setDesktopFontByName(QString)));
    connect(font_widget, SIGNAL(setMonospaceFontByName(QString)), this, SIGNAL(setMonospaceFontByName(QString)));
    connect(font_widget, SIGNAL(setDocumentFontByName(QString)), this, SIGNAL(setDocumentFontByName(QString)));
    connect(font_widget, SIGNAL(setTitlebarFontByName(QString)), this, SIGNAL(setTitlebarFontByName(QString)));
    connect(font_widget, SIGNAL(resetFontZoomScalingValue(double)), this, SIGNAL(resetFontZoomScalingValue(double)));
    connect(font_widget, SIGNAL(resetFontHinting(QString)), this, SIGNAL(resetFontHinting(QString)));
    connect(font_widget, SIGNAL(resetFontAntialiasing(QString)), this, SIGNAL(resetFontAntialiasing(QString)));
    connect(font_widget, SIGNAL(restoreDefaultFont(bool)), this, SIGNAL(restoreDefaultFont(bool)));
    connect(font_widget, SIGNAL(restoreDesktopDefaultFont(bool)), this, SIGNAL(restoreDesktopDefaultFont(bool)));
    connect(font_widget, SIGNAL(restoreMonospaceDefaultFont(bool)), this, SIGNAL(restoreMonospaceDefaultFont(bool)));
    connect(font_widget, SIGNAL(restoreDocumentDefaultFont(bool)), this, SIGNAL(restoreDocumentDefaultFont(bool)));
    connect(font_widget, SIGNAL(restoreTitlebarDefaultFont(bool)), this, SIGNAL(restoreTitlebarDefaultFont(bool)));


    //touchpad
    connect(touchpad_widget, SIGNAL(requestMateOrUnityTouchpadData(bool)), this, SIGNAL(requestMateOrUnityTouchpadData(bool)));
    connect(this, SIGNAL(sendTouchPadValue(bool,bool,QString,int,QString)), touchpad_widget, SLOT(onSendTouchPadValue(bool,bool,QString,int,QString)));
    connect(touchpad_widget, SIGNAL(resetTouchpad(bool)), this, SIGNAL(resetTouchpad(bool)));
    connect(touchpad_widget, SIGNAL(resetHorizontalScrolling(bool)), this, SIGNAL(resetHorizontalScrolling(bool)));
    connect(touchpad_widget, SIGNAL(setScrollbarOverlayOrLegacyMode(bool)), this, SIGNAL(setScrollbarOverlayOrLegacyMode(bool)));
    connect(touchpad_widget, SIGNAL(setMateTouchscrollingMode(int)), this, SIGNAL(setMateTouchscrollingMode(int)));
    connect(touchpad_widget, SIGNAL(setUnityTouchscrollingMode(int)), this, SIGNAL(setUnityTouchscrollingMode(int)));


    //ac and battery
    connect(conserve_widget, SIGNAL(requestPowerAndBatteryData()), this, SIGNAL(requestPowerAndBatteryData()));
    connect(this, SIGNAL(sendIdleAndGammaData(double,QStringList,int,QString,QString,QString,QStringList)), conserve_widget, SLOT(onSendIdleAndGammaData(double,QStringList,int,QString,QString,QString,QStringList)));
    connect(this, SIGNAL(sendLockAndSleepData(bool,QString,QStringList,QString,QString,QString,QString,QStringList,QString)), conserve_widget, SLOT(onSendLockAndSleepData(bool,QString,QStringList,QString,QString,QString,QString,QStringList,QString)));

    connect(conserve_widget, SIGNAL(resetScreenGammaValue(double)), this, SIGNAL(resetScreenGammaValue(double)));
    connect(conserve_widget, SIGNAL(resetBrightnessValue(int)), this, SIGNAL(resetBrightnessValue(int)));
    connect(conserve_widget, SIGNAL(resetIdleDelay(int,int)), this, SIGNAL(resetIdleDelay(int,int)));
    connect(conserve_widget, SIGNAL(resetLockEnabled(bool)), this, SIGNAL(resetLockEnabled(bool)));
    connect(conserve_widget, SIGNAL(resetLockDelay(int,int)), this, SIGNAL(resetLockDelay(int,int)));
    connect(conserve_widget, SIGNAL(setCurrentCriticalLow(QString)), this, SIGNAL(setCurrentCriticalLow(QString)));
    connect(conserve_widget, SIGNAL(setCurrentLidBattery(QString)), this, SIGNAL(setCurrentLidBattery(QString)));
    connect(conserve_widget, SIGNAL(setCurrentLidAC(QString)), this, SIGNAL(setCurrentLidAC(QString)));
    connect(conserve_widget, SIGNAL(resetSleepTimeoutBattery(int,int)), this, SIGNAL(resetSleepTimeoutBattery(int,int)));
    connect(conserve_widget, SIGNAL(resetSleepTimeoutAC(int,int)), this, SIGNAL(resetSleepTimeoutAC(int,int)));
    connect(conserve_widget, SIGNAL(resetSleepTimeoutDisplayBattery(int,int)), this, SIGNAL(resetSleepTimeoutDisplayBattery(int,int)));
    connect(conserve_widget, SIGNAL(resetSleepTimeoutDisplayAC(int,int)), this, SIGNAL(resetSleepTimeoutDisplayAC(int,int)));
    connect(conserve_widget, SIGNAL(setCurrentCpuMode(QString)), this, SIGNAL(setCurrentCpuMode(QString)));

    //file manager
    connect(nautilus_widget, SIGNAL(requestFileManagerData()), this, SIGNAL(requestFileManagerData()));
    connect(this, SIGNAL(sendFileManagerData(bool,bool,bool,bool,int,int,int)), nautilus_widget, SLOT(onSendFileManagerData(bool,bool,bool,bool,int,int,int)));

    connect(nautilus_widget, SIGNAL(resetLocationReplacePathbar(bool)), this, SIGNAL(resetLocationReplacePathbar(bool)));
    connect(nautilus_widget, SIGNAL(resetAutoMountMedia(bool)), this, SIGNAL(resetAutoMountMedia(bool)));
    connect(nautilus_widget, SIGNAL(resetAutoOpenFolder(bool)), this, SIGNAL(resetAutoOpenFolder(bool)));
    connect(nautilus_widget, SIGNAL(resetPromptAutorunPrograms(bool)), this, SIGNAL(resetPromptAutorunPrograms(bool)));
    connect(nautilus_widget, SIGNAL(resetThumbnailIconSize(int)), this, SIGNAL(resetThumbnailIconSize(int)));
    connect(nautilus_widget, SIGNAL(resetThumbnailCacheTime(int)), this, SIGNAL(resetThumbnailCacheTime(int)));
    connect(nautilus_widget, SIGNAL(resetThumbnailCacheSize(int)), this, SIGNAL(resetThumbnailCacheSize(int)));
}

void SettingWidget::on_string_value_notify(QString key, QString value)
{
    if (key == "launcher-position" && launcher_widget) {
        launcher_widget->launcherwidget_notify_string(key, value);
    }
}

void SettingWidget::on_bool_value_notify(QString key, bool value)
{
    if (key == "auto-hide-top" || key == "auto-hide-bottom") {
        if (launcher_widget)
            launcher_widget->launcherwidget_notify_bool(key, value);
    }
}

void SettingWidget::on_int_value_notify(QString key, int value)
{
    if (key == "icon-size" || key == "launcher-hide-mode" || key == "backlight-mode" || key == "size-top" || key == "size-bottom") {
        if (launcher_widget) {
            launcher_widget->launcherwidget_notify_int(key, value);
        }
    }
}

void SettingWidget::on_double_value_notify(QString key, double value)
{
    if (key == "launcher-opacity" && launcher_widget) {
        launcher_widget->launcherwidget_notify_double(key, value);
    }
}

void SettingWidget::resetSkin(QString skin)
{
//    if(font_widget != NULL)
//        font_widget->resetCurrentSkin(skin);
}

/*void SettingWidget::startMonitorCheck() {
    if (this->qtui)
    {
        delete this->qtui;
        this->qtui = NULL;
    }
    this->qtui = new QUIBO();
}*/

void SettingWidget::displaySettingHomePage() {
    m_settingListView->setVisible(true);
    stacked_widget->setVisible(false);
}
