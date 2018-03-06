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

#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QDBusInterface>

#include "../qdbusservice/systemdbus/data/systemdbusproxy.h"
#include "../qdbusservice/systemdbus/customdata.h"
#include "../qdbusservice/systemdbus/customdatalist.h"

class QTimer;
class SessionDispatcher;
class SystemDispatcher;

class DataWorker : public QObject
{
    Q_OBJECT
public:
    explicit DataWorker(QString desk, QObject *parent = 0);
    ~DataWorker();
    void initDataWorker();

    bool deleteAppointedFile(QString filename);
    bool copyAppointedFile(QString filename);
    bool isBatteryExist() { return m_existBattery; }
    bool isSensorExist() { return m_existSensor; }

    const QStringList cpuModeList() const;
    const QString cpuCurrentMode() const;

public slots:
    void doWork();
    void updateSensorValue();

    //scan on homepage
    void onStartOneKeyScan(const QStringList &categorys);
    //clean on homepage
    void onStartOneKeyClean();

    //scan
    void onStartScanSystem(QMap<QString, QVariant> itemsMap);
    //clean
    void onStartCleanSystem(QMap<QString, QVariant> itemsMap);

    //system info
    void onUpdateSystemRunnedTime();
    void onRequestRefreshSystemInfo();

    //desktop info
    void onRequestDesktopInfo();

    //cpu info
    void onRequestCpuInfo();

    //memory info
    void onRequestMemoryInfo();

    //board info
    void onRequestBoardInfo();

    //hd info
    void onRequestHDInfo();

    //nic info
    void onRequestNicInfo();

    //monitor info
    void onRequestMonitorInfo();

    //audio info
    void onRequestAudioInfo();

    //battery info
    void onRequestBatteryInfo();

    //sensor info
    void onRequestSensorInfo();

    //driver info


    //theme
    void onRequestThemeData();
    void onChangeSystemTheme(const QString &theme);

    //icon
    void onRequestIconData();
    void onResetIconTheme(const QString &theme);
    void onDisplayComputerIcon(bool b);
    void onDisplayFolderIcon(bool b);
    void onDisplayNetworkIcon(bool b);
    void onDisplayRecycleBinIcon(bool b);
    void onDisplayDiskIcon(bool b);

    //mouse
    void onRequestMouseData();
    void onResetMouseCursorTheme(const QString &theme);
    void onResetMouseCursorSize(int cursorSize);

    //voice
    void onRequestSoundData();
    void onResetVoiceTheme(QString selectTheme);
    void onResetLoginTipVoice(bool b);
    void onResetEventVoice(bool b);
    void onResetInputFeedbackVoice(bool b);

    //panel
    void onRequestMateOrUnityPanelData(bool isMate);
    void onResetPanelTransparencyValue(double value);
    void onResetDateFormat(const QString &selected);
    void onResetShowBatteryIcon(const QString &selected);
    void onResetDashBlurExperimental(int value);
    void onResetDisplaySeconds(bool b);
    void onResetDisplayWeek(bool b);
    void onResetDisplayDate(bool b);
    void onResetDisplayBatteryPercentage(bool b);
    void onResetDisplayBatteryTime(bool b);
    void onResetShowApplications(bool b);
    void onResetShowDesktop(bool b);
    void onResetShowIcon(bool b);
    void onResetShowPlaces(bool b);


    //launcher menu
    void onRequestMateOrUnityMenuData(bool isMate);
    void onResetIconSizeValue(int value);
    void onResetTransparencyValue(int value);
    void onResetIconColouring(int value);
    void onResetAutoHide(bool b);
    void onResetDisplayDesktopIcon(bool b);
    void onResetTopIconSizeValue(int value);
    void onResetBottomIconSizeValue(int value);
    void onResetTopAutoHide(bool b);
    void onResetBottomAutoHide(bool b);
    void onResetLauncherPosition(const QString &position);

    //window
    void onRequesetWindowButtonAlign();
    void onRequesetMenusHaveIcons();
    void onRequesetWindowTitileTags();
    void onResetMenusHaveIcon(bool b);
    void onResetTitlebarWheel(const QString &selected);
    void onResetTitlebarDoubleClick(const QString &selected);
    void onResetMouseMiddleClick(const QString &selected);
    void onResetMouseRightClick(const QString &selected);
    void onResetWindowButtonLeftOrRightAlign(bool isLeft);

    //font
    void onRequestFontData();
    void onSetDefaultFontByName(const QString &cur_font);
    void onSetDesktopFontByName(const QString &cur_font);
    void onSetMonospaceFontByName(const QString &cur_font);
    void onSetDocumentFontByName(const QString &cur_font);
    void onSetTitlebarFontByName(const QString &cur_font);
    void onResetFontZoomScalingValue(double value);
    void onResetFontHinting(const QString &selected);
    void onResetFontAntialiasing(const QString &selected);
    void onRestoreDefaultFont(bool isMate);
    void onRestoreDesktopDefaultFont(bool isMate);
    void onRestoreMonospaceDefaultFont(bool isMate);
    void onRestoreDocumentDefaultFont(bool isMate);
    void onRestoreTitlebarDefaultFont(bool isMate);

    //touchpad
    void onRequestMateOrUnityTouchpadData(bool isMate);
    void onResetTouchpad(bool b);
    void onResetHorizontalScrolling(bool b);
    void onSetScrollbarOverlayOrLegacyMode(bool b);
    void onSetMateTouchscrollingMode(int flag);
    void onSetUnityTouchscrollingMode(int flag);

    //ac and battery
    void onRequestPowerAndBatteryData();
    void onResetScreenGammaValue(double value);
    void onResetBrightnessValue(int value);
    void onResetIdleDelay(int index, int curValue);
    void onResetLockEnabled(bool b);
    void onResetLockDelay(int index, int curValue);
    void onSetCurrentCriticalLow(const QString &value);
    void onSetCurrentLidBattery(const QString &value);
    void onSetCurrentLidAC(const QString &value);
    void onResetSleepTimeoutBattery(int index, int value);
    void onResetSleepTimeoutAC(int index, int value);
    void onResetSleepTimeoutDisplayBattery(int index, int value);
    void onResetSleepTimeoutDisplayAC(int index, int value);
    void onSetCurrentCpuMode(const QString &mode);

    //file manager
    void onRequestFileManagerData();
    void onResetLocationReplacePathbar(bool b);
    void onResetAutoMountMedia(bool b);
    void onResetAutoOpenFolder(bool b);
    void onResetPromptAutorunPrograms(bool b);
    void onResetThumbnailIconSize(int value);
    void onResetThumbnailCacheTime(int value);
    void onResetThumbnailCacheSize(int value);


signals:
    void dataLoadFinished();

    void string_value_notify(QString key, QString value);
    void bool_value_notify(QString key, bool value);
    void int_value_notify(QString key, int value);
    void double_value_notify(QString key, double value);


    void tellCleanerDetailStatus(const QString &status);
    void tellCleanerDetailData(const QStringList &data);
    void tellCleanerDetailError(const QString &status);

    void sendCleanOverSignal();
    void policykitCleanSignal(bool status);
    void tellCleanerMainData(const QStringList &data);
    void tellCleanerMainStatus(const QString &status, const QString &domain);
    void sendCleanErrorSignal(const QString &status);

    void isScanning(QString msg);
    void finishScanWork(QString msg);
    void tellScanResult(QString flag, QString msg);
    void finishCleanWorkMain(QString msg);
    void finishCleanWorkMainError(QString msg);
    void quickCleanProcess(QString type, QString status);




    //system info
    void sendSystemRunnedTime(int time_value);
    void sendSystemInfo(QMap<QString, QVariant> tmpMap);

    //desktop info
    void sendDesktopInfo(QMap<QString, QVariant> tmpMap);

    //cpu info
    void sendCpuInfo(QMap<QString, QVariant> tmpMap);

    //memory info
    void sendMemoryInfo(QMap<QString, QVariant> tmpMap);

    //board info
    void sendBoardInfo(QMap<QString, QVariant> tmpMap);

    //hd info
    void sendHDInfo(QMap<QString, QVariant> tmpMap);

    //nic info
    void sendNicInfo(QMap<QString, QVariant> tmpMap);

    //monitor info
    void sendMonitorInfo(QMap<QString, QVariant> tmpMap);

    //audio info
    void sendAudioInfo(QMap<QString, QVariant> tmpMap);

    //battery info
    void sendBatteryInfo(QMap<QString, QVariant> tmpMap);

    //sensor info
    void sendSensorInfo(QMap<QString, QVariant> tmpMap);

    //driver info







    //theme
    void sendThemeList(const QString &currentTheme, const QStringList &themeList);

    //icon
    void sendIconThemeList(const QString &currentTheme, const QStringList &themeList);
    void sendDisplayIconValue(bool computer, bool folder, bool network, bool recycle, bool disk);

    //mouse
    void sendMouseThemeAndCusorSize(const QString &currentTheme, const QStringList &themeList, int cusorSize);

    //voice
    void sendSoundList(const QString &currentSound, const QStringList &soundList);
    void sendEnableSoundValue(bool login_music, bool sound_event, bool input_sound);

    //panel
    void sendMatePanelValue(bool app, bool desktop, bool icon, bool places);
    void sendUnityBlurAndTransparencyValue(int blur, double transparent);
    void sendUnityTimeValue(const QString &time_format, const QStringList &timelist, bool showSecond, bool showWeek, bool showDate);
    void sendUnityPanelPowerValue(const QString &cur_power, const QStringList &powerlist, bool showPower, bool showBatteryTime);


    //launcher menu
    void sendMatePanelIconValue(int topIconSize, int bottomIconSize, bool topIconHide, bool bottomIconHide);
    void sendUnityIconValue(int iconSize, bool iconHide, bool desktopIconShowed, double launcherTransparency, int iconColourIndex, const QStringList &colourlist);
    void sendUnityLauncherPosition(const QString &current_position, const QStringList &positionlist);


    //window
    void sendWindowButtonAlign(const QString &current_value);
    void sendMenusHaveIcons(bool menuHaveIcons);
    void sendWindowTitileTags(const QString &current_wheel_type, const QStringList &wheellist, const QStringList &titlebarOptions, const QString &current_double_type, const QString &current_middle_type, const QString &current_right_type);

    //font
    void sendFontValue(const QString &curFont);
    void sendDesktopFontValue(const QString &curFont);
    void sendMonospaceFontValue(const QString &curFont);
    void sendDocumentFontValue(const QString &curFont);
    void sendTitlebarFontValue(const QString &curFont);
    void sendFontSmoothAndAntialiasingValue(double fontZoom, const QString &current_smooth, const QStringList &smoothlist, const QString &current_antialiasing, const QStringList &antialiasinglist);

    //touchpad
    void sendTouchPadValue(bool touchpadEnable, bool touchscrollingHorizontal, const QString &mode_value, int scroll_int_value, const QString &scroll_string_value);

    //ac and battery
    void sendIdleAndGammaData(double gamma, const QStringList &aclist, int brightnessValue, const QString &sleepTimeoutDisplayBattery, const QString &sleepTimeoutFisplayAC, const QString &idle_delay, const QStringList &idledelaylist);
    void sendLockAndSleepData(bool lockEnabled, const QString &lock_delay, const QStringList &lockdelaylist, const QString &critical_low, const QString &laptop_battery, const QString &laptop_ac, const QString &sleepTimeoutBattery, const QStringList &batterylist, const QString &sleepTimeoutAc);

    //file manager
    void sendFileManagerData(bool locationReplacePathbar, bool autoMountMedia, bool autoOpenFolder, bool promptAutorunPrograms, int thumbnailIconSize, int thumbnailCacheTime, int thumbnailCacheSize);

private:
    QDBusInterface *m_powerIface = nullptr;
    SessionDispatcher *m_sessionInterface = nullptr;
    SystemDispatcher *m_systemInterface = nullptr;
    SystemDbusProxy *m_qSystemDbus = nullptr;
    QString desktop;

    bool m_existBattery;
    bool m_existSensor;
    QStringList m_cpulist;
    QString m_currentCpuMode;

    QTimer *m_sensorTimer = nullptr;
};

