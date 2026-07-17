QT += core testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_funcional_fluxo_pedido

INCLUDEPATH += \
    ../src/services \
    ../src/models

SOURCES += \
    test_funcional_fluxo_pedido.cpp \
    ../src/services/estoqueserviceImpl.cpp \
    ../src/services/pedidoserviceImpl.cpp \
    ../src/models/produto.cpp \
    ../src/models/pedido.cpp

HEADERS += \
    ../src/services/IEstoqueService.h \
    ../src/services/IPedidoService.h \
    ../src/services/estoqueserviceImpl.h \
    ../src/services/pedidoserviceImpl.h \
    ../src/models/produto.h \
    ../src/models/pedido.h