/*
    CABEÇALHO
*/

#ifndef ARESTA_H
#define ARESTA_H 1

class Aresta {
    private:
    int idAdjacente;
    float peso;
    Aresta* prox;
    bool visitado;

    public:
    Aresta();
    Aresta(int idAdjacente);
    Aresta(int idAdjacente, float peso);

    int getIdAdjacente();
    void setIdAdjacente(int id);
    float getPeso();
    void setPeso(float peso);
    Aresta* getProx();
    void setProxima(Aresta* prox);
    void setVisitado(bool visitado);
    bool getVisitado();
};

#endif // ARESTA_H