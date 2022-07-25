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

        //usado em Dijkstra
        void caminhoMinimo(list<int> &antecessor);
        void saidaDijkstra(int antecessor[], int idOrigem, int idDestino);

        //usado em floyd        
        void imprimirFloyd(int **path, int **cost, int idOrig, int idDest);
        void imprimirCaminhoFloyd(int **path, int idOrig, int idDest);

        //usado em prim
        void imprimirPrim(Grafo *subgrafo, vector<int> &agm);

        //funcoes auxiliares
        void profundidade(Vertice *vertice); //caminhamento profundidade 1
        void auxCaminhamentoProfundidade(Vertice *v, vector<int> *findG, vector<int> *retorno,vector<string> *graf);
        void addAresta (int id_origem, int  id_destino, float peso); //adicionar arestas
        void apagaAresta(int id_origem, int id_destino); //apagar aresta
        void addVertice(int id); //adicionar vertice
        void apagaVertice(int idVertice); //apagar vertice 
        void limparVisitados(); //colocar todos os nos como nao visitados
        Vertice *getVerticePosicao(int posicao); //obter a posicao de determinado no
        Grafo *getVertInduz(vector<int> idvertices); //subgrafo vertice induzido

    public:
        bool debug = false;
        Grafo(int ordem,bool direcionado,bool peso_aresta, bool peso_vertice);
        ~Grafo();

        void leitura(ifstream &arquivo); //funcao para leitura do grafo no arquivo txt
        void escreverArquivo(ofstream &arquivo); 

        //Getters
        int getOrdem();
        bool getDirecionado();
        bool getPeso_aresta();
        bool getPeso_vertice();
        int getTotalArestas();
        int      getPosicao(int id);
        Vertice* getV(int id);
        Vertice* getVPosicao(int p);
        Vertice* getPrimeiro();
        int getPosicao();
        void setPosicao(int posicao);

        void imprimeGrafo(); //funcao para imprimir grafo na tela

        void transitivoDireto(int id); //fecho transitivo direto
        void transitivoIndireto(int id); //fecho transitivo indireto
        int  Kcoeficienteagrupamento(int *IDs); //coeficiente de agrupamento
        float caminhoMinimoDijkstra(int idOrigem, int idDestino); //dijkstra
        void caminhoMinimoFloyd(int idOrigem, int idDestino); //floyd
        void arvoreGeradoraPrim(vector<int> vertices); //prim
        void arvoreGeradoraKruskal(vector<int> vertices); //arvore geradora minima por Kruskal (letra h);
        void arvoreCaminhamentoProfundidade(int id); //arvore destacando arestas de retorno(letra i);

};

#endif // GRAFO_H