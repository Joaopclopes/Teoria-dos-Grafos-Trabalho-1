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

        // confere se a aresta já existe
        if (!vertice->procurarAresta(id_destino))
        {
            // caso o node exista mas a aresta nao, insere a aresta
            vertice->inserirAresta(id_destino, aux->getPosicao(),peso);

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
    Vertice *vertice = this->getPrimeiro(); // Ponteiro que armazena o endereço de memória do primeiro nó do grafo.

    // Realiza a operação para todos os nós do grafo.
    while (vertice != nullptr)
    {
        vertice->setVisitado(false);    // Define o nó como não visitado.
        vertice = vertice->getProximoVertice(); // Ponteiro passa a apontar para o próximo nó do grafo.
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
    Vertice *indice = this->getV(id);    // Nó alvo que recebe o id passado como parâmetro.
    Vertice *primeiro = this->getPrimeiro(); // Nó através do qual será feita a verificação se target é acessível.

    // Verifica se o nó target existe.
    if (indice != nullptr)
    {

        // Realiza a busca em profundidade para todos os nós do grafo.
        while (primeiro != nullptr)
        {

            this->limparVisitados(); // Chama a função para setar todos os nós do grafo como não visitados.

            this->profundidade(primeiro); // Realiza o caminho em profundidade no grafo a partir do nó source.

            // Se target foi visitado no caminho em profundidade, imprime o id de source.
            if (indice->getVisitado())
            {
                cout << primeiro->getId() << "  ";

            }
            primeiro = primeiro->getProximoVertice();
        }

    }
    // Se target não existe, imprime uma mensagem de erro.
    else
    {
        cout << "Vertice nao encontrado" << endl;
    }
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

void Grafo::caminhoMinimoDijkstra(int id_inicio ,int id_final)
{
    Vertice *v_inicio,*v_final;

    v_inicio = getV(id_inicio);
    v_final  = getV(id_final);

    if(v_inicio != nullptr && v_final != nullptr)
    {

        int p_inicio = getPosicao(id_inicio), p_final = getPosicao(id_final), distance = INFINITO, V = getOrdem();
        int ver = 0, aresta = 0, u;

        int *distancia  = new int[V];
        int *antec      = new int[V];
        bool *visitados = new bool[V];
        
        for(int i = 0; i < V; i++)
        {
            distancia[i] = INFINITO;
            visitados[i] = false;
        }
        distancia[p_inicio] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila_prioridade;

        fila_prioridade.push(make_pair(distancia[p_inicio], p_inicio));

        pair<int, int> p = fila_prioridade.top();

        Vertice *vert = nullptr;
        Aresta  *are = nullptr;

        while(!fila_prioridade.empty())
        {

            pair<int, int> p = fila_prioridade.top();
            u = p.second;
            fila_prioridade.pop();
            if(visitados[u] == false)
            {
                visitados[u] = true;
                vert = getVPosicao(u);
                if(vert != nullptr)
                    are = vert->getPrimeira();
                else
                    are = nullptr;

                while(are != nullptr)
                {
                    if(!getPeso_aresta())
                        aresta = 1;
                    else
                        aresta = are->getPeso();
                    
                    ver = getPosicao(are->getIdAdjacente());

                    if(distancia[ver] > (distancia[u] + aresta))
                    {
                        antec[ver] = u;
                        distancia[ver] = (distancia[u] + aresta);
                        fila_prioridade.push(make_pair(distancia[ver], ver));
                    }
                    are = are->getProx();
                }        
            }
        }

        distance = distancia[p_final];

        delete[] distancia;
        delete[] visitados;

        // if(distance < INFINITO)
        //    sai
    }
}

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
Grafo *Grafo::getVertInduz(vector<int> idvertices)
{
    // Criar o subgrafo vértice induzido
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
// Estrutura e funções para o algoritmo de Kruskal
struct Arvore
{
    int pai;
    int ordem;
};

// Função para encontrar em qual arvore está o o vertice de id n. Usada no Kruskal
int qualArvore(Arvore subarvores[], int n)
{
    if (subarvores[n].pai != n)
        subarvores[n].pai = qualArvore(subarvores, subarvores[n].pai);

    return subarvores[n].pai;
}

// Função para unir duas arvores de dois nós u e v. Usada no Kruskal
void unirArvores(Arvore subarvores[], int u, int v)
{
    // Encontrando os índices das subárvores
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
// Função para imprimir a AGM via Kruskal
void imprimirKruskal(vector<pair<int, pair<int, int>>> &arestas, vector<int> &agm)
{
    //funcao para imprimir agm via Kruskal, com a criacao do arquivo dot para uso no graphviz
    ofstream output_Kruskal;
    output_Kruskal.open("output_Kruskal.dot", ios::out | ios::trunc);
    output_Kruskal << "graph{\n";

    int peso = 0;
    cout << "\nÁRVORE GERADORA MÍNIMA via Kruskal\n"
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
    cout << "\nKruskal concluído com sucesso!" << endl;

    output_Kruskal << "}";
    output_Kruskal.close();
    system("dot -Tpng output_Kruskal.dot -o output_Kruskal.png");
}
// ALGORITMO DE KRUSKAL
// para encontrar a Árvore Geradora Mínima
void Grafo::arvoreGeradoraKruskal(vector<int> vertices)
{
    Grafo* subgrafo = this->getVertInduz(vertices); //criando um subgrafo com o conjunto de vertices dado
    cout << "\nArvore Geradora Minima pelo Algoritmo de Kruskal" << endl;

    //armazenar as arestas do grafo
    vector<pair<int, pair<int, int>>> arestas; //vector<peso, vertice de origem, vertice de destino>
    arestas.clear();

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

            // se a aresta não for null muda os valores dos auxiliares
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
    Arvore *subarvores = new Arvore[(V * sizeof(Arvore))]; //armazenar todas as subárvores

    for (int i = 0; i < V; i++)
    {
        subarvores[i].pai = i;
        subarvores[i].ordem = 1;
    }

    //arvore geradora minima
    vector<int> agm; // vetor com o índice da posição de cada aresta da agm do vetor arestas
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

        // Se u e v não estão na mesma subárvore
        if (qualArvore(subarvores, subgrafo->getV(u)->getPosicao()) != qual(subarvores, subgrafo->getV(v)->getPosicao()))
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
    // variáveis
    this->limparVisitados();
    vector<int> retorno; //vetor para guardar os indices dos vertices que relacinados com as arestas de retorno
    vector<int> vertices; //vetor para guardar o indices dos vertices da arvore em profundidade
    vector<string> grafo; //vetor de string para gerar arquiv dot

    //Checar se o id do vertice passado como parametro é válido
    if(this->getV(id)==nullptr){
        cout << "Indice invalido, vertice nao existe no grafo" << endl;
    }

    else{
        Vertice *vertice = this->getV(id);
        this->auxCaminhamentoProfundidade(vertice, &vertices, &retorno, &grafo); // chama a função auxiliar

        cout << "\nÁrvore em Profundidade\n";
        for (int i = 0; i < vertices.size(); i++)
            cout << vertices[i] << " -- ";

        cout << "\n\nArestas de Retorno\n";
        for (int i = 0; i < retorno.size(); i++)
            cout << retorno[i] << " -- ";
        cout << endl;

        //GERANDO ARQUIVO DOT PARA USO NO GRAPHVIZ
        ofstream output_profundidade;
        output_profundidade.open("output_profundidade.dot", ios::out | ios::trunc);
        output_profundidade << "grafo{\n";
        for (int i = 0; i < grafo.size(); i++)
        {
            output_profundidade << grafo.at(i) << endl;
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
            graf->push_back(to_string(v->getId()) + "--" + to_string(aresta->getIdAdjacente()));
            auxCaminhamentoProfundidade(getV(aresta->getIdAdjacente()), findG, retorno,graf);
        }
    }
    retorno->push_back(v->getId()); 
}
