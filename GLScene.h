
#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include "loadconnector.h"


class GLScene : public QGLWidget
{
    Q_OBJECT
private:
    QTimer *timer;
    LoadConnector *lConn;
    GLfloat quatVertexArray[4][2];
    GLfloat quatColorArray[2][3];
    GLfloat quatIndexArray[10000][4];
protected:
    void initializeGL();
    void resizeGL(int weigth, int height);
    void paintGL();

public:
    GLScene(QWidget *parent);
    ~GLScene();
    void setLoadConnector(LoadConnector *loadConnector);
    void paintRect(float x, float y, float width, float height);
    void drawTestCellAuto();
public slots:
    void startTimer();
    void paintGLSlot();
};


