QT += core gui widgets testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_mainwindow

INCLUDEPATH += \
    ../src/views \
    ../src/services \
    ../src/models

SOURCES += \
    test_mainwindow.cpp \
    ../src/views/mainwindow.cpp \
    ../src/views/pedidowindow.cpp \
    ../src/models/pedido.cpp

HEADERS += \
    ../src/views/mainwindow.h \
    ../src/views/pedidowindow.h \
    ../src/services/IPedidoService.h \
    ../src/models/pedido.h

FORMS += \
    ../src/views/mainwindow.ui \
    ../src/views/pedidowindow.ui