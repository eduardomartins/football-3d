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

#include "object.h"


#include <GL/gl.h>
#include <GL/glu.h>

#include <fstream>
#include <assert.h>


#include <QMap>
#include <QVector>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QGenericMatrix>

#define NORM_HEX(V) V/255.0


class Room: public Object {
public:

    explicit Room(float = 100.0, float = 100.0, float = 100.0);

    ~Room();

    typedef enum {
        DIREITA  = 0,
        TETO     = 1,
        FRENTE   = 2,
        ESQUERDA = 3,
        PISO     = 4,
        FUNDO    = 5,
    } PARTES;

    void draw();
    void clearTexture();
    void drawTexture(Room::PARTES);
    QString getTexturePath(Room::PARTES);
    void setTexture(QString, Room::PARTES);


private:

    float cube[6][4][3];
    float textureCoord[6][4][2];
    float base, largura, altura;

    PARTES faces[6];
    QMap<PARTES, QString> textures_paths;
    QMap<PARTES, QOpenGLTexture *> textures;


};

class Campo: public Object {
public:

    explicit Campo(float = 100.0, float = 100.0, QString = "");

    ~Campo();

    void draw();


private:

    float coordenates[4][3];
    float base, largura;

};

class Floor: public Object {
public:

    explicit Floor(float = 100.0, float = 100.0, QString = "");

    ~Floor();

    void draw();


private:

    float coordenates[4][3];
    float base, largura;

};

class Crowd: public Object {
public:

    explicit Crowd(float = 100.0, float = 100.0, QString = "");

    ~Crowd();

    void draw();


private:

    float coordenates[4][3];
    float base, largura;
    int count;

};

class Player: public Object {
public:

    explicit Player(float = 100.0, float = 100.0, float = 100, QString = "");

    ~Player();

    void draw(float = 0.0, float = 0.0, float = 0.0);


private:

    float coordenates[6][4][3];
    float base, largura, altura;
};



#endif // SCENE_H
