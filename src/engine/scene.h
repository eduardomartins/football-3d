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
#include "vector3d.h"


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


class Room: public Object
{
    Q_OBJECT
public:

    explicit Room(float = 0.0, float = 0.0, float = 0.0, QObject *p = 0);

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

class Campo: public Object
{
    Q_OBJECT
public:

    explicit Campo(float = 100.0, float = 100.0, QString = "", QObject *p = 0);

    void draw();


private:

    float coordenates[4][3];
    float base, largura;

};

class Floor: public Object
{
    Q_OBJECT
public:
    explicit Floor(float = 100.0, float = 100.0, QString = "", QObject *p = 0);

    void draw();


private:

    float coordenates[4][3];
    float base, largura;

};

class Crowd: public Object
{
    Q_OBJECT
public:

    explicit Crowd(float = 100.0, float = 100.0, QString = "", QObject *p = 0);

    void draw();

private:

    int count;
    float base, largura;
    float coordenates[4][3];

};

class Player: public Object
{
    Q_OBJECT
public:

    explicit Player(float = 100.0, float = 100.0, float = 100.0, int id = 0, QObject *p = 0);

    void setId(int);

    int getId();

    void draw();

signals:
    void defendeBall(float, float);
    void takeGoal(int);

public slots:
    void movePlayer(int);
    void ballOnGoal(float, float, float);

private:

    int id;
    float coordenates[6][4][3];
    float base, largura, altura;
};

class Ball: public Object
{
    Q_OBJECT
public:
    explicit Ball(float = 100.0, QString = "", QObject *p = 0);

    void draw();

    Vector3D velocidade;

    void start(int = -1);

public slots:

    void ballWasDefended(float x, float y);
    void repositBall(int id);

signals:
    void onGoal(float, float, float);

private:

    void updatePosition();

    float raio;
    GLUquadricObj *quadric;

};

#endif // SCENE_H
