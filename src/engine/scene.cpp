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
#include <QDebug>


Room::Room(float base, float largura, float altura):
    Object(1.0, 1.0, 1.0)
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


Room::~Room()
{

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

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

// Campo

Campo::Campo(float base, float largura, QString texture_path):
    Object(1.0, 1.0, 1.0)
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
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

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

Floor::Floor(float base, float largura, QString texture_path):
    Object(1.0, 1.0, 1.0)
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

Crowd::Crowd(float base, float largura, QString texture_path):
    Object(1.0, 1.0, 1.0)
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
        {0.0, 16.0},
        {0.0, 0.0},
        {4.0, 0.0},
        {4.0, 16.0},
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

    if(count > 25){
        fator = 1.1;
        count = 0;
    } else {
        fator = 1.0;
        count++;
    }

    for(int i = 0; i < 4; i++){
        glPushMatrix();

        translate(location[i][0] * largura, 400.0, location[i][1] * base);

        if(location[i][3] != 0.0)
            glRotated(270.0, 0.0, 1.0, 0.0);

        rotateXY(location[i][2]);

        glFlush();
        // Draw object
        glBegin(GL_POLYGON);
        glNormal3f(0.0, 1.0, 0.0);


        for(int j = 0; j < 4; j++)
        {
            glTexCoord2f(texCoord[j][0] * fator, texCoord[j][1] * fator);
            glVertex3f(coordenates[j][0] * 3500.0, coordenates[j][1], coordenates[j][2] * 800.0);
        }
        glEnd();

        glPopMatrix();
        glFlush();
    }
    glDisable(GL_TEXTURE_2D);
}

// Player


Player::Player(float base, float largura, float altura, QString texture_path):
    Object(1.0, 1.0, 1.0)
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
    this->base = base;
    this->largura = largura;
    this->altura = altura;
    setTexture(texture_path);
}

void Player::draw(float x, float y, float z) {

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
        translate(x, z, y);

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
