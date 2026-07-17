QT += testlib core

CONFIG += console c++17
CONFIG -= app_bundle

TEMPLATE = app
TARGET = test_produto

SOURCES += \
    test_produto.cpp \
    ../src/models/produto.cpp

HEADERS += \
    ../src/models/produto.h