TEMPLATE = aux

inst1.files += ../backends/youker-assistant-daemon/data/youkersystem
inst1.path = /usr/bin
inst2.files += ../backends/youker-assistant-daemon/data/youkersession
inst2.path = /usr/bin
inst3.files += ../backends/youker-assistant-daemon/data/com.youker-assistant.daemon.policy
inst3.path = /usr/share/polkit-1/actions/
inst4.files += ../backends/youker-assistant-daemon/data/com.ubuntukylin_tools.daemon.service
inst4.path = /usr/share/dbus-1/system-services/
inst5.files += ../backends/youker-assistant-daemon/data/youker-assistant-daemon.conf
inst5.path = /etc/dbus-1/system.d/
inst6.files += ../backends/youker-assistant-daemon/src/
inst6.path = /usr/lib/python2.7/dist-packages/youker-assistant-daemon/

INSTALLS += inst1 \
    inst2 \
    inst3 \
    inst4 \
    inst5 \
    inst6
