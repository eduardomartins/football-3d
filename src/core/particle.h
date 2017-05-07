#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include "vector3d.h"

class Particle : public QObject
{
    Q_OBJECT
public:
    explicit Particle(QObject *parent = 0);

signals:

public slots:

private:
    Vector3D position;
    Vector3D velocity;
    // color
    float timeAlive;
    float lifeSpan;
};

#endif // PARTICLE_H
