#ifndef NO_H
#define NO_H

#include <vector>

#include "Aresta.h"

using namespace std;

class No
{

    private:
    int Id;
    int grauIn;
    int grauOut;
    bool visitado = false;
    No *proxNo;

    vector<Aresta> lista_adjacencia;

    public:

    No();

    /*funcoes sem retorno*/
    
    /*funcoes com retorno*/
    int GetId();
};

#endif