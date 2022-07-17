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
  cout << "[3]  Caminho Mínimo entre dois vértices - Dijkstra" << endl;
  cout << "[4]  Caminho Mínimo entre dois vértices - Floyd" << endl;
  cout << "[5]  Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Prim" << endl;
  cout << "[6]  Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Kruskal" << endl;
  cout << "[7]  Caminhamento Profundidade destacando as Arestas de retorno" << endl;
  cout << "[8]  Ordenação topologica em D ou a informação de que não é um grafo acíclico direcionado" << endl;
  cout << "[9]  Imprimir grafo" << endl;
  cout << "[0]  Sair" << endl;

  cout << "\nSua opção: ";
  cin >> selecao;

  return selecao;
}
void selecionar(int selecao, Grafo *grafo) {

  switch (selecao) {
    //Sair;
  case 0:
    exit(0);
    break;
  case 1: // Fecho Transitivo Direto;
    int v;
    cout << "Digite o id do nó: ";
    cin >> v;

    grafo->transitivoDireto(v);
    cout << endl;
    break;

  case 2: // Fecho Transitivo Indireto;
    int h;
    cout << "Digite o id do nó: ";
    cin >> h;
    grafo->transitivoIndireto(h);
    cout << endl;
    break;

  case 3: //Caminho Mínimo entre dois vértices - Dijkstra
    //graph->dijkstra(output_file);
    break;

  case 4: // Caminho Mínimo entre dois vértices - Floyd
    //graph->floydWarshall(output_file);
    break;

  case 5: // Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Prim
    cout << "\nPara rodar o algoritmo de Prim, é preciso um subgrafo vértice induzido" << endl;
    //graph->agmPrim(graph->getVertInduz(), output_file);
    break;

  case 6: // Árvore Geradora Mínima sobre subgrafo vertice induzido por X usando algoritmo de Kruskal
    cout << "\nPara rodar o algoritmo de Kruskal, é preciso um subgrafo vértice induzido" << endl;
    //graph->agmKruskal(graph->getVertInduz(), output_file);
    break;

  case 7: // Caminhamento Profundidade destacando as Arestas de retorno
    grafo->busca_profundidade();
    break;
  
  case 9: // Caminhamento Profundidade destacando as Arestas de retorno
    grafo->imprimeGrafo();
    break;

  default:
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