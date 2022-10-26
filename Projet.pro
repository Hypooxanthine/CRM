QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console
CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contactmanager.cpp \
    date.cpp \
    interaction.cpp \
    contact.cpp \
    interactionmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    todo.cpp \
    todomanager.cpp \
    unit_tests.cpp

HEADERS += \
    contact.h \
    contactmanager.h \
    date.h \
    datelib.h \
    interaction.h \
    interactionmanager.h \
    mainwindow.h \
    manager.h \
    todo.h \
    contact.h \
    mainwindow.h \
    todomanager.h \
    unit_tests.h

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
