/*
    CABEÇALHO
*/

#ifndef ARESTA_H
#define ARESTA_H 1

class Aresta {
    private:
    int idAdjacente; //id do indice adjacente
    float peso;
    Aresta* prox;
    bool visitado;
    int idAdjacentePosicao; //posicao do indice adjacente

    public:
    Aresta();
    Aresta(int idAdjacente);
    Aresta(int idAdjacente, int idAdjacentePosicao,float peso);

    //getters
    int getIdAdjacente();
    float getPeso();
    bool getVisitado();
    int getIdAdjacentePosicao();
    Aresta* getProx();
    //setters
    void setProxima(Aresta* prox);
    void setVisitado(bool visitado);
    void setPeso(float peso);
    void setIdAdjacente(int id);
};

#endif // ARESTA_H