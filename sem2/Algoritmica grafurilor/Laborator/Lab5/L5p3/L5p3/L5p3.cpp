#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Graf {
    int V, E;
    int** adj;

    Graf(int V, int E) {
        this->V = V;
        this->E = E;
        adj = new int*[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new int[V];
        }
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
        }
    }

    ~Graf() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
    }

    void add_muchie(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void delete_muchie(int u, int v) {
        adj[u][v] = -1;
        adj[v][u] = -1;
    }
};

int cauta_varf(Graf& g) {
    // cautam un vf cu grad par de la care sa incepem
    for (int u = 0; u < g.V; u++) {
        int grad = 0;
        for (int v = 0; v < g.V; v++) {
            if (g.adj[u][v] == 1) {
                grad++;
            }
        }
        if (grad % 2 == 0) {
            return u;
        }
    }
}

void ciclu_eulerian(Graf& g, int u, vector<int>& rez) {
    
    for (int v = 0; v < g.V; v++) {
        if (g.adj[u][v] == 1) {
            g.delete_muchie(u, v);
            ciclu_eulerian(g, v, rez);
        }
    }
    rez.push_back(u);
}

int main() {
    ifstream fin("graf.txt");
    int V, E;
    fin >> V >> E;
    Graf g(V, E);
    for (int i = 0; i < E; i++) {
        int u, v;
        fin >> u >> v;
        g.add_muchie(u, v);
    }
    fin.close();
    int sursa = cauta_varf(g);
    vector<int> rez;
    ciclu_eulerian(g, sursa, rez);
    for (int el : rez) {
        cout << el << "  ";
    }
}
