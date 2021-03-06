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

#define INFINITO std::numeric_limits<int>::max()


//Construtor
Grafo::Grafo(int ordem,bool direcionado,bool peso_aresta, bool peso_vertice)
{
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->peso_vertice = peso_vertice;
    this->peso_aresta = peso_aresta;
    this->primeiro = nullptr;
    this->ultimo = nullptr;
    this->posicao = 0;
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
void Grafo::setPosicao(int posicao)
{
    this->posicao = posicao;
}
//Getters
int Grafo::getPosicao()
{
    return this->posicao;
}
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

int Grafo::getPosicao(int id)
{
    Vertice *vertice = this->getPrimeiro();
    int pos = 0;

    while (vertice != nullptr)
    {
        if (vertice->getId() == id)
            return pos;
        pos++;
        vertice = vertice->getProximoVertice();
    }
    return 0;
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

Vertice* Grafo::getVPosicao(int p)
{

    Vertice *vertice = this->getPrimeiro();
    int pos = 0;

    while (vertice != nullptr)
    {
        if (pos == p)
            return vertice;
        pos++;
        vertice = vertice->getProximoVertice();
    }
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
        novo->setPosicao(this->getPosicao());       
        this->ultimo = novo;
    }
    else
    {
        // caso nao tenha, cria um novo node e ele se torna o ultimo e o primeiro
        Vertice *novo = new Vertice(id);
        novo->setPosicao(this->getPosicao());
        this->primeiro = novo;
        this->ultimo = novo;
    }
    this->posicao = this->posicao + 1;
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

        // confere se a aresta j?? existe
        if (!vertice->procurarAresta(id_destino))
        {
            // caso o node exista mas a aresta nao, insere a aresta
            vertice->inserirAresta(id_destino, aux->getPosicao(),peso);
            aux->incrementaGrauEntrada();

            this->totalArestas++;

            // se o grafo for nao-direcionado e nao houver aresta de volta
            if (this->direcionado == 0 && !aux->procurarAresta(id_origem))
            {
                // insere a aresta de volta
                aux->inserirAresta(id_origem,vertice->getPosicao(),peso);
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
    Vertice *vertice = this->getPrimeiro(); // Ponteiro que armazena o endere??o de mem??ria do primeiro n?? do grafo.

    // Realiza a opera????o para todos os n??s do grafo.
    while (vertice != nullptr)
    {
        vertice->setVisitado(false);    // Define o n?? como n??o visitado.
        vertice = vertice->getProximoVertice(); // Ponteiro passa a apontar para o pr??ximo n?? do grafo.
    }
}

int Grafo::Kcoeficienteagrupamento(int *IDs)
{
    double open = 0, closed = 0;
    Vertice *i,*j;
    i = getPrimeiro();
    j = i->getProximoVertice();

    while (i != NULL)
    {
       while (j != NULL)
       {
            Vertice *temp;
            Aresta *A_temp = j->getPrimeira();
            temp = getV(A_temp->getIdAdjacente());
            
            while(temp != NULL)
            {
                if(temp->getId() == i->getId())
                {
                    Vertice *k = j->getProximoVertice();
                    while(k != NULL)
                    {
                        Vertice *temp;
                        Aresta *A_temp = k->getPrimeira();
                        temp = getV(A_temp->getIdAdjacente());
                        while(temp != NULL)
                        {
                            if(temp->getId() == i->getId())
                            {
                                if(temp->getId() == k->getId())
                                   closed++;
                                else
                                   open++;   
                            }
                        }
                    }
                }
            }
            j->getProximoVertice();
       }
       
       i->getProximoVertice();
    }

    if(open + closed == 0)
       return 0;

    return closed / (open + closed);   
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
  if (!this->getPeso_aresta() && !this->getPeso_vertice()) // Sem peso nas arestas e sem peso nos n??s
  {

    while (arquivo >> idVerticeOrigem >> idVerticeDestino >> pesoAresta) {
      //cout << "Edge: " << idNodeSource << " -- " << idNodeTarget << endl;
      this->addAresta(idVerticeOrigem, idVerticeDestino, 0);
      cout << idVerticeOrigem << idVerticeDestino << pesoAresta << endl;
    }
  } else if (this->getPeso_aresta() && !this->getPeso_vertice()) // Com peso nas arestas e sem peso nos n??s
  {
    while (arquivo >> idVerticeOrigem >> idVerticeDestino >> pesoAresta) {
      //cout << "Edge: " << idNodeSource << " - " << idNodeTarget << " - " << edgeWeight << endl;
      this->addAresta(idVerticeOrigem, idVerticeDestino, pesoAresta);
    }
  } else if (this->getPeso_vertice() && !this->getPeso_aresta()) // Com peso no n?? e sem peso na aresta
  {
    float pesoVerticeOrigem, pesoVerticeDestino;

    while (arquivo >> idVerticeOrigem >> pesoVerticeOrigem >> idVerticeDestino >> pesoVerticeDestino) {
      this->addAresta(idVerticeOrigem, idVerticeDestino, 0);
      this->getV(idVerticeOrigem)->setPeso(pesoVerticeOrigem);
      this->getV(idVerticeDestino)->setPeso(pesoVerticeDestino);
    }
  } else if (this->getPeso_vertice() && this->getPeso_aresta()) // Com peso no n?? e com peso na aresta
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
    if(this->getV(id)!=nullptr){
        this->limparVisitados();
        profundidade(this->getV(id));
        for (Vertice *vertice = this->getPrimeiro(); vertice!=nullptr; vertice = vertice->getProximoVertice()){
            if(vertice->getVisitado()){
                cout << vertice->getId() << "  ";
            }
        }
    cout << endl;
    }
    else{
        cout << "Vertice nao encontrado" << endl;
    }
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
    Vertice *indice = this->getV(id);    // N?? alvo que recebe o id passado como par??metro.
    Vertice *primeiro = this->getPrimeiro(); // N?? atrav??s do qual ser?? feita a verifica????o se target ?? acess??vel.

    // Verifica se o n?? target existe.
    if (indice != nullptr)
    {

        // Realiza a busca em profundidade para todos os n??s do grafo.
        while (primeiro != nullptr)
        {

            this->limparVisitados(); // Chama a fun????o para setar todos os n??s do grafo como n??o visitados.

            this->profundidade(primeiro); // Realiza o caminho em profundidade no grafo a partir do n?? source.

            // Se target foi visitado no caminho em profundidade, imprime o id de source.
            if (indice->getVisitado())
            {
                cout << primeiro->getId() << "  ";

            }
            primeiro = primeiro->getProximoVertice();
        }

    }
    // Se target n??o existe, imprime uma mensagem de erro.
    else
    {
        cout << "Vertice nao encontrado" << endl;
    }
}
float Grafo::caminhoMinimoDijkstra(int idOrigem, int idDestino)
{
    this->limparVisitados();
    Vertice *origem, *destino;
    int distancia;    

    if (idOrigem == idDestino)
    {
        cout << "\n\nA dist??ncia ??: " << 0 << endl;
        return 0;
    } //Encer?? caso seja o mesmo no

    origem = getV(idOrigem); //Busca o no
    destino = getV(idDestino); //Busca o no

    if (origem != nullptr && destino != nullptr)
    {

        int pSource = origem->getPosicao(), pTarget = destino->getPosicao(), distancia = INFINITO, V = getOrdem();
        int ver = 0, c_edge = 0, u;

        int *distance = new int[V];  //Vetor para os dist??ncias entre a posi????o do noSorce e os demais
        int *antec = new int[V];     //Vetor para os antecessores
        bool *visited = new bool[V]; //Vetor para as posi????es j?? visitadas
        for (int i = 0; i < V; i++)
        {
            distance[i] = INFINITO;
            visited[i] = false;
        }                      //Inicializador dos vetores visitados e dist??ncia
        distance[pSource] = 0; //Dist??ncia do vertice para ele mesmo

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fp; //Fila de prioridade para os pares distancia e vertice

        fp.push(make_pair(distance[pSource], pSource)); //Adiciona o par vetor dist??ncia e

        pair<int, int> p = fp.top(); //Adiciona o p na fila de prioridade

        Vertice *vertice = nullptr;
        Aresta *aresta = nullptr;

        while (!fp.empty())
        {

            pair<int, int> p = fp.top(); //Pega o do topo
            u = p.second;                //Obtem o v??rtice
            fp.pop();                    //Remove da lista de prioridade
            if (visited[u] == false)
            {
                visited[u] = true; //Marca o vertice como visitado
                vertice = getVerticePosicao(u);
                if (vertice != nullptr) //Busca o no pela posi????o
                    aresta = vertice->getPrimeira();
                else
                    aresta = nullptr; //Pega a primeira aresta do no

                while (aresta != nullptr)
                { //Passa por todas as arestas do vertice u

                    if (!getPeso_aresta())
                        c_edge = 1; //Para caso n??o haja pesso a dist??ncia ser?? 1 por salto
                    else
                        c_edge = aresta->getPeso();

                    ver = aresta->getIdAdjacentePosicao(); //Pega a posi????o do no Target dessa aresta

                    if (distance[ver] > (distance[u] + c_edge))
                    {                                           //Verifica se a dist??ncia ?? menor
                        antec[ver] = u;                         //Atualiza o antecessor
                        distance[ver] = (distance[u] + c_edge); //Atualiza a dist??ncia
                        fp.push(make_pair(distance[ver], ver)); //Adiciona o vertice na fila de prioridade
                    }
                    aresta = aresta->getProx(); //Avan??a para o a proxima aresta do vertice
                }
            }
        }

        distancia = distance[pTarget];

        delete[] distance; //Desalocando o vetore usado
        delete[] visited;  //Desalocando o vetore usado

        if (distancia < INFINITO)
            saidaDijkstra(antec, pSource, pTarget); //Imprime todo a lista na ordem de acesso

        delete[] antec;
        cout << "\n\nA dist??ncia ??: " << distancia << endl;
        return distancia;
    }
    else
    {

        if (origem == nullptr)
            cout << "Source node n??o existe nesse grafo" << endl;
        if (destino == nullptr)
            cout << "Target node n??o existe nesse grafo" << endl;
        return -1;
    }
}
Grafo *Grafo::getVertInduz(vector<int> idvertices)
{
    // Criar o subgrafo v??rtice induzido
    Grafo *subgrafo = new Grafo(idvertices.size(), this->getDirecionado(), this->getPeso_aresta(), this->getPeso_vertice());
    
    bool verifica = 1;
    //Verificar de todos os vertices passados por parametro existem no grafo
    for (int i = 0; i < idvertices.size(); i++){
        if(this->getV(idvertices[i]) == nullptr){
            cout << "O vertice" << idvertices[i] << "nao existe no grafo, nao e possivel obter um grafo vertice induzido" << endl;
            verifica = 0;
        }
    }

    if (verifica = 1){
        // Inserindo as arestas correspondentes no subgrafo
    this->limparVisitados();
    for (int i = 0; i < idvertices.size(); i++)
    {
        for (int j = i + 1; j < idvertices.size(); j++)

            // Verificar se a aresta realmente existe no grafo original
            if ((!this->getV(idvertices[j])->getVisitado()) && this->getV(idvertices[i])->procurarAresta(idvertices[j]))
            {
                Aresta *aux = this->getV(idvertices[i])->getAresta(idvertices[j]);
                subgrafo->addAresta(idvertices[i], idvertices[j], aux->getPeso());
            }
            else
                subgrafo->addVertice(idvertices[j]);

        this->getV(idvertices[i])->setVisitado(true);
    }

    cout << "\nO Subgrafo X foi gerado com sucesso! ";
    cout << "(Ordem = " << subgrafo->getOrdem() << " e Num de Arestas = " << subgrafo->getTotalArestas() << ")" << endl;

    return subgrafo;

    }
    else{
        return nullptr;
    }
}
// Estrutura e fun????es para o algoritmo de Kruskal
struct Arvore
{
    int pai;
    int ordem;
};

// Fun????o para encontrar em qual arvore est?? o o vertice de id n. Usada no Kruskal
int qualArvore(Arvore subarvores[], int n)
{
    if (subarvores[n].pai != n)
        subarvores[n].pai = qualArvore(subarvores, subarvores[n].pai);

    return subarvores[n].pai;
}

// Fun????o para unir duas arvores de dois n??s u e v. Usada no Kruskal
void unirArvores(Arvore subarvores[], int u, int v)
{
    // Encontrando os ??ndices das sub??rvores
    int subU = qualArvore(subarvores, u);
    int subV = qualArvore(subarvores, v);

    // Unindo a menor com a maior
    if (subarvores[subU].ordem < subarvores[subV].ordem)
        subarvores[subU].pai = subV;
    else if (subarvores[subU].ordem > subarvores[subV].ordem)
        subarvores[subV].pai = subU;

    else
    {
        subarvores[subV].pai = subU;
        subarvores[subU].ordem += subarvores[subV].ordem;
    }
}

void Grafo::imprimirPrim(Grafo *subgrafo, vector<int> &agm)
{
    //funcao para imprimir agm via Prim, com a criacao do arquivo dot para uso no graphviz
    ofstream output_Prim;
    output_Prim.open("output_Prim.dot", ios::out | ios::trunc);
    output_Prim << "graph{\n";

    int peso = 0;
    cout << "\n??RVORE GERADORA M??NIMA via Prim\n"
         << endl;
    for (int i = 0; i < subgrafo->getOrdem(); i++)
    {
        if (agm[i] != INFINITO)
        {
            int id_destino = subgrafo->getVerticePosicao(i)->getId();
            if (agm[i] == id_destino){
                cout << "  " << agm[i] << endl;
                output_Prim <<  agm[i] << ";" << endl;
            }

            else
            {
                cout << "  " << agm[i] << " -- " << id_destino;
                //cout << " Peso = " << arestas[agm[i]].first  << endl;
                peso += subgrafo->getV(agm[i])->getAresta(id_destino)->getPeso();
                output_Prim << " [label = " << subgrafo->getV(agm[i])->getAresta(id_destino)->getPeso() << "]" << endl;
                output_Prim<<agm[i] << " -- " << id_destino;
            }
        }
    }

    cout << "\nPeso da AGM: " << peso << endl;
    cout << "\nPrim conclu??do com sucesso!" << endl;

    output_Prim << "}";
    output_Prim.close();
    system("dot -Tpng output_Prim.dot -o output_Prim.png");

}

// Fun????o para imprimir a AGM via Kruskal
void imprimirKruskal(vector<pair<int, pair<int, int>>> &arestas, vector<int> &agm)
{
    //funcao para imprimir agm via Kruskal, com a criacao do arquivo dot para uso no graphviz
    ofstream output_Kruskal;
    output_Kruskal.open("output_Kruskal.dot", ios::out | ios::trunc);
    output_Kruskal << "graph{\n";

    int peso = 0;
    cout << "\n??RVORE GERADORA M??NIMA via Kruskal\n"
         << endl;
    for (int i = 0; i < agm.size(); i++)
    {
        if (arestas[agm[i]].second.first == arestas[agm[i]].second.second){
            cout << "  " << arestas[agm[i]].second.first << endl;
            output_Kruskal << arestas[agm[i]].second.first << ";" << endl;
        }
        else
        {
            cout << "  " << arestas[agm[i]].second.first << " -- " << arestas[agm[i]].second.second;
            cout << " Peso = " << arestas[agm[i]].first  << endl;
            peso += arestas[agm[i]].first;
            output_Kruskal << arestas[agm[i]].second.first << " -- " << arestas[agm[i]].second.second;
            output_Kruskal << "[label = " << arestas[agm[i]].first << "];" << endl;

        }

    }
    cout << endl;
    cout << "\nPeso da AGM: " << peso << endl;
    cout << "\nKruskal conclu??do com sucesso!" << endl;

    output_Kruskal << "}";
    output_Kruskal.close();
    system("dot -Tpng output_Kruskal.dot -o output_Kruskal.png");
}
// ALGORITMO DE KRUSKAL
// para encontrar a ??rvore Geradora M??nima
void Grafo::arvoreGeradoraKruskal(vector<int> vertices)
{
    Grafo* subgrafo = this->getVertInduz(vertices); //criando um subgrafo com o conjunto de vertices dado
    cout << "\nArvore Geradora Minima pelo Algoritmo de Kruskal" << endl;

    //armazenar as arestas do grafo
    vector<pair<int, pair<int, int>>> arestas; //vector<peso, vertice de origem, vertice de destino>
    arestas.clear();

    this->limparVisitados();
    subgrafo->limparVisitados();
    Vertice *noAux = subgrafo->getPrimeiro();
    Aresta *arestaAux = noAux->getPrimeira();

    int u = noAux->getId(); // id do vertice de origem
    int v;

    if (arestaAux != nullptr)
        v = arestaAux->getIdAdjacente(); //id do vertice destino

    // Percorrer as arestas do Grafo
    for (int i = 1; i < subgrafo->getOrdem(); i++)
    {
        if (arestaAux == nullptr)
            arestas.push_back({INFINITO, {u, u}});

        while (arestaAux != nullptr)
        {
            // armazena a aresta no vetor de arestas
            if (!subgrafo->getV(v)->getVisitado())
                arestas.push_back({arestaAux->getPeso(), {u, v}});

            // se a aresta n??o for null muda os valores dos auxiliares
            arestaAux = arestaAux->getProx();
            if (arestaAux != nullptr)
            {
                v = arestaAux->getIdAdjacente();
            }
        }

        noAux->setVisitado(true);
        noAux = subgrafo->getVerticePosicao(i);
        arestaAux = noAux->getPrimeira();
        u = noAux->getId();
        if (arestaAux != nullptr)
            v = arestaAux->getIdAdjacente();
    }


    //ordenar as arestas
    sort(arestas.begin(), arestas.end());

    //criando subarvores com um vertice
    int V = subgrafo->getOrdem();
    Arvore *subarvores = new Arvore[(V * sizeof(Arvore))]; //armazenar todas as sub??rvores

    for (int i = 0; i < V; i++)
    {
        subarvores[i].pai = i;
        subarvores[i].ordem = 1;
    }

    //arvore geradora minima
    vector<int> agm; // vetor com o ??ndice da posi????o de cada aresta da agm do vetor arestas
    agm.clear();

    //algoritmo 
    int cont = 0;
    while (agm.size() < V - 1 && cont < arestas.size())
    {
        pair<int, int> proxAresta = arestas[cont].second;
        int u = proxAresta.first;
        int v = proxAresta.second;

        if (u == v)
            agm.push_back(cont);

        // Se u e v n??o est??o na mesma sub??rvore
        if (qualArvore(subarvores, subgrafo->getV(u)->getPosicao()) != qualArvore(subarvores, subgrafo->getV(v)->getPosicao()))
        {
            agm.push_back(cont);
            unirArvores(subarvores, subgrafo->getV(u)->getPosicao(), subgrafo->getV(v)->getPosicao());
        }
        cont++;
    }

    //impressao da agm
    imprimirKruskal(arestas, agm);

    delete[] subarvores;
    return;
}
Vertice *Grafo::getVerticePosicao(int posicao)
{
    //cria ponteiro para percorrer a lista de nodes
    Vertice *vertice = this->getPrimeiro();

    //encontra o node com o id desejado
    while (vertice != nullptr)
    {
        if (vertice->getPosicao() == posicao)
            return vertice;

        vertice = vertice->getProximoVertice();
    }

    //retorna o node ou null caso nao encontre
    return nullptr;
}
void Grafo::arvoreCaminhamentoProfundidade(int id)
{
    cout << "Caminhamento em profundidade, destacando arestas de retorno" << endl;
    // vari??veis
    this->limparVisitados();
    vector<int> retorno; //vetor para guardar os indices dos vertices que relacinados com as arestas de retorno
    vector<int> vertices; //vetor para guardar o indices dos vertices da arvore em profundidade
    vector<string> grafo; //vetor de string para gerar arquiv dot

    //Checar se o id do vertice passado como parametro ?? v??lido
    if(this->getV(id)==nullptr){
        cout << "Indice invalido, vertice nao existe no grafo" << endl;
    }

    else{
        Vertice *vertice = this->getV(id);
        this->auxCaminhamentoProfundidade(vertice, &vertices, &retorno, &grafo); // chama a fun????o auxiliar

        cout << "\n??rvore em Profundidade\n";
        for (int i = 0; i < vertices.size(); i++)
            cout << vertices[i] << " -- ";

        cout << "\n\nArestas de Retorno\n";
        for (int i = 0; i < retorno.size(); i++)
            cout << retorno[i] << " -- ";
        cout << endl;

        //GERANDO ARQUIVO DOT PARA USO NO GRAPHVIZ
        ofstream output_profundidade;
        output_profundidade.open("output_profundidade.dot", ios::out | ios::trunc);
        output_profundidade << "graph{\n";
        for (int i = 0; i < grafo.size(); i++)
        {
            output_profundidade << grafo.at(i) << ";" << endl;
        }
        output_profundidade << "}";
        output_profundidade.close();
        system("dot -Tpng output_profundidade.dot -o output_profundidade.png");

        retorno.clear();
        vertices.clear();
        grafo.clear();
    }
}
void Grafo::auxCaminhamentoProfundidade(Vertice *v, vector<int> *findG, vector<int> *retorno,vector<string> *graf)
{
    //funcao auxiliar para caminhamento em profundidade destacando as arestas de retorno
    findG->push_back(v->getId());
    v->setVisitado(true);
    for (Aresta *aresta = v->getPrimeira(); aresta != nullptr; aresta = aresta->getProx())
    {
        if (!getV(aresta->getIdAdjacente())->getVisitado())
        {
            graf->push_back(to_string(v->getId()) + " -- " + to_string(aresta->getIdAdjacente()));
            auxCaminhamentoProfundidade(getV(aresta->getIdAdjacente()), findG, retorno,graf);
        }
    }
    retorno->push_back(v->getId()); 
}
// Fun????o para auxiliar o algoritmo de Prim. Retorna a posi????o do n?? com menor custo de vizinhan??a que n??o esteja na agm
int posicaoMenor(vector<int> &custoViz, vector<bool> &naAGM)
{
    int min = INFINITO;
    int pos;
    bool tem_pos = false;
    for (int i = 0; i < custoViz.size(); i++)
    {
        if (custoViz[i] < min && naAGM[i] == false)
        {
            min = custoViz[i];
            pos = i;
            tem_pos = true;
        }
    }
    if (tem_pos)
        return pos;
    else
    {
        for (int i = 0; i < custoViz.size(); i++)
        {
            if (custoViz[i] == min && naAGM[i] == false)
            {
                min = custoViz[i];
                pos = i;
                tem_pos = true;
                return pos;
            }
        }
    }
    return pos;
}
void Grafo::arvoreGeradoraPrim(vector<int> vertices)
{
    Grafo *subgrafo = this->getVertInduz(vertices);
    cout << "\nIniciando a execu????o do algoritmo de Prim..." << endl;

    //Organizar os custos das vizinhan??as dos n??s em um vector

    // Vector para armazenar os custoViz dos n??s do subgrafo. O ??ndice no vector ?? compat??vel com a posi????o do n?? no subgrafo
    vector<int> custo;
    custo.clear();

    // Vector para checar se o n?? j?? foi inserido na agm
    vector<bool> naAGM(subgrafo->getOrdem(), false);

    // O primeiro n?? do vector ser?? inicializado com custoViz = 0
    custo.push_back(0);

    // Os demais n??s ser??o inicializados com custoViz = INFINITO
    for (int i = 1; i < subgrafo->getOrdem(); i++)
        custo.push_back(INFINITO);

    // 2?? PASSO: Criar Arvore Geradora Minima -> vetor com os pais de cada n?? da agm ou INF caso nao tenha pai

    // Os ??ndices da agm corresponder??o ?? posi????o do n?? no subgrafo
    // A raiz da agm, indice 0, ser?? o primeiro n?? do subgrafo, portanto n??o ter?? pai
    vector<int> agm(subgrafo->getOrdem(), INFINITO);

    // 3?? PASSO: Iterar pelos v??rtices verificando o custoViz e inserindo na agm

    int cont = 0;
    while (cont < subgrafo->getOrdem())
    {
        // Pega o n?? com menor custoViz que ainda n??o est?? na agm
        int pos_menor = posicaoMenor(custo, naAGM);         // Posi????o do n??
        int u = subgrafo->getVerticePosicao(pos_menor)->getId(); // ID do n??
        // Atualiza naAGM, pois, nessa itera????o, u ser?? colocado na agm
        naAGM[pos_menor] = true;

        // Iterar pelos n??s v adjacentes a u e verificar se o peso da aresta entre eles ?? menor que o seu custoViz
        Aresta *aux = subgrafo->getV(u)->getPrimeira();
        if (aux == nullptr) // n?? n??o tem arestas
            agm[pos_menor] = u;
        else
        {
            while (aux != nullptr)
            {
                int v = aux->getIdAdjacente();                      // ID de v
                int pos_v = subgrafo->getV(v)->getPosicao(); // posi????o de v
                if (!naAGM[pos_v])                               // executa caso o n?? v ainda n??o esteja na agm
                {
                    // Se o peso da aresta (u, v) for menor que o custoViz de v, atualiza o custoViz com o valor do peso
                    if (aux->getPeso() < custo[pos_v])
                    {
                        custo[pos_v] = aux->getPeso();
                        // Atualiza o pai de v na agm
                        agm[pos_v] = u;
                    }
                }
                aux = aux->getProx();
            }
        }
        cont++;
    }

    // 4?? PASSO: Imprimir a ??rvore Geradora M??nima e seu peso

    imprimirPrim(subgrafo, agm);

    return;
}
void Grafo::caminhoMinimo(list<int> &antecessor)
{
    string arco, entrada;                            //Para a escrita no outFile, se for arco '->' se for aresta '--'
    int primeiro = antecessor.front(), tVertice, sVertice; //Usado para armazenar o primeiro vertice

    Vertice *v = getVerticePosicao(primeiro);
    sVertice = v->getId();
    Vertice *aux = nullptr; //No auxiliar
    Aresta *aresta = nullptr;  //Edge auxiliar para pegar o peso
    cout << "\nCAMINHO MINIMO\n"
         << endl;
    while (!antecessor.empty())
    {                                   //Passa por toda a lista de ordem de acesso em buscando o ID
        v = getVerticePosicao(primeiro); //no recebe o node que ?? o primeiro no caminho minimo
        tVertice = v->getId();

        sVertice = tVertice; //Atualiza o valor do sNode

        cout << v->getId() << "--" << arco;   //Imprime para o usu??rio
        antecessor.pop_front();        //Remove o primeiro elemento da lista dos antecessor
        primeiro = antecessor.front(); //Atualiza o valor do primeiro
        aux = v;                    //Atualiza o valor do noAux
    }
}
void Grafo::caminhoMinimoFloyd(int idOrig, int idDest)
{ //
    this->limparVisitados();
    // cost[] e matrizAdjac[] armazenam o menor caminho
    int **cost, **path;
    int **matrizAdjac;
    path = new int *[this->getOrdem()];
    cost = new int *[this->getOrdem()];
    matrizAdjac = new int *[this->getOrdem()];

    //inicializa as matrizes
    for (int i = 0; i < this->getOrdem(); i++)
    {
        path[i] = new int[this->getOrdem()];
        cost[i] = new int[this->getOrdem()];
        matrizAdjac[i] = new int[this->getOrdem()];
        for (int j = 0; j < this->getOrdem(); j++)
        {
            matrizAdjac[i][j] = INFINITO;
            if (i == j)
            {
                matrizAdjac[i][j] = 0;
            }
        }
    }

    Vertice *v = this->getPrimeiro();
    Aresta *a;
    while (v != nullptr)
        {
            a = v->getPrimeira();

            while (a != nullptr)
            {
                    matrizAdjac[v->getId()][a->getIdAdjacente()] = a->getPeso();

                a = a->getProx();
            }
            v = v->getProximoVertice();
        }

    // Preenche cost[] e path[]
    for (int v = 0; v < this->getOrdem(); v++)
    {
        for (int u = 0; u < this->getOrdem(); u++)
        {
            // inicialmente o cost sera igual ao peso da aresta
            cost[v][u] = matrizAdjac[v][u];
            if (v == u)
                path[v][u] = 0;
            else if (cost[v][u] != INFINITO)
                path[v][u] = v;
            else
                path[v][u] = -1;
        }
    }

    //algoritmo de Floyd
    //como a complexidade deste algoritmo ?? O(n^3), para instancias muito grandes ele demora a executar
    for (int k = 0; k < this->getOrdem(); k++)
    {
        for (int v = 0; v < this->getOrdem(); v++)
        {
            for (int u = 0; u < this->getOrdem(); u++)
            {
                // caso o vertice k esteja no menor path de v para u, ent??o o valor da posi????o cost[v][u] ?? atualizado
                if (cost[v][k] != INFINITO && cost[k][u] != INFINITO && cost[v][k] + cost[k][u] < cost[v][u])
                {
                    cost[v][u] = cost[v][k] + cost[k][u];
                    path[v][u] = path[k][u];
                }
            }

            // se os elementos da diagonal se tornam negativos, o grafo atua em um ciclo de peso negativo
            if (cost[v][v] < 0)
            {
                cout << "** Ciclo de peso negativo!! **"<<endl;
                return;
            }
        }
    }

    //Resultado em tela
    imprimirFloyd(path, cost, idOrig, idDest);

    for (int i = 0; i < this->getOrdem(); i++)
    {
        delete[] path[i];
        delete[] cost[i];
        delete[] matrizAdjac[i];
    }
    delete[] path;
    delete[] cost;
    delete[] matrizAdjac;
    
    getchar();
    getchar();
}

//Fun????o para imprimir em tela o resultado

void Grafo::imprimirFloyd(int **path, int **cost, int idOrig, int idDest)
{
    cout << "Caminho minimo entre " << idOrig << " e " << idDest << " usando Floyd " << endl;

    if(cost[idOrig][idDest]==INFINITO){
        cout << idOrig << ", "<< idDest<<"]"<< " - " <<" Nao existe caminho" <<endl;
    }
    else if(idOrig == idDest)
    {
        cout << idOrig << ", "<<idDest << " - "<< "0"<< endl;
    }
    else{
        cout <<  idOrig << ", ";
        imprimirCaminhoFloyd(path, idOrig, idDest);
        cout << idDest << " - ";
        cout<< cost[idOrig][idDest] << endl;
    }
}


//Auxiliar para imprimir caminho minimo no algoritimo de Floyd

void Grafo::imprimirCaminhoFloyd(int **path, int idOrig, int idDest)
{
        if (path[idOrig][idDest] == idOrig)
        return;

        imprimirCaminhoFloyd(path, idOrig, path[idOrig][idDest]);
        cout << path[idOrig][idDest] << ", ";

}
void Grafo::saidaDijkstra(int antecessor[], int idOrigem, int idDestino)
{

    string arco;
    int noAnterior, primeiro, tNode, sNode; //Usado para armazenar o vertice anterior, e auxiliar na escrita no arquivo dot

    list<int> ordemAcesso; //Lista contendo a ordem de acesso dos vertices

    ordemAcesso.push_front(idDestino);  //Armazena na lista na ordem de acesso dos vertices,
    noAnterior = antecessor[idDestino]; //apartir de seus anteriores, come??ando pelo n?? target

    while (noAnterior != idOrigem)
    {
        ordemAcesso.push_front(noAnterior);
        noAnterior = antecessor[noAnterior];
    }
    ordemAcesso.push_front(idOrigem); //Insere o n?? Source como o primeiro a ser acessado
    primeiro = ordemAcesso.front();

    caminhoMinimo(ordemAcesso);
}
//quantas vezes um n?? aparece na lista de outro n??
int Grafo::aparecerNaLista(int id, int id_encontrar) {
    Vertice *vertice = this->getV(id);
    Aresta *aresta = nullptr;
    int valor = 0; //quantas vezes um n?? aparece na lista de outro n??

    if (vertice != nullptr) {
        aresta = vertice->getPrimeira();
        while (aresta != nullptr) {
            if (aresta->getIdAdjacente() == id_encontrar)
                valor++;
            aresta = aresta->getProx();
        }
    }
    return valor;
}
float Grafo::coeficienteLocal(int id) {
    Vertice *vertice = this->getV(id);
    Vertice *aux = nullptr;
    Aresta *aresta = nullptr;
    Aresta *auxiliar = nullptr;
    float coeficiente = 0; //coeficiente local
    float grauEntradaVertice = 0; //grau de entrada do vertice id
    float P = 0;

    if(vertice != nullptr) {
        grauEntradaVertice = vertice->getGrauEntrada();
        aresta = vertice->getPrimeira();
        float idAresta;
        while(aresta != nullptr) {
            idAresta = aresta->getIdAdjacente();
            aux = this->getV(idAresta);
            // Acessa a lista de adj da lista de adj de vertide id
            if (aux != nullptr) {
                auxiliar = aux->getPrimeira();
                while(auxiliar != nullptr) {
                    P += this->aparecerNaLista(auxiliar->getIdAdjacente(), id);
                    auxiliar = auxiliar->getProx();
                }
            }
            aresta = aresta->getProx();
        }
    }
    if(grauEntradaVertice != 1) {
        grauEntradaVertice=(grauEntradaVertice*(grauEntradaVertice-1))/2;
    }
    coeficiente = float(P/grauEntradaVertice);
    // cout << P << "/" << dv << endl;
    return coeficiente;
}
float Grafo::coeficienteMedio() {
    Vertice *vertice = this->getPrimeiro();
    float coeficiente = 0; //coeficiente de agrupamento
    int id;
    float resultado; //coeficiente de agrupamento medio do grafo;

    while(vertice != nullptr) {
        id = vertice->getId();
        coeficiente += this->coeficienteLocal(id);
        vertice = vertice->getProximoVertice();
    }

    resultado = coeficiente/this->getOrdem();

    return resultado;
}
