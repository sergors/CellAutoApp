
#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>


class GLScene : public QGLWidget
{
protected:
    void initializeGL();
    void resizeGL(int weigth, int height);
    void paintGL();

public:
    GLScene(QWidget *parent = 0);
};


