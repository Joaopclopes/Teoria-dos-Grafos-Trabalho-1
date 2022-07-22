#include <iostream>
#include <fstream>

#include "Aresta.h"
#include "Vertice.h"

using namespace std;

Aresta::Aresta(){
    this->setPeso(0);
    this->setProxima(nullptr);
    this->setVisitado(false);
}

Aresta::Aresta(int idAdjacente){
    this->setIdAdjacente(idAdjacente);
    this->setPeso(0);
    this->setProxima(nullptr);
    this->setVisitado(false);
}

Aresta::Aresta(int idAdjacente,  int target_position, float peso){
    this->setIdAdjacente(idAdjacente);
    this->setPeso(peso);
    this->setProxima(nullptr);
    this->setVisitado(false);
    this->target_position = target_position;
}
void Aresta::setVisitado(bool visitado)
{
    this->visitado = visitado;
}
bool Aresta::getVisitado()
{
    return this->visitado;
}
int Aresta::getIdAdjacente()
{
    return this->idAdjacente;
}
void Aresta::setIdAdjacente(int id)
{
    this->idAdjacente = id;
}
float Aresta::getPeso()
{
    return this->peso;
}
void Aresta::setPeso(float peso)
{
    this->peso = peso;
}
Aresta* Aresta::getProx()
{
    return this->prox;
}
void Aresta::setProxima(Aresta* prox)
{
    this->prox = prox;
}