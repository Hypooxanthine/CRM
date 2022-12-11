QT       += core gui
QT       += sql

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
    include/ExtData/JsonInterface.h \
    include/ExtData/dbinterface.h \
    include/HUD/contactexplorer.h \
    include/HUD/contacttab.h \
    include/HUD/contacttoolbar.h \
    include/HUD/mainwindow.h \
    include/HUD/todoentry.h \
    include/HUD/todoexplorer.h \
    include/UnitTests/unit_tests.h \

SOURCES += \
    src/DataStructures/contact.cpp \
    src/DataStructures/contactmanager.cpp \
    src/DataStructures/date.cpp \
    src/DataStructures/interaction.cpp \
    src/DataStructures/interactionmanager.cpp \
    src/DataStructures/manager.cpp \
    src/DataStructures/todo.cpp \
    src/DataStructures/todomanager.cpp \
    src/ExtData/JsonInterface.cpp \
    src/ExtData/dbinterface.cpp \
    src/HUD/contactexplorer.cpp \
    src/HUD/contacttab.cpp \
    src/HUD/contacttoolbar.cpp \
    src/HUD/mainwindow.cpp \
    src/HUD/todoentry.cpp \
    src/HUD/todoexplorer.cpp \
    src/UnitTests/unit_tests.cpp \
    src/main.cpp \

FORMS +=
