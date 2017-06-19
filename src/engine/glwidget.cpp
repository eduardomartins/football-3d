#include "glwidget.h"

#include <QDebug>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    setFormat(format);

    lock = true;

    rotate_camera = 0.0;

    camera = Camera();
    ball = new Ball(60.0);
    floor = new Floor(7200.0, 7200.0);
    campo = new Campo(1100.0, 1700.0);
    torcida = new Crowd(1100.0, 1900.0);
    room = new Room(1200.0, 1800.0, 100.0);
    stadium = new Room(3500.0, 3600.0, 800.0);
    player1 = new Player(200.0, 30.0, 100.0, 1);
    player2 = new Player(200.0, 30.0, 100.0, 2);

    game = new Game(player2, ball);

}

GLWidget::~GLWidget()
{
    mouse3d->stop();
    mouse3d->wait();
    delete room;
    delete texture;
}

void GLWidget::resizeGL(int w, int h)
{
    view_w = w;
    view_h = h;
    camera.setViewport(w, h);
}

void GLWidget::light()
{
    GLfloat diffuse[4]={0.7,0.7,0.7,0.0};
    GLfloat specular[4]={1.0, 1.0, 1.0, 0.0};
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT4, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT5, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT6, GL_SPECULAR, specular );
    glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT7, GL_SPECULAR, specular );
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}


void GLWidget::updateCamera()
{
    camera.setAngle(angle);
    camera.setAngleV(anglev);
    emit angleChanged(angle);
    emit angleVChanged(anglev);
}


void GLWidget::initializeGL()
{

    initializeOpenGLFunctions();

    init();
    initMap();

    mouse3d = new Mouse3D();
    connect(mouse3d, SIGNAL(finished()), mouse3d, SLOT(deleteLater()));

    mouse3d->start();
}

void GLWidget::startMatch(bool state)
{
    angle = 0.0;
    anglev = 65.0;
    radius = 3000;
    rotate_camera = 0.0;

    lock = state;

    ball->setLock(lock);
    player1->setLock(lock);
    player2->setLock(lock);


}

void GLWidget::finishMatch(bool state)
{
    angle = 45.0;
    anglev = 30.0;
    rotate_camera = 0.5;

    ball->position.setX(0.0)->setY(0.0);

    lock = !state;
}


void GLWidget::draw()
{
    // Dome
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->textureId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glRotatef(270, 1.0f, 0.0f, 0.0f);
    glRotatef(rotate, 0.0f, 0.0f, 1.0f);

    rotate += 0.02;
    rotate *= 1.0001;

    if (rotate > 360)
        rotate = 0.1;

    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, 7100, 60, 60);
    glFlush();
    glPopMatrix();
    glFlush();
    glDisable(GL_TEXTURE_2D);

    // camera

    angle = angle + rotate_camera;

    if (angle > 360)
        angle = 0.0;

}


void GLWidget::paintGL()
{

    lightController();
    drawPrimitive();
    animate();
    updateCamera();
}



void GLWidget::init()
{

    texture = new QOpenGLTexture(QImage(QString(":/textures/skyline.jpg")).mirrored());

    room->setTexture(QString(":/textures/pastilha.jpg"), Room::PISO);
    room->setTexture(QString(":/textures/propoganda.jpeg"), Room::FRENTE);
    room->setTexture(QString(":/textures/propoganda.jpeg"), Room::FUNDO);
    room->setTexture(QString(":/textures/propoganda.jpeg"), Room::DIREITA);
    room->setTexture(QString(":/textures/propoganda.jpeg"), Room::ESQUERDA);

    stadium->setTexture(QString(":/textures/pastilha.jpg"), Room::PISO);
    stadium->setTexture(QString(":/textures/arch.jpg"), Room::FRENTE);
    stadium->setTexture(QString(":/textures/arch.jpg"), Room::FUNDO);
    stadium->setTexture(QString(":/textures/arch.jpg"), Room::DIREITA);
    stadium->setTexture(QString(":/textures/arch.jpg"), Room::ESQUERDA);

    stadium->position.setZ(100.0);


    campo->setTexture(QString(":/textures/grass.jpg"));
    player1->setTexture(QString(":/textures/spfc.jpg"));
    player2->setTexture(QString(":/textures/csc.jpg"));
    ball->setTexture(QString(":/textures/adidas_ball.jpg"));
    floor->setTexture(QString(":/textures/terrain.jpg"));
    torcida->setTexture(QString(":/textures/crowd.jpg"));

    floor->position.setX(0.0)->setY(20.0)->setZ(0.0);

    player1->position.setX(0.0)->setY(+1500.0)->setZ(+75.0);

    player2->position.setX(0.0)->setY(-1500.0)->setZ(+75.0);

    room->position.setX(0.0)->setY(90.0)->setZ(0.0);

    ball->position.setZ(75.0);

    ball->start();

    connect(ball, SIGNAL(onGoal(float,float)), player1, SLOT(ballOnGoal(float,float)));
    connect(ball, SIGNAL(onGoal(float,float)), player2, SLOT(ballOnGoal(float,float)));
    connect(player1, SIGNAL(defendeBall(float,float)), ball, SLOT(ballWasDefended(float, float)));
    connect(player2, SIGNAL(defendeBall(float,float)), ball, SLOT(ballWasDefended(float, float)));
    connect(player1, SIGNAL(takeGoal(int)), ball, SLOT(repositBall(int)));
    connect(player2, SIGNAL(takeGoal(int)), ball, SLOT(repositBall(int)));

    connect(player1, SIGNAL(updatePlayer()), player2, SLOT(restartPosition()));
    connect(player2, SIGNAL(updatePlayer()), player1, SLOT(restartPosition()));

    quadric = gluNewQuadric();

    angle = 45.0;
    anglev = 30.0;
    fovy = 1.0;
    radius = 4000;
    max_radius = 7000;

    rotate = 1.0;

    sens = 0.2;

    mouse_xini = 1;
    mouse_yini = 1;
    motion_angle = 0;

    camera.setAngle(angle);
    camera.setAngleV(anglev);
    camera.setRadius(radius);
    camera.setFovy(fovy);

    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
}

void GLWidget::initMap(){

    glClearColor(135.0/255.0, 206.0/255.0, 250/255.0, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
}

void GLWidget::animate()
{

}

void GLWidget::drawPrimitive()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw();

    player1->setLock(lock);
    player2->setLock(lock);
    ball->setLock(lock);

    floor->draw();
    campo->draw();
    room->draw();
    stadium->draw();
    torcida->draw();
    player2->draw();
    player1->draw();
    ball->draw();

    update();
}

void GLWidget::lightController()
{
    glPushMatrix();

    light();

    GLfloat ambient[4]={0.8,0.8,0.8, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);

    int i;

    if(default_light)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    for(i=0;i<=LIGHT_LIMIT-1;i++){
        switch(i){
        case 0:
            if(light_used[i]) {
                glEnable(GL_LIGHT1);
                glDisable(GL_LIGHT0);
            }
            else glDisable(GL_LIGHT1);
            break;
        case 1:
            if(light_used[i]) {
                glEnable(GL_LIGHT2);
                glDisable(GL_LIGHT0);
            }
            else glDisable(GL_LIGHT2);
            break;
        case 2:
            if(light_used[i]) {
                glEnable(GL_LIGHT3);
                glDisable(GL_LIGHT0);
            }
            else glDisable(GL_LIGHT3);
            break;
        case 3:
            if(light_used[i]) {
                glEnable(GL_LIGHT4);
                glDisable(GL_LIGHT0);
            }
            else glDisable(GL_LIGHT4);
            break;
        case 4:
            if(light_used[i]) {
                glEnable(GL_LIGHT5);
                glDisable(GL_LIGHT0);
            }
            else glDisable(GL_LIGHT5);
            break;
        case 5:
            if(light_used[i]) {
                glEnable(GL_LIGHT6);
                glDisable(GL_LIGHT0);
            }
            else glDisable(GL_LIGHT6);
            break;
        case 6:
            if(light_used[i]) {
                glEnable(GL_LIGHT7);
                glDisable(GL_LIGHT0);
            }
            else glDisable(GL_LIGHT7);
            break;
        }
    }
    glPopMatrix();
    update();
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!lock) {
        if(event->x() > mouse_xini)
            angle += 10 * sens;

        if(event->x() < mouse_xini)
            angle -= 10 * sens;

        if(event->y()>mouse_yini) {
            if (anglev < 90) anglev += 10*sens;
        }

        if(event->y()<mouse_yini) {
            if (anglev > -90) anglev -= 10*sens;
        }

        mouse_xini = event->x();
        mouse_yini = event->y();

        if (angle <= 0)
            angle = angle + 360;
        else if (angle >= 360)
            angle = angle - 360;

        if (anglev <= -90)
            anglev = -89;
        else if (anglev >= 90)
            anglev = 89;

        update();
    }

}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if (!lock){
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;

        if (numSteps == 1) {

            radius *= 0.95;

            if(radius < 100)
                radius = 100;

            camera.setRadius(radius);

            emit radiusChanged(radius);
        } else {

            radius *= 1.05;

            if(radius > max_radius)
                radius = max_radius;

            camera.setRadius(radius);

            emit radiusChanged(radius);
        }
    }
    event->accept();

}


void GLWidget::setAngle(int a)
{
    angle = a;
}

void GLWidget::setAngleV(int av)
{
    anglev = av;
}

void GLWidget::setRadius(int z)
{
    camera.setRadius(z);
    radius=z;
}
