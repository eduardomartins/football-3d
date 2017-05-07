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

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

#include <QObject>
#include <QDebug>


const double PI = 3.14159265359;


class Vector3D : public QObject
{
    Q_OBJECT
public:
    explicit Vector3D(QObject *parent = 0);
    Vector3D(const Vector3D &other, QObject *parent = 0);
    Vector3D(float x, float y, float z, QObject *parent = 0);

    Vector3D *setX(float x);
    Vector3D *setY(float Y);
    Vector3D *setZ(float Z);

    float getX(void);
    float getY(void);
    float getZ(void);

    float getX(void) const;
    float getY(void) const;
    float getZ(void) const;

    float &operator[](int index);
    float operator[](int index) const;

    Vector3D operator*(float scale) const;

    Vector3D operator/(float scale) const;

    Vector3D operator+(float scale) const;
    Vector3D operator+(const Vector3D &other) const;

    Vector3D operator-(void) const;
    Vector3D operator-(float scale) const;
    Vector3D operator-(const Vector3D &other) const;

    Vector3D &operator=(const Vector3D &other);

    const Vector3D &operator+=(float scale);
    const Vector3D &operator-=(float scale);
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

QDebug operator<<(QDebug dbg, const Vector3D &other);

Vector3D rotate(Vector3D v, Vector3D axis, float degrees);

Vector3D adjParticlePos(Vector3D pos);

#endif // VECTOR3D_H
