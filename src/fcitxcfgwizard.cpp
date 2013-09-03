/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  lenky gao    lenky0401@gmail.com
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

#include <QObject>
#include <QString>
#include <QFontDialog>

#include "fcitxcfgwizard.h"
#include "fcitx-qt/fcitxqtformattedpreedit.h"
#include "fcitx/module/ipc/ipc.h"
#include "fcitx-config/fcitx-config.h"
#include "fcitx-utils/utils.h"
#include "fcitxwarndialog.h"

#include <QDeclarativeView>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeItem>
#include <QMetaObject>
#include <QDeclarativeContext>
#include <QDesktopWidget>
#include <QGraphicsObject>
#include <QDialog>
#include <QProcess>
#include "authdialog.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QtDBus>

#include <string.h>
#include "qtkeytrans.h"

FcitxCfgWizard::FcitxCfgWizard(QObject *parent) :
    QObject(parent)
{
    FcitxQtInputMethodItem::registerMetaType();

    m_separator = "<5|13)";
    m_string = (char *)malloc(32);
    m_font = (char *)malloc(32);
    m_skin_type = (char *)malloc(32);

    m_connection = new FcitxQtConnection(this);
    m_connection->setAutoReconnect(true);
    m_connection->startConnection();

    fcitxWarnSig = new FcitxWarnDialog();

//    viewer_float = new QDeclarativeView;
//    viewer_float->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    viewer_float->setSource(QUrl::fromLocalFile("floatmain.qml"));
////    viewer_float->setSource(QUrl("../qml/floatmain.qml"));
//    viewer_float->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    QObject *rootObject = dynamic_cast<QObject*>(viewer_float->rootObject());
//    QObject::connect(tray, SIGNAL(showFloat()), rootObject, SLOT(show_float_frame()));
//    viewer_float->rootContext()->setContextProperty("fmainwindow", viewer_float);
//    viewer_float->setStyleSheet("background:transparent");
//    viewer_float->setAttribute(Qt::WA_TranslucentBackground);
//    viewer_float->setWindowFlags(Qt::FramelessWindowHint);
//    QDesktopWidget* fdesktop = QApplication::desktop();
//    viewer_float->move(fdesktop->width(), 0);
//    viewer_float->show();

    //connect FcitxConfigtool.qml
//    view = new QDeclarativeView;
//    view->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    view->setSource(QUrl::fromLocalFile("FcitxConfigtool.qml"));
////    view->setSource(QUrl("../qml/func/settings/FcitxConfigtool.qml"));
//    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    QObject *rootObject = dynamic_cast<QObject*>(view->rootObject());
//    QObject::connect(fcitxWarnSig, SIGNAL(fcitxWarntest()), rootObject, SLOT(refreshFcitxtool()));


//    connect(fcitxWarnSig, SIGNAL(fcitxWarntest()),SLOT(handler_okBtn_fcitx_warn()));//测试信号
//    connect(m_connection, SIGNAL(connected()),SLOT(connected()));
}



FcitxCfgWizard::~FcitxCfgWizard()
{
    free(m_string);
    free(m_font);
    free(m_skin_type);
    m_connection->endConnection();
    delete m_connection;
    if (m_improxy)
        delete m_improxy;
}

bool FcitxCfgWizard::connected()
{
    qDebug() << "connected";
    if (!m_connection->isConnected())
        return false;

    if (m_improxy) {
        delete m_improxy;
        m_improxy = 0;
    }

    m_improxy = new FcitxQtInputMethodProxy(m_connection->serviceName(),
        QLatin1String(FCITX_IM_DBUS_PATH), *m_connection->connection(), this);

    if (m_improxy == NULL || !m_improxy->isValid())
        return false;

    return true;
}

bool FcitxCfgWizard::is_connected_ok()
{
    return !((m_improxy == NULL || !m_improxy->isValid()) && !connected());
}

QStringList FcitxCfgWizard::get_im_list()
{
    QString tmp;
    QStringList ret_value;
    FcitxQtInputMethodItemList im_item_list;
    FcitxQtInputMethodItemList::iterator im_iter;

    if (!is_connected_ok())
        return ret_value;

    im_item_list = m_improxy->iMList();

    for (im_iter = im_item_list.begin(); im_iter != im_item_list.end(); ++ im_iter) {
        tmp = im_iter->name() + m_separator +  im_iter->uniqueName() + m_separator
            +  im_iter->langCode();
        if (im_iter->enabled())
            tmp += m_separator + "true";
        else
            tmp += m_separator + "false";

        ret_value << tmp;
        //qDebug() << tmp;
    }

    //Debug
    //this->set_im_list(ret_value);

    m_im_list = ret_value;

    return ret_value;
}

bool FcitxCfgWizard::set_im_list(QStringList im_list, bool real_save)
{
    QString tmp;
    QStringList tmp_list;
    QList<QString>::Iterator iter;
    FcitxQtInputMethodItemList im_item_list;
    FcitxQtInputMethodItem im_item;

    m_im_list = im_list;

    if (!real_save)
        return true;

    if (!is_connected_ok())
        return false;

    for (iter = m_im_list.begin(); iter != m_im_list.end(); ++ iter) {
        tmp = *iter;
        tmp_list = tmp.split(m_separator);

        im_item.setName(tmp_list.at(0));
        im_item.setUniqueName(tmp_list.at(1));
        im_item.setLangCode(tmp_list.at(2));
        if (tmp_list.at(3) == "true")
            im_item.setEnabled(true);
        else
            im_item.setEnabled(false);

        im_item_list.append(im_item);
    }

    m_improxy->setIMList(im_item_list);

    return true;
}

/**
 * @brief FcitxCfgWizard::get_fcitx_cfg_value：获取小企鹅输入配置值
 * @param cd_path_prefix：配置描述文件路径前缀
 * @param cd_file_name：配置描述文件名
 * @param c_path_prefix：配置文件路径前缀
 * @param c_file_name：配置文件名
 * @param groupName：具体配置项目所在组
 * @param optionName：具体配置项目名
 * @param ret_value：取得的配置值
 * @return：返回为true表示获取成功，反之获取失败
 */
bool FcitxCfgWizard::get_fcitx_cfg_value(char *cd_path_prefix, char *cd_file_name,
    char *c_path_prefix, char *c_file_name, char *groupName, const char *optionName,
    void *ret_value)
{
    FILE *c_fp;
    FILE *cd_fp;
    FcitxConfigFile *cfg;
    FcitxConfigFileDesc *cfg_desc;
    FcitxGenericConfig gc;

    if ((cd_fp = FcitxXDGGetFileWithPrefix(cd_path_prefix, cd_file_name, "r", NULL))
        == NULL)
    {
        qDebug() << QString("Open file(%0/%1) error.").arg(cd_path_prefix)
            .arg(cd_file_name);
        goto err;
    }

    if ((cfg_desc = FcitxConfigParseConfigFileDescFp(cd_fp)) == NULL) {
        qDebug() << "FcitxConfigParseConfigFileDescFp error.";
        goto err1;
    }

    if ((c_fp = FcitxXDGGetFileWithPrefix(c_path_prefix, c_file_name, "r", NULL))
        == NULL)
    {
        qDebug() << QString("Open file(%0/%1) error.").arg(c_path_prefix)
            .arg(c_file_name);
        goto err2;
    }

    if ((cfg = FcitxConfigParseConfigFileFp(c_fp, cfg_desc)) == NULL) {
        qDebug() << "FcitxConfigParseConfigFileFp error.";
        goto err3;
    }

    gc.configFile = cfg;
    FcitxConfigBindValue(cfg, groupName, optionName, ret_value, NULL, NULL);
    //把配置值绑定上来，即读取
    FcitxConfigBindSync(&gc);

    FcitxConfigFreeConfigFile(cfg);
    fclose(c_fp);
    FcitxConfigFreeConfigFileDesc(cfg_desc);
    fclose(cd_fp);

    return true;

err3:
    fclose(c_fp);
err2:
    FcitxConfigFreeConfigFileDesc(cfg_desc);
err1:
    fclose(cd_fp);
err:
    return false;
}

/**
 * @brief FcitxCfgWizard::set_fcitx_cfg_value：设置小企鹅输入配置值
 * @param cd_path_prefix：配置描述文件路径前缀
 * @param cd_file_name：配置描述文件名
 * @param c_path_prefix：配置文件路径前缀
 * @param c_file_name：配置文件名
 * @param groupName：具体配置项目所在组
 * @param optionName：具体配置项目名
 * @param ret_value：设置的配置值
 * @return：返回为true表示设置成功，反之获取失败
 */
bool FcitxCfgWizard::set_fcitx_cfg_value(char *cd_path_prefix, char *cd_file_name,
    char *c_path_prefix, char *c_file_name, char *groupName, const char *optionName,
    void *set_value)
{
    FILE *c_fp;
    FILE *cd_fp;
    FcitxConfigFile *cfg;
    FcitxConfigFileDesc *cfg_desc;
    FcitxGenericConfig gc;

    if ((cd_fp = FcitxXDGGetFileWithPrefix(cd_path_prefix, cd_file_name, "r", NULL))
        == NULL)
    {
        qDebug() << QString("Open file(%0/%1) error.").arg(cd_path_prefix)
            .arg(cd_file_name);
        goto err;
    }

    if ((cfg_desc = FcitxConfigParseConfigFileDescFp(cd_fp)) == NULL) {
        qDebug() << "FcitxConfigParseConfigFileDescFp error.";
        goto err1;
    }

    if ((c_fp = FcitxXDGGetFileWithPrefix(c_path_prefix, c_file_name, "r+", NULL))
        == NULL)
    {
        qDebug() << QString("Open file(%0/%1) error.").arg(c_path_prefix)
            .arg(c_file_name);
        goto err2;
    }

    if ((cfg = FcitxConfigParseConfigFileFp(c_fp, cfg_desc)) == NULL) {
        qDebug() << "FcitxConfigParseConfigFileFp error.";
        goto err3;
    }

    gc.configFile = cfg;
    FcitxConfigBindValue(cfg, groupName, optionName, set_value, NULL, NULL);

    //把配置值绑定下去，即写入
    rewind(c_fp);
    if (FcitxConfigSaveConfigFileFp(c_fp, &gc, cfg_desc) == false) {
        qDebug() << "FcitxConfigSaveConfigFileFp error.";
        //Go Through
    }

    FcitxConfigFreeConfigFile(cfg);
    fclose(c_fp);
    FcitxConfigFreeConfigFileDesc(cfg_desc);
    fclose(cd_fp);

    return true;

err3:
    fclose(c_fp);
err2:
    FcitxConfigFreeConfigFileDesc(cfg_desc);
err1:
    fclose(cd_fp);
err:
    return false;
}

void FcitxCfgWizard::save_q_string_2_m_string(QString q_string, char **m_buf)
{
    int len;
    std::string tmp_str;
    char *m_buf_tmp;

    tmp_str = q_string.toStdString();
    len = tmp_str.length() + 1;

    if ((m_buf_tmp = (char *)malloc(len)) == NULL)
        return;

    memset(m_buf_tmp, 0, len);
    memcpy(m_buf_tmp, tmp_str.c_str(), len);

    if (*m_buf)
        free(*m_buf);

    *m_buf = m_buf_tmp;
}

QString FcitxCfgWizard::get_font()
{
    if (get_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
        "fcitx-classic-ui.config", "ClassicUI", "Font", &m_font))
    {
        qDebug() << "lenky get_font():" << m_font;
        return m_font;
    }

    return "";
}

void FcitxCfgWizard::set_font(QString font, bool real_save)
{
    save_q_string_2_m_string(font, &m_font);

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
            "fcitx-classic-ui.config", "ClassicUI", "Font", &m_font);
    }
}

int FcitxCfgWizard::get_candidate_word_number()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Output",
        "CandidateWordNumber", &m_candidate_word_number))
    {
        qDebug() << "lenky get_candidate_word_number():" << m_candidate_word_number;
        return m_candidate_word_number;
    }

    return 5;
}

void FcitxCfgWizard::set_candidate_word_number(int num, bool real_save)
{
    m_candidate_word_number = num;

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Output",
            "CandidateWordNumber", &m_candidate_word_number);
    }
}

int FcitxCfgWizard::get_font_size()
{
    if (get_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
        "fcitx-classic-ui.config", "ClassicUI", "FontSize", &m_font_size))
    {
        qDebug() << "lenky get_font_size():" << m_font_size;
        return m_font_size;
    }

    return 12;
}

void FcitxCfgWizard::set_font_size(int size, bool real_save)
{
    m_font_size = size;

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
            "fcitx-classic-ui.config", "ClassicUI", "FontSize", &m_font_size);
    }
}

bool FcitxCfgWizard::get_vertical_list()
{
    if (get_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
        "fcitx-classic-ui.config", "ClassicUI", "VerticalList", &m_vertical_list))
    {
        qDebug() << "lenky get_vertical_list():" << m_vertical_list;
        return m_vertical_list;
    }

    return false;
}

void FcitxCfgWizard::set_vertical_list(bool vertical, bool real_save)
{
    m_vertical_list = vertical;

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
            "fcitx-classic-ui.config", "ClassicUI", "VerticalList", &m_vertical_list);
    }
}

QString FcitxCfgWizard::get_trigger_key_first()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "TriggerKey", &m_trigger_key))
    {
        if (m_trigger_key.hotkey[0].desc == NULL)
            return "Empty";
        else
            return m_trigger_key.hotkey[0].desc;
    }
    qDebug() << "lenky get_trigger_key_first():" << m_trigger_key.hotkey[0].desc;
    return "Empty";
}

QString FcitxCfgWizard::get_trigger_key_second()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "TriggerKey", &m_trigger_key))
    {
        if (m_trigger_key.hotkey[1].desc == NULL)
            return "Empty";
        else
            return m_trigger_key.hotkey[1].desc;
    }
    qDebug() << "lenky get_trigger_key_second():" << m_trigger_key.hotkey[1].desc;
    return "Empty";
}

void FcitxCfgWizard::set_trigger_key_first(QString hotkey, bool real_save)
{

    save_q_string_2_m_string(hotkey, &m_string);
    FcitxHotkeySetKey(m_string, &(m_trigger_key.hotkey[0]));

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "TriggerKey", &m_trigger_key);
    }
}

void FcitxCfgWizard::set_trigger_key_second(QString hotkey, bool real_save)
{

    save_q_string_2_m_string(hotkey, &m_string);
    FcitxHotkeySetKey(m_string, &(m_trigger_key.hotkey[1]));

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "TriggerKey", &m_trigger_key);
    }
}

//=================================================================================//

QString FcitxCfgWizard::get_prev_page_key_first()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "PrevPageKey", &m_prev_page_key))
    {
        if (m_prev_page_key.hotkey[0].desc == NULL)
            return "Empty";
        else
            return m_prev_page_key.hotkey[0].desc;
    }
    qDebug() << "lenky get_prev_page_key_first():" << m_prev_page_key.hotkey[0].desc;
    return "Empty";
}

QString FcitxCfgWizard::get_prev_page_key_second()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "PrevPageKey", &m_prev_page_key))
    {
        if (m_prev_page_key.hotkey[1].desc == NULL)
            return "Empty";
        else
            return m_prev_page_key.hotkey[1].desc;
    }

    return "Empty";
}

void FcitxCfgWizard::set_prev_page_key_first(QString hotkey, bool real_save)
{

    save_q_string_2_m_string(hotkey, &m_string);
    FcitxHotkeySetKey(m_string, &(m_prev_page_key.hotkey[0]));

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "PrevPageKey", &m_prev_page_key);
    }
}

void FcitxCfgWizard::set_prev_page_key_second(QString hotkey, bool real_save)
{

    save_q_string_2_m_string(hotkey, &m_string);
    FcitxHotkeySetKey(m_string, &(m_prev_page_key.hotkey[1]));

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "PrevPageKey", &m_prev_page_key);
    }
}

//=================================================================================//

//=================================================================================//

QString FcitxCfgWizard::get_next_page_key_first()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "NextPageKey", &m_next_page_key))
    {
        if (m_next_page_key.hotkey[0].desc == NULL)
            return "Empty";
        else
            return m_next_page_key.hotkey[0].desc;
    }

    return "Empty";
}

QString FcitxCfgWizard::get_next_page_key_second()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "NextPageKey", &m_next_page_key))
    {
        if (m_next_page_key.hotkey[1].desc == NULL)
            return "Empty";
        else
            return m_next_page_key.hotkey[1].desc;
    }

    return "Empty";
}

void FcitxCfgWizard::set_next_page_key_first(QString hotkey, bool real_save)
{

    save_q_string_2_m_string(hotkey, &m_string);
    FcitxHotkeySetKey(m_string, &(m_next_page_key.hotkey[0]));

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "NextPageKey", &m_next_page_key);
    }
}

void FcitxCfgWizard::set_next_page_key_second(QString hotkey, bool real_save)
{

    save_q_string_2_m_string(hotkey, &m_string);
    FcitxHotkeySetKey(m_string, &(m_next_page_key.hotkey[1]));

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "NextPageKey", &m_next_page_key);
    }
}

//=================================================================================//

//=================================================================================//

int FcitxCfgWizard::get_im_switch_hot_key()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "IMSwitchHotkey", &m_im_switch_hot_key))
    {
        qDebug() << "lenky get_im_switch_hot_key():" << m_im_switch_hot_key;
        return m_im_switch_hot_key;
    }

    return 0;
}

void FcitxCfgWizard::set_im_switch_hot_key(int hotkey, bool real_save)
{
    m_im_switch_hot_key = hotkey;

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "IMSwitchHotkey", &m_im_switch_hot_key);
    }
}

//=================================================================================//

bool FcitxCfgWizard::get_im_switch_key()
{
    if (get_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "IMSwitchKey", &m_im_switch_key))
    {
        qDebug() << "lenky get_im_switch_hot_key():" << m_im_switch_key;
        return m_im_switch_key;
    }

    return 0;
}

void FcitxCfgWizard::set_im_switch_key(bool swh, bool real_save)
{
    m_im_switch_key = swh;

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
            "IMSwitchKey", &m_im_switch_key);
    }
}

//=================================================================================//

QString FcitxCfgWizard::get_skin_type()
{
    if (get_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
        "fcitx-classic-ui.config", "ClassicUI", "SkinType", &m_skin_type))
    {
        qDebug() << "lenky get_font():" << m_skin_type;
        return m_skin_type;
    }
    return "";
}

void FcitxCfgWizard::set_skin_type(QString skin_type, bool real_save)
{
    save_q_string_2_m_string(skin_type, &m_skin_type);

    if (real_save) {
        set_fcitx_cfg_value("configdesc", "fcitx-classic-ui.desc", "conf",
            "fcitx-classic-ui.config", "ClassicUI", "SkinType", &m_skin_type);
    }
}

//=================================================================================//
void FcitxCfgWizard::set_trigger_key()
{
    set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "TriggerKey", &m_trigger_key);
}

void FcitxCfgWizard::set_prev_page_key()
{
    set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "PrevPageKey", &m_prev_page_key);
}

void FcitxCfgWizard::set_next_page_key()
{
    set_fcitx_cfg_value("configdesc", "config.desc", "", "config", "Hotkey",
        "NextPageKey", &m_next_page_key);
}

//=================================================================================//
QStringList FcitxCfgWizard::get_all_skin_type()
{
    int i;
    size_t len;
    QStringList ret_value;
    QDir skin_dir;
    QFileInfoList list;
    QFileInfoList::Iterator list_iter;
    char **skin_path = FcitxXDGGetPathWithPrefix(&len, "skin");

    for (i = 0; i < len; i ++) {
        skin_dir = QDir(skin_path[i]);
        if (!skin_dir.exists())
            continue;

        skin_dir.setFilter(QDir::Dirs);
        list = skin_dir.entryInfoList();
        for (list_iter = list.begin(); list_iter != list.end(); ++ list_iter) {
            if (list_iter->isDir() && "." != list_iter->fileName() && ".." != list_iter->fileName()) {
                ret_value << list_iter->fileName();
            }
        }
    }

    FcitxXDGFreePath(skin_path);

    return ret_value;
}

void FcitxCfgWizard::update_cfg_to_fcitx()
{
    fcitx_utils_launch_tool("fcitx-remote", "-r");
}

void FcitxCfgWizard::all_cfg_save()
{
    set_im_list(m_im_list, true);
    set_font(m_font, true);
    set_candidate_word_number(m_candidate_word_number, true);
    set_font_size(m_font_size, true);
    set_vertical_list(m_vertical_list, true);
    set_trigger_key();
    set_prev_page_key();
    set_next_page_key();
    set_im_switch_hot_key(m_im_switch_hot_key, true);
    set_im_switch_key(m_im_switch_key, true);
    set_skin_type(m_skin_type, true);
    update_cfg_to_fcitx();
}

//=========================================================================
QString FcitxCfgWizard::show_font_dialog()
{
 //   emit sigText();
    bool ok;
    const QFont &font = QFontDialog::getFont(&ok, 0);
    if(ok)
        return font.family();
    return font.family();
}

//qt控件貌似（？不确定，先这么做了）没法返回右shiht、右ctrl、右alt键，
//所以这里统一只支持shiht、ctrl和alt。
char* FcitxCfgWizard::deal_R_L_diff(char *key_str)
{
    QString str = QString(key_str);
    QStringList str_list = str.split("_");
    QStringList::Iterator iter;
    QStringList ret_list;
    QString tmp;

    for (iter = str_list.begin(); iter != str_list.end(); ++ iter) {
        if ("LCTRL" == *iter)
            tmp = "CTRL";
        else if ("LSHIFT" == *iter)
            tmp = "SHIFT";
        else if ("LALT" == *iter)
            tmp = "ALT";
        else
            tmp = *iter;

        if (!ret_list.contains(tmp))
            ret_list << tmp;
    }

    tmp = ret_list.join("_");
    save_q_string_2_m_string(tmp, &m_string);

    return m_string;
}

QString FcitxCfgWizard::get_fcitx_hot_key_string(unsigned int qtcode, unsigned int mod)
{
    int sym;
    unsigned int state;
    char *ret_value;

    keyQtToSym(qtcode, (Qt::KeyboardModifiers)mod, sym, state);
    if ((ret_value = FcitxHotkeyGetKeyString((FcitxKeySym)sym, state)) == NULL)
        return "";

    ret_value = deal_R_L_diff(ret_value);
    qDebug() << ret_value;

    return ret_value;
}


void FcitxCfgWizard::send_fcitx_ok_warn()
{
    create_fcitx_ok_warn();
}
void FcitxCfgWizard::create_fcitx_ok_warn()
{
 //   FcitxWarnDialog *app = new FcitxWarnDialog;
      fcitxWarnSig->exec();
}

void FcitxCfgWizard::handler_okBtn_fcitx_warn(){


//    //connect FcitxConfigtoolFont.qml
//     view = new QDeclarativeView;
//     view->setSource(QUrl("../qml/func/settings/FcitxConfigtoolFont.qml"));
//     view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//     QObject *rootObjectFont = dynamic_cast<QObject*>(view->rootObject());
//     QObject::connect(fcitxWarnSig, SIGNAL(fcitxWarntest()), rootObjectFont, SLOT(refreshFcitxFont()));

//     //connect FcitxConfigtoolKey.qml
//      view = new QDeclarativeView;
//      view->setSource(QUrl("../qml/func/settings/FcitxConfigtoolKey.qml"));
//      view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//      QObject *rootObjectKey = dynamic_cast<QObject*>(view->rootObject());
//      QObject::connect(fcitxWarnSig, SIGNAL(fcitxWarntest()), rootObjectKey, SLOT(refreshFcitxKey()));

//        delete fcitxWarnSig;

}

inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        qDebug() << QCoreApplication::applicationDirPath();
        return QString("/usr/share/youker-assistant/qml/");
//        return QString("/usr/share/youker-assistant/qml/main.qml");
    } else {
//        return QString(QCoreApplication::applicationDirPath() + "/../qml/main.qml");
        return QString(QCoreApplication::applicationDirPath() + "/../qml/func/settings/");
    }
}
