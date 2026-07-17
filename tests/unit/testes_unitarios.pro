QT += core gui widgets testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = testes_unitarios

INCLUDEPATH += \
    ../../src/models \
    ../../src/services \
    ../../src/interfaces \
    ../../src/views

SOURCES += \
    main.cpp \
    test_usuario.cpp \
    test_produto.cpp \
    test_pedido.cpp \
    test_estoqueserviceimpl.cpp \
    test_pedidoserviceimpl.cpp \
    test_loginwindow.cpp \
    test_mainwindow.cpp \
    test_pedidowindow.cpp \
    test_reservawindow.cpp \
    ../../src/models/usuario.cpp \
    ../../src/models/produto.cpp \
    ../../src/models/pedido.cpp \
    ../../src/services/estoqueserviceImpl.cpp \
    ../../src/services/pedidoserviceImpl.cpp \
    ../../src/views/loginwindow.cpp \
    ../../src/views/mainwindow.cpp \
    ../../src/views/pedidowindow.cpp \
    ../../src/views/reservawindow.cpp

HEADERS += \
    ../../src/models/produto.h \
    ../../src/models/pedido.h \
    ../../src/services/estoqueserviceImpl.h \
    ../../src/services/pedidoserviceImpl.h \
    ../../src/interfaces/IEstoqueService.h \
    ../../src/interfaces/ipedidoservice.h \
    ../../src/views/loginwindow.h \
    ../../src/views/mainwindow.h \
    ../../src/views/pedidowindow.h \
    ../../src/models/usuario.h \
    ../../src/views/reservawindow.h

FORMS += \
    ../../src/views/loginwindow.ui \
    ../../src/views/mainwindow.ui \
    ../../src/views/pedidowindow.ui \
    ../../src/views/reservawindow.ui