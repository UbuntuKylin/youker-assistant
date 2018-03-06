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

#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QPen>
#include <QHBoxLayout>
#include <QEvent>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "../setting/themewidget.h"
#include "../setting/iconwidget.h"
#include "../setting/mousewidget.h"
#include "../setting/soundwidget.h"
//#include "../setting/animationwidget.h"
#include "../setting/menuwidget.h"
#include "../setting/panelwidget.h"
#include "../setting/windowwidget.h"
#include "../setting/fontwidget.h"
#include "../setting/touchpadwidget.h"
//#include "../setting/deadpixelwidget.h"
#include "../setting/energywidget.h"
#include "../setting/filemanagerwidget.h"
#include "../component/quibo.h"

//#include "../component/settingaction.h"

class MainWindow;
class SettingListView;
class SettingModel;

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(/*QStringList cpulist, QString cpu, */QString cur_desktop, /*bool has_battery = false, */QWidget *parent = 0);
    ~SettingWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initSettingsUI(QStringList cpulist, QString cpu, bool has_battery = false /*QString skin*/);
    void resetSkin(QString skin);

signals:
    void changeActionPage(const QString &moduleName);//void changeActionPage(SettingAction::SettingModuleID moduleId);

    void string_value_notify(QString key, QString value);
    void bool_value_notify(QString key, bool value);
    void int_value_notify(QString key, int value);
    void double_value_notify(QString key, double value);

    //theme
    void changeSystemTheme(const QString &name);
    void requestThemeData();
    void sendThemeList(const QString &currentTheme, const QStringList &themeList);

    //icon
    void requestIconData();
    void resetIconTheme(const QString &name);
    void sendIconThemeList(const QString &currentTheme, const QStringList &themeList);
    void sendDisplayIconValue(bool computer, bool folder, bool network, bool recycle, bool disk);
    void displayComputerIcon(bool b);
    void displayFolderIcon(bool b);
    void displayNetworkIcon(bool b);
    void displayRecycleBinIcon(bool b);
    void displayDiskIcon(bool b);

    //mouse
    void requestMouseData();
    void sendMouseThemeAndCusorSize(const QString &currentTheme, const QStringList &themeList, int cusorSize);
    void resetMouseCursorTheme(const QString &name);
    void resetMouseCursorSize(int cursorSize);

    //voice
    void requestSoundData();
    void sendSoundList(const QString &currentSound, const QStringList &soundList);
    void sendEnableSoundValue(bool login_music, bool sound_event, bool input_sound);
    void resetVoiceTheme(QString selectTheme);
    void resetLoginTipVoice(bool b);
    void resetEventVoice(bool b);
    void resetInputFeedbackVoice(bool b);

    //panel
    void requestMateOrUnityPanelData(bool isMate);
    void sendMatePanelValue(bool app, bool desktop, bool icon, bool places);
    void sendUnityBlurAndTransparencyValue(int blur, double transparent);
    void sendUnityTimeValue(const QString &time_format, const QStringList &timelist, bool showSecond, bool showWeek, bool showDate);
    void sendUnityPanelPowerValue(const QString &cur_power, const QStringList &powerlist, bool showPower, bool showBatteryTime);
    void resetPanelTransparencyValue(double value);
    void resetDateFormat(const QString &selected);
    void resetShowBatteryIcon(const QString &selected);
    void resetDashBlurExperimental(int value);
    void resetDisplaySeconds(bool b);
    void resetDisplayWeek(bool b);
    void resetDisplayDate(bool b);
    void resetDisplayBatteryPercentage(bool b);
    void resetDisplayBatteryTime(bool b);
    void resetShowApplications(bool b);
    void resetShowDesktop(bool b);
    void resetShowIcon(bool b);
    void resetShowPlaces(bool b);

    //launcher menu
    void requestMateOrUnityMenuData(bool isMate);
    void sendMatePanelIconValue(int topIconSize, int bottomIconSize, bool topIconHide, bool bottomIconHide);
    void sendUnityIconValue(int iconSize, bool iconHide, bool desktopIconShowed, double launcherTransparency, int iconColourIndex, const QStringList &colourlist);
    void sendUnityLauncherPosition(const QString &current_position, const QStringList &positionlist);
    void resetIconSizeValue(int value);
    void resetTransparencyValue(int value);
    void resetIconColouring(int value);
    void resetAutoHide(bool b);
    void resetDisplayDesktopIcon(bool b);
    void resetTopIconSizeValue(int value);
    void resetBottomIconSizeValue(int value);
    void resetTopAutoHide(bool b);
    void resetBottomAutoHide(bool b);
    void resetLauncherPosition(const QString &position);

    //window
    void requesetWindowButtonAlign();
    void requesetMenusHaveIcons();
    void requesetWindowTitileTags();
    void sendWindowButtonAlign(const QString &current_value);
    void sendMenusHaveIcons(bool menuHaveIcons);
    void sendWindowTitileTags(const QString &current_wheel_type, const QStringList &wheellist, const QStringList &titlebarOptions, const QString &current_double_type, const QString &current_middle_type, const QString &current_right_type);
    void resetMenusHaveIcon(bool);
    void resetTitlebarWheel(const QString &selected);
    void resetTitlebarDoubleClick(const QString &selected);
    void resetMouseMiddleClick(const QString &selected);
    void resetMouseRightClick(const QString &selected);
    void resetWindowButtonLeftOrRightAlign(bool isLeft);


    //font
    void requestFontData();
    void sendFontValue(const QString &curFont);
    void sendDesktopFontValue(const QString &curFont);
    void sendMonospaceFontValue(const QString &curFont);
    void sendDocumentFontValue(const QString &curFont);
    void sendTitlebarFontValue(const QString &curFont);
    void sendFontSmoothAndAntialiasingValue(double fontZoom, const QString &current_smooth, const QStringList &smoothlist, const QString &current_antialiasing, const QStringList &antialiasinglist);
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


    //touchpad
    void requestMateOrUnityTouchpadData(bool isMate);
    void sendTouchPadValue(bool touchpadEnable, bool touchscrollingHorizontal, const QString &mode_value, int scroll_int_value, const QString &scroll_string_value);
    void resetTouchpad(bool b);
    void resetHorizontalScrolling(bool b);
    void setScrollbarOverlayOrLegacyMode(bool b);
    void setMateTouchscrollingMode(int flag);
    void setUnityTouchscrollingMode(int flag);

    //ac and battery
    void requestPowerAndBatteryData();
    void sendIdleAndGammaData(double gamma, const QStringList &aclist, int brightnessValue, const QString &sleepTimeoutDisplayBattery, const QString &sleepTimeoutFisplayAC, const QString &idle_delay, const QStringList &idledelaylist);
    void sendLockAndSleepData(bool lockEnabled, const QString &lock_delay, const QStringList &lockdelaylist, const QString &critical_low, const QString &laptop_battery, const QString &laptop_ac, const QString &sleepTimeoutBattery, const QStringList &batterylist, const QString &sleepTimeoutAc);
    void resetScreenGammaValue(double value);
    void resetBrightnessValue(int value);
    void resetIdleDelay(int index, int curValue);
    void resetLockEnabled(bool b);
    void resetLockDelay(int index, int curValue);
    void setCurrentCriticalLow(const QString &value);
    void setCurrentLidBattery(const QString &value);
    void setCurrentLidAC(const QString &value);
    void resetSleepTimeoutBattery(int index, int value);
    void resetSleepTimeoutAC(int index, int value);
    void resetSleepTimeoutDisplayBattery(int index, int value);
    void resetSleepTimeoutDisplayAC(int index, int value);
    void setCurrentCpuMode(const QString &mode);

    //file manager
    void requestFileManagerData();
    void sendFileManagerData(bool locationReplacePathbar, bool autoMountMedia, bool autoOpenFolder, bool promptAutorunPrograms, int thumbnailIconSize, int thumbnailCacheTime, int thumbnailCacheSize);
    void resetLocationReplacePathbar(bool b);
    void resetAutoMountMedia(bool b);
    void resetAutoOpenFolder(bool b);
    void resetPromptAutorunPrograms(bool b);
    void resetThumbnailIconSize(int value);
    void resetThumbnailCacheTime(int value);
    void resetThumbnailCacheSize(int value);

public slots:
    void displaySettingHomePage();
    //void startMonitorCheck();

    void onSettingItemClicked(const QModelIndex &index);
    void onSettingItemEntered(const QModelIndex &index);


    void on_string_value_notify(QString key, QString value);
    void on_bool_value_notify(QString key, bool value);
    void on_int_value_notify(QString key, int value);
    void on_double_value_notify(QString key, double value);

private:
    SettingListView *m_settingListView;
    SettingModel *m_settingModel;
    int itemSpace;
    MainWindow *p_mainwindow;
    QString desktop;
    bool battery;
    QStringList m_cpuList;
    QString m_currentCpu;

    QStackedWidget *stacked_widget;
    ThemeWidget *theme_widget;
    IconWidget *icon_widget;
    MouseWidget *mouse_widget;
    SoundWidget *sound_widget;
//    AnimationWidget *animation_widget;
    MenuWidget *launcher_widget;
    PanelWidget *panel_widget;
    WindowWidget *window_widget;
    FontWidget *font_widget;
    TouchpadWidget *touchpad_widget;
//    DeadpixelWidget *deadpixel_widget;
    EnergyWidget *conserve_widget;
    FileManagerWidget *nautilus_widget;
    //QUIBO *qtui;
};

#endif // SETTINGWIDGET_H
