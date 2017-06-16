#include "object.h"

#include <cmath>
#include <ctime>
#include <GL/gl.h>
#include <stdlib.h>
#include <GL/glu.h>

#include <QMessageBox>
#include <QDebug>


Object::Object(GLfloat X, GLfloat Y, GLfloat Z)
{

    x = X;
    y = Y;
    z = Z;

    scale_x = 1;
    scale_y = 1;
    scale_z = 1;

    rotate_x = 0;
    rotate_y = 0;
    rotate_z = 0;

    texture = NULL;
    texture_path = "";
}

void Object::setScale(GLfloat sx,GLfloat sy,GLfloat sz){
    if(sx > 0 && sy > 0 && sz > 0) {
        scale_x = sx;
        scale_y = sy;
        scale_z = sz;
    }
    glScalef(scale_x, scale_y, scale_z);
}


void Object::setPosX(GLfloat x)
{
    this->x = x;
}

void Object::setPosY(GLfloat y)
{
    this->y = y;
}

void Object::setPosZ(GLfloat z)
{
    this->z = z;
}

void Object::setRotX(GLfloat rotx)
{
    rotate_x = rotx;
}

void Object::setRotY(GLfloat roty)
{
    rotate_y = roty;
}

void Object::setRotZ(GLfloat rotz)
{
    rotate_z = rotz;
}

void Object::getRot(float &rx, float &ry, float &rz)
{
    rx = rotate_x;
    ry = rotate_y;
    rz = rotate_z;
}

void Object::getPos(float &px, float &py, float &pz)
{
    px = x;
    py = y;
    pz = z;
}


void Object::setTexture(QString image_path)
{
    texture_path = image_path;
    texture = new QOpenGLTexture(QImage(image_path).mirrored());
}

void Object::clearTexture()
{
    texture_path = "";
    delete texture;
    texture = NULL;
}

QString Object::getTexturePath()
{
    return texture_path;
}

void Object::setColorRGB(float r, float g, float b)
{

    this->r = (GLfloat) (this->r + r);
    this->g = (GLfloat) (this->g + g);
    this->b = (GLfloat) (this->b + b);

    while (this->r > 255.0)
        this->r = (GLfloat) (this->r - 255.0);

    while (this->g > 255.0)
        this->g = (GLfloat) (this->g - 255.0);

    while (this->b > 255.0)
        this->b = (GLfloat) (this->b - 255.0);
}

void Object::getColorRGB(float &r, float &g, float &b)
{
    r = this->r;
    g = this->g;
    b = this->b;
}

void Object::drawTexture(){
    if(texture != NULL){
        glEnable(GL_TEXTURE_2D);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BGRA);

        glBindTexture(GL_TEXTURE_2D, texture->textureId());

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}


void Object::rotateXY(float degree) {
    glRotatef(degree, 1, 0, 0);
    glFlush();
}

void Object::rotateXZ(float degree) {
    glRotatef(degree, 0, 0, 1);
    glFlush();
}

void Object::rotateYZ(float degree) {
    glRotatef(degree, 0, 1, 0);
    glFlush();
}

void Object::translate(float x, float y, float z) {
    glTranslatef(x, y, z);
    glFlush();
}
