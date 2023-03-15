#include <iostream>
#include <fstream>
#include <queue>
#define INF 99999999
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
	return gasit; // returnam true daca exista drum pana la t, false altfel
}

int ford_fulkerson(int** g, int V, int s, int t, int* flux_camine, int C) {
	int** gf = new int* [V]; // alocare memorie pt graf rezidual
	for (int i = 0; i < V; i++) {
		gf[i] = new int[V];
	} 

	for (int u = 0; u < V; u++) { // initializare graf rezidual
		for (int v = 0; v < V; v++) {
			gf[u][v] = g[u][v];
		}
	}

	int* parent = new int[V]; // vector pt a determina drumul de la s la t aflat cu bfs
	int flux_max = 0;

	while (bfs(gf, V, s, t, parent)) { // cat timp exista drum de la s la t in graful rezidual
		int flux_drum = INF;
		int v = t;

		while (v != s) { // aici determinam minimul de flux trimis pe s->t
			int u = parent[v];
			if (gf[u][v] < flux_drum) {
				flux_drum = gf[u][v];
			}
			v = parent[v];
		}

		v = t;
		while (v != s) {
			int u = parent[v]; // arcul (u, v) din drumult s->t
			gf[u][v] -= flux_drum; // gf[u][v] scade, adica avem la dispozitie mai putin de trimis, iar gf[v][u] creste
			gf[v][u] += flux_drum;
			v = parent[v];
		}

		flux_max += flux_drum;
	}

	for (int i = 0; i < C; i++) { // in graful rezidual pe linia i, valorile >0 repr. flux trimis, iar cele <0, flux primit
		for (int j = 0; j < V; j++) {
			if (gf[i][j] > 0) {
				flux_camine[i] += gf[i][j];
			}
		}
	}

	for (int i = 0; i < V; i++) { // eliberam memoria
		delete[] gf[i];
	}
	delete[] gf;
	delete[] parent;

	return flux_max;
}


int main() {
	// aceasta este o problema de flux, cu mai multe noduri sursa
	// se rezolva legand un nou nod, "super-sursa", de aceste surse, iar pe aceste legaturi trimitem flux infinit
	
	ifstream fin("in.txt");
	int N, C, D; // N - cladiri(noduri), C - camine(surse), D - drumuri(arce)
	
	fin >> N >> C >> D;
	int** g = new int* [N + 1]; // alocam cu un nod in plus pt super-sursa
	for (int i = 0; i < N + 1; i++) {
		g[i] = new int[N + 1];
	}
	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < N + 1; j++) {
			g[i][j] = 0;
		}
	}

	for (int i = 1; i < D; i++) {
		int u, v, cap;
		fin >> u >> v >> cap;
		g[u][v] = cap;
	}
	fin.close();

	for (int i = 0; i < C; i++) { // trimitem flux infinit de la super-sursa la camine
		g[N][i] = INF;
	}

	// aplicam ford_fulkerson pentru N+1 noduri, sursa este N si destinatia N-1
	// pasam ca argument si un vector flux_camine in care se vor salva valorile fluxului trimis din varfurile 0,..,C-1
	int V = N + 1;
	int* flux_camine = new int[C];
	for (int i = 0; i < C; i++) {
		flux_camine[i] = 0;
	}
	int flux_max = ford_fulkerson(g, V, N, N - 1, flux_camine, C);

	ofstream fout("out.txt");
	fout << flux_max << endl;
	for (int i = 0; i < C; i++) {
		fout << flux_camine[i] << " ";
	}
	fout.close();

	delete[] flux_camine;

	for (int i = 0; i < N + 1; i++) { // eliberam memoria
		delete[] g[i];
	}
	delete[] g;

	return 0;
}