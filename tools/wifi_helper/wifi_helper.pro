QT -= gui
CONFIG += c++11
TARGET = wifi_helper
DESTDIR = $$PWD/../../

LIBS += \
    -L$$PWD/../../../qt-egui/ \
    -lwifi_utils \

INCLUDEPATH += \
    $$PWD \
    $$PWD/../../libs/wifi_utils \

SOURCES += \
  main.cpp

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
