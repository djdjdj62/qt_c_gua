QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form0.cpp \
    main.cpp \
    mainwindow.cpp \
    play.cpp

HEADERS += \
    form0.h \
    mainwindow.h \
    play.h

FORMS += \
    form0.ui \
    mainwindow.ui \
    play.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    all_gua.qrc \
    image.qrc \
    main_icon.qrc \
    play_data.qrc

DISTFILES +=


RC_ICONS = main_data/aubergine.ico
