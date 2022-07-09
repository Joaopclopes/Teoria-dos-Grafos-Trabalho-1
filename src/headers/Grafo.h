/*
    CABEÇALHO
*/

#ifndef GRAFO_H
#define GRAFO_H 1

#include "Vertice.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <forward_list>

class Grafo {

    private:
        int ordem;
        int nArestas;
        Vertice* primeiro;

    std::string _trim(std::string linha);
    void _addAresta(Vertice* x, Vertice y, float peso, bool& inseriu);
    void _apagarAresta(Vertice* v, int id_y, bool& apagou);
    //std::forward_list<Vertice> auxGuloso(float alfa);

    public:
        bool debug = false;
        Grafo();
        ~Grafo();

        std::istream& lerArquivo(std::istream &arquivo);
        std::ostream& escreverArquivo(std::ostream &arquivo);

        Vertice* getV(int id);
        Vertice* getPrimeiro();

        void addAresta(Vertice x, Vertice y, float peso);
        void apagaAresta(int id_x, int id_y);

        Vertice* addVertice(Vertice vertice);
        void apagaVertice(int idVertice);

        int getTotalArestas();
        int getTotalVertices();
        int getGrauVertice();
        float getGrauMedio();
        float getFrequenciaRelativa(int grau);
        void imprimeGrafo();

        void caminhamentoLargura(int id_inicio);
        void caminhamentoProfundidade(int id_inicio);
        void caminhoMinimoDijkstra(int id_inicio);
        void caminhoMinimoFloyd();
        void arvoreGeradoraPrim();
        void arvoreGeradoraKruskal();

};

inline std::istream& operator >>(std::istream &arquivo, Grafo &grafo) {
    return grafo.lerArquivo(arquivo);
}

inline std::ostream& operator <<(std::ostream &arquivo, Grafo &grafo) {
    return grafo.escreverArquivo(arquivo);
}

#endif // GRAFO_H