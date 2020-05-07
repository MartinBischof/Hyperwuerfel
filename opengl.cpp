#include "opengl.h"


OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent), indexBuff(QOpenGLBuffer::IndexBuffer), vertexBuff(QOpenGLBuffer::VertexBuffer){}

void OpenGL::timerEvent(QTimerEvent *){
    update();
}

void OpenGL::mousePressEvent(QMouseEvent *me){

}

void OpenGL::keyPressEvent(QKeyEvent *ke){
    if(ke->key() == Qt::Key_W){
        if(angleX < 180 && angleX >= -180){
            camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1,0,0),2));
            history.push_back(0); //0 = x
            history.push_back(2); //wert
            angleX +=2;
        }
    }
    if(ke->key() == Qt::Key_A){
        if(angleY <= 180 && angleY > -180){
            camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D(0,1,0),-2));
            history.push_back(1);   //1 = y
            history.push_back(-2);  //wert
            angleY -= 2;
        }
    }
    if(ke->key() == Qt::Key_S){
        if(angleX <= 180 && angleX > -180){
            camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1,0,0),-2));
            history.push_back(0);
            history.push_back(-2);
            angleX -=2;
        }
    }
    if(ke->key() == Qt::Key_D){
        if(angleY < 180 && angleY >= -180){
            camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D(0,1,0),+2));
            history.push_back(1);
            history.push_back(2);
            angleY += 2;
        }
    }
    if(ke->key() == Qt::Key_R){
        for (int i{history.size()}; i!=0;i-=2) {
            if(history.at(i-2) == 0){
                camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1,0,0),(history.at((i-1))*(-1))));
            }else{
                camera.rotate(QQuaternion::fromAxisAndAngle(QVector3D(0,1,0),(history.at((i-1))*(-1))));
            }
        }
        angleX = 0;
        angleY = 0;
        history = {};
        camPos = QVector3D(0.0f,0.0f,-5.0f);
        camera.setPosition(camPos);
    }
    if(ke->key() == Qt::Key_Plus){
        camPos.setZ((camPos.z()+0.1));
        camera.setPosition(camPos);
    }
    if(ke->key() == Qt::Key_Minus){
        camPos.setZ((camPos.z()-0.1));
        camera.setPosition(camPos);
    }
    if(ke->key() == Qt::Key_Up){
        camPos.setY((camPos.y()-0.1));
        camera.setPosition(camPos);
    }
    if(ke->key() == Qt::Key_Down){
        camPos.setY((camPos.y()+0.1));
        camera.setPosition(camPos);
    }
    if(ke->key() == Qt::Key_Left){
        camPos.setX((camPos.x()+0.1));
        camera.setPosition(camPos);
    }
    if(ke->key() == Qt::Key_Right){
        camPos.setX((camPos.x()-0.1));
        camera.setPosition(camPos);
    }
}

void OpenGL::initializeGL(){
    QOpenGLFunctions *OGL_funk = QOpenGLContext::currentContext()->functions();
    //shader und Buffer initialiseiren
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.vsh");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.frag");
    shader.link();
    shader.bind();
    indexBuff.create();
    indexBuff.bind();
    vertexBuff.create();
    vertexBuff.bind();
    led.loadOBJ("H:\\hyperwuerfel\\monkey.obj"); /*Hier muss unbedingt ein absoluter Pfad stehen!*/
    //vertices im Buffer Allocieren
    vertexBuff.allocate(led.VerticesData(),led.numVertices()*static_cast<int>(sizeof(meinModel::Vertex)));
    //indices im Buffer Allocieren
    indexBuff.allocate(led.IndicesData(),led.numIndices()*static_cast<int>(sizeof(int)));
    //Vertices position in Shader parsen*/
    shader.enableAttributeArray(shader.attributeLocation("a_position"));
    shader.setAttributeBuffer(shader.attributeLocation("a_position"),GL_FLOAT,0,3,sizeof(meinModel::Vertex));
    //Vertices Normals in Shader parsen
    shader.enableAttributeArray(shader.attributeLocation("a_normals"));
    shader.setAttributeBuffer(shader.attributeLocation("a_normals"),GL_FLOAT,sizeof(QVector3D),3,sizeof(meinModel::Vertex));
    //Vertices Farbe in Shader parsen
    shader.enableAttributeArray(shader.attributeLocation("a_color"));
    shader.setAttributeBuffer(shader.attributeLocation("a_color"),GL_FLOAT,sizeof(QVector3D)*2,3,sizeof(meinModel::Vertex));
    //ModelMatrix für das erstellen
    model = QMatrix4x4();
    model.scale(QVector3D(1.2f,1.2f,1.2f));
    //ModelViewProjMatrix erstellen und Location im shader bestimmen
    modelViewProj = QMatrix4x4();
    modelViewProjMatrixLocation = shader.uniformLocation("u_modelViewProjMatrix");
    //Kamera Rotation/Position
    angleX = 0;
    angleY = 0;
    camPos = QVector3D(0.0f,0.0f,-5.0f);
    camera.setPosition(camPos);
    camera.setAspectRatio(970/700);
    camera.setNearPlane(0.1f);
    camera.setFarPlane(100.0f);
    camera.setFieldOfView(90);
    camera.setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    //rotation initialisieren
    spin = 0.0f;

    //timer starten
    timer.start(1, this);
    OGL_funk->glEnable(GL_CULL_FACE);
    OGL_funk->glEnable(GL_DEPTH_TEST);
    OGL_funk->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}

void OpenGL::resizeGL(int w, int h) {
    // Update camaras AspectRatio
    camera.setAspectRatio(w/h);
}

void OpenGL::paintGL() {
    QOpenGLFunctions *OGL_funk = QOpenGLContext::currentContext()->functions();
    //roatation als Easteregg
    model.rotate(spin,QVector3D(0.0f,1.0f,0.0f));
    modelViewProj = camera.projectionMatrix()*(camera.transform()->matrix())*model;
    //OpenGL zum zeichnen Vorbereiten
    OGL_funk->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Buffer binden
    vertexBuff.bind();
    indexBuff.bind();
    //zeichnen
    OGL_funk->glUniformMatrix4fv(modelViewProjMatrixLocation,1,false,modelViewProj.constData());
    OGL_funk->glDrawElements(GL_TRIANGLES, static_cast<int>(led.numIndices()), GL_UNSIGNED_INT, nullptr);
}

void OpenGL::setRotation(const int &angle){
    spin = angle;
}

