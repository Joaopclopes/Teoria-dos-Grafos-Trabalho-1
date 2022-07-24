/*TRABALHO PARTE 1 - TEORIA DOS GRAFOS 
GRUPO: NUBIA, EWERSON, PEDRO ALEXANDRE, JOAO PEDRO COSTA*/

#include <iostream>
#include <fstream>

#include "Aresta.h"
#include "Grafo.h"

using namespace std;

int menu() {

  int selecao;

  cout << "\nMENU" << endl;
  cout << "----" << endl;
  cout << "[1]  Fecho Transitivo Direto" << endl;
  cout << "[2]  Fecho Transitivo Indireto" << endl;
  cout << "[3]  Coeficiente de agrupamento local do vértice" << endl;
  cout << "[4]  Coeficiente de agrupamento médio do grafo" << endl;
  cout << "[5]  Caminho Mínimo entre dois vértices - Dijkstra" << endl;
  cout << "[6]  Caminho Mínimo entre dois vértices - Floyd" << endl;
  cout << "[7]  Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Prim" << endl;
  cout << "[8]  Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Kruskal" << endl;
  cout << "[9]  Caminhamento Profundidade destacando as Arestas de retorno" << endl;
  cout << "[10]  Imprimir grafo" << endl;
  cout << "[0]  Sair" << endl;

  cout << "\nSua opção: ";
  cin >> selecao;

  return selecao;
}
void selecionar(int selecao, Grafo *grafo) {

  if (selecao == 0) {
    exit(0);
    //Sair;
  }
  else if (selecao == 1){
    // Fecho Transitivo Direto;
    int v;
    cout << "Digite o id do nó: ";
    cin >> v;

    grafo->transitivoDireto(v);
    cout << endl;
  }
  else if (selecao == 2){ // Fecho Transitivo Indireto;
    int h;
    cout << "Digite o id do nó: ";
    cin >> h;
    grafo->transitivoIndireto(h);
    cout << endl;
  }
  else if (selecao == 3){
    //Coeficiente de agrupamento local do vértice"    
  }
  else if (selecao == 4){
    //Coeficiente de agrupamento médio do grafo   
  }
  else if (selecao == 5){ 
    //Caminho Mínimo entre dois vértices - Dijkstra
    int idOrigem, idDestino;
    cout << "Digite o vertice de origem" << endl;
    cin >> idOrigem;
    cout << "Digite o vertice de destino" << endl;
    cin >> idDestino;
    grafo->caminhoMinimoDijkstra(idOrigem,idDestino);
  }
  else if (selecao == 6){ 
    //Caminho Mínimo entre dois vértices - Floyd
    int idOrigem, idDestino;
    cout << "Digite o vertice de origem" << endl;
    cin >> idOrigem;
    cout << "Digite o vertice de destino" << endl;
    cin >> idDestino;
    grafo->caminhoMinimoFloyd(idOrigem,idDestino);
  }
  else if (selecao == 7){
    //Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Prim 
    cout << "\nPara rodar o algoritmo de Prim, é preciso um subgrafo vértice induzido" << endl;
    cout << "\nDigite quantos vertices tera o subgrafo vertice induzido: ";
    // Vector para armazenar os ids dos vértices do subgrafo
        vector<int> idvertices;
        idvertices.clear();

        // Lendo os vértices do subgrafo
        int num;
        cin >> num;
        for (int i = 0; i < num; i++){
          cout << "Digite o " << i+1 << "º vertice:";
          int id;
          cin >> id;
          idvertices.push_back(id);
        }

    grafo->arvoreGeradoraPrim(idvertices);
  }
  else if (selecao == 8){ // Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Kruskal
    cout << "\nPara rodar o algoritmo de Kruskal, é preciso um subgrafo vértice induzido" << endl;
    cout << "\nDigite quantos vertices tera o subgrafo vertice induzido: ";
    // Vector para armazenar os ids dos vértices do subgrafo
        vector<int> idvertices;
        idvertices.clear();

        // Lendo os vértices do subgrafo
        int num;
        cin >> num;
        for (int i = 0; i < num; i++){
          cout << "Digite o " << i+1 << "º vertice:";
          int id;
          cin >> id;
          idvertices.push_back(id);
        }

    grafo->arvoreGeradoraKruskal(idvertices);
  }
  else if (selecao == 9){ // Caminhamento Profundidade destacando as Arestas de retorno
    int id;
    cout << "Digite o id do vertice para Caminhamento Profundidade destacando as Arestas de retorno: ";
    cin >> id;
    cout << endl;
    grafo->arvoreCaminhamentoProfundidade(id);
  }  
  else if (selecao == 10){// Caminhamento Profundidade destacando as Arestas de retorno
    grafo->imprimeGrafo();
  }
  else {
    system("clear");
    cout << " Erro!!! Opção invalida." << endl;
  }
}


int main(int argc, char const *argv[])
{
    if (argc != 6) {
    cout << "ERRO: Esperado: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
    return 1;
  }
  //Abrindo arquivo de entrada
  ifstream arquivo;
  ofstream output_file;
  arquivo.open(argv[1], ios::in);
  output_file.open(argv[2], ios::out | ios::trunc);
  
  if (arquivo.is_open()){
    int ordem;
    //Pegando a ordem do grafo
    arquivo >> ordem;
    Grafo *grafo = new Grafo(ordem, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    grafo->leitura(arquivo);
    int selecao = -1;
    while (selecao != 0)
    {
      selecao = menu();
      selecionar(selecao,grafo);
    }
  }
  arquivo.close();
  output_file.close();
  return 0;
    
}