TEMPLATE = subdirs
SUBDIRS = \
    src \
    plugins \
    kyasDbus

TRANSLATIONS += \
    src/translation/kylin-assistant_zh_CN.ts \
    src/translation/kylin-assistant_es.ts \
    src/translation/kylin-assistant_de.ts \
    src/translation/kylin-assistant_fr.ts \
    src/translation/kylin-assistant_ru.ts \
    src/translation/kylin-assistant_bo.ts

CONFIG += qt

QT += widgets
