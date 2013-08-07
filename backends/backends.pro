TEMPLATE = aux

inst1.files += ../backends/youker-assistant-daemon/bin/youkersession
inst1.path = /usr/bin
inst2.files += ../backends/youker-assistant-daemon/bin/youkersystem
inst2.path = /usr/bin
inst3.files += ../backends/youker-assistant-daemon/
inst3.path = /usr/lib/python2.7/dist-packages/
inst4.files += ../backends/youker-assistant-daemon/data/youker-assistant-daemon.conf
inst4.path = /etc/dbus-1/system.d/
inst5.files += ../backends/youker-assistant-daemon/data/com.youker_assistant.daemon.service
inst5.path = /usr/share/dbus-1/system-services/
inst6.files += ../backends/youker-assistant-daemon/src/beautify/res/autostart/
inst6.path = /usr/share/youker-assistant-daemon/
inst7.files += ../backends/youker-assistant-daemon/src/beautify/res/plymouth/
inst7.path = /usr/share/youker-assistant-daemon/
inst8.files += ../backends/youker-assistant-daemon/src/beautify/res/plymouth/
inst8.path = /usr/share/youker-assistant-daemon/

INSTALLS += inst1 \
    inst2 \
    inst3 \
    inst4 \
    inst5 \
    inst6 \
    inst7 \
    inst8
