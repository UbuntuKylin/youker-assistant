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

#ifndef FCITXCFGWIZARD_H
#define FCITXCFGWIZARD_H

#include <QObject>
#include "fcitx-qt/fcitxqtconnection.h"
#include "fcitx-qt/fcitxqtinputmethodproxy.h"
#include "fcitx-utils/utils.h"
#include "fcitx-config/hotkey.h"
#include <QDeclarativeView>
#include "fcitxwarndialog.h"


class FcitxCfgWizard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QNOTIFY Fcitxwarn)

public:
    explicit FcitxCfgWizard(QObject *parent = 0);
    ~FcitxCfgWizard();

private:
    FcitxQtConnection *m_connection;
    FcitxQtInputMethodProxy *m_improxy;
    QString m_separator;

private:

    QStringList m_im_list;
    //注意：因为fcitx提供的库的缘故，这里必须采用malloc动态内存
    //因为fcitx库内部会调用到realloc，如果采用固定数组会出异常
    char *m_string;

    char *m_font;
    int m_candidate_word_number;
    int m_font_size;
    //布尔必须采用fcitx库里提供的boolean，而不能直接使用bool类型
    //否则读取/写入失败
    boolean m_vertical_list;

    FcitxHotkeys m_trigger_key;
    FcitxHotkeys m_prev_page_key;
    FcitxHotkeys m_next_page_key;
    //枚举类型，直接用int代替
    int m_im_switch_hot_key;
    boolean m_im_switch_key;

    //QString m_skin_type;
    char *m_skin_type;
    boolean m_cloud_enable;

private:
    bool connected();
    bool is_connected_ok();
    bool get_fcitx_cfg_value(char *cd_path_prefix, char *cd_file_name,
        char *c_path_prefix, char *c_file_name, char *groupName, const char *optionName,
        void *ret_value);
    bool set_fcitx_cfg_value(char *cd_path_prefix, char *cd_file_name,
        char *c_path_prefix, char *c_file_name, char *groupName, const char *optionName,
        void *set_value);

    void save_q_string_2_m_string(QString q_string, char **m_string);

public:
    Q_INVOKABLE QStringList get_im_list();
    Q_INVOKABLE bool set_im_list(QStringList im_list, bool real_save);

    Q_INVOKABLE QString get_font();
    Q_INVOKABLE void set_font(QString font, bool real_save);

    Q_INVOKABLE int get_candidate_word_number();
    Q_INVOKABLE void set_candidate_word_number(int num, bool real_save);

    Q_INVOKABLE int get_font_size();
    Q_INVOKABLE void set_font_size(int size, bool real_save);

    Q_INVOKABLE bool get_vertical_list();
    Q_INVOKABLE void set_vertical_list(bool vertical, bool real_save);

    Q_INVOKABLE QString get_trigger_key_first();
    Q_INVOKABLE QString get_trigger_key_second();
    Q_INVOKABLE void set_trigger_key_first(QString hotkey, bool real_save);
    Q_INVOKABLE void set_trigger_key_second(QString hotkey, bool real_save);

    Q_INVOKABLE QString get_prev_page_key_first();
    Q_INVOKABLE QString get_prev_page_key_second();
    Q_INVOKABLE void set_prev_page_key_first(QString hotkey, bool real_save);
    Q_INVOKABLE void set_prev_page_key_second(QString hotkey, bool real_save);

    Q_INVOKABLE QString get_next_page_key_first();
    Q_INVOKABLE QString get_next_page_key_second();
    Q_INVOKABLE void set_next_page_key_first(QString hotkey, bool real_save);
    Q_INVOKABLE void set_next_page_key_second(QString hotkey, bool real_save);

    Q_INVOKABLE int get_im_switch_hot_key();
    Q_INVOKABLE void set_im_switch_hot_key(int hotkey, bool real_save);

    Q_INVOKABLE bool get_im_switch_key();
    Q_INVOKABLE void set_im_switch_key(bool swh, bool real_save);

    //获取当前所有可用皮肤
    Q_INVOKABLE QStringList get_all_skin_type();
    Q_INVOKABLE QString get_skin_type();
    Q_INVOKABLE void set_skin_type(QString skin, bool real_save);

    Q_INVOKABLE void all_cfg_save();

    Q_INVOKABLE QString show_font_dialog();

    Q_INVOKABLE void send_fcitx_ok_warn();
    void create_fcitx_ok_warn();

    //


private:
    char* deal_R_L_diff(char *key_str);
public:
    Q_INVOKABLE QString get_fcitx_hot_key_string(unsigned int qtcode, unsigned int mod);
    QDeclarativeView *view;

public slots:
    void handler_okBtn_fcitx_warn();
private:
    void set_trigger_key();
    void set_prev_page_key();
    void set_next_page_key();
    //配置下发，让修改立即生效
    void update_cfg_to_fcitx();
};

#endif // FCITXCFGWIZARD_H
