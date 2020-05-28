TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        calendario.cpp \
	data.cpp \
	outofboundexception.cpp \
        main.cpp

HEADERS += \
    calendario.h \
    data.h \
    outofboundexception.h
