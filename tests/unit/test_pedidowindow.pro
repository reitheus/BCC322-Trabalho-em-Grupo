QT += core gui widgets testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_pedidowindow

INCLUDEPATH += \
    ../src/views \
    ../src/services \
    ../src/models

SOURCES += \
    test_pedidowindow.cpp \
    ../src/views/pedidowindow.cpp \
    ../src/views/reservawindow.cpp \
    ../src/models/pedido.cpp

HEADERS += \
    ../src/views/pedidowindow.h \
    ../src/views/reservawindow.h \
    ../src/services/IPedidoService.h \
    ../src/models/pedido.h

FORMS += \
    ../src/views/pedidowindow.ui \
    ../src/views/reservawindow.ui