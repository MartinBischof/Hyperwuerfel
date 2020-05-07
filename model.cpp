#include "model.h"

meinModel::Vertex::Vertex(){
    Position = QVector3D(0.0f,0.0f,0.0f);
    AmbientColor = QVector3D(0.0f,0.0f,0.0f);
    DiffuseColor = QVector3D(0.0f,0.0f,0.0f);
    Alpha = 1.0f;
}

void meinModel::Vertex::setPosition(QVector3D position){
    Position = position;
}
void meinModel::Vertex::setAmbientColor(QVector3D ambientColor){
    AmbientColor = ambientColor;
}
void meinModel::Vertex::setDiffuseColor(QVector3D diffuseColor){
    DiffuseColor = diffuseColor;
}
void meinModel::Vertex::setAlpha(float alpha){
    Alpha = alpha;
}
void meinModel::Vertex::setNormal(QVector3D normal){
    Normal = normal;
}
QVector3D meinModel::Vertex::getPosition(){
    return Position;
}
QVector3D meinModel::Vertex::getAmbientColor(){
    return AmbientColor;
}
QVector3D meinModel::Vertex::getDiffuseColor(){
    return DiffuseColor;
}
float meinModel::Vertex::getAlpha(){
    return Alpha;
}

meinModel::Mesh::Mesh(){
    Vertices = {};
    Indices = {};
}
meinModel::Mesh::Mesh(const char* url){
    loadOBJ(url);
}
int meinModel::Mesh::numVertices(){
    return Vertices.size();
}
int meinModel::Mesh::numIndices(){
    return Indices.size();
}
meinModel::Vertex* meinModel::Mesh::VerticesData(){
    return Vertices.data();
}
int* meinModel::Mesh::IndicesData(){
    return Indices.data();
}
bool meinModel::Mesh::loadOBJ(const char* url){
    std::ifstream objDatei {};
    objDatei.open(url,std::ios::in);
    std::string  zeile{},value{};
    size_t i {0};
    QVector<QVector3D> Normals;
    while(!objDatei.eof()){
        i = 0;
        std::getline(objDatei,zeile);
        //ende erreicht?
        if(zeile.size() == 0){
            /*for (auto wert : IndicesNormals) {
                std::cout <<wert << std::endl;
            }*/
            for(int i{0};i<Indices.size();++i){
                Vertices[Indices[i]].setNormal(Normals[IndicesNormals[i]]);
/*
                std::cout<<"Vertex: " << Indices[i] <<" Normal: "<< Normals[(IndicesNormals[i])].x()
                                                           <<" " << Normals[(IndicesNormals[i])].y()
                                                           <<" " << Normals[(IndicesNormals[i])].z() <<std::endl;
/*
                std::cout<<"Vertex: " << Indices[i] <<" NormalInd: "<<IndicesNormals[i] <<std::endl;
*/
            }
            return true;
        }
/**************************************************VERTEX*********************************************************/
        //war es ein vertex command?
        if(zeile.at(0)=='v' && zeile.at(1)!='n' && zeile.at(1)!='t'){
            //std::cout << "vertex"<< std::endl;
            //wenn ja handelt es sich um ein vertex, das float x fängt beim index 2
            float x{0},y{0},z{0};
            i = 2;
            Vertices.push_back(meinModel::Vertex()); //vertex hinzufüegen

            while(zeile.at(i)!=' '){ //x ermitteln
                value.push_back(zeile.at(i));
                ++i;
            }
            x = std::stof(value);
            value = {};
            ++i;

            while(zeile.at(i)!=' '){ //y ermiteln
                value.push_back(zeile.at(i));
                ++i;
            }
            y = std::stof(value);
            value = {};
            ++i;

            while(i<zeile.size()){ //z ermiteln
                value.push_back(zeile.at(i));
                ++i;
            }
            z = std::stof(value);
            value = {};

            //das letzte vertex mit ermitellten daten für Position füllen
            Vertices[(Vertices.size()-1)].setPosition(QVector3D(x,y,z));
            Vertices[(Vertices.size()-1)].setAmbientColor(QVector3D(1.0f,0.0f,0.0f));
            //std::cout << "x: " << x << " y: " << y << " z: " << z <<std::endl;
            x = {0.0};
            y = {0.0};
            z = {0.0};
/*************************************************NORMALS**********************************************************/
        }else if(zeile.at(0)=='v' && zeile.at(1)=='n'){
            float x{0},y{0},z{0};
            i = 3;
            Normals.push_back(QVector3D()); //vertex hinzufüegen

            while(zeile.at(i)!=' '){ //x ermitteln
                value.push_back(zeile.at(i));
                ++i;
            }
            x = std::stof(value);
            value = {};
            ++i;

            while(zeile.at(i)!=' '){ //y ermiteln
                value.push_back(zeile.at(i));
                ++i;
            }
            y = std::stof(value);
            value = {};
            ++i;

            while(i<zeile.size()){ //z ermiteln
                value.push_back(zeile.at(i));
                ++i;
            }
            z = std::stof(value);
            value = {};
            Normals[(Normals.size()-1)] = QVector3D(x,y,z);
            //std::cout << "x: " << Normals[(Normals.size()-1)].x() << " y: " << Normals[(Normals.size()-1)].y() << " z: " << Normals[(Normals.size()-1)].z() <<std::endl;
            x = {0.0};
            y = {0.0};
            z = {0.0};
/**************************************************FACE************************************************************/
        }else if(zeile.at(0)=='f'){ //war das ein f command?
            //std::cout << "face"<< std::endl;
            i = 2;

            for (int j{0};j<3;++j){
                //Indizes der Faces
                while(zeile.at(i) != '/'){
                    value.push_back(zeile.at(i));
                    ++i;
                }
                //std::cout<<"I ";
                Indices.push_back((std::stoi(value)-1));
                value = {};
                ++i;
                //Texturen der Faces
                while(zeile.at(i) != '/'){
                    //texturen
                    value.push_back(zeile.at(i));
                    //std::cout<<"T ";
                    ++i;
                }
                if(value.size()!=0){
                   //value zur textur indizen hinzufugen
                }
                value = {};
                ++i;
                //NormalsIndices der faces
                if(j<2){
                    while(zeile.at(i) != ' '){
                        //normals
                        value.push_back(zeile.at(i));
                        //std::cout<<"N"<<std::endl;
                        ++i;
                    }
                }else{
                    while(i<zeile.size()){
                        //normals
                        value.push_back(zeile.at(i));
                        //std::cout<<"N"<<std::endl;
                        ++i;
                    }
                }
                if(value.size()!=0){
                   //value zur Normals indizen hinzufugen
                    IndicesNormals.push_back((std::stoi(value)-1));
                }
                value = {};
                ++i;
            }
       }
    }
    return false;
}
