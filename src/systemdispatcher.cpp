/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
#include "systemdispatcher.h"
#include <QDebug>
#include <QVariant>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QDir>

#include <QFile>
#include <QDataStream>
#include <iostream>
#include "authdialog.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>
#include <sys/wait.h>
extern QString passwd;
extern QString music_path;

SystemDispatcher::SystemDispatcher(QObject *parent) :
    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin_tools.daemon",
                               "/",
                               "com.ubuntukylin_tools.daemon",
                               QDBusConnection::systemBus());

    //绑定到底层清理完毕后发送到信号函数clear_browser
    QObject::connect(systemiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_main(QString)),this,SLOT(handler_clear_rubbish_main_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_main(QString)),this,SLOT(handler_clear_rubbish_main_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_second(QString)),this,SLOT(handler_clear_rubbish_second_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_second(QString)),this,SLOT(handler_clear_rubbish_second_error(QString)));
//    QObject::connect(systemiface,SIGNAL(scan_complete(QString)),this,SLOT(handler_scan_rubbish(QString)));

    notify_str = "";
    history_flag = true;
    onekey_args << "cache" << "history" << "cookies" << "unneed";
    onekey_args2 << "cache" << "history" << "cookies" << "unneed";

}

void SystemDispatcher::handler_clear_rubbish_second_error(QString msg)
{
     emit finishCleanWorkSecondError(msg);
}

void SystemDispatcher::exit_qt()
{
    systemiface->call("exit");
}

QString SystemDispatcher::get_system_daemon_qt() {
    QDBusReply<QString> reply = systemiface->call("get_system_daemon");
    return reply.value();
}

QString SystemDispatcher::get_system_daemon_qt_default() {
    QDBusReply<QString> reply = systemiface->call("get_system_daemon");
    return reply.value();
}

void SystemDispatcher::get_music_path(QString musicpath) {
    music_path = musicpath;
}

void SystemDispatcher::set_homedir_qt() {
    QString homedir = QDir::homePath();
    systemiface->call("set_homedir", homedir);
}

void SystemDispatcher::set_user_homedir_qt() {
    QString homedir = QDir::homePath();
    systemiface->call("set_user_homedir", homedir);
}


void SystemDispatcher::set_history_flag(bool flag) {
    history_flag = flag;
}

bool SystemDispatcher::get_history_flag() {
    return history_flag;
}

int SystemDispatcher::get_add_value()
{
    QDBusReply<int> reply = systemiface->call("test_add", 3, 4);
    int tt = reply.value();
    return tt;
}

void SystemDispatcher::handler_clear_rubbish(QString msg)
{
     emit finishCleanWork(msg);
}

void SystemDispatcher::handler_clear_rubbish_main_onekey(QString msg)
{
     emit finishCleanWorkMain(msg);
}

void SystemDispatcher::handler_clear_rubbish_main_error(QString msg)
{
     emit finishCleanWorkMainError(msg);
}
void SystemDispatcher::handler_clear_rubbish_second_onekey(QString msg)
{
     emit finishCleanWorkSecond(msg);
}

void SystemDispatcher::handler_scan_rubbish(QString msg)
{
    emit finishScanWork(msg);
}


void SystemDispatcher::send_btn_msg(QString str)
{
    systemiface->call("test_fastclear", str);
}

void SystemDispatcher::check_screen_break_point() {
    systemiface->call("check_screen");
}


//-----------------------sound------------------------
QStringList SystemDispatcher::get_sound_themes_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_sound_themes");
    return reply.value();
}
QStringList SystemDispatcher::get_sounds_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_sounds");
    return reply.value();
}
void SystemDispatcher::replace_sound_file_qt(QString origfile, QString targetfile) {
    systemiface->call("replace_sound_file", origfile, targetfile);
}
void SystemDispatcher::restore_sound_file_qt(QString targetfile) {
    systemiface->call("restore_sound_file", targetfile);
}
void SystemDispatcher::restore_all_sound_file_qt(QString soundtheme) {
    systemiface->call("restore_all_sound_file", soundtheme);
}

//-----------------------------------------------
//-----------------------others------------------------
void SystemDispatcher::custom_plymouth_bg_qt(QString plymouthName) {
    systemiface->call("custom_plymouth_bg", plymouthName);
}
void SystemDispatcher::add_new_plymouth_qt(QString customBG, QString plymouthName) {
    systemiface->call("add_new_plymouth", customBG, plymouthName);
}
void SystemDispatcher::send_boot_signal() {
    emit addBootImage();
}

QStringList SystemDispatcher::get_existing_plymouth_list_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_existing_plymouth_list");
    return reply.value();
}
void SystemDispatcher::plymouth_init_check_qt() {
    systemiface->call("plymouth_init_check");
}

//-----------------------------------------------


QString SystemDispatcher::show_file_dialog(QString flag) {
    if (flag == "bootanimation") {
        QString bootfileName = QFileDialog::getOpenFileName(0, tr("选择开机动画"), "", tr("Image Files (*.png)"));
        return bootfileName;
    }
    else if (flag == "soundeffects") {
        QString musicfileName = QFileDialog::getOpenFileName(0, tr("选择音乐"), "", tr("Music Files (*.ogg *.wav *.mp3 *.wma)"));
        return musicfileName;
    }
    else
        return "/ubuntukylin";
}

//QStringList SystemDispatcher::scan_of_large_qt(QString abspath) {
//    QDBusReply<QStringList> reply = systemiface->call("scan_of_large", abspath);
//    return reply.value();
//}

//QStringList SystemDispatcher::scan_of_same_qt(QString abspath) {
//    QDBusReply<QStringList> reply = systemiface->call("scan_of_same", abspath);
//    return reply.value();
//}

//int SystemDispatcher::scan_history_records_qt() {
//    QDBusReply<int> reply = systemiface->call("scan_history_records");
//    return reply.value();
//}
//void SystemDispatcher::clean_history_records_qt() {
////    QDBusReply<void> reply = systemiface->call("clean_history_records");
//    systemiface->call("clean_history_records");
//}
//QStringList SystemDispatcher::scan_cookies_records_qt() {
//    QDBusReply<QStringList> reply = systemiface->call("scan_cookies_records");
//    return reply.value();
//}
//void SystemDispatcher::clean_cookies_records_qt(QStringList strlist) {
////    QDBusReply<void> reply = systemiface->call("clean_cookies_records", strlist);
//    systemiface->call("clean_cookies_records", strlist);
//}
//QStringList SystemDispatcher::scan_unneed_packages_qt() {
//    QDBusReply<QStringList> reply = systemiface->call("scan_unneed_packages");
//    return reply.value();
//}
void SystemDispatcher::clean_package_cruft_qt(QStringList strlist) {
    systemiface->call("clean_package_cruft", strlist);
}
void SystemDispatcher::clean_file_cruft_qt(QStringList strlist, QString str) {
    systemiface->call("clean_file_cruft", strlist, str);
}
void SystemDispatcher::scan_cache_cruft_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("scan_cache_cruft");
    apt_center = reply.value();
}
QStringList SystemDispatcher::get_apt_data()
{
    return apt_center["apt"].toStringList();
}
QStringList SystemDispatcher::get_center_data() {
    return apt_center["softwarecenter"].toStringList();
}

//QStringList SystemDispatcher::scan_apt_cruft_qt() {
//    QDBusReply<QStringList> reply = systemiface->call("scan_apt_cruft");
//    return reply.value();
//}
//QStringList SystemDispatcher::scan_softwarecenter_cruft_qt() {
//    QDBusReply<QStringList> reply = systemiface->call("scan_softwarecenter_cruft");
//    return reply.value();
//}

void SystemDispatcher::clean_by_main_one_key_qt(QStringList strlist) {
    systemiface->call("clean_by_main_one_key", strlist);
}
void SystemDispatcher::clean_by_second_one_key_qt(QStringList strlist) {
    systemiface->call("clean_by_second_one_key", strlist);
}
//------------------------------------------------------



//--------------------
void SystemDispatcher::set_apt_args(QString str) {
    apt_args.append(str);
}
void SystemDispatcher::del_apt_args(QString str) {
    QStringList bake;
    int len = apt_args.length();
    for (int i=0; i< len; i++) {
        if (apt_args[i] != str)
            bake.append(apt_args[i]);
    }
    apt_args.clear();
    apt_args = bake;
}
void SystemDispatcher::clear_apt_args() {
    apt_args.clear();
}
QStringList SystemDispatcher::get_apt_args() {
    return apt_args;
}

void SystemDispatcher::set_software_args(QString str) {
    software_args.append(str);
}
void SystemDispatcher::del_software_args(QString str) {
    QStringList bake;
    int len = software_args.length();
    for (int i=0; i< len; i++) {
        if (software_args[i] != str)
            bake.append(software_args[i]);
    }
    software_args.clear();
    software_args = bake;
}
void SystemDispatcher::clear_software_args() {
    software_args.clear();
}
QStringList SystemDispatcher::get_software_args() {
    return software_args;
}

void SystemDispatcher::set_cookies_args(QString str) {
    cookies_args.append(str);
}
void SystemDispatcher::del_cookies_args(QString str) {
    QStringList bake;
    int len = cookies_args.length();
    for (int i=0; i< len; i++) {
        if (cookies_args[i] != str)
            bake.append(cookies_args[i]);
    }
    cookies_args.clear();
    cookies_args = bake;
}
void SystemDispatcher::clear_cookies_args() {
    cookies_args.clear();
}
QStringList SystemDispatcher::get_cookies_args() {
    return cookies_args;
}

void SystemDispatcher::set_package_args(QString str) {
    package_args.append(str);
}
void SystemDispatcher::del_package_args(QString str) {
    QStringList bake;
    int len = package_args.length();
    for (int i=0; i< len; i++) {
        if (package_args[i] != str)
            bake.append(package_args[i]);
    }
    package_args.clear();
    package_args = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_package_args() {
    package_args.clear();
}
QStringList SystemDispatcher::get_package_args() {
    return package_args;
}

void SystemDispatcher::set_onekey_args(QString str) {
    onekey_args.append(str);
}
void SystemDispatcher::del_onekey_args(QString str) {
    QStringList bake;
    int len = onekey_args.length();
    for (int i=0; i< len; i++) {
        if (onekey_args[i] != str)
            bake.append(onekey_args[i]);
    }
    onekey_args.clear();
    onekey_args = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_onekey_args() {
    onekey_args.clear();
}
QStringList SystemDispatcher::get_onekey_args() {
    return onekey_args;
}

void SystemDispatcher::set_onekey_args2(QString str) {
    onekey_args2.append(str);
}
void SystemDispatcher::del_onekey_args2(QString str) {
    QStringList bake;
    int len = onekey_args2.length();
    for (int i=0; i< len; i++) {
        if (onekey_args2[i] != str)
            bake.append(onekey_args2[i]);
    }
    onekey_args2.clear();
    onekey_args2 = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_onekey_args2() {
    onekey_args2.clear();
}
QStringList SystemDispatcher::get_onekey_args2() {
    return onekey_args2;
}

void SystemDispatcher::set_largestfile_args(QString str) {
    largestfile_args.append(str);
}
void SystemDispatcher::del_largestfile_args(QString str) {
    QStringList bake;
    int len = largestfile_args.length();
    for (int i=0; i< len; i++) {
        if (largestfile_args[i] != str)
            bake.append(largestfile_args[i]);
    }
    largestfile_args.clear();
    largestfile_args = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_largestfile_args() {
    largestfile_args.clear();
}
QStringList SystemDispatcher::get_largestfile_args() {
    return largestfile_args;
}

//QMap<QString, QStringList> SystemDispatcher::search_the_same_file(QString path) {
//    QDBusReply<QMap<QString, QStringList> > reply = iface->call("search_the_same", path);
////    if (reply.isValid()) {
////        QMap<QString, QStringList> value = reply.value();
//////        myinfo = value;
////    }
////    else {
////        qDebug() << "get same file failed!";
////    }
//}

int SystemDispatcher::get_the_record_qt(QString mode) {
    QDBusReply<int> reply = systemiface->call("get_the_record", mode);
    int value = reply.value();
    return value;
//    if (reply.isValid()) {
//        int value = reply.value();
//        return value;
//    }
//    else {
//        qDebug() << "get record number failed!";
//        return 0;
//    }
}


void SystemDispatcher::clean_the_browser_qt(QString mode) {
    systemiface->call("clean_the_browser", mode);
}

QMap<QString, QVariant> SystemDispatcher::search_same_files(QString path) {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("search_the_same", path);
    return reply.value();
//    if (reply.isValid()) {
//        return reply.value();
//    }
//    else {
//        qDebug() << "search_the_same failed!";
////        return "search_the_same has error";
//    }
}

QStringList SystemDispatcher::search_largest_file(QString path) {
    QDBusReply<QStringList> reply = systemiface->call("search_the_large", path);
    return reply.value();
//    if (reply.isValid()) {
//        QStringList value = reply.value();
//        return reply.value();
//    }
//    else {
//        qDebug() << "search_the_large failed!";
////        return "search_the_large has error";
//    }
}

void SystemDispatcher::set_str(QString str)
{
    notify_str = str;
}
QString SystemDispatcher::get_str()
{
    return notify_str;
}

/*
QMap(("cookies", QVariant(QString, "admaster.com.cn<2_2>2<1_1>alimama.com<2_2>1<1_1>google.com<2_2>1<1_1>google.com.hk<2_2>2<1_1>mediav.com<2_2>1<1_1>miaozhen.com<2_2>5<1_1>mmstat.com<2_2>2<1_1>nokia.com<2_2>3<1_1>qq.com<2_2>51<1_1>tanx.com<2_2>1<1_1>taobao.com<2_2>1") )
( "history" ,  QVariant(QString, "148<2_2>http://ptlogin2.qq.com/jump?ptlang=2052&clientuin=349098792&clientkey=AA9B77287B5EE763BA127F36D16D076D0F464F2232562AC1C96D4131F48B100A&u1=http%3A%2F%2Fuser.qzone.qq.com%2F349098792%2Finfocenter&ADUIN=349098792&ADSESSION=1374020152&ADTAG=CLIENT.QQ.4735_Mysrv.0<2_2>None<2_2>1<1_1>149<2_2>http://user.qzone.qq.com/349098792/infocenter<2_2>天使城8号 [http://349098792.qzone.qq.com]<2_2>5<1_1>150<2_2>http://www.qq.com/<2_2>腾讯首页<2_2>2<1_1>151<2_2>http://ent.qq.com/a/20130716/018497.htm<2_2>冯版春晚首个节目创意曝光：王菲五大天后合体_娱乐_腾讯网<2_2>1<1_1>152<2_2>http://sports.qq.com/nba/<2_2>NBA_腾讯体育_腾讯网_做最好的中文NBA门户<2_2>1<1_1>153<2_2>http://house.qq.com/<2_2>房产频道_腾讯网<2_2>1<1_1>154<2_2>http://cs.house.qq.com/<2_2>房产频道_腾讯·大湘网_湖南城市生活门户<2_2>1<1_1>155<2_2>http://cs.house.qq.com/a/20130717/002230.htm<2_2>上半年湖南房价同比上涨5.1% 居民收入增速回落_房产长沙站_腾讯网<2_2>1<1_1>156<2_2>http://ptlogin2.qq.com/jump?ptlang=2052&clientuin=349098792&clientkey=AA9B77287B5EE763BA127F36D16D076D0F464F2232562AC1C96D4131F48B100A&u1=http://ptlogin2.qq.com/qqfriends?pgv_ref=im.perinfo.perinfo.icon<2_2>None<2_2>1<1_1>157<2_2>http://ptlogin2.qq.com/qqfriends?pgv_ref=im.perinfo.perinfo.icon&ptlang=2052<2_2>None<2_2>1<1_1>158<2_2>http://t.qq.com/ilist/qqfriends?filter=0&pgv_ref=im.perinfo.perinfo.icon&ptlang=2052<2_2>None<2_2>1<1_1>159<2_2>http://list.t.qq.com/ilist/qqfriends?filter=0&pgv_ref=im.perinfo.perinfo.icon&ptlang=2052<2_2>None<2_2>1<1_1>160<2_2>http://t.qq.com/UbuntuKylin?pgv_ref=im.perinfo.perinfo.icon#!/list/qqfriends/5/?pgv_ref=im.perinfo.perinfo.icon&ptlang=2052&pgv_ref=im.perinfo.perinfo.icon<2_2>首页_腾讯微博<2_2>1<1_1>161<2_2>http://t.qq.com/UbuntuKylin?pgv_ref=im.perinfo.perinfo.icon#<2_2>首页_腾讯微博<2_2>1<1_1>162<2_2>http://t.qq.com/UbuntuKylin?pgv_ref=im.perinfo.perinfo.icon#!/quan/4004<2_2>首页_腾讯微博<2_2>1<1_1>163<2_2>http://ptlogin2.qq.com/jump?ptlang=2052&clientuin=349098792&clientkey=D40B98314E92397624B0DA01EBF2436618015F460F397BCB0B6623A24B48A313&u1=http%3A%2F%2Fuser.qzone.qq.com%2F349098792%2Finfocenter&ADUIN=349098792&ADSESSION=1374020152&ADTAG=CLIENT.QQ.4735_Mysrv.0<2_2>None<2_2>1<1_1>164<2_2>http://ptlogin2.qq.com/qqmail?Fun=clientread&ADUIN=349098792&ADSESSION=iii&ADTAG=jjj&clientuin=349098792&clientkey=D40B98314E92397624B0DA01EBF2436618015F460F397BCB0B6623A24B48A313&ptlang=2052&httptype=0&ADUIN=349098792&ADSESSION=1374020152&ADTAG=CLIENT.QQ.4735_Mysrv.0<2_2>None<2_2>1<1_1>165<2_2>http://ptlogin4.mail.qq.com/check_sig?pttype=2&uin=349098792&service=pt2__1__qqmail__httptype__0&nodirect=0&ptsig=j1CUsOBMyzqr*XpTv18aP-ADPDvPzMFHS5sJ916CWI8_&s_url=http%3a%2f%2fmail.qq.com%2fcgi-bin%2flogin%3flc%3dzh%5fCN%26vm%3dpt%26Fun%3dclientread%26ADUIN%3d349098792%26ADSESSION%3diii%26ADTAG%3djjj%26ptlang%3d2052%26httptype%3d0%26ADUIN%3d349098792%26ADSESSION%3d1374020152%26ADTAG%3dCLIENT.QQ.4735%5fMysrv.0&f_url=http%3a%2f%2fmail.qq.com%2fcgi-bin%2flogin%3flc%3dzh%5fCN%26vm%3dptf%26Fun%3dclientread%26ADUIN%3d349098792%26ADSESSION%3diii%26ADTAG%3djjj%26ptlang%3d2052%26httptype%3d0%26ADUIN%3d349098792%26ADSESSION%3d1374020152%26ADTAG%3dCLIENT.QQ.4735%5fMysrv.0&ptlang=2052&ptredirect=0&aid=23000101&daid=4&j_later=0&low_login_hour=0&regmaster=0<2_2>None<2_2>1<1_1>166<2_2>http://mail.qq.com/cgi-bin/login?lc=zh_CN&vm=pt&Fun=clientread&ADUIN=349098792&ADSESSION=iii&ADTAG=jjj&ptlang=2052&httptype=0&ADUIN=349098792&ADSESSION=1374020152&ADTAG=CLIENT.QQ.4735_Mysrv.0&qqmailkey=6c36c0e6cfde3b763252ec9b37d562b53ac6f34ffab4acda06df777a7ed904c6<2_2>None<2_2>1<1_1>167<2_2>http://mail.qq.com/cgi-bin/frame_html?sid=Hzf7JPcddrhdCR1M&r=3cc3efd8ed793663a4b8c13d21fbf8e3<2_2>QQ邮箱 - 群邮件<2_2>1<1_1>168<2_2>http://www.google.com/<2_2>None<2_2>2<1_1>169<2_2>http://www.google.com.hk/url?sa=p&hl=zh-CN&pref=hkredirect&pval=yes&q=http://www.google.com.hk/&ust=1374023390368601&usg=AFQjCNEMYZczk4DB429-Ut963OPKiGCeTw<2_2>None<2_2>1<1_1>170<2_2>http://www.google.com.hk/<2_2>Google<2_2>2<1_1>171<2_2>http://www.google.com.hk/#newwindow=1&safe=strict&site=&source=hp&q=QML+wrapMode&oq=QML+wrapMode&gs_l=hp.3...1872.2871.0.3275.5.5.0.0.0.0.0.0..0.0....0...1c.1.21.hp.h_MB9tepMrg&bav=on.2,or.&bvm=bv.49405654,d.dGI&fp=b4516977249b93c8&biw=1375&bih=810<2_2>QML wrapMode - Google 搜索<2_2>1<1_1>172<2_2>http://www.google.com.hk/url?sa=t&rct=j&q=QML%20wrapMode&source=web&cd=1&ved=0CCwQFjAA&url=%68%74%74%70%3a%2f%2f%68%61%72%6d%61%74%74%61%6e%2d%64%65%76%2e%6e%6f%6b%69%61%2e%63%6f%6d%2f%64%6f%63%73%2f%6c%69%62%72%61%72%79%2f%68%74%6d%6c%2f%71%74%34%2f%71%6d%6c%2d%74%65%78%74%2e%68%74%6d%6c&ei=ye7lUdWAIY6nkAX2koDgDg&usg=AFQjCNGtNj0b6wVYEB39hvH-ZvJ5FbEpCQ&bvm=bv.49405654,d.dGI&cad=rjt<2_2>None<2_2>1<1_1>173<2_2>http://harmattan-dev.nokia.com/docs/library/html/qt4/qml-text.html<2_2>Qt 4.7: QML Text Element<2_2>1<1_1>174<2_2>http://www.google.com.hk/url?sa=p&hl=zh-CN&pref=hkredirect&pval=yes&q=http://www.google.com.hk/&ust=1374027691811048&usg=AFQjCNEulYm1Cf1Y-kCv0kN1-P79E_OaAw<2_2>None<2_2>1<1_1>175<2_2>http://www.google.com.hk/#newwindow=1&safe=strict&site=&source=hp&q=QML+GridView&oq=QML+GridView&gs_l=hp.3...331.3913.0.4183.12.10.0.0.0.0.0.0..0.0....0...1c.1.21.hp.t64pazJl4k0&bav=on.2,or.&bvm=bv.49405654,d.dGI&fp=b4516977249b93c8&biw=1375&bih=810<2_2>QML GridView - Google 搜索<2_2>1<1_1>176<2_2>http://www.google.com.hk/url?sa=t&rct=j&q=QML%20GridView&source=web&cd=1&ved=0CCwQFjAA&url=%68%74%74%70%3a%2f%2f%68%61%72%6d%61%74%74%61%6e%2d%64%65%76%2e%6e%6f%6b%69%61%2e%63%6f%6d%2f%64%6f%63%73%2f%6c%69%62%72%61%72%79%2f%68%74%6d%6c%2f%71%74%34%2f%71%6d%6c%2d%67%72%69%64%76%69%65%77%2e%68%74%6d%6c&ei=kv_lUYuhOsaXkgWCsYGQBg&usg=AFQjCNE8sGcIlqUXMF-YGYQo7RsJyxxgnA&bvm=bv.49405654,d.dGI&cad=rjt<2_2>None<2_2>2<1_1>177<2_2>http://harmattan-dev.nokia.com/docs/library/html/qt4/qml-gridview.html<2_2>Qt 4.7: QML GridView Element<2_2>2<1_1>178<2_2>http://ptlogin2.qq.com/jump?ptlang=2052&clientuin=349098792&clientkey=41F1014AC16D9F6CBD998A0062DD7BE3AAE41A577B1DCB589E6AD2F977D8F7C6&u1=http%3A%2F%2Fuser.qzone.qq.com%2F349098792%2Finfocenter&ADUIN=349098792&ADSESSION=1374026854&ADTAG=CLIENT.QQ.4735_Mysrv.0<2_2>None<2_2>1<1_1>179<2_2>http://harmattan-dev.nokia.com/docs/library/html/qt4/qml-component.html<2_2>Qt 4.7: QML Component Element<2_2>1<1_1>180<2_2>http://ptlogin2.qq.com/jump?ptlang=2052&clientuin=349098792&clientkey=5D0987002168E847AA785DBB953A4C382A49E1C2C9EBF661FEFDD7FC250B439A&u1=http%3A%2F%2Fuser.qzone.qq.com%2F349098792%2Finfocenter&ADUIN=349098792&ADSESSION=1374026854&ADTAG=CLIENT.QQ.4735_Mysrv.0<2_2>None<2_2>1<1_1>181<2_2>http://ptlogin2.qq.com/jump?ptlang=2052&clientuin=349098792&clientkey=9040AF58E04A4C3AA20D4F1A6CD3176A6607578DEBC44A5CA50E663CFABC014D&u1=http%3A%2F%2Fuser.qzone.qq.com%2F349098792%2Finfocenter&ADUIN=349098792&ADSESSION=1374039113&ADTAG=CLIENT.QQ.4735_Mysrv.0<2_2>None<2_2>1") ) ( "unneed" ,  QVariant(QString, "linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464<1_1>linux-headers-3.8.0-19-generic<2_2>Linux kernel headers for version 3.8.0 on 32 bit x86 SMP<2_2>11802624<1_1>linux-headers-generic<2_2>Generic Linux kernel headers<2_2>33792") ) )
*/

QMap<QString, QVariant> SystemDispatcher::scan_by_one_key_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("scan_by_one_key");
    return reply.value();
//    if (reply.isValid()) {
//        QString aa = reply.value()["unneed"].toString();
//        QVariant(QString, "linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
//        <1_1>linux-headers-3.8.0-19-generic<2_2>Linux kernel headers for version 3.8.0 on 32 bit x86 SMP<2_2>11802624
//        <1_1>linux-headers-generic<2_2>Generic Linux kernel headers<2_2>33792")
//        return reply.value();
//    }
//    else {
//        qDebug() << "scan_by_one_key failed!";
//    }
}


void SystemDispatcher::show_passwd_dialog() {
    AuthDialog *dialog = new AuthDialog;
    dialog->exec();
}
