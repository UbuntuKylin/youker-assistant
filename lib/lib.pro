QMAKE_EXTRA_TARGETS += other
PRE_TARGETDEPS += other
other.commands = make -f Makefile
