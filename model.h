#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <QVector>
#include <QVector3D>
#include <QVector4D>
#include <QUrl>
#include <fstream>
#include <iostream>
namespace meinModel {



    class Vertex{
        QVector3D Position;
        QVector3D Normal;
        QVector3D AmbientColor;
        QVector3D DiffuseColor;
        float Alpha;  //0 (totally transparent) to 1 (totally opaque)
    public:
        Vertex();
        void setPosition(QVector3D position);
        void setNormal(QVector3D normal);
        void setAmbientColor(QVector3D ambientColor);
        void setDiffuseColor(QVector3D diffuseColor);
        void setAlpha(float alpha);
        QVector3D getPosition();
        QVector3D getAmbientColor();
        QVector3D getDiffuseColor();
        float getAlpha();
    };


    class Mesh{
        QVector<Vertex> Vertices;
        QVector<int> Indices;
        QVector<int> IndicesNormals;
    public:
        Mesh();
        Mesh(const char* url);
        bool loadOBJ(const char* url);
        int numVertices();
        int numIndices();
        Vertex* VerticesData();
        int* IndicesData();
    };


   /* class Model
    {
        QVector<Mesh> Meshes;
    public:
        Model();
        bool addMesh(QUrl url);
    };*/
}
#endif // MODEL_H
