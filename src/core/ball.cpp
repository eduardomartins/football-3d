#include "ball.h"

Ball::Ball(QObject *parent) : QObject(parent)
{

}

void Ball::setVelocity(Vector3D velo)
{
    m_velocity = velo;
}

Vector3D Ball::velocity()
{
    return m_velocity;
}

void Ball::setPosition(Vector3D pos)
{
    m_posistion = pos;
}

Vector3D Ball::position()
{
    return m_posistion;
}

void Ball::setRadius(float r)
{
    m_radius = r;
}

float Ball::radius()
{
    return m_radius;
}
