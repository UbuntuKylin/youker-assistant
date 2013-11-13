TEMPLATE = subdirs

#DEFINES += "GETTEXT_PACKAGE=\\\""youker-assistant"\\\""
#isEmpty(PREFIX) {
#  PREFIX = /usr/local
#}
#DEFINES += "INSTALL_PREFIX=\\\"$$PREFIX\\\""

SUBDIRS += src qml backends

# i18n setting
TRANSLATIONS += \
    src/translation/youker-assistant_en.ts \
    src/translation/youker-assistant_zh_CN.ts
#CONFIG += localize_deployment
#SYMBIAN_SUPPORTED_LANGUAGES += zh_CN
#SYMBIAN_LANG.zh_CN = 31

#TRANSLATIONS += \
#    Translation/youker_zh_CN.ts

#symbian{
#addFiles.sources = youker_zh_CN.qm
#addFiles.path = .
#DEPLOYMENT += addFiles
#}

#DEFINES += QT_NO_DEBUG_OUTPUT
