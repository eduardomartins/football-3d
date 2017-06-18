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

#include "scene.h"

#include <math.h>

#include <QDebug>
#define TO_RADIANS(X) X * PI * 1.0/180.15151


Room::Room(float base, float largura, float altura, QObject *p):
    Object(p)
  ,textureCoord
{
{{2.5, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {2.5, 1.0}}, // Direita
{{1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}}, // Teto
{{0.0, 1.0}, {0.0, 0.0}, {3.5, 0.0}, {3.5, 1.0}}, // Frente
{{2.5, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {2.5, 1.0}}, // Esquerda
{{10.0, 0.0}, {0.0, 0.0}, {0.0, 20.0}, {10.0, 20.0}}, // Piso
{{0.0, 1.0}, {0.0, 0.0}, {3.5, 0.0}, {3.5, 1.0}}, // Fundo
       }
  ,cube
{
{{ -1, -1, -1 }, { +1, -1, -1 }, { +1, +1, -1 }, { -1, +1, -1 }}, // Direita
{{ -1, +1, -1 }, { +1, +1, -1 }, { +1, +1, +1 }, { -1, +1, +1 }}, // Teto
{{ -1, +1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { -1, +1, -1 }}, // Frente
{{ -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 }}, // Esquerda
{{ -1, -1, -1 }, { +1, -1, -1 }, { +1, -1, +1 }, { -1, -1, +1 }}, // Piso
{{ +1, +1, +1 }, { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }}, // Fundo
       }
  , faces
{
        DIREITA,
        TETO,
        FRENTE,
        ESQUERDA,
        PISO,
        FUNDO,
        }
{
    this->base = base;
    this->altura = altura;
    this->largura = largura;
}



void Room::draw() {
    glPushMatrix();
    for(int i = 0; i < 6; i++){
        if (textures.value(faces[i]) != NULL){
            drawTexture(faces[i]);
            glBegin(GL_POLYGON);
            glNormal3f(0.0, 1.0, 0.0);

            for(int j = 0; j < 4; j++)
            {
                glTexCoord2f(textureCoord[faces[i]][j][0], textureCoord[faces[i]][j][1]);
                glVertex3f(cube[i][j][0] * base, cube[i][j][1] * altura, cube[i][j][2] * largura);
            }
            glEnd();
        }
    }
    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);

}

void Room::setTexture(QString image_path, Room::PARTES parte)
{
    textures_paths[parte] = image_path;
    textures[parte] = new QOpenGLTexture(QImage(image_path).mirrored());
}

void Room::clearTexture()
{
    for(int i = 0; i < textures.size();i++){
        delete textures[faces[i]];
        textures[faces[i]] = NULL;
    }
}

QString Room::getTexturePath(Room::PARTES parte)
{
    return textures_paths[parte];
}


void Room::drawTexture(Room::PARTES parte)
{

    if(textures[parte] != NULL)
    {
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, textures[parte]->textureId());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    }
}

Room::~Room()
{
    clearTexture();
}

// Campo

Campo::Campo(float base, float largura, QString texture_path, QObject *p):
    Object(p)
  ,coordenates
{{ -1, -1, -1 }, { +1, -1, -1 }, { +1, -1, +1 }, { -1, -1, +1 }} // Piso
{
    this->base = base;
    this->largura = largura;
    setTexture(texture_path);
}

void Campo::draw() {

    float texCoord[4][2] = {
        {0.0, 1.0},
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
    };

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Draw object
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for(int j = 0; j < 4; j++)
    {
        glTexCoord2f(texCoord[j][0], texCoord[j][1]);
        glVertex3f(coordenates[j][0] * base, coordenates[j][1], coordenates[j][2] * largura);
    }
    glEnd();

    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}


// Flooor

Floor::Floor(float base, float largura, QString texture_path, QObject *p):
    Object(p)
  ,coordenates
{{ -1, -1, -1 }, { +1, -1, -1 }, { +1, -1, +1 }, { -1, -1, +1 }} // Piso
{
    this->base = base;
    this->largura = largura;
    setTexture(texture_path);
}

void Floor::draw() {

    float texCoord[4][2] = {
        {0.0, 30.0},
        {0.0, 0.0},
        {30.0, 0.0},
        {30.0, 30.0},
    };

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTranslated(0.0, -150.0, 0.0);

    // Draw object
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for(int j = 0; j < 4; j++)
    {
        glTexCoord2f(texCoord[j][0], texCoord[j][1]);
        glVertex3f(coordenates[j][0] * base, coordenates[j][1], coordenates[j][2] * largura);
    }
    glEnd();

    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}

// Crowd

Crowd::Crowd(float base, float largura, QString texture_path, QObject *p):
    Object(p)
  ,coordenates
{{ -1, -1, -1 }, { +1, -1, -1 }, { +1, -1, +1 }, { -1, -1, +1 }} // Piso
{
    this->base = base;
    this->largura = largura;
    setTexture(texture_path);
    count = 0.0;
}

void Crowd::draw() {

    float fator = 1.0;

    float texCoord[4][2] = {
        {8.0, 0.0},
        {0.0, 0.0},
        {0.0, 2.0},
        {8.0, 2.0},
    };

    float location[4][4] = {
        // X , Y , rot XY,
        {0.0, 2.7, -33.0, 0.0},
        {0.0, -2.7, 33.0, 0.0},
        {1.5, 0.0, 33.0, 90.0},
        {-1.5, 0.0, -33.0, -90.0},
    };

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    count = (count + 1) % 201;

    if(count > 100)
        fator = 1.02;
    else
        fator = 1.0;


    for(int i = 0; i < 4; i++){
        glPushMatrix();

        glTranslatef(location[i][0] * largura, 400.0, location[i][1] * base);


        if(location[i][3] != 0.0)
            glRotated(270.0, 0.0, 1.0, 0.0);

        glRotated(location[i][2], 1.0, 0.0, 0.0);

        glFlush();
        // Draw object
        glBegin(GL_POLYGON);
        glNormal3f(0.0, 1.0, 0.0);

        for(int j = 0; j < 4; j++)
        {
            glTexCoord2f(texCoord[j][0] * fator, texCoord[j][1]);
            glVertex3f(coordenates[j][0] * 3500.0, coordenates[j][1], coordenates[j][2] * 800.0);
        }
        glEnd();

        glPopMatrix();
        glFlush();
    }
    glDisable(GL_TEXTURE_2D);
}

// Player

Player::Player(float base, float largura, float altura, int id, QObject *p):
    Object(p)
  ,coordenates
{
{{ -1, -1, -1 }, { +1, -1, -1 }, { +1, +1, -1 }, { -1, +1, -1 }}, // Direita
{{ -1, +1, -1 }, { +1, +1, -1 }, { +1, +1, +1 }, { -1, +1, +1 }}, // Teto
{{ -1, +1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { -1, +1, -1 }}, // Frente
{{ -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 }}, // Esquerda
{{ -1, -1, -1 }, { +1, -1, -1 }, { +1, -1, +1 }, { -1, -1, +1 }}, // Piso
{{ +1, +1, +1 }, { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }}, // Fundo
       }
{
    this->id = id;
    this->base = base;
    this->largura = largura;
    this->altura = altura;
}

void Player::setId(int id)
{
    this->id = id;
}

int Player::getId()
{
    return id;
}



void Player::draw()
{
    float texCoord[4][2] = {
        {1.0, 0.0},
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 1.0},
    };

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Draw object
    for(int i = 0; i < 6; i++){
        glPushMatrix();
        glTranslatef(position.getX(), position.getZ(), position.getY());

        glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);

        for(int j = 0; j < 4; j++)
        {
            glTexCoord2f(texCoord[j][0], texCoord[j][1]);
            glVertex3f(coordenates[i][j][0] * base, coordenates[i][j][1] * altura, coordenates[i][j][2] * largura);
        }

        glEnd();
        glPopMatrix();
        glFlush();
    }
    glDisable(GL_TEXTURE_2D);
}

void Player::movePlayer(int sentido)
{
    if (!lock()) {
        position.setX(position.getX() + (sentido * 55.0));

        if (position.getX() > 875.0)
            position.setX(875.0);

        if (position.getX() < -875.0)
            position.setX(-875.0);
    }
}


void Player::ballOnGoal(float x, float y, float z)
{

    if ((position[1] < 0.0 ? y < position[1] : y > position[1])) // Bola passou ?
    {
        if (x >= (position[0] - base) * 1.2 && x <= (position[0] + base) * 1.2) {

            if ((x <= position[0] - base * 0.75) || (x >=  position[0] + base * 0.75))
                emit defendeBall(1.517, 0.517);
            else if ((x <= position[0] - base * 0.3) || (x >=  position[0] + base * 0.3))
                emit defendeBall(0.917, 1.17);
            else
                emit defendeBall(1.0117, 1.0517);

        } else {
            emit takeGoal(id);
        }
    }
}


// Ball

Ball::Ball(float raio, QString texture_path, QObject *p):
    Object(p)
{
    this->raio = raio;
    quadric = gluNewQuadric();
    setTexture(texture_path);
}


void Ball::repositBall(int id)
{
    start(id);
}

void Ball::ballWasDefended(float x, float y)
{
    velocidade.setX(velocidade[0] * x);
    velocidade.setY(velocidade[1] * y);
}



void Ball::updatePosition()
{
    if (!lock()) {

        if (position.getX() > 1000.0 || position.getX() < -1000.0)
            velocidade.setX(-1.015 * velocidade[0]);

        position.setX(position.getX() + velocidade.getX());

        if (position.getY() > 1500.0 || position.getY() < -1500.0) {
            emit onGoal(position[0], position[1], position[2]);
            velocidade.setY(-1.015  * velocidade[1]);
        }

        if (fabs(velocidade[0]) < 1.0 || fabs(velocidade[1]) < 1.0) {
            float mag = sqrt(pow(velocidade[0], 2.0) + pow(velocidade[2], 2.0));
            velocidade.setX(mag * velocidade[0]/fabs(velocidade[0]));
            velocidade.setY(mag * velocidade[1]/fabs(velocidade[1]));
        }

        if (fabs(velocidade[0]) > 20.0)
            velocidade.setX(20 * (velocidade[0]/fabs(velocidade[0])));

        if (fabs(velocidade[1]) > 20.0)
            velocidade.setY(20 * (velocidade[1]/fabs(velocidade[1])));

        position.setY(position.getY() + velocidade.getY());

        position.setZ(position.getZ() + velocidade.getZ());
    }
}

void Ball::start(int player)
{
    if (!lock()) {

        position.setX(0.0)->setY(0.0);

        srand (time(NULL));

        if (player == -1)
            player = (rand() % 2) + 1;

        float radians;

        switch (player) {
        case 2:
            srand (time(NULL));
            radians = (rand() % 120) + 210.5;
            break;

        case 1:
            srand (time(NULL));
            radians = (rand() % 12) + 30.5;
            break;
        }

        velocidade.setX(15.0 * cos(TO_RADIANS(radians)))->setY(15.0 * sin(TO_RADIANS(radians)));

    }
}


void Ball::draw() {

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    updatePosition();

    glTranslatef(position.getX(), position.getZ(), position.getY());

    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, raio, 60, 60);
    glFlush();
    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}
