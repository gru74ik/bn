TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BigInt.cpp \
    BigFloat.cpp \
    bn_functions.cpp \
    BigNumber.cpp

HEADERS += \
    BigInt.h \
    BigFloat.h \
    bn_functions.h \
    stdafx.h \
    BigNumber.h
