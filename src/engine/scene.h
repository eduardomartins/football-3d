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
#include <assert.h>
#include <fstream>


#include <QVector>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>


#define NORM_HEX(V) V/255.0

class Image {
    public:
        Image(char* ps, int w, int h);
        ~Image();

        /* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
         * color of each pixel in image.  Color components range from 0 to 255.
         * The array starts the bottom-left pixel, then moves right to the end
         * of the row, then moves up to the next column, and so on.  This is the
         * format in which OpenGL likes images.
         */
        char* pixels;
        int width;
        int height;
};

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

    float cube[6][4][3];
    float colors[6][3];

   GLuint texture;
   Image *image;

    QOpenGLBuffer vbo;
};


//Reads a bitmap image from file.
Image* loadBMP(const char* filename);

GLuint loadTexture(Image* image);

#endif // SCENE_H
