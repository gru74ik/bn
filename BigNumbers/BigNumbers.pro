TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BigInt.cpp \
    BigFloat.cpp \
    bn_functions.cpp \
    bn_tests.cpp \
    BigFloatTester.cpp

HEADERS += \
    BigInt.h \
    BigFloat.h \
    bn_functions.h \
    bn_tests.h \
    BigFloatTester.h
