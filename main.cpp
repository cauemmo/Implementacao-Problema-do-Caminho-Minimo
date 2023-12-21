#include <iostream>
#include <vector>
#include <set>
#include <limits>

/*
 * CÓDIGO IMPLEMENTADO POR:
 *
 * CAUÊ MENDONÇA MAGELA DO Ó
 * VINICIUS SILVA BALBINO
 *
 * */

using namespace std;

// Classe para representar um grafo ponderado
class Grafo {
    int V; // Número de vértices
    vector<vector<pair<int, int>> > adj; // Lista de adjacência (vértice de destino, peso)
public:

    Grafo(int V){
        this->V = V;
        adj.resize(V);
    };

    void adicionarAresta(int u, int v, int peso){
        adj[u].push_back(make_pair(v, peso));
        adj[v].push_back(make_pair(u, peso)); // Se o grafo for não direcionado
    };

    void menorCaminho(int origem){
        set<pair<int, int>> fila; // Usamos um conjunto (set) para manter os vértices ordenados por distância.
        vector<int> dist(V, numeric_limits<int>::max()); // Inicializamos as distâncias de todos os vértices como infinito.

        dist[origem] = 0; // A distância da origem para ela mesma é 0.
        fila.insert(make_pair(0, origem)); // Inserimos a origem na fila com distância 0.

        while (!fila.empty()) {
            pair<int, int> temp = *(fila.begin()); // Pegamos o vértice com a menor distância na fila.
            fila.erase(fila.begin()); // Removemos esse vértice da fila.
            int u = temp.second; // O vértice atual.

            for (const pair<int, int>& vizinho : adj[u]) {
                int v = vizinho.first; // O vértice vizinho.
                int peso = vizinho.second; // O peso da aresta entre u e v.

                // Atualizamos a distância de v se encontrarmos um caminho mais curto através de u.
                if (dist[v] > dist[u] + peso) {
                    if (dist[v] != numeric_limits<int>::max()) {
                        fila.erase(fila.find(make_pair(dist[v], v))); // Removemos a versão anterior de v da fila.
                    }

                    dist[v] = dist[u] + peso; // Atualizamos a distância.
                    fila.insert(make_pair(dist[v], v)); // Inserimos v na fila com a nova distância.
                }
            }
        }

        // Imprimimos as distâncias mínimas para cada vértice a partir da origem.
        cout << "Vertice \t Distancia da Origem" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " \t \t \t " << dist[i] << endl;
        }
    };
};


int main() {

    int Vertices = 6; // Número de vértices

    Grafo grafo1(Vertices);

    // Adicionamos arestas ao grafo com pesos.

    grafo1.adicionarAresta(0, 1, 5);
    grafo1.adicionarAresta(0, 2, 3);
    grafo1.adicionarAresta(1, 3, 6);
    grafo1.adicionarAresta(1, 2, 2);
    grafo1.adicionarAresta(2, 4, 4);
    grafo1.adicionarAresta(2, 5, 2);
    grafo1.adicionarAresta(2, 3, 7);
    grafo1.adicionarAresta(3, 5, 1);
    grafo1.adicionarAresta(3, 4, 1);
    grafo1.adicionarAresta(4, 5, 3);

    int origem = 0; // Vértice de origem

    grafo1.menorCaminho(origem);

    return 0;
}