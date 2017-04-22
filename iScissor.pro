
QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iScissor
TEMPLATE = app


SOURCES += main.cpp\
        iScissor.cpp \
    ImgLabel.cpp \
    LiveWireDP.cpp

HEADERS  += iScissor.h \
    ImgLabel.h \
    LiveWireDP.h \
    ui_iScissor.h \
    intelligentscissor.h

FORMS    += iScissor.ui

RESOURCES += tumblr_test.jpg
