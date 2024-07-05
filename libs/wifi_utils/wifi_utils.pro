TEMPLATE = lib
CONFIG += staticlib
QT -= gui
CONFIG += c++11
TARGET = wifi_utils
DESTDIR = $$PWD/../../

DEFINES += WIFI_UTILS_LIB

HEADERS += \
  wifi_utils.h

SOURCES += \
  wifi_utils.cpp

DEFINES += QT_DEPRECATED_WARNINGS
