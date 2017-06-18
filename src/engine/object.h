#ifndef OBJECT_H
#define OBJECT_H

#include "vector3d.h"

#include <QObject>
#include <QString>
#include <QOpenGLTexture>


class Object: public QObject
{
    Q_OBJECT
public:
    Object(QObject *p = 0);
    Object(float = 0.0, float = 0.0, float = 0.0, QObject *p = 0);

    ~Object();

    virtual void draw() {}

    void drawTexture();

    void clearTexture();
    QString getTexturePath();
    void setTexture(QString image_path);

    bool lock();

    void setLock(bool);

    Vector3D position;
    QOpenGLTexture *texture;

public slots:
    void locked();
    void unlocked();
    void locked(bool);

private:

    bool v_lock;
    QString texture_path;

};

#endif // OBJECT_H
