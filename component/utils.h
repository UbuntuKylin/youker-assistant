#ifndef UTILS_H
#define UTILS_H

#include <QString>

#define ITEMHEIGHT 30
#define ITEMHSPACE 10
#define ITEMVSPACE 5
#define PAGESPACE 20
#define ITEMWIDTH 650

const QString YOUKER_COMPANY_SETTING = "ubuntukylin/youker-assistant";
const QString YOUKER_SETTING_FILE_NAME_SETTING = "youker-assistant";

typedef enum{
    YOUKER_EN,
    YOUKER_ZH_CN,
    YOUKER_ES,
} LANGUAGE;

typedef enum{
    CACHE,
    PACAKAGE,
    COOKIES,
    BROWSER,
    TRACE,
    BIGFILE,
} CLEANERTAB;

struct AutoData
{
    QString appPath;
    QString appName;
    QString appComment;
    QString iconName;
    QString appStatus;
};

#endif // UTILS_H
