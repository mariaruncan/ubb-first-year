#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

typedef struct Graf{
	int V, E; // V - nr de noduri, E - nr de muchii
	int** adj; // adj - matricea de adiacenta

	Graf(int V, int E) { // constructor pentru graf
		this->V = V;
		this->E = E;
		adj = new int*[V]; // alocam memorie pe heap pentru matricea de adiacenta
		for (int i = 0; i < V; i++) {
			adj[i] = new int[V];
		}
	}

	Graf(const Graf& o) { // constructor de copiere
		this->V = o.V;
		this->E = o.E;
		this->adj = new int* [this->V];
		for (int i = 0; i < this->V; i++) {
			this->adj[i] = new int[V];
		}
		for (int i = 0; i < this->V; i++) {
			for (int j = 0; j < this->V; j++) {
				this->adj[i][j] = o.adj[i][j]; // copiem element cu element
			}
		}
	}

	~Graf() { // destructor; dealocam memoria
		for (int i = 0; i < V; i++) {
			delete[] adj[i];
		}
		delete[] adj;
	}

	void sterge(int u, int v) {
		adj[u][v] = 0;
		adj[v][u] = 0;
	}

	void adauga(int u, int v) {
		adj[u][v] = 1;
		adj[v][u] = 1;
	}
}Graf;

int grad(Graf& g, int vf) {
	// returnam gradul unui nod, adica numarul valorilor de 1 de la linia/coloana sa
	int gr = 0;
	for (int i = 0; i < g.V; i++) {
		if (g.adj[vf][i] == 1) {
			gr++;
		}
	}
	return gr;
}

stack<int> ordine_colorare(Graf& g, int k) {
	stack<int> s;
	vector<int> noduri;
	for (int i = 0; i < g.V; i++) {
		noduri.push_back(i);
	}

	for (int i = 0; i < g.V; i++) {
		int vf = -1;

		for (int j = 0; j < noduri.size(); j++) { // cautam un nod u care respecta d(u) < k, il stergem din graf si il adaugam pe stiva s
			if (grad(g, noduri[j]) < k) {
				vf = noduri[j];
				for (int v = 0; v < g.V; v++) {
					if (g.adj[vf][v] == 1) {
						g.sterge(vf, v); // stergem muchiile adiacente cu vf
					}
				}
				noduri.erase(noduri.begin() + j);
				break;
			}
		}
	
		if (vf != -1) {
			s.push(vf);
		}
		else {
			// nu am gasit un nod cu d(u) < k, deci alegem aleator
			int index = rand() % (noduri.size());
			vf = noduri[index];
			for (int v = 0; v < g.V; v++) {
				if (g.adj[vf][v] == 1) {
					g.sterge(vf, v);
				}
			}
			noduri.erase(noduri.begin() + index);
			s.push(vf);
		}
	}

	return s;
}

int* colorare(Graf& g, int k) {

	// determinam ordinea de colorare a nodurilor
	Graf aux = g;
	stack<int> s = ordine_colorare(aux, k);

	int* culori = new int[g.V];
	for (int i = 0; i < g.V; i++) { // initializam culorile cu 0, deci niciun vf nu este colorat
		culori[i] = 0;
	} 

	while (!s.empty()) {
		int vf = s.top();
		int c = 1;
		bool gasit = true;
		while (gasit) {
			gasit = false;
			// testam fiecare culoare daca este disponibila
			for (int i = 0; i < g.V && !gasit; i++) {
				if (culori[i] == c && g.adj[vf][i] == 1) {
					gasit = true;
					c++;
				}
			}
		}
		// daca o culoare este mai mare decat k, vor ramane varfuri necolorate, deci nu este un rezultat ce ne ajuta si ne putem opri
		if (c > k) {
			break;
		}
		culori[vf] = c;
		s.pop();
	}
	return culori;
}

void run() {
	ifstream fin("in.txt");
	int V, E;
	
	fin >> V >> E;
	Graf g{ V, E };

	for (int i = 0; i < g.E; i++) {
		int u, v;
		fin >> u >> v;
		g.adauga(u, v);
	}
	fin.close();
	
	int* rezultat = NULL;
	int k;
	if (E == 0) { // graf doar cu noduri izolate
		k = 1;
		rezultat = colorare(g, k);
	}
	else {
		// facem o k-colorare incepand de la k = 2 si ne oprim cand toate varfurile sunt colorate (nu raman varfuri care au culoare 0)
		k = 2;
		bool ok = true;
		while (ok) {
			ok = false;
			rezultat = colorare(g, k);
			for (int i = 0; i < V; i++) {
				if (rezultat[i] == 0) {
					k++;
					delete[] rezultat;
					ok = true;
					break;
				}
			}
		}
	}

	ofstream fout("out.txt");
	fout << k << endl;
	for (int i = 0; i < V; i++) {
		fout << rezultat[i] << "  ";
	}
	fout.close();
	delete[] rezultat;
}

int main() {
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}