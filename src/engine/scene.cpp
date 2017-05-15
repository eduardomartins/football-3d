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

Scene::Scene(QObject *parent) : QObject(parent)
{

}


Room::Room(QObject *parent) : QObject(parent)
  , cube {

       // Piso
{ { -1, -1, -1 }, { +1, -1, -1 }, { +1, -1, +1 }, { -1, -1, +1 } },

       // Teto
{ { -1, +1, -1 }, { +1, +1, -1 }, { +1, +1, +1 }, { -1, +1, +1 } },

       // Paredes
{ { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } },
{ { -1, -1, -1 }, { +1, -1, -1 }, { +1, +1, -1 }, { -1, +1, -1 } },
{ { +1, +1, +1 }, { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 } },
{ { -1, +1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { -1, +1, -1 } },
       }
{
   //memset(texture, 0, sizeof(texture));

}


Room::~Room()
{
    delete texture;
    vbo.destroy();
}


void Room::draw() {
    glColor3f(NORM_HEX(200), NORM_HEX(0), NORM_HEX(0));

    glBegin(GL_QUADS);
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            glVertex3f(cube[i][j][0], cube[i][j][1], cube[i][j][2]);
        }
    }
    glEnd();
}


void Room::drawTextures()
{

    texture = new QOpenGLTexture(QImage("://wood_texture.bmp").mirrored());

    QVector<GLfloat> vertData;

    for(int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; ++j) {
            // vertex position
            vertData.append(0.2 * cube[i][j][0]);
            vertData.append(0.2 * cube[i][j][1]);
            vertData.append(0.2 * cube[i][j][2]);
            // texture coordinate
            vertData.append(j == 0 || j == 3);
            vertData.append(j == 0 || j == 1);
        }
    }

    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

}
