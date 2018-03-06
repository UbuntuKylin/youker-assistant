kylin-assistant
================

Attention
=========
It supports unity and mate for Ubuntu/Ubuntu Kylin.

Depends
=======
debhelper (>= 9),python-dev,python-lxml,python-piston-mini-client,python-xdg,qtbase5-dev,qt5-qmake,qtscript5-dev,qttools5-dev-tools,pkg-config,python (>= 2.6.6-3~),libglib2.0-dev,libgtop2-dev

GitHub
=======
https://github.com/KylinAppCenter/kylin-assistant

Internationalization
=======
lupdate kylin-assistant.pro
linguist kylin-assistant_zh_CN.ts
lrelease kylin-assistant.pro

Python Internationalization
=======
xgettext -k_ -o kylin-assistant.pot cpuinfo.py
kylin-assistant.pot:修改charset为utf-8
cp kylin-assistant.pot kylin-assistant.po
msgfmt -o kylin-assistant.mo kylin-assistant.po
(sudo cp kylin-assistant.mo /usr/share/locale/zh_CN/LC_MESSAGES/)




FT Version:
changelog like this:
kylin-assistant (1.0.0kord) juniper; urgency=low

DEBUG:
gdb python
set args start_sessiondbus.py
run
