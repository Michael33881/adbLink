#-------------------------------------------------
#
# Project created by QtCreator 2014-05-21T01:43:07
#
#-------------------------------------------------

QT       += core gui sql network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adbLink
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog2.cpp \
    helpdialog.cpp \
    uninstalldialog.cpp \
    preferencesdialog.cpp \
    usbfiledialog.cpp \
    adblogdialog.cpp \
    kodidialog.cpp \
    bootmenudialog.cpp \
    datadialog.cpp \
    restdialog.cpp \
    backupdialog.cpp \
    cachedialog.cpp \
    filedownloader.cpp \
    keyboarddialog.cpp \
    klogdialog.cpp


RESOURCES = adbLink.qrc

HEADERS  += mainwindow.h \
    dialog2.h \
    helpdialog.h \
    uninstalldialog.h \
    preferencesdialog.h \
    usbfiledialog.h \
    creditsdialog.h \
    adblogdialog.h \  
    cifsdialog.h \
    kodidialog.h \
    bootmenudialog.h \
    datadialog.h \
    restdialog.h \
    backupdialog.h \
    cachedialog.h \
    filedownloader.h \
    keyboarddialog.h \
    klogdialog.h

FORMS    += mainwindow.ui \
    dialog2.ui \
    helpdialog.ui \
    uninstalldialog.ui \
    preferencesdialog.ui \
    usbfiledialog.ui \
    adblogdialog.ui \
    kodidialog.ui \
    datadialog.ui \
    restdialog.ui \
    backupdialog.ui \
    cachedialog.ui \
    keyboarddialog.ui \
    klogdialog.ui

RC_FILE = adbLink.rc

ICON = adbLink.icns

QMAKE_MAC_SDK = macosx10.11

OTHER_FILES +=
