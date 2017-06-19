#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "game.h"
#include "scene.h"
#include "camera.h"
#include "object.h"
#include "mouse3d.h"

#include <cmath>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>
#include <valarray>
#include <iostream>
#include <GL/glu.h>

#include <QDebug>
#include <QThread>
#include <QVector2D>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QWheelEvent>
#include <QBasicTimer>
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>


#define LIGHT_LIMIT 7


class GLWidget : public QOpenGLWidget,  protected QOpenGLFunctions
{
    Q_OBJECT
    Mouse3D *mouse3d;

public:

    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void init();
    void animate();
    void initMap();
    void lightController();
    void drawPrimitive();

    bool default_light;

    Player *player1, *player2;

public slots:

    void setAngle(int);
    void setAngleV(int);
    void setRadius(int);

    void startMatch(bool);
    void finishMatch(bool);

signals:

    void angleChanged(int);
    void angleVChanged(int);
    void radiusChanged(int);


protected:

    void paintGL();
    void initializeGL();
    void resizeGL(int w, int h);

    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void button(int bnum, int bpress);


private:

    void draw();
    void light();
    void updateCamera();

    QPoint lastPosition;

    float sens;
    float max_radius;
    float motion_angle;
    float rotate, rotate_camera;

    GLint primitive;
    GLint view_w, view_h;

    GLfloat fovy;
    GLfloat angle;
    GLfloat anglev;
    GLfloat radius;
    GLfloat r, g, b;


    GLfloat mat_specular[4];
    GLfloat mat_shininess[1];
    GLfloat light_position[4];

    Camera camera;

    int mouse_x,mouse_y;
    int xRot, yRot, zRot;
    int mouse_xini, mouse_yini;
    int mouse_xclick, mouse_yclick;

    char auto_mode;
    char pivot_mode;

    bool lock, started;
    bool light_used[LIGHT_LIMIT];

    QTimer *timer;

    Game *game;
    Ball *ball;
    Floor *floor;
    Campo *campo;
    Crowd *torcida;
    Room *room, *stadium;
    GLUquadricObj *quadric;
    QOpenGLTexture *texture;

};


#endif // GLWIDGET_H
