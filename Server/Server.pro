QT += core network
QT -u gui

CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH += include

HEADERS += include/chatserver.h
SOURCES += src/main.cpp \
           src/chatserver.cpp