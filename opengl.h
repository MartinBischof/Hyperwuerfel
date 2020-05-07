#ifndef OPENGL_H
#define OPENGL_H
/*Diese Klasse erbt von dem QOpenGlwidget um einige Methoden neudefinieren
zu könen.*/

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <Qt3DRender/QCamera>
#include <QTransform>
#include <QBasicTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QQuaternion>
#include "model.h"
#include "comport.h"

class OpenGL: public QOpenGLWidget
{
public:
    OpenGL(QWidget *parent);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void setRotation(const int& angle);
    //timer
    void timerEvent(QTimerEvent *e) override;
    //mousabfragen
    void mousePressEvent(QMouseEvent *me) override;
    void keyPressEvent(QKeyEvent *ke) override;
private:
    //Matrizen mit Locations
    QMatrix4x4 model;
    QTransform view;
    QMatrix4x4 modelViewProj;
    int modelViewProjMatrixLocation;
    //Variable für die Rotation des cubes
    float spin;
    //Buffer und Shader
    QOpenGLShaderProgram shader;
    QOpenGLBuffer indexBuff;
    QOpenGLBuffer vertexBuff;
    //camera und dessen position
    Qt3DRender::QCamera camera;
    QVector3D camPos;
    //floats für den Winkel der x und y achse
    float angleX, angleY;
    QVector<int> history;
    //Mesh
    meinModel::Mesh led;
    //Timer
    QBasicTimer timer;
};
#endif
