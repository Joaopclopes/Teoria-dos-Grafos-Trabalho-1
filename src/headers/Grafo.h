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
#include <list>

using namespace std;

class Grafo {

    private:
        int ordem;
        Vertice* primeiro;
        Vertice *ultimo;
        bool direcionado;
        bool peso_aresta;
        bool peso_vertice;
        int totalArestas;
        int posicao; //para guarda a posição de inserção do no

        void auxCaminhamentoProfundidade(Vertice *v, vector<int> *findG, vector<int> *retorno,vector<string> *graf);
        void saidaFloyd(int **pred, Vertice *origem, Vertice *destino);
        void caminhoMinimo(list<int> &antecessor);
        int **iniciaDistanciaFloyd(int **distancia, int tam);
        int **iniciaAnterioresFloyd(int **anteriores, int tam);
        void saidaDijkstra(int antecessor[], int idOrigem, int idDestino);
        void printFloyd(int **path, int **cost, int idOrig, int idDest);
        void printPathFloyd(int **path, int idOrig, int idDest);

    public:
        bool debug = false;
        Grafo(int ordem,bool direcionado,bool peso_aresta, bool peso_vertice);
        ~Grafo();

        void leitura(ifstream &arquivo);
        void escreverArquivo(ofstream &arquivo);

        //Getters
        int getOrdem();
        bool getDirecionado();
        bool getPeso_aresta();
        bool getPeso_vertice();
        int getTotalArestas();
        Vertice* getV(int id);
        Vertice* getPrimeiro();
        int getGrauVertice();
        float getGrauMedio();
        float getFrequenciaRelativa(int grau);
        int getPosicao();
        void setPosicao(int posicao);

        void addAresta (int id_origem, int  id_destino, float peso);
        void apagaAresta(int id_origem, int id_destino);

        void addVertice(int id);
        void apagaVertice(int idVertice);
        void imprimeGrafo();
        Grafo* verticeInduzido();
        void limparVisitados();
        Vertice *getVerticePosicao(int posicao);

        void transitivoDireto(int id);
        void profundidade(Vertice *vertice);
        void transitivoIndireto(int id);
        void auxTransIndireto(Vertice *vertice, int id);
        void caminhamentoLargura(int id_inicio);
        void caminhamentoProfundidade(int id_inicio);
        float caminhoMinimoDijkstra(int idOrigem, int idDestino);
        void caminhoMinimoFloyd(int idOrigem, int idDestino);
        void arvoreGeradoraPrim(vector<int> vertices);
        void arvoreGeradoraKruskal(vector<int> vertices); //arvore geradora minima por Kruskal (letra h);
        void arvoreCaminhamentoProfundidade(int id); //arvore destacando arestas de retorno(letra i);
        void aux_busca_profundidade(Vertice *vertice);
        void busca_profundidade();
        Grafo *getVertInduz(vector<int> idvertices);

};

#endif // GRAFO_H