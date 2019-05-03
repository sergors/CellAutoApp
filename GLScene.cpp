#include "GLScene.h"

GLScene::GLScene(QWidget *parent) : QGLWidget (parent)
{
}

void GLScene::initializeGL()
{
    glClearColor(1.0f, 0.8f, 0.8f, 1.0f);
}

void GLScene::resizeGL(int weight, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glViewport(0, 0, weight, height);
}

void GLScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25f, 0.87f, 0.81f);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, 0.0);

    glEnd();
}
