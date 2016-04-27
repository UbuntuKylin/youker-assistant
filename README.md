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
