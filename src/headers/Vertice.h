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
    Aresta* primeira;
    Aresta* ultima;
    bool visitado;

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
    bool getVisitado();
    void setVisitado(bool visitado);
    Aresta* getPrimeira();
    void setPeso(float peso);
    Vertice* getProximoVertice();
    void setProximoVertice(Vertice* proxV);
    Aresta* getProximaAresta();
    void setProximaAresta(Aresta* proxA);
    void removerArestas();
    bool procurarAresta(int id);
    void inserirAresta(int id,float peso);
    Aresta* getAresta(int idAdjacente);


};

#endif // VERTICE_H