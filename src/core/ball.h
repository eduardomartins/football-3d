#ifndef BALL_H
#define BALL_H

#include <QObject>

#include "vector3d.h"


class Ball : public QObject
{
    Q_OBJECT
public:
    explicit Ball(QObject *parent = 0);

    void setVelocity(Vector3D velo);

    Vector3D velocity();

    void setPosition(Vector3D pos);

    Vector3D position();

    void setRadius(float r);

    float radius();


signals:

public slots:

private:
    Vector3D m_velocity; // Velocidade
    Vector3D m_posistion; // Posição
    float m_radius; // Raio
};

#endif // BALL_H
