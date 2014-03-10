#!/bin/sh
backupPath="/var/lib/youker-assistant-daemon/"
backendPath="/usr/lib/python2.7/dist-packages/youker-assistant-daemon/"
cd `dirname $0`

cp ./dbus/com.ubuntukylin.youker.service /usr/share/dbus-1/system-services/ 
echo "Copy .service file to /usr/share/dbus-1/system-services/"

cp ./dbus/com.ubuntukylin.youker.policy /usr/share/polkit-1/actions/
echo "Copy .policy file to /usr/share/polkit-1/actions/"

cp ./dbus/com.ubuntukylin.youker.conf /etc/dbus-1/system.d/
echo "Copy .conf file to /etc/dbus-1/system.d/"

if [ ! -d "$backendPath" ]; then
    cp -rf ./src /usr/lib/python2.7/dist-packages/youker-assistant-daemon/
    echo "Copy backend folder to /usr/lib/python2.7/dist-packages/youker-assistant-daemon/"
else
    rm -rf "$bakendPath"
    cp -rf ./src /usr/lib/python2.7/dist-packages/youker-assistant-daemon/
    echo "Copy backend folder to /usr/lib/python2.7/dist-packages/youker-assistant-daemon/"
fi

if [ ! -d "$backupPath" ]; then
    cp -rf ./data/beautify /var/lib/youker-assistant-daemon/
    cp -rf ./data/processmanager /var/lib/youker-assistant-daemon/
    echo "Copy backup folder to /var/lib/youker-assistant-daemon/"
fi

rm -f /usr/bin/youker-assistant-backend.py
echo "Remove /usr/bin/youker-assistant-backend.py"

rm -f /usr/bin/youker-assistant-session.py
echo "Remove /usr/bin/youker-assistant-session.py"

chmod +x "$backendPath"/src/start_systemdbus.py
ln -s "$backendPath"/src/start_systemdbus.py  /usr/bin/youker-assistant-backend.py

chmod +x "$backendPath"/src/start_sessiondbus.py
ln -s "$backendPath"/src/start_sessiondbus.py  /usr/bin/youker-assistant-session.py

echo "Build symbol link for service file"
echo "^^ Now, You can run the program in QtCreator!"
