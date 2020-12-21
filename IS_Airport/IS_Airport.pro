QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AuthWindow.cpp \
    DataBases.cpp \
    EditPassWindow.cpp \
    EditUserWindow.cpp \
    MainWindow.cpp \
    ManageRoutesWindow.cpp \
    MyInfoWindow.cpp \
    Passenger.cpp \
    PassengersBase.cpp \
    PassesViewWindow.cpp \
    RegistryWindow.cpp \
    Route.cpp \
    RoutesBase.cpp \
    RoutesViewWindow.cpp \
    Ticket.cpp \
    TicketRequestWindow.cpp \
    TicketsBase.cpp \
    TicketsViewWindow.cpp \
    User.cpp \
    UsersBase.cpp \
    UsersViewWindow.cpp \
    main.cpp

HEADERS += \
    AuthWindow.h \
    DataBases.h \
    EditPassWindow.h \
    EditUserWindow.h \
    MainWindow.h \
    ManageRoutesWindow.h \
    MyInfoWindow.h \
    Passenger.h \
    PassengersBase.h \
    PassesViewWindow.h \
    RegistryWindow.h \
    Route.h \
    RoutesBase.h \
    RoutesViewWindow.h \
    Ticket.h \
    TicketRequestWindow.h \
    TicketsBase.h \
    TicketsViewWindow.h \
    User.h \
    UsersBase.h \
    UsersViewWindow.h

FORMS += \
    AuthWindow.ui \
    EditPassWindow.ui \
    EditUserWindow.ui \
    MainWindow.ui \
    ManageRoutesWindow.ui \
    MyInfoWindow.ui \
    PassesViewWindow.ui \
    RegistryWindow.ui \
    RoutesViewWindow.ui \
    TicketRequestWindow.ui \
    TicketsViewWindow.ui \
    UsersViewWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
