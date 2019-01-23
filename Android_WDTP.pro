#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T08:40:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Android_WDTP
TEMPLATE = app


SOURCES += main.cpp\
    Adb_Progress.cpp \
    Dialog_AdbProcess.cpp \
    Dialog_ProgressBar.cpp \
    ThreadCommon.cpp \
    ThreadADBSlots.cpp \
    AES/aes.cpp \
    httpApi/httpApi.cpp \
    ListProtocol.cpp

HEADERS  += \
    Adb_Progress.h \
    Dialog_AdbProcess.h \
    Dialog_ProgressBar.h \
    ThreadCommon.h \
    ThreadADBSlots.h \
    AES/aes.h \
    httpApi/httpApi.h \
    ListProtocol.h

FORMS    += Dialog_AdbProcess.ui \
    Dialog_ProgressBar.ui
