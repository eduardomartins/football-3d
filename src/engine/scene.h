/*
 * MIT License
 *
 * Copyright (c) 2017 Eduardo Sant'Anna Martins <eduardo@eduardomartins.site>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SCENE_H
#define SCENE_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <QVector>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>


#define NORM_HEX(V) V/255.0

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);

    //virtual void draw();

signals:

public slots:

};


class Room: public QObject {
    Q_OBJECT

public:

    explicit Room(QObject *parent = 0);

    ~Room();

    void draw();

    void drawTextures();

private:

    int cube[6][4][3];

    QOpenGLTexture *texture;

    QOpenGLBuffer vbo;
};

#endif // SCENE_H
