QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_globaltest.cpp \
    ../IS_Airport/Passenger.cpp \
    ../IS_Airport/Ticket.cpp \
    ../IS_Airport/User.cpp

HEADERS += \
    ../IS_Airport/Passenger.h \
    ../IS_Airport/Ticket.h \
    ../IS_Airport/User.h
