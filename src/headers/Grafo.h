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

    /*std::string _trim(std::string linha);
    void _addAresta(Vertice* x, Vertice y, float peso, bool& inseriu);
    void _apagarAresta(Vertice* v, int id_y, bool& apagou);
    //std::forward_list<Vertice> auxGuloso(float alfa);*/

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
        int      getPosicao(int id);
        Vertice* getV(int id);
        Vertice* getVPosicao(int p);
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

        int  Kcoeficienteagrupamento(int *IDs);


        void transitivoDireto(int id);
        void profundidade(Vertice *vertice);
        void transitivoIndireto(int id);
        void auxTransIndireto(Vertice *vertice, int id);
        void caminhamentoLargura(int id_inicio);
        void caminhamentoProfundidade(int id_inicio);
        void caminhoMinimoDijkstra(int id_inicio ,int id_final);
        void caminhoMinimoFloyd();
        void arvoreGeradoraPrim(Grafo *subgrafo);
        void arvoreGeradoraKruskal(vector<int> vertices); //arvore geradora minima por Kruskal (letra h);
        void arvoreCaminhamentoProfundidade(int id); //arvore destacando arestas de retorno(letra i);
        void aux_busca_profundidade(Vertice *vertice);
        void busca_profundidade();
        Grafo *getVertInduz(vector<int> idvertices);

};

#endif // GRAFO_H