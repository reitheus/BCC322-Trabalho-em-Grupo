QT += core testlib

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_estoqueserviceimpl

SOURCES += \
    test_estoqueserviceimpl.cpp \
    ../src/services/estoqueserviceImpl.cpp \
    ../src/models/produto.cpp

HEADERS += \
    ../src/services/estoqueserviceImpl.h \
    ../src/services/iestoqueservice.h \
    ../src/models/produto.h