isEmpty(PREFIX) {
  PREFIX = /usr/local
}

TEMPLATE = aux

QMAKE_RESOURCE_FLAGS += -root .

# Install

#install_resources.path = $$PREFIX/share/youker-assistant/
install_resources.path = /usr/share/youker-assistant/
install_resources.files = .
INSTALLS = install_resources

RESOURCES +=

lupdate_only{
    SOURCES = *.qml \
              func/*.qml \
              func/bars/*.qml \
              func/cleaner/*.qml \
              func/common/*.qml \
              func/info/*.qml \
              func/others/*.qml \
              func/page/*.qml \
              func/settings/*.qml
}
