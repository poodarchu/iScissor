
QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iScissor
TEMPLATE = app


SOURCES += main.cpp\
        iScissor.cpp \
    my_label.cpp \
    dijkstra.cpp

HEADERS  += iScissor.h \
    my_label.h \
    dijkstra.h \
    ui_iScissor.h \
    intelligentscissor.h
FORMS    += iScissor.ui

#RESOURCES += res_file.qrc
