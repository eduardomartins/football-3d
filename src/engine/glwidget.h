#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <QWidget>
#include <QOpenGLWidget>



class GLWidget : public QOpenGLWidget
{
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

public slots:

protected:
    void paintGL();

    void resizeGL(int w, int h);

    void initializeGL();

private:

};

#endif // GLWIDGET_H
