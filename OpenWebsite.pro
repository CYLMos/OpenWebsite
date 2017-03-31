TEMPLATE = app

QT += qml quick
QT += sql
QT += core
QT += gui

CONFIG += c++11

SOURCES += main.cpp \
    DatabaseManage.cpp \
    ListViewModel.cpp \
    StartBrowser.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    DatabaseManage.h \
    ListViewModel.h \
    StartBrowser.h
