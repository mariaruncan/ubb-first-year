#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int max_s = 20;
const int INF = 9999;

typedef struct {
	int vf;
	int cost;
	int parinte;
}Nod;

void initializare(int s, int n, vector<Nod>& noduri) {
	noduri.clear();
	for (int i = 1; i <= n; i++) {
		Nod x;
		x.vf = i;
		x.parinte = -1;
		if (i == s)
			x.cost = 0;
		else
			x.cost = INF;
		noduri.push_back(x);
	}
}

void relax(int u, int v, vector<Nod>& noduri, int w[][max_s]) {
	
	for (int i = 0; i < noduri.size(); i++) {
		if (noduri[i].vf == u) {
			for (int j = 0; j < noduri.size(); j++) {
				if(noduri[j].vf == v)
					if (noduri[j].cost > noduri[i].cost + w[i][j]) {
						noduri[j].cost = noduri[i].cost + w[i][j];
						noduri[j].parinte = i;
					}
			}
		}
					
	}
}

bool bellman_ford(int a[][max_s], int w[][max_s], int s, vector<Nod>& noduri, int n) {
	initializare(s, n, noduri);
	for (int i = 1; i <= n; i++)
		for (int u = 1; u <= n; u++)
			for (int v = 1; v <= n; v++)
				if (a[u][v] != 0)
					relax(u, v, noduri, w);

	for (int u = 1; u <= n; u++)
		for (int v = 1; v <= n; v++)
			if (a[u][v] != 0 && noduri[v].cost > noduri[u].cost + w[u][v])
				return false;
	return true;
}

int extract_minim(vector<int>& q, int n, vector<Nod>& noduri) {
	int costMinim = INF, u = n + 1;
	int poz = 0;
	for (int i = 0; i < q.size(); i++) {
		int x = q[i];
		if (noduri[x].cost < costMinim) {
			poz = i;
			costMinim = noduri[x].cost;
			u = q[i];
		}
	}
	q.erase(q.begin() + poz);
	return u;
}

void dijkstra(int a[][max_s], int w[][max_s], int n, vector<Nod>& noduri, int s) {
	initializare(s, n, noduri);
	vector<int> q;
	for (int i = 1; i <= n; i++) {
		q.push_back(i);
	}
	while(!q.empty()){
		int u = extract_minim(q, n, noduri);
		for (int v = 1; v <= n; v++) {
			if (a[u][v] != 0) {
				relax(u, v, noduri, w);
			}
		}
	}

}

void johnson(int a[][max_s], int w[][max_s], int n, int nodSursa) {
	int new_a[20][20];
	int new_w[20][20];
	int newN = n + 1;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			new_a[i][j] = a[i][j];
			new_w[i][j] = w[i][j];
		}

	for (int i = 1; i <= n; i++) {
		new_a[newN][i] = 1;
		new_w[newN][i] = 0;
	}

	for (int i = 1; i <= newN; i++) {
		new_a[i][newN] = 0;
		new_w[i][newN] = 0;
	}

	vector<Nod> noduri;

	bool ok = bellman_ford(new_a, new_w, newN, noduri, newN);
	
	if (!ok) {
		throw ("NUU");
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			w[i][j] = w[i][j] + noduri[i - 1].cost - noduri[j -1].cost;

	dijkstra(a, w, n, noduri, nodSursa);

	for (int i = 1; i <= n; i++)
		if (noduri[i].cost == INF)
			cout << "INF  ";
		else
			cout << noduri[i].cost << "  ";

	cout << "\n";
}

int main() {
	ifstream fin("in.txt");
	int n, m, x, y, c;
	int a[20][20], w[20][20];
	fin >> n >> m;
	for (int i = 1; i <= m; i++) {
		fin >> x >> y >> c;
		a[x][y] = 1;
		w[x][y] = c;
	}
	try {
		for (int i = 1; i <= n; i++)
			johnson(a, w, n, i);
	}
	catch (...) {
		cout << "-1\n";
	}
	return 0;
}