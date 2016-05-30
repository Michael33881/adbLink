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
    uuiddialog.cpp \
    llamadialog.cpp \
    creditsdialog.cpp \
    adblogdialog.cpp \
    cifsdialog.cpp \
    kodidialog.cpp \
    unlockdialog.cpp \
    bootmenudialog.cpp \
    unbootdialog.cpp \
    datadialog.cpp \
    mediacenterdialog.cpp \ 
    firestarterdialog.cpp \
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
    uuiddialog.h \
    llamadialog.h \
    creditsdialog.h \
    adblogdialog.h \  
    cifsdialog.h \
    kodidialog.h \
    unlockdialog.h \
    bootmenudialog.h \
    unbootdialog.h \
    datadialog.h \
    mediacenterdialog.h \ 
    firestarterdialog.h \
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
    uuiddialog.ui \
    llamadialog.ui \
    creditsdialog.ui \
    adblogdialog.ui \
    cifsdialog.ui \
    kodidialog.ui \
    unlockdialog.ui \
    bootmenudialog.ui \
    unbootdialog.ui \
    datadialog.ui \
    mediacenterdialog.ui \
    firestarterdialog.ui \
    restdialog.ui \
    backupdialog.ui \
    cachedialog.ui \
    keyboarddialog.ui \
    klogdialog.ui

RC_FILE = adbLink.rc

ICON = adbLink.icns

QMAKE_MAC_SDK = macosx10.11

OTHER_FILES +=