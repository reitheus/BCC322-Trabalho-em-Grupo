QT += core gui widgets testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_funcional_interface

INCLUDEPATH += \
    ../src/views \
    ../src/services \
    ../src/interfaces \
    ../src/models

SOURCES += \
    test_funcional_interface.cpp \
    ../src/views/loginwindow.cpp \
    ../src/views/mainwindow.cpp \
    ../src/views/pedidowindow.cpp \
    ../src/views/reservawindow.cpp \
    ../src/services/estoqueserviceImpl.cpp \
    ../src/services/pedidoserviceImpl.cpp \
    ../src/models/pedido.cpp \
    ../src/models/produto.cpp

HEADERS += \
    ../src/views/loginwindow.h \
    ../src/views/mainwindow.h \
    ../src/views/pedidowindow.h \
    ../src/views/reservawindow.h \
    ../src/services/estoqueserviceImpl.h \
    ../src/services/pedidoserviceImpl.h \
    ../src/interfaces/ipedidoservice.h \
    ../src/interfaces/iestoqueservice.h \
    ../src/models/pedido.h \
    ../src/models/produto.h

FORMS += \
    ../src/views/loginwindow.ui \
    ../src/views/mainwindow.ui \
    ../src/views/pedidowindow.ui \
    ../src/views/reservawindow.ui