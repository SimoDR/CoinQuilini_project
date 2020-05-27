TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        data.cpp \
        main.cpp \
        outofboundexception.cpp

HEADERS += \
    data.h \
    outofboundexception.h
