#include "GLScene.h"

struct CellData {
    GLfloat vertex[4][2];
    GLfloat color[4][3];
    GLbyte index[1][4];
};

GLScene::~GLScene(){}
GLScene::GLScene(QWidget *parent) : QGLWidget (parent)
{
    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(paintGLSlot()));
}

void GLScene::setLoadConnector(LoadConnector *loadConnector) {
    this->lConn = loadConnector;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            this->lConn->getGlobalArea()[i][j] = false;
        }
    }
}

void GLScene::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
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
   /* float rnd = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
    glColor3f(rnd, 1.0f - rnd, abs(0.5f - rnd));
    drawTestCellAuto();*/

    CellData cells[100][100];     //автомат 100x100
                                  //vertex - точки (4 штуки)
                                  //color - 4 цвета RGB
                                  //index - указывает точки по порядку
    GLfloat R = 0.8;
    GLfloat G = 0.4;
    GLfloat B = 0.7;

    GLfloat vertex[100][2];
    GLfloat color [100][3];
    GLbyte  index[25][4];
    GLfloat delta = 0.2;
    int k = 0;

    for(int i = 0; i < 5 ; i++) {
        for(int j = 0; j < 5; j++) {
            if(i == 0 || i == 4) {
                this->lConn->getGlobalArea()[i][j] = true;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            //               x                                   y
            vertex[k + 0][0] = j * delta;       vertex[k + 0][1] = i * delta;        /*левый нижний*/
            vertex[k + 1][0] = (j + 1) * delta; vertex[k + 1][1] = i * delta;        /*правый нижний*/
            vertex[k + 2][0] = (j + 1) * delta; vertex[k + 2][1] = (i + 1) * delta;  /*правый верхний*/
            vertex[k + 3][0] = j * delta;       vertex[k + 3][1] = (i + 1) * delta;  /*левый верхний*/

            if(this->lConn->getGlobalArea()[i][j] == true) {
                R = 0.0;
                G = 0.0;
                B = 1.0;
            } else {
                //фиолетовый
                R = 0.7;
                G = 0.1;
                B = 0.9;
            }

            color[k + 0][0] = R; color[k + 0][1] = G; color[k + 0][2] = B;
            color[k + 1][0] = R; color[k + 1][1] = G; color[k + 1][2] = B;
            color[k + 2][0] = R; color[k + 2][1] = G; color[k + 2][2] = B;
            color[k + 3][0] = R; color[k + 3][1] = G; color[k + 3][2] = B;

            index[k][0] = k;         index[k + 1][1] = k + 1;
            index[k + 2][2] = k + 2; index[k + 3][3] = k + 3;
            k+=4;
        }
    }
    GLfloat vertex2[16][2];
    GLfloat color2[16][3];
    GLbyte  index2[4][4];

    float delta2 = 0.25;
    vertex2[0][0] = 0 * delta2; vertex2[0][1] = 0 * delta2;        /*левый нижний*/
    vertex2[1][0] = 1 * delta2; vertex2[1][1] = 0 * delta2;        /*правый нижний*/
    vertex2[2][0] = 1 * delta2; vertex2[2][1] = 1 * delta2;        /*правый верхний*/
    vertex2[3][0] = 0 * delta2; vertex2[3][1] = 1 * delta2;        /*левый верхний*/

    vertex2[4][0] = 1 * delta2; vertex2[4][1] = 0 * delta2;        /*левый нижний*/
    vertex2[5][0] = 2 * delta2; vertex2[5][1] = 0 * delta2;        /*правый нижний*/
    vertex2[6][0] = 2 * delta2; vertex2[6][1] = 1 * delta2;        /*правый верхний*/
    vertex2[7][0] = 1 * delta2; vertex2[7][1] = 1 * delta2;        /*левый верхний*/

    vertex2[8][0] = 0 * delta2; vertex2[8][1] = 1 * delta2;        /*левый нижний*/
    vertex2[9][0] = 1 * delta2; vertex2[9][1] = 1 * delta2;        /*правый нижний*/
    vertex2[10][0] = 1 * delta2; vertex2[10][1] = 2 * delta2;        /*правый верхний*/
    vertex2[11][0] = 0 * delta2; vertex2[11][1] = 2 * delta2;        /*левый верхний*/

    vertex2[12][0] = 1 * delta2; vertex2[12][1] = 1 * delta2;        /*левый нижний*/
    vertex2[13][0] = 2 * delta2; vertex2[13][1] = 1 * delta2;        /*правый нижний*/
    vertex2[14][0] = 2 * delta2; vertex2[14][1] = 2 * delta2;        /*правый верхний*/
    vertex2[15][0] = 1 * delta2; vertex2[15][1] = 2 * delta2;        /*левый верхний*/

    color2[0][0] = 1.0; color2[0][1] = 0.0; color2[0][2] = 0.0;
    color2[1][0] = 1.0; color2[1][1] = 0.0; color2[1][2] = 0.0;
    color2[2][0] = 1.0; color2[2][1] = 0.0; color2[2][2] = 0.0;
    color2[3][0] = 1.0; color2[3][1] = 0.0; color2[3][2] = 0.0;

    color2[4][0] = 0.1; color2[4][1] = 0.5; color2[4][2] = 0.5;
    color2[5][0] = 0.1; color2[5][1] = 0.5; color2[5][2] = 0.5;
    color2[6][0] = 0.1; color2[6][1] = 0.5; color2[6][2] = 0.5;
    color2[7][0] = 0.1; color2[7][1] = 0.5; color2[7][2] = 0.5;

    color2[8][0] = 0.0; color2[8][1] = 0.0; color2[8][2] = 1.0;
    color2[9][0] = 0.0; color2[9][1] = 0.0; color2[9][2] = 1.0;
    color2[10][0] = 0.0; color2[10][1] = 0.0; color2[10][2] = 1.0;
    color2[11][0] = 0.0; color2[11][1] = 0.0; color2[11][2] = 1.0;

    color2[12][0] = 0.0; color2[12][1] = 1.0; color2[12][2] = 0.0;
    color2[13][0] = 0.0; color2[13][1] = 1.0; color2[13][2] = 0.0;
    color2[14][0] = 0.0; color2[14][1] = 1.0; color2[14][2] = 0.0;
    color2[15][0] = 0.0; color2[15][1] = 1.0; color2[15][2] = 0.0;

    index[0][0] = 0;         index[0][1] = 1;
    index[0][2] = 2;         index[0][3] = 3;

    index[1][0] = 4;         index[1][1] = 5;
    index[1][2] = 6;         index[1][3] = 7;

    index[2][0] = 8;         index[2][1] = 9;
    index[2][2] = 10;         index[2][3] = 11;

    index[3][0] = 12;         index[3][1] = 13;
    index[3][2] = 14;         index[3][3] = 15;


    glVertexPointer(2, GL_FLOAT, 0, vertex2);
    glColorPointer(3, GL_FLOAT, 0, color2);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, index2);
}
void GLScene::paintRect(float x, float y, float width, float height) {
    //qDebug() << "x=" << x << ", y=" << y << ", w=" << width << ", h=" <<height;
    glRectf(x, 1.0f - y, x + width, 1.0f - y - height);
}

void GLScene::startTimer() {
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            if(j % 2 == 0 && i % 2 != 0) {
                this->lConn->getGlobalArea()[i][j] = false;
            } else {
                this->lConn->getGlobalArea()[i][j] = true;
            }
        }
    }
    this->timer->start(3000);
}
void GLScene::paintGLSlot() {
    qDebug() << "paintGLStart";
    //this->paintGL();
    this->updateGL();
}
void GLScene::drawTestCellAuto() {
    float delta = 0.01;
    int size = 100;

    for (int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            if(this->lConn->getGlobalArea()[i][j] == true) {
                paintRect((float)i/size + delta, (float)j/size + delta, delta, delta);
            }
        }
    }
}
