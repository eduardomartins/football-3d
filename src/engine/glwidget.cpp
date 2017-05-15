#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent):
    //QOpenGLWidget(parent)
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    //connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    xRot = 0;
    yRot = 0;
    zRot = 0;

    bowling = new Room(this);
}

GLWidget::~GLWidget()
{

}


void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
}

void GLWidget::initializeGL()
{
    /*glClearColor(0.6, 0.7, 0.8, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);*/

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor(0.6, 0.7, 0.8, 1.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(xRot / 1.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 1.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 1.0, 0.0, 0.0, 1.0);

    bowling->draw();
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPosition.x();
    int dy = event->y() - lastPosition.y();

    qDebug() << dx << dy;

    if (event->buttons() & Qt::LeftButton) {

        setXRotation(normalize(xRot + dy));
        setYRotation(normalize(yRot + dx));

        lastPosition = event->pos();
    }

}


static int normalize(int delta)
{

    return (int) (delta * 0.3);
}

// Extra
static void qNormalizeAngle(int &angle)
{

    qDebug() << "ANGLO" << angle;
    if (angle < 0)
        angle = -1 * (angle % 360);
    else
        angle = angle % 360;
}
