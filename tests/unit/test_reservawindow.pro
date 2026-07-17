QT += core gui widgets testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_reservawindow

INCLUDEPATH += \
    ../src/views \
    ../src/services \
    ../src/models

SOURCES += \
    test_reservawindow.cpp \
    ../src/views/reservawindow.cpp \
    ../src/views/pedidowindow.cpp \
    ../src/models/pedido.cpp

HEADERS += \
    ../src/views/reservawindow.h \
    ../src/views/pedidowindow.h \
    ../src/services/IPedidoService.h \
    ../src/models/pedido.h

FORMS += \
    ../src/views/reservawindow.ui \
    ../src/views/pedidowindow.ui