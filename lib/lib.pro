QMAKE_EXTRA_TARGETS += other
PRE_TARGETDEPS += other
other.commands = make -f Makefile


#TEMPLATE = lib
#INCLUDEPATH += /usr/include/python2.7 /usr/lib/python2.7/config
#SOURCES     = cmmap.c
#TARGET      = MyCppModule
#target.source += $$TARGET
#target.path = /usr/lib/python2.7/dist-packages/
#INSTALLS = target
