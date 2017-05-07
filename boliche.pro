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

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = water-simulation
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/core/vector3d.cpp \
    src/engine/camera.cpp \
    src/engine/scene.cpp \
    src/core/particle.cpp \
    src/engine/phisics.cpp \
    src/core/ball.cpp \
    src/engine/character.cpp \
    src/engine/glwidget.cpp

HEADERS  += src/mainwindow.h \
    src/core/vector3d.h \
    src/engine/camera.h \
    src/engine/scene.h \
    src/core/particle.h \
    src/engine/phisics.h \
    src/core/ball.h \
    src/engine/character.h \
    src/engine/glwidget.h

FORMS += src/mainwindow.ui


LIBS += -lglut -lGLU
