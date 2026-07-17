QT += core testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_pedidoserviceimpl

SOURCES += \
    test_pedidoserviceimpl.cpp \
    ../src/services/pedidoserviceImpl.cpp \
    ../src/models/pedido.cpp

HEADERS += \
    ../src/services/pedidoserviceImpl.h \
    ../src/services/IPedidoService.h \
    ../src/services/IEstoqueService.h \
    ../src/models/pedido.h