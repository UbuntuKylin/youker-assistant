TEMPLATE = aux

inst1.files += ../backends/youker-assistant-daemon/src/
inst1.path = /usr/lib/python2.7/dist-packages/youker-assistant-daemon/
inst2.files += ../backends/youker-assistant-daemon/data/beautify/autostart/
inst2.path = /var/lib/youker-assistant-daemon/
inst3.files += ../backends/youker-assistant-daemon/data/beautify/plymouth/
inst3.path = /var/lib/youker-assistant-daemon/
inst4.files += ../backends/youker-assistant-daemon/data/beautify/sound-theme/
inst4.path = /var/lib/youker-assistant-daemon/
inst5.files += ../backends/youker-assistant-daemon/data/ubuntukylin-default-settings.ini
inst5.path = /var/lib/youker-assistant-daemon/

INSTALLS += inst1 \
    inst2 \
    inst3 \
    inst4 \
    inst5
