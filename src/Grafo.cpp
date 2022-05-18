#include <iostream>
#include <fstream>

#include "Grafo.h"

using namespace std;

Grafo::Grafo()
{
}

int Grafo::KCoeficienteLocal(int Idno)
{
}
/*procura se o No desejado foi adicionado no vetor de visitados.*/
bool procuraNo(vector<int> tempCaminho,int elemento)
{
    for(int i = 0;i < tempCaminho.size();i++)
    {
        if(tempCaminho.at(i) == elemento)
           return true;
    }
    return false;
}

vector<int> Grafo::CaminhoMinDjkstra(No *a,No *b)
{
    vector<int> caminho;

    while(!procuraNo(caminho,b->GetId()))
    {
        
    }
}