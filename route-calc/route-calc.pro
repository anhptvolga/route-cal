# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = route-calc
DESTDIR = ../Win32/Release
QT += core widgets gui
CONFIG += release
DEFINES += WIN64 QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(route-calc.pri)
TRANSLATIONS += route-calc_en.ts \
    route-calc_ru.ts
win32:RC_FILE = route-calc.rc
