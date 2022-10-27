QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console
CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += \
    include \
    libs

HEADERS += \
    include/DataStructures/contact.h \
    include/DataStructures/contactmanager.h \
    include/DataStructures/date.h \
    include/DataStructures/interaction.h \
    include/DataStructures/interactionmanager.h \
    include/DataStructures/manager.h \
    include/DataStructures/todo.h \
    include/DataStructures/todomanager.h \
    include/UnitTests/unit_tests.h \
    include/datelib.h \
    include/mainwindow.h

SOURCES += \
    src/DataStructures/contact.cpp \
    src/DataStructures/contactmanager.cpp \
    src/DataStructures/date.cpp \
    src/DataStructures/interaction.cpp \
    src/DataStructures/interactionmanager.cpp \
    src/DataStructures/manager.cpp \
    src/DataStructures/todo.cpp \
    src/DataStructures/todomanager.cpp \
    src/UnitTests/unit_tests.cpp \
    src/main.cpp \
    src/mainwindow.cpp
