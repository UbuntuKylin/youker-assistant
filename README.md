youker-assistant
================

Attention
=========
It supports unity and mate for Ubuntu/Ubuntu Kylin.

Depends
=======
debhelper (>= 9),python-dev,python-lxml,python-piston-mini-client,python-xdg,libqt4-dev,pkg-config,python (>= 2.6.6-3~),libglib2.0-dev,libgtop2-dev

Launchpad
=======
https://launchpad.net/youker-assistant

Internationalization
=======
lupdate youker-assistant.pro
linguist youker-assistant_zh_CN.ts
lrelease youker-assistant.pro

Python Internationalization
=======
xgettext -k_ -o youker-assistant.pot cpuinfo.py
youker-assistant.pot:修改charset为utf-8
cp youker-assistant.pot youker-assistant.po
msgfmt -o youker-assistant.mo youker-assistant.po
(sudo cp youker-assistant.mo /usr/share/locale/zh_CN/LC_MESSAGES/)




FT Version:
1)changelog like this:
youker-assistant (2.0.7kord) juniper; urgency=low

2)youker-assistant.dekstop

3)debian/source/format
replace quilt with native


DEBUG:
gdb python
set args start_sessiondbus.py
run
