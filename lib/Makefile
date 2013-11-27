CC            = gcc
INCPATH       = -I/usr/include/python2.7 -I/usr/lib/python2.7/config
SOURCE        = cmmap.c
targets       = MyCppModule.so

all:
	$(CC) $(INCPATH) \
	-shared -fPIC \
	$(SOURCE) \
	-o $(targets)

clean:
	rm -f ${targets}

install:
	install -m 0755 ${targets} ${DESTDIR}/usr/lib/python2.7/dist-packages/${targets}

remove:
	rm -f ${DESTDIR}/usr/lib/python2.7/dist-packages/${targets}

