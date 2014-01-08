TEMPLATE = aux

inst1.files += ../backends/youker-assistant-daemon/data/youkersystem
inst1.path = /usr/bin
inst2.files += ../backends/youker-assistant-daemon/data/youkersession
inst2.path = /usr/bin
inst3.files += ../backends/youker-assistant-daemon/keyrings/ubuntukylin-archive-keyring.gpg
inst3.path = /usr/share/keyrings/
inst4.files += ../backends/youker-assistant-daemon/src/
inst4.path = /usr/lib/python2.7/dist-packages/youker-assistant-daemon/
inst5.files += ../backends/youker-assistant-daemon/data/beautify/autostart/
inst5.path = /var/lib/youker-assistant-daemon/
inst6.files += ../backends/youker-assistant-daemon/data/beautify/plymouth/
inst6.path = /var/lib/youker-assistant-daemon/
inst7.files += ../backends/youker-assistant-daemon/data/beautify/sound-theme/
inst7.path = /var/lib/youker-assistant-daemon/
inst8.files += ../backends/youker-assistant-daemon/data/processmanager/
inst8.path = /var/lib/youker-assistant-daemon/

INSTALLS += inst1 \
    inst2 \
    inst3 \
    inst4 \
    inst5 \
    inst6 \
    inst7 \
    inst8
