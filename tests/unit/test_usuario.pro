QT += testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_usuario

SOURCES += \
    test_usuario.cpp \
    ../src/models/usuario.cpp

HEADERS += \
    ../src/models/usuario.h