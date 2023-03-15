#include <iostream>
#include <fstream>
#include <queue>
#define INF 99999;
using namespace std;

bool bfs(int** g, int& V, int s, int t, int* parent) {
	bool* vizitat = new bool[V];
	
	for (int i = 0; i < V; i++) {
		vizitat[i] = false;
	}

	queue<int> q;
	q.push(s);
	parent[s] = -1;
	vizitat[s] = true;

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v = 0; v < V; v++) {
			if (vizitat[v] == false && g[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				vizitat[v] = true;
			}
		}
	}

	bool gasit = vizitat[t];
	delete[] vizitat; // eliberam memoria
	return gasit;
}

int ford_fulkerson(int** g, int& V, int s, int t) {
	int** gf = new int* [V];
	for (int i = 0; i < V; i++) {
		gf[i] = new int[V];
	} // alocare memorie pt graf rezidual
	for (int u = 0; u < V; u++) {
		for (int v = 0; v < V; v++) {
			gf[u][v] = g[u][v];
		}
	} // initializare graf rezidual

	int* parent = new int[V]; // vector pt a determina drumul de la s la t aflat cu bfs
	int flux_max = 0;

	while (bfs(gf, V, s, t, parent)) {
		int flux_drum = INF;
		int v = t;
		while (v != s) {
			int u = parent[v];
			if (gf[u][v] < flux_drum) {
				flux_drum = gf[u][v];
			}
			v = parent[v];
		}

		v = t;
		while (v != s) {
			int u = parent[v];
			gf[u][v] -= flux_drum;
			gf[v][u] += flux_drum;
			v = parent[v];
		}

		flux_max += flux_drum;
	}

	for (int i = 0; i < V; i++) { // eliberam memoria
		delete[] gf[i];
	}
	delete[] gf;
	delete[] parent;

	return flux_max;
}

int main() {
	
	ifstream fin("in.txt");
	int V, E;
	fin >> V >> E;
	int** g = new int* [V];
	for (int i = 0; i < V; i++) {
		g[i] = new int[V];
	}
	for (int i = 1; i <= E; i++) {
		int u, v, cap;
		fin >> u >> v >> cap;
		g[u][v] = cap;
	}
	fin.close();

	cout << "Fluxul maxim este: " << ford_fulkerson(g, V, 0, V - 1) << "\n";
	
	for (int i = 0; i < V; i++) { // eliberam memoria
		delete[] g[i];
	}
	delete[] g;
}