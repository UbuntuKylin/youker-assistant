TEMPLATE = aux

inst1.files += ../backends/youker-assistant-daemon/data/youkersystem
inst1.path = /usr/bin
inst2.files += ../backends/youker-assistant-daemon/data/youkersession
inst2.path = /usr/bin
inst3.files += ../backends/youker-assistant-daemon/data/youkersudo
inst3.path = /usr/bin
inst4.files += ../backends/youker-assistant-daemon/data/com.youker-assistant.daemon.policy
inst4.path = /usr/share/polkit-1/actions/
inst5.files += ../backends/youker-assistant-daemon/data/com.ubuntukylin_tools.daemon.service
inst5.path = /usr/share/dbus-1/system-services/
inst6.files += ../backends/youker-assistant-daemon/data/youker-assistant-daemon.conf
inst6.path = /etc/dbus-1/system.d/
inst7.files += ../backends/youker-assistant-daemon/src/
inst7.path = /usr/lib/python2.7/dist-packages/youker-assistant-daemon/
inst8.files += ../backends/youker-assistant-daemon/data/beautify/autostart/
inst8.path = /usr/share/youker-assistant-daemon/
inst9.files += ../backends/youker-assistant-daemon/data/beautify/plymouth/
inst9.path = /usr/share/youker-assistant-daemon/
inst10.files += ../backends/youker-assistant-daemon/data/beautify/sound-theme/
inst10.path = /usr/share/youker-assistant-daemon/
inst11.files += ../backends/youker-assistant-daemon/data/processmanager/
inst11.path = /usr/share/youker-assistant-daemon/

INSTALLS += inst1 \
    inst2 \
    inst3 \
    inst4 \
    inst5 \
    inst6 \
    inst7 \
    inst8 \
    inst9 \
    inst10 \
    inst11
