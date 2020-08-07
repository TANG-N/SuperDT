#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T13:35:24
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       += xml
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperDT
TEMPLATE = app

MOC_DIR = temp/moc
RCC_DIR = temp/rcc
UI_DIR = temp/ui
OBJECTS_DIR = temp/obj

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    Form/AdvaForm/TLineEditCardItem.cpp \
    Form/AdvaForm/TListCard.cpp \
    Form/AdvaForm/TTreeCard.cpp \
    Network/CConnectTools.cpp \
    Network/CSerialConnection.cpp \
    Network/CTcpClientConnection.cpp \
    Network/CTcpServerConnection.cpp \
    Network/CUdpConnection.cpp \
    Widget/StatusBar.cpp \
    Widget/TitleBar.cpp \
    main.cpp \
    MainWidget.cpp \
    Widget/TMsgArea.cpp \
    Widget/TTextEditor.cpp \
    Widget/TSettingArea.cpp \
    Application/NetworkApp.cpp \
    General/Log/CLogWin.cpp \
    General/Log/CLogWinForWindow.cpp \
    General/Log/CLogWinForDB.cpp \
    General/Log/CLogWinForTxt.cpp \
    General/Log/CLogWinEnm.cpp \
    Widget/TSettingBtnBar.cpp \
    Form/AdvaForm/TCardTitle.cpp \
    Form/AdvaForm/TComBoxCardItem.cpp \
    Form/AdvaForm/TLockButtonCardItem.cpp \
    Form/AdvaForm/TLoopTextCardItem.cpp \
    Form/AdvaForm/TTriggerCardItem.cpp \
    Form/AdvaForm/TUserCardItem.cpp \
    Application/NetworkData.cpp



HEADERS += \
    Form/AdvaForm/TLineEditCardItem.h \
    Form/AdvaForm/TListCard.h \
    Form/AdvaForm/TTreeCard.h \
    MainWidget.h \
    Network/AbsConnection.h \
    Network/CConnectTools.h \
    Network/CSerialConnection.h \
    Network/CTcpClientConnection.h \
    Network/CTcpServerConnection.h \
    Network/CUdpConnection.h \
    Widget/StatusBar.h \
    Widget/TWindowLayoutDefine.h \
    Widget/TitleBar.h \
    Widget/TMsgArea.h \
    Widget/TTextEditor.h \
    Widget/TSettingArea.h \
    General/Log/clog.h \
    General/Log/CLogWin.h \
    Application/NetworkApp.h \
    General/Log/CLogWin.h \
    General/Log/CLogWinForWindow.h \
    General/Log/CLogWinForDB.h \
    General/Log/CLogWinForTxt.h \
    General/Log/CLogWinEnm.h \
    Widget/TSettingBtnBar.h \
    Form/AdvaForm/TCardTitle.h \
    Form/AdvaForm/TComBoxCardItem.h \
    Form/AdvaForm/TLockButtonCardItem.h \
    Form/AdvaForm/TLoopTextCardItem.h \
    Form/AdvaForm/TTriggerCardItem.h \
    Form/AdvaForm/TUserCardItem.h \
    Application/NetworkData.h


INCLUDEPATH += \
        Widget \
        Form \
        Form/BaseForm \
        Form/AdvaForm \
        General/Log \
        Network \
        General/Database \
        Application


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

#RC_FILE += icon.rc

DISTFILES += \
    General/Log/LogWinConfig.xml \
    Style/SuperDT.qss

