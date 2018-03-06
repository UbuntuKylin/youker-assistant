TEMPLATE = aux

inst1.files += ../backends/kylin-assistant-daemon/src/
inst1.path = /usr/lib/python3/dist-packages/kylin-assistant-daemon/
inst2.files += ../backends/kylin-assistant-daemon/data/beautify/autostart/
inst2.path = /var/lib/kylin-assistant-daemon/
inst3.files += ../backends/kylin-assistant-daemon/data/beautify/plymouth/
inst3.path = /var/lib/kylin-assistant-daemon/
inst4.files += ../backends/kylin-assistant-daemon/data/beautify/sound-theme/
inst4.path = /var/lib/kylin-assistant-daemon/
inst5.files += ../backends/kylin-assistant-daemon/data/ubuntukylin-default-settings.ini
inst5.path = /var/lib/kylin-assistant-daemon/

INSTALLS += inst1 \
    inst2 \
    inst3 \
    inst4 \
    inst5
