#ifndef OBJECT_H
#define OBJECT_H

#include <time.h>
#include <GL/gl.h>


#include <QString>
#include <QOpenGLTexture>


class Object
{
public:
    Object(GLfloat = 0.0, GLfloat = 0.0, GLfloat = 0.0);

    void draw(){

    }

    void animate(){

    }

    void drawTexture();

    GLfloat x, y, z;
    GLfloat r, g, b;

    void setPosX(GLfloat);
    void setPosY(GLfloat);
    void setPosZ(GLfloat);

    void setRotX(GLfloat rotx);
    void setRotY(GLfloat roty);
    void setRotZ(GLfloat rotz);

    void rotateXY(float degree);
    void rotateXZ(float degree);
    void rotateYZ(float degree);

    void translate(float, float, float);

    void clearTexture();
    QString getTexturePath();
    void setTexture(QString image_path);

    void getPos(float &px,float &py,float &pz);
    void getRot(float &rx,float &ry,float &rz);

    void setColorRGB(float r, float g, float b);
    void getColorRGB(float &r, float &g, float &b);

    void incScale(GLfloat,GLfloat,GLfloat);
    void decScale(GLfloat,GLfloat,GLfloat);
    void setScale(GLfloat, GLfloat, GLfloat);
    void getScale(float &sx,float &sy,float &sz);


    QOpenGLTexture *texture;

private:

    GLfloat scale_x, scale_y, scale_z;
    GLfloat rotate_x,rotate_y,rotate_z;

    GLfloat arotate_x, arotate_y, arotate_z;

    float px, py, pz;
    float sx, sy, sz;

    QString texture_path;

};

#endif // OBJECT_H
