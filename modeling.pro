#-------------------------------------------------
#
# Project created by QtCreator 2017-06-10T16:44:59
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -LC:\Qt\Qt5.5.1\5.5\mingw492_32\lib\libQt5OpenGL.a -lopengl32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = modeling
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    point.cpp \
    plotwidget.cpp \
    paintwidget.cpp \
    rainbow.cpp \
    qcustomplot.cpp \
    scheme.cpp \
    simplex.cpp

HEADERS  += window.h \
    point.h \
    plotwidget.h \
    paintwidget.h \
    rainbow.h \
    qcustomplot.h \
    scheme.h \
    simplex.h
