#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <QObject>

class Vector3D : public QObject
{
    Q_OBJECT
public:
    explicit Vector3D(QObject *parent = 0);
    Vector3D(float x, float y, float z);

    float &operator[](int index);
    float operator[](int index) const;

    Vector3D operator*(float scale) const;
    Vector3D operator/(float scale) const;
    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D operator-() const;

    const Vector3D &operator*=(float scale);
    const Vector3D &operator/=(float scale);
    const Vector3D &operator+=(const Vector3D &other);
    const Vector3D &operator-=(const Vector3D &other);

    float magnitude() const;
    float magnitudeSquared() const;
    Vector3D normalize() const;
    float dot(const Vector3D &other) const;
    Vector3D cross(const Vector3D &other) const;

signals:

public slots:

private:
    float x;
    float y;
    float z;
};

#endif // VECTOR3D_H
