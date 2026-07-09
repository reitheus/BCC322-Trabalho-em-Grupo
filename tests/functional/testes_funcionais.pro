

```pro
QT += core gui widgets testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = testes_funcionais

INCLUDEPATH += \
    ../../src/views \
    ../../src/services \
    ../../src/interfaces \
    ../../src/models

SOURCES += \
    main.cpp \
    test_funcional_fluxo_pedido.cpp \
    test_funcional_interface.cpp \
    ../../src/views/loginwindow.cpp \
    ../../src/views/mainwindow.cpp \
    ../../src/views/pedidowindow.cpp \
    ../../src/views/reservawindow.cpp \
    ../../src/services/estoqueserviceImpl.cpp \
    ../../src/services/pedidoserviceImpl.cpp \
    ../../src/models/pedido.cpp \
    ../../src/models/produto.cpp

HEADERS += \
    ../../src/views/loginwindow.h \
    ../../src/views/mainwindow.h \
    ../../src/views/pedidowindow.h \
    ../../src/views/reservawindow.h \
    ../../src/interfaces/IEstoqueService.h \
    ../../src/interfaces/ipedidoservice.h \
    ../../src/services/estoqueserviceImpl.h \
    ../../src/services/pedidoserviceImpl.h \
    ../../src/models/pedido.h \
    ../../src/models/produto.h

FORMS += \
    ../../src/views/loginwindow.ui \
    ../../src/views/mainwindow.ui \
    ../../src/views/pedidowindow.ui \
    ../../src/views/reservawindow.ui