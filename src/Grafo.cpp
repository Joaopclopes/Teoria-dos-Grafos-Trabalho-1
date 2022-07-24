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
#define INF std::numeric_limits<int>::max()


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
/*void Grafo::caminhoMinimoFloyd()
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
}*/

/**
 * Árvore Geradora de Prim
 * */
/*void Grafo::arvoreGeradoraPrim(vector<int> vertices)
{
    Grafo *subgrafo = this->getVertInduz(vertices);
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
    Vertice *v = subgrafo->getPrimeiro();
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
    }*/
    /* Imprime quem é o pai de cada vertice na arvore */
    /*if (debug)
    {
        for (int i = 1; i < tam; i++)
        {
            cout << "[ " << pais[i] << " - " << i << " ] => ";
        }
    }

    cout << endl
         << "Peso minimo: " << pesoTotalMinimo; //peso minimo para percorrer o grafo todo
} */
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
            arestas.push_back({INF, {u, u}});

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
// Função para imprimir a AGM via Prim
void imprimirPrim(Grafo *subgrafo, vector<int> &agm)
{
    ofstream output_Prim;
    output_Prim.open("output_Prim.dot", ios::out | ios::trunc);
    output_Prim << "graph{\n";

    int peso = 0;
    cout << "\nÁRVORE GERADORA MÍNIMA via Prim\n"
         << endl;
    cout << "graph {" << endl;
    for (int i = 0; i < subgrafo->getOrdem(); i++)
    {
        if (agm[i] != INF)
        {
            int id_destino = subgrafo->getVerticePosicao(i)->getId();
            if (agm[i] == id_destino){
                cout << "  " << agm[i] << endl;
                output_Prim << agm[i] << ";" << endl;
            }
            else
            {
                cout << "  " << agm[i] << " -- " << id_destino;
                cout << " Peso = " << subgrafo->getV(agm[i])->getAresta(id_destino)->getPeso() << endl;
                peso += subgrafo->getV(agm[i])->getAresta(id_destino)->getPeso();
                output_Prim << agm[i] << " -- " << id_destino;
                output_Prim << "[label = " << subgrafo->getV(agm[i])->getAresta(id_destino)->getPeso()<< "];" << endl;
            }
        }
    }
    cout << "}" << endl;
    cout << "\nPeso da AGM: " << peso << endl;
    cout << "\nPrim concluído com sucesso!" << endl;

    output_Prim << "}";
    output_Prim.close();
    system("dot -Tpng output_Prim.dot -o output_Prim.png");      
}
// Função para auxiliar o algoritmo de Prim. Retorna a posição do nó com menor custo de vizinhança que não esteja na agm
int posicaoMenor(vector<int> &custoViz, vector<bool> &naAGM)
{
    int min = INF;
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
    cout << "\nIniciando a execução do algoritmo de Prim..." << endl;

    //Organizar os custos das vizinhanças dos nós em um vector

    // Vector para armazenar os custoViz dos nós do subgrafo. O índice no vector é compatível com a posição do nó no subgrafo
    vector<int> custo;
    custo.clear();

    // Vector para checar se o nó já foi inserido na agm
    vector<bool> naAGM(subgrafo->getOrdem(), false);

    // O primeiro nó do vector será inicializado com custoViz = 0
    custo.push_back(0);

    // Os demais nós serão inicializados com custoViz = INFINITO
    for (int i = 1; i < subgrafo->getOrdem(); i++)
        custo.push_back(INF);

    // 2º PASSO: Criar Arvore Geradora Minima -> vetor com os pais de cada nó da agm ou INF caso nao tenha pai

    // Os índices da agm corresponderão à posição do nó no subgrafo
    // A raiz da agm, indice 0, será o primeiro nó do subgrafo, portanto não terá pai
    vector<int> agm(subgrafo->getOrdem(), INF);

    // 3º PASSO: Iterar pelos vértices verificando o custoViz e inserindo na agm

    int cont = 0;
    while (cont < subgrafo->getOrdem())
    {
        // Pega o nó com menor custoViz que ainda não está na agm
        int pos_menor = posicaoMenor(custo, naAGM);         // Posição do nó
        int u = subgrafo->getVerticePosicao(pos_menor)->getId(); // ID do nó
        // Atualiza naAGM, pois, nessa iteração, u será colocado na agm
        naAGM[pos_menor] = true;

        // Iterar pelos nós v adjacentes a u e verificar se o peso da aresta entre eles é menor que o seu custoViz
        Aresta *aux = subgrafo->getV(u)->getPrimeira();
        if (aux == nullptr) // nó não tem arestas
            agm[pos_menor] = u;
        else
        {
            while (aux != nullptr)
            {
                int v = aux->getIdAdjacente();                      // ID de v
                int pos_v = subgrafo->getV(v)->getPosicao(); // posição de v
                if (!naAGM[pos_v])                               // executa caso o nó v ainda não esteja na agm
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

    // 4º PASSO: Imprimir a Árvore Geradora Mínima e seu peso

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
        v = getVerticePosicao(primeiro); //no recebe o node que é o primeiro no caminho minimo
        tVertice = v->getId();

        sVertice = tVertice; //Atualiza o valor do sNode

        cout << v->getId() << "--" << arco;   //Imprime para o usuário
        antecessor.pop_front();        //Remove o primeiro elemento da lista dos antecessor
        primeiro = antecessor.front(); //Atualiza o valor do primeiro
        aux = v;                    //Atualiza o valor do noAux
    }
}
void Grafo::caminhoMinimoFloyd(int idOrig, int idDest)
{ //
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
            matrizAdjac[i][j] = INF;
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
            else if (cost[v][u] != INF)
                path[v][u] = v;
            else
                path[v][u] = -1;
        }
    }

    //algoritmo de Floyd
    //como a complexidade deste algoritmo é O(n^3), para instancias muito grandes ele demora a executar
    for (int k = 0; k < this->getOrdem(); k++)
    {
        for (int v = 0; v < this->getOrdem(); v++)
        {
            for (int u = 0; u < this->getOrdem(); u++)
            {
                // caso o vertice k esteja no menor path de v para u, então o valor da posição cost[v][u] é atualizado
                if (cost[v][k] != INF && cost[k][u] != INF && cost[v][k] + cost[k][u] < cost[v][u])
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
    printFloyd(path, cost, idOrig, idDest);

    for (int i = 0; i < this->getOrdem(); i++)
    {
        delete[] path[i];
        delete[] cost[i];
        delete[] matrizAdjac[i];
    }
    delete[] path;
    delete[] cost;
    delete[] matrizAdjac;
    cout << "-------------------------------------------------------------------" << endl;

    getchar();
    getchar();
}

//Função para imprimir em tela o resultado

void Grafo::printFloyd(int **path, int **cost, int idOrig, int idDest)
{
    cout << "-------------------------------FLOYD-------------------------------" << endl;
    cout << "[caminho minimo entre os nos " << idOrig << " e " << idDest << " ]" << " - custo do caminho minimo" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    if(cost[idOrig][idDest]==INF){
        cout<< "[ "<<idOrig << ", "<< idDest<<"]"<< " - " <<"Nao existe caminho"<<endl;
    }
    else if(idOrig == idDest)
    {
        cout<< "[ " << idOrig << ", "<<idDest<< "] "<< " - "<< "0"<< endl;
    }
    else{
        cout << "[" << idOrig << ", ";
        printPathFloyd(path, idOrig, idDest);
        cout << idDest << "] - ";
        cout<< cost[idOrig][idDest] << endl;
    }
}


//Auxiliar para imprimir caminho minimo no algoritimo de Floyd

void Grafo::printPathFloyd(int **path, int idOrig, int idDest)
{
        if (path[idOrig][idDest] == idOrig)
        return;

        printPathFloyd(path, idOrig, path[idOrig][idDest]);
        cout << path[idOrig][idDest] << ", ";

}
void Grafo::saidaDijkstra(int antecessor[], int idOrigem, int idDestino)
{

    string arco;
    int noAnterior, primeiro, tNode, sNode; //Usado para armazenar o vertice anterior, e auxiliar na escrita no arquivo dot

    list<int> ordemAcesso; //Lista contendo a ordem de acesso dos vertices

    ordemAcesso.push_front(idDestino);  //Armazena na lista na ordem de acesso dos vertices,
    noAnterior = antecessor[idDestino]; //apartir de seus anteriores, começando pelo nó target

    while (noAnterior != idOrigem)
    {
        ordemAcesso.push_front(noAnterior);
        noAnterior = antecessor[noAnterior];
    }
    ordemAcesso.push_front(idOrigem); //Insere o nó Source como o primeiro a ser acessado
    primeiro = ordemAcesso.front();

    caminhoMinimo(ordemAcesso);
}
float Grafo::caminhoMinimoDijkstra(int idOrigem, int idDestino)
{
    Vertice *origem, *destino;
    int distancia;

    if (idOrigem == idDestino)
    {
        cout << "\n\nA distância é: " << 0 << endl;
        return 0;
    } //Encerá caso seja o mesmo no

    origem = getV(idOrigem); //Busca o no
    destino = getV(idDestino); //Busca o no

    if (origem != nullptr && destino != nullptr)
    {

        int pSource = origem->getPosicao(), pTarget = destino->getPosicao(), distancia = INF, V = getOrdem();
        int ver = 0, c_edge = 0, u;

        int *distance = new int[V];  //Vetor para os distâncias entre a posição do noSorce e os demais
        int *antec = new int[V];     //Vetor para os antecessores
        bool *visited = new bool[V]; //Vetor para as posições já visitadas
        for (int i = 0; i < V; i++)
        {
            distance[i] = INF;
            visited[i] = false;
        }                      //Inicializador dos vetores visitados e distância
        distance[pSource] = 0; //Distância do vertice para ele mesmo

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fp; //Fila de prioridade para os pares distancia e vertice

        fp.push(make_pair(distance[pSource], pSource)); //Adiciona o par vetor distância e

        pair<int, int> p = fp.top(); //Adiciona o p na fila de prioridade

        Vertice *vertice = nullptr;
        Aresta *aresta = nullptr;

        while (!fp.empty())
        {

            pair<int, int> p = fp.top(); //Pega o do topo
            u = p.second;                //Obtem o vértice
            fp.pop();                    //Remove da lista de prioridade
            if (visited[u] == false)
            {
                visited[u] = true; //Marca o vertice como visitado
                vertice = getVerticePosicao(u);
                if (vertice != nullptr) //Busca o no pela posição
                    aresta = vertice->getPrimeira();
                else
                    aresta = nullptr; //Pega a primeira aresta do no

                while (aresta != nullptr)
                { //Passa por todas as arestas do vertice u

                    if (!getPeso_aresta())
                        c_edge = 1; //Para caso não haja pesso a distância será 1 por salto
                    else
                        c_edge = aresta->getPeso();

                    ver = aresta->getIdAdjacentePosicao(); //Pega a posição do no Target dessa aresta

                    if (distance[ver] > (distance[u] + c_edge))
                    {                                           //Verifica se a distância é menor
                        antec[ver] = u;                         //Atualiza o antecessor
                        distance[ver] = (distance[u] + c_edge); //Atualiza a distância
                        fp.push(make_pair(distance[ver], ver)); //Adiciona o vertice na fila de prioridade
                    }
                    aresta = aresta->getProx(); //Avança para o a proxima aresta do vertice
                }
            }
        }

        distancia = distance[pTarget];

        delete[] distance; //Desalocando o vetore usado
        delete[] visited;  //Desalocando o vetore usado

        if (distancia < INF)
            saidaDijkstra(antec, pSource, pTarget); //Imprime todo a lista na ordem de acesso

        delete[] antec;
        cout << "\n\nA distância é: " << distancia << endl;
        return distancia;
    }
    else
    {

        if (origem == nullptr)
            cout << "Source node não existe nesse grafo" << endl;
        if (destino == nullptr)
            cout << "Target node não existe nesse grafo" << endl;
        return -1;
    }
}
