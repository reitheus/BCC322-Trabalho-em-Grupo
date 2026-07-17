QT += testlib core

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_pedido

SOURCES += \
    test_pedido.cpp \
    ../src/models/pedido.cpp

HEADERS += \
    ../src/models/pedido.h