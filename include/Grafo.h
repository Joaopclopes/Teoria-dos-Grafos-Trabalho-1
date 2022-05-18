#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

#include "No.h"
#include "Aresta.h"

using namespace std;

class Grafo
{
    private:
    int  Ordem;
    bool direcionado;
    bool peso_aresta;
    bool peso_no;

    No *primeiroNo;
    No *ultimoNo;

    /*funcoes sem retorno*/

    public:

    Grafo();

    /*funcoes sem retorno*/
    
    /*funcoes com retorno*/
    int          KCoeficienteLocal(int Idno);
    vector<int>  CaminhoMinDjkstra(No *a,No *b);
};
#endif