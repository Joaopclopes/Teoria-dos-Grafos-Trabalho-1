#include <iostream>
#include <fstream>

#include "Vertice.h"

using namespace std;

Vertice::Vertice()
{
    this->id = 0;
    this->peso = 0;
    this->grau = 0;
    this->primeira = nullptr;
    this->proxV = nullptr;
    this->ultima = nullptr;
    this->visitado = false;

}
Vertice::Vertice(int id)
{
    this->id = id;
    this->peso = 0;
    this->grau = 0;
    this->primeira = nullptr;
    this->proxV = nullptr;
    this->ultima = nullptr;
    this->visitado = false;

}
Vertice::Vertice(int id, float peso)
{
    this->id = id;
    this->peso = peso;
    this->grau = 0;
    this->primeira = nullptr;
    this->proxV = nullptr;
    this->ultima = nullptr;
    this->visitado = false;
}
int Vertice::getId()
{
    return this->id;
}
void Vertice::setId(int id)
{
    this->id = id;
}
int Vertice::getGrau()
{
    return this->grau;
}
void Vertice::setGrau(int grau)
{
    this->grau = grau;
}
void Vertice::addGrau()
{
    this->grau++;
}
void Vertice::subGrau()
{
    this->grau--;
}
float Vertice::getPeso()
{
    return this->peso;
}
void Vertice::setPeso(float peso)
{
    this->peso = peso;
}
Vertice* Vertice::getProximoVertice()
{
    return this->proxV;
}
void Vertice::setProximoVertice(Vertice* proxV)
{
    this->proxV = proxV;
}
Aresta* Vertice::getProximaAresta()
{
    return this->primeira;
}
void Vertice::setProximaAresta(Aresta* proxA)
{
    this->primeira = proxA;
}
bool Vertice::getVisitado()
{
    return this->visitado;
}
void Vertice::setVisitado(bool visitado)
{
    this->visitado = visitado;
}
Aresta* Vertice::getPrimeira()
{
    return this->primeira;
}
void Vertice::removerArestas(){
    // Verifies whether there are at least one edge in the node
    if(this->primeira != nullptr){

        Aresta* prox = nullptr;
        Aresta* aux = this->primeira;
        // Removing all edges of the node
        while(aux != nullptr){

            prox = aux->getProx();
            delete aux;

        }

    }
    this->primeira = this->ultima = nullptr;
}
bool Vertice::procurarAresta(int id)
{
     // Verifica se há uma Aresta no Nó.
    if(this->primeira != nullptr){
        // Procurando por uma Aresta especifica do id informado
        for(Aresta* aux = this->primeira; aux != nullptr; aux = aux->getProx())
            if(aux->getIdAdjacente() == id)
                return true;

    }
    return false;
}
void Vertice::inserirAresta(int id,float peso)
{
    // Verifica se há pelo menos uma aresta no nó
    if(this->primeira != nullptr){
        // Alocando a nova aresta e mantendo a integridade da lista de aresta
        Aresta* aresta = new Aresta(id,peso);
        aresta->setPeso(peso);
        this->ultima->setProxima(aresta);
        this->ultima = aresta;
    }
    else{
         // Alocando a nova aresta e mantendo a integridade da lista de aresta
        this->primeira = new Aresta(id,peso);
        this->primeira->setPeso(peso);
        this->ultima = this->primeira;

    }
}
Aresta* Vertice::getAresta(int idAdjacente)
{

    for(Aresta *aux = this->getPrimeira(); aux != nullptr; aux = aux->getProx())
    {
        if(aux->getIdAdjacente() == idAdjacente)
            return aux;
    }
    return nullptr;
}