QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    showwidget.cpp

HEADERS += \
    mainwindow.h \
    qcustomplot.h \
    showwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPtUtilsLib
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lEbInstallerLib
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvBase
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvBuffer
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvDevice
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvGenICam
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvGUI_VC8
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvGUI_VC9
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvGUI_VC10
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvGUIUtils
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvPersistence
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvSerial
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvStream
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvStreamRaw
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvTransmitterRaw
#win32: LIBS += -L$$PWD/eBus/Libraries/ -lPvVirtualDevice

#INCLUDEPATH += $$PWD/eBus/Includes
#DEPENDPATH += $$PWD/eBus/Includes
