#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T15:49:26
#
#-------------------------------------------------
#
# MIT License
#
# Copyright (c) 2017 Eduardo Sant'Anna Martins <eduardo@eduardomartins.site>

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


QT += core
QT += gui
QT += opengl
QT += widgets
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = boliche.bin

TEMPLATE = app

LIBS += -lGLU -lGL

QT_DEBUG_PLUGINS = 1

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/engine/vector3d.cpp \
    src/engine/camera.cpp \
    src/engine/scene.cpp \
    src/engine/glwidget.cpp \
    src/engine/mouse3d.cpp \
    src/engine/spnav.c \
    src/engine/object.cpp \
    src/engine/game.cpp

HEADERS  += src/mainwindow.h \
    src/engine/vector3d.h \
    src/engine/camera.h \
    src/engine/scene.h \
    src/engine/glwidget.h \
    src/engine/mouse3d.h \
    src/engine/spnav.h \
    src/engine/object.h \
    src/engine/game.h


DESTDIR = bin
OBJECTS_DIR = bin/.obj
MOC_DIR = bin/.moc
RCC_DIR = bin/.rcc
UI_DIR = .ui


debug
{
    DESTDIR = bin/debug
    OBJECTS_DIR = bin/debug/.obj
    MOC_DIR = bin/debug/.moc
    RCC_DIR = bin/debug/.rcc
    UI_DIR = .ui
}

FORMS += src/mainwindow.ui



RESOURCES += \
    media/textures.qrc

