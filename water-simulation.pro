#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T15:49:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = water-simulation
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/core/vector3d.cpp \
    src/core/kdtree.cpp \
    src/engine/camera.cpp \
    src/engine/scene.cpp

HEADERS  += src/mainwindow.h \
    src/core/vector3d.h \
    src/core/kdtree.h \
    src/engine/camera.h \
    src/engine/scene.h

FORMS += src/mainwindow.ui
