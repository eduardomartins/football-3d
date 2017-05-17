#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <QDebug>
#include <QWidget>
#include <QtOpenGL>
#include <QGLWidget>
#include <QMouseEvent>


#include "scene.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void paintGL();

    void resizeGL(int w, int h);

    void initializeGL();

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

private:
    Room *bowling;

    QPoint lastPosition;

    int xRot, yRot, zRot;

    GLfloat mat_specular[4];
    GLfloat mat_shininess[1];
    GLfloat light_position[4];
};


#endif // GLWIDGET_H
