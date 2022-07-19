#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <stack>
#include <forward_list>
#include <algorithm>
#include <list>
#include <math.h>
#include <chrono>

#include "Grafo.h"

using namespace std;

#define INFINITO std::numeric_limits<float>::max()

//Construtor
Grafo::Grafo(int ordem,bool direcionado,bool peso_aresta, bool peso_vertice)
{
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;
    this->primeiro = nullptr;
    this->ultimo = nullptr;
}
//Destrutor
Grafo::~Grafo()
{
    Vertice *vertice = this->primeiro;

    while (vertice != nullptr)
    {
        vertice->removerArestas();
        Vertice *aux = vertice->getProximoVertice();
        delete vertice;
        vertice = aux;
    }
}
//Getters
int Grafo::getOrdem()
{
    return this->ordem;
}
bool Grafo::getDirecionado()
{
    return this->direcionado;
}
bool Grafo::getPeso_aresta()
{
    return this->peso_aresta;
}
bool Grafo::getPeso_vertice()
{
    return this->peso_vertice;
}
int Grafo::getTotalArestas()
{
    return this->totalArestas;
}
Vertice* Grafo::getV(int id)
{
    // cria ponteiro para percorrer a lista de nodes
    Vertice *vertice = this->getPrimeiro();

    // encontra o node com o id desejado
    while (vertice != nullptr)
    {
        if (vertice->getId() == id)
            return vertice;
        vertice = vertice->getProximoVertice();
    }

    // retorna o node ou null caso nao encontre
    return nullptr;
}
Vertice* Grafo::getPrimeiro()
{
    return this->primeiro;
}
void Grafo::addVertice(int id)
{
    // confere se o grafo tem nodes
    if (this->primeiro != nullptr)
    {
        // caso tenha, cria um novo node, aponta o ultimo pro novo e o novo de torna o ultimo
        Vertice *novo = new Vertice(id);
        this->ultimo->setProximoVertice(novo);        
        this->ultimo = novo;
    }
    else
    {
        // caso nao tenha, cria um novo node e ele se torna o ultimo e o primeiro
        Vertice *novo = new Vertice(id);
        this->primeiro = novo;
        this->ultimo = novo;
    }
}
void Grafo::addAresta(int id_origem, int  id_destino, float peso)
{
    // cria um ponteiro para o node desejado e o um auxiliar para o node alvo da aresta
    Vertice *vertice = getV(id_origem);
    Vertice *aux = getV(id_destino);

    if (vertice == nullptr)
    {
        this->addVertice(id_origem);
        vertice = this->ultimo;
    }
    if (aux == nullptr)
    {
        this->addVertice(id_destino);
        aux = this->ultimo;
    }
    // confere se os nodes existem
    if (vertice != nullptr && aux != nullptr)
    {

        // confere se a aresta já existe
        if (!vertice->procurarAresta(id_destino))
        {
            // caso o node exista mas a aresta nao, insere a aresta
            vertice->inserirAresta(id_destino, peso);

            this->totalArestas++;

            // se o grafo for nao-direcionado e nao houver aresta de volta
            if (this->direcionado == 0 && !aux->procurarAresta(id_origem))
            {
                // insere a aresta de volta
                aux->inserirAresta(id_origem,peso);
            }
        }
    }
}
void Grafo::apagaVertice(int idVertice)
{
    // cria um ponteiro para o node desejado
    Vertice *vertice = this->getV(idVertice);

    // retorna caso nao exista o node desejado
    if (vertice == nullptr)
        return;
    else if (vertice == this->primeiro) // se o node eh o primeiro, apenas faz o proximo ser o primeiro
        primeiro = vertice->getProximoVertice();
    else
    {
        // caso seja um node do meio ou o ultimo, cria um ponteiro auxiliar
        Vertice *aux = this->primeiro;

        // encontra o node anterior ao node desejado
        while (aux->getProximoVertice() != vertice)
            aux = aux->getProximoVertice();

        // se o no desejado for o ultimo, atualiza o ultimo para o anterior
        if (vertice == this->ultimo)
            ultimo = aux;

        // seta o proximo de anterior para o proximo do desejado
        aux->setProximoVertice(vertice->getProximoVertice());
    }

    // deleta o node desejado
    delete vertice;

}
void Grafo::limparVisitados()
{
    Vertice *vertice = this->getPrimeiro(); // Ponteiro que armazena o endereço de memória do primeiro nó do grafo.

    // Realiza a operação para todos os nós do grafo.
    while (vertice != nullptr)
    {
        vertice->setVisitado(false);    // Define o nó como não visitado.
        vertice = vertice->getProximoVertice(); // Ponteiro passa a apontar para o próximo nó do grafo.
    }
}
void Grafo::imprimeGrafo()
{
    cout << "Imprimindo grafo: " << endl;
    Vertice *vertice = this->getPrimeiro();
    Aresta *aresta = vertice->getPrimeira();
    while (vertice != nullptr)
    {
        aresta = vertice->getPrimeira();
        cout << "Arestas de " << vertice->getId() << ":";
        while (aresta != nullptr)
        {
            cout << aresta->getIdAdjacente() << " ";
            aresta = aresta->getProx();
        }
        cout << endl;
        vertice = vertice->getProximoVertice();
    }
}
void Grafo::leitura(ifstream &arquivo)
{
    int idVerticeOrigem;
    int idVerticeDestino;
    float pesoAresta;
    cout << "\nLendo o arquivo input.txt..." << endl;
  //cout << "Ordem: " << order << endl; 

  //Leitura de arquivo
  if (!this->getPeso_aresta() && !this->getPeso_vertice()) // Sem peso nas arestas e sem peso nos nós
  {

    while (arquivo >> idVerticeOrigem >> idVerticeDestino >> pesoAresta) {
      //cout << "Edge: " << idNodeSource << " -- " << idNodeTarget << endl;
      this->addAresta(idVerticeOrigem, idVerticeDestino, 0);
      cout << idVerticeOrigem << idVerticeDestino << pesoAresta << endl;
    }
  } else if (this->getPeso_aresta() && !this->getPeso_vertice()) // Com peso nas arestas e sem peso nos nós
  {
    while (arquivo >> idVerticeOrigem >> idVerticeDestino >> pesoAresta) {
      //cout << "Edge: " << idNodeSource << " - " << idNodeTarget << " - " << edgeWeight << endl;
      this->addAresta(idVerticeOrigem, idVerticeDestino, pesoAresta);
    }
  } else if (this->getPeso_vertice() && !this->getPeso_aresta()) // Com peso no nó e sem peso na aresta
  {
    float pesoVerticeOrigem, pesoVerticeDestino;

    while (arquivo >> idVerticeOrigem >> pesoVerticeOrigem >> idVerticeDestino >> pesoVerticeDestino) {
      this->addAresta(idVerticeOrigem, idVerticeDestino, 0);
      this->getV(idVerticeOrigem)->setPeso(pesoVerticeOrigem);
      this->getV(idVerticeDestino)->setPeso(pesoVerticeDestino);
    }
  } else if (this->getPeso_vertice() && this->getPeso_aresta()) // Com peso no nó e com peso na aresta
  {

    float pesoVerticeOrigem, pesoVerticeDestino;

    while (arquivo >> idVerticeOrigem >> pesoVerticeOrigem >> idVerticeDestino >> pesoVerticeDestino) {
      this->addAresta(idVerticeOrigem, idVerticeDestino, pesoAresta);
      this->getV(idVerticeOrigem)->setPeso(pesoVerticeOrigem);
      this->getV(idVerticeDestino)->setPeso(pesoVerticeDestino);
    }
  }  

}
void Grafo::transitivoDireto(int id)
{
    cout << "Fecho transitivo direto do vertice:" << id << endl;
    vector<int> idvertices;
    idvertices.clear();
    if(this->getV(id)!=nullptr){
        this->limparVisitados();
        profundidade(this->getV(id));
        for (Vertice *vertice = this->getPrimeiro(); vertice!=nullptr; vertice = vertice->getProximoVertice()){
            if(vertice->getVisitado()){
                idvertices.push_back(vertice->getId());
            }
        }
    }
    for(int i = 0; i < idvertices.size(); i++){
        cout << idvertices[i] << " ";
    }
    cout << endl;
}
void Grafo::profundidade(Vertice *vertice)
{
    vertice->setVisitado(true);
    for (Aresta *aresta = vertice->getPrimeira(); aresta != nullptr; aresta = aresta->getProx()){
        if (!this->getV(aresta->getIdAdjacente())->getVisitado()){
            profundidade(this->getV(aresta->getIdAdjacente()));
        }
    }
}
void Grafo::transitivoIndireto(int id)
{
    cout << "Fecho transitivo indireto do vertice:" << id << endl;
    Vertice *vertice = this->getPrimeiro();
    vector<int> idvertices;
    idvertices.clear();
    while(vertice!=nullptr){
        if(vertice->getId()!=id){
            this->limparVisitados();
            auxTransIndireto(vertice,id);
            if(getV(id)->getVisitado()){
            idvertices.push_back(vertice->getId());
            }
        }
        vertice = vertice->getProximoVertice();
    }
    for(int i = 0; i < idvertices.size(); i++){
        cout << idvertices[i] << " ";
    }
    cout << endl;
}
void Grafo::auxTransIndireto(Vertice *vertice, int id)
{
    vertice->setVisitado(true);
    Aresta *aresta = vertice->getPrimeira();
    while(aresta!=nullptr){
        if(aresta->getIdAdjacente()==id){
        this->getV(aresta->getIdAdjacente())->setVisitado(true);
        break;
        }
        else if(!this->getV(aresta->getIdAdjacente())->getVisitado()){
            auxTransIndireto(this->getV(aresta->getIdAdjacente()),id);
        }
        aresta = aresta->getProx();
    }  
       
}
void Grafo::busca_profundidade()
{   
    Vertice* vertice = this->getPrimeiro();
    vector<int> arestas_retorno;
    this->limparVisitados();
    aux_busca_profundidade(vertice);
    while (vertice!=nullptr){
        if(vertice->getVisitado()){
            cout << vertice->getId() << "  ";
        }
        for(Aresta *aresta = vertice->getPrimeira(); aresta!=nullptr; aresta = aresta->getProx()){
            if (!aresta->getVisitado()){
                arestas_retorno.push_back(aresta->getPeso());
            }
        }
        vertice = vertice->getProximoVertice();
    }
    cout << "Arestas de retorno: " << endl;
    for (int i = 0; i < arestas_retorno.size(); i++){
        cout << arestas_retorno[i] << " ";
    }
    
}
void Grafo::aux_busca_profundidade(Vertice *vertice)
{
    vertice->setVisitado(true);
    Aresta *aresta = vertice->getPrimeira();
    while (aresta != nullptr)
    {
        if(!(this->getV(aresta->getIdAdjacente())->getVisitado()))
        {
            if(!this->getDirecionado()){
                aresta->setVisitado(true);
                this->getV(aresta->getIdAdjacente())->getAresta(vertice->getId())->setVisitado(true);
            }
            else{
                aresta->setVisitado(true);
            }
            aux_busca_profundidade(this->getV(aresta->getIdAdjacente()));
        }
        aresta = aresta->getProx();        
    }
}
//int Grafo::KCoeficienteLocal(int Idno)

/*procura se o No desejado foi adicionado no vetor de visitados.*/
//bool procuraNo(vector<int> tempCaminho,int elemento)
/*{
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
}*/

/**
 * Caminho mínimo de floyd: imprime uma matriz de
 * pesos, onde cada item da matriz m[i][j] representa o
 * peso do nó i ao nó j.
 * */
void Grafo::caminhoMinimoFloyd()
{
    // Estrutura Caminho para armazenar os pesos das arestas e o primeiro vetor do caminho
    struct Caminho
    {
        Vertice *primeiro;
        float peso;
    };

    int tam = this->getOrdem();

    //Alocação dinamica da matriz
    Caminho **d;
    d = new Caminho *[tam];

    for (int i = 0; i < tam; i++)
    {
        d[i] = new Caminho[tam];
    }

    //inicializando a matriz com peso 0 para a diagonal e infinito para o resto
    //Cria em cada elemento da matriz uma lista que servirá para guardar o caminho
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (i == j)
            {
                d[i][j].peso = 0;
            }
            else
            {
                d[i][j].peso = INFINITO;
            }

            d[i][j].primeiro = new Vertice(i);
        }
    }

    //Setando os valores iniciais dado grafo a partir dos vertices vizinhos
    Vertice *v = this->primeiro;
    while (v != NULL)
    {
        Aresta *a = v->getProximaAresta();
        while (a != NULL)
        {
            d[v->getId()][a->getIdAdjacente()].peso = a->getPeso();
            d[v->getId()][a->getIdAdjacente()].primeiro->setId(v->getId());
            a = a->getProx();
        }
        v = v->getProximoVertice();
    }

    //Metodo de Floyd para encontrar o menor caminho partindo de cada ponto diferente
    for (int k = 0; k < tam; k++)
    {
        for (int i = 0; i < tam; i++)
        {
            for (int j = 0; j < tam; j++)
            {
                float pesoExistente = d[i][j].peso;            //Pega o menor caminho entre dois vertices(i,j)
                float pesoTeste = d[i][k].peso + d[k][j].peso; //Soma o caminho de ir de i à j passando por k
                if (pesoTeste < pesoExistente)                 //Se passando por k for menor entra no if e atualiza o peso na matriz
                {
                    d[i][j].peso = pesoTeste;
                    Vertice *c = new Vertice(k);
                    Vertice *aux = d[i][j].primeiro;
                    while (aux->getProximoVertice() != NULL) //atualiza a matriz de caminhos
                    {
                        aux = aux->getProximoVertice();
                    }
                    aux->setProximoVertice(c);
                }
            }
        }
    }

    //Coloca o vertice de chegada como o ultimo vertice da lista de caminhos
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            Vertice *c = new Vertice(j);
            Vertice *aux = d[i][j].primeiro;
            while (aux->getProximoVertice() != NULL)
            {
                aux = aux->getProximoVertice();
            }
            aux->setProximoVertice(c);
        }
    }

    //Imprime uma matriz com o peso para ir de um vertice [i] para outro [j]
    std::cout << std::endl;
    std::cout << "-----Matriz de Pesos------" << std::endl;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            std::cout << d[i][j].peso << " ";
        }
        std::cout << std::endl;
    }

    // Desalocando memória
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            while (d[i][j].primeiro != NULL)
            {
                Vertice *aux = d[i][j].primeiro;
                d[i][j].primeiro = d[i][j].primeiro->getProximoVertice();
                delete aux; //Deleta cada vertice da lista
            }
        }
        delete[] d[i]; //Deleta cada linha da matriz
    }
    delete[] d; //Deleta a matriz
}

/**
 * Árvore Geradora de Prim
 * */
void Grafo::arvoreGeradoraPrim()
{
    using namespace std;

    int tam = this->getOrdem();

    struct No
    {
        Vertice *id;
        float peso;
    };

    struct ComparaMinimo
    {
        bool operator()(No &a, No &b)
        {
            return a.peso > b.peso;
        }
    };

    priority_queue<No, vector<No>, ComparaMinimo> minheap;
    vector<No> caminho;
    caminho.reserve(tam);

    //Setando os valores iniciais
    No primeiro;
    Vertice *v = this->primeiro;
    while (v != NULL)
    {
        No a;
        a.id = v;
        a.peso = INFINITO;
        caminho[v->getId()] = a; // vetor ordenado de cada vertice por seu id
        v = v->getProximoVertice();
    }
    vector<bool> inMST(tam, false); //Se o indice i está na lista da arvore minima. Todos começam com falso
    vector<int> pais(tam, -1);      //Armazena o id do pai do indice i;
    caminho[0].peso = 0;
    inMST[0] = true; // Inicializa o primeiro vertice como raiz da arvore
    pais[0] = 0;
    minheap.push(caminho[0]);

    float pesoTotalMinimo = 0;

    while (!minheap.empty()) //varre a minheap
    {
        No u = minheap.top(); //guarda as informações de quem estava no topo da minheap
        minheap.pop();
        if (inMST[u.id->getId()] == false) //Verifica se quem estava no topo ja estava na arvore
        {
            pesoTotalMinimo += caminho[u.id->getId()].peso;
        }

        inMST[u.id->getId()] = true; //coloca na arvore

        Aresta *a = u.id->getProximaAresta();
        while (a != NULL) //varre as arestas do vertice no topo da minheap
        {
            float pesoAresta = a->getPeso();
            //cout << pesoAresta;
            int id_adj = a->getIdAdjacente();

            if (inMST[id_adj] == false && caminho[id_adj].peso > pesoAresta) //Se o vertice ainda nao estiver na arvore
            {                                                                //E sua presente aresta custar menos que
                caminho[id_adj].peso = pesoAresta;                           //sua aresta anterior
                caminho[id_adj].id->setId(id_adj);                           //Atuliza como menor caminho, entra na minheap
                minheap.push(caminho[id_adj]);                               //E atuliza seu pai
                pais[id_adj] = u.id->getId();
            }

            a = a->getProx();
        }
    }
    /* Imprime quem é o pai de cada vertice na arvore */
    if (debug)
    {
        for (int i = 1; i < tam; i++)
        {
            cout << "[ " << pais[i] << " - " << i << " ] => ";
        }
    }

    cout << endl
         << "Peso minimo: " << pesoTotalMinimo; //peso minimo para percorrer o grafo todo
}