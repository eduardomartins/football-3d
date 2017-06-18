#include "object.h"


Object::Object(QObject *p):
    QObject(p)
{
    texture = NULL;
    texture_path = "";
    position = Vector3D(0.0, 0.0, 0.0);
}

Object::Object(float x, float y, float z, QObject *p):
    QObject(p)
{
    texture = NULL;
    texture_path = "";
    position = Vector3D(x, y, z);
}


Object::~Object()
{
    delete texture;
}


void Object::setTexture(QString image_path)
{
    if(image_path != "")
    {
        texture_path = image_path;
        texture = new QOpenGLTexture(QImage(image_path).mirrored());
    }
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

void Object::locked()
{
    v_lock = true;
}


void Object::unlocked()
{
    v_lock = false;
}

void Object::locked(bool v)
{
    v_lock = v;
}

void Object::setLock(bool v)
{
    v_lock = v;
}

bool Object::lock()
{
    return v_lock;
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

