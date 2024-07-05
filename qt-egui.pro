TEMPLATE = subdirs
INCLUDEPATH += $$PWD
CONFIG += ordered
SUBDIRS += \
    $$PWD/libs/libs.pro \
    $$PWD/apps/qt-egui.pro \
    $$PWD/tools/tools.pro

