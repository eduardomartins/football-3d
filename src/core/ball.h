#ifndef BALL_H
#define BALL_H

#include <QObject>

#include "vector3d.h"


class Ball : public QObject
{
    Q_OBJECT
public:
    explicit Ball(QObject *parent = 0);

signals:

public slots:

private:
    Vector3D velocity; // Velocidade
    Vector3D posistion; // Posição
    float radius; // Raio
};

#endif // BALL_H
