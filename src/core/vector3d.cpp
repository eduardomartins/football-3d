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

#include "vector3d.h"
#include <math.h>


// Contructors
Vector3D::Vector3D(QObject *parent):
    QObject(parent)
{
    setX(0.0)->setY(0.0)->setZ(0.0);
}

Vector3D::Vector3D(const Vector3D &other, QObject *parent):
    QObject(parent)
{
    setX(other.getX())->setY(other.getY())->setZ(other.getZ());
}


Vector3D::Vector3D(float x, float y, float z, QObject *parent):
    QObject(parent)
{
    setX(x)->setY(y)->setZ(z);
}

// Sets
Vector3D *Vector3D::setX(float X){
    x = X;
    return this;
}

Vector3D *Vector3D::setY(float Y){
    y = Y;
    return this;
}

Vector3D *Vector3D::setZ(float Z){
    z = Z;
    return this;
}


// Gets
float Vector3D::getX(void){
    return x;
}

float Vector3D::getY(void){
    return y;
}

float Vector3D::getZ(void){
    return z;
}

float Vector3D::getX(void) const{
    return x;
}

float Vector3D::getY(void) const{
    return y;
}

float Vector3D::getZ(void) const{
    return z;
}


// Operators

Vector3D & Vector3D::operator =(const Vector3D &other){
    this->setX(other.getX())->setY(other.getY())->setZ(other.getZ());
    return *this;
}


float & Vector3D::operator [](int index){
    switch (index) {
    case 0:
        return x;
        break;

    case 1:
        return y;
        break;

    case 2:
        return z;
        break;

    default:
        throw std::out_of_range ("This index is out of range");
        break;
    };
}


float Vector3D::operator [](int index) const{
    switch (index) {
    case 0:
        return x;
        break;

    case 1:
        return y;
        break;

    case 2:
        return z;
        break;

    default:
        throw std::out_of_range ("This index is out of range");
        break;
    };
}


Vector3D Vector3D::operator *(float scale) const {
    return Vector3D(x * scale, y * scale, z * scale);
}

Vector3D Vector3D::operator /(float scale) const {
    return Vector3D(x/scale, y/scale, z/scale);
}

Vector3D Vector3D::operator +(float scale) const {
    return Vector3D(x + scale, y + scale, z + scale);
}

Vector3D Vector3D::operator +(const Vector3D &other) const {
    return Vector3D(x + other.getX(), y + other.getY(), z + other.getZ());
}


Vector3D Vector3D::operator-(void) const{
    return Vector3D(-x, -y, -z);
}


Vector3D Vector3D::operator -(float scale) const {
    return Vector3D(x - scale, y - scale, z - scale);
}

Vector3D Vector3D::operator -(const Vector3D &other) const {
    return Vector3D(x - other.getX(), y - other.getY(), z - other.getZ());
}


const Vector3D & Vector3D::operator *=(float scale) {
    x *= scale;
    y *= scale;
    z *= scale;

    return *this;
}

const Vector3D & Vector3D::operator /=(float scale) {
    x /= scale;
    y /= scale;
    z /= scale;

    return *this;
}

const Vector3D & Vector3D::operator +=(float scale) {
    x += scale;
    y += scale;
    z += scale;

    return *this;
}

const Vector3D & Vector3D::operator -=(float scale) {
    x -= scale;
    y -= scale;
    z -= scale;

    return *this;
}

float Vector3D::magnitude() const {
    return sqrt(magnitudeSquared());
}


float Vector3D::magnitudeSquared() const {
    return x*x + y*y + z*z;
}

Vector3D Vector3D::normalize() const {
    float m = magnitude();
    return Vector3D(x/m, y/m, z/m);
}


float Vector3D::dot(const Vector3D &other) const {
    return (other.getX() * x + other.getY() * y + other.getZ() * z);
}

Vector3D Vector3D::cross(const Vector3D &other) const {
    return Vector3D(
        y * other.getY() - z * other.getY(),
        z * other.getX() - x * other.getZ(),
        x * other.getY() - y * other.getX()
    );
}

QDebug operator<<(QDebug dbg, const Vector3D &other) {
    dbg.nospace() << "(" << other.getX() << ", " << other.getY() << ", " << other.getZ() << ")";

    return dbg.space();
}

Vector3D rotate(Vector3D v, Vector3D axis, float degrees) {
    axis = axis.normalize();
    float radians = degrees * PI / 180;
    float s = sin(radians);
    float c = cos(radians);
    return v * c + axis * axis.dot(v) * (1 - c) + v.cross(axis) * s;
}

Vector3D adjParticlePos(Vector3D pos) {
    return rotate(pos, Vector3D(1, 0, 0), -30);
}
