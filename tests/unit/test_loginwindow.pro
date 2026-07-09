QT += core gui widgets testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_loginwindow

INCLUDEPATH += \
    ../src/views \
    ../src/interfaces \
    ../src/models

SOURCES += \
    test_loginwindow.cpp \
    ../src/views/loginwindow.cpp \
    ../src/views/mainwindow.cpp \
    ../src/views/pedidowindow.cpp \
    ../src/models/pedido.cpp

HEADERS += \
    ../src/views/loginwindow.h \
    ../src/views/mainwindow.h \
    ../src/views/pedidowindow.h \
    ../src/interfaces/ipedidoservice.h \
    ../src/models/pedido.h

FORMS += \
    ../src/views/loginwindow.ui \
    ../src/views/mainwindow.ui \
    ../src/views/pedidowindow.ui