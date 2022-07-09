/*
    CABEÇALHO
*/

#ifndef VERTICE_H
#define VERTICE_H 1

#include "Aresta.h"

class Vertice {

    private:
    int id;
    int grau;
    float peso;
    Vertice* proxV;
    Aresta* proxA;

    public:
    Vertice();
    Vertice(int id);
    Vertice(int id, float peso);

    int getId();
    void setId(int id);
    int getGrau();
    void setGrau(int grau);
    void addGrau();
    void subGrau();
    float getPeso();
    void setPeso(float peso);
    Vertice* getProximoVertice();
    void setProximoVertice(Vertice* proxV);
    Aresta* getProximaAresta();
    void setProximaAresta(Aresta* proxA);


};

#endif // VERTICE_H