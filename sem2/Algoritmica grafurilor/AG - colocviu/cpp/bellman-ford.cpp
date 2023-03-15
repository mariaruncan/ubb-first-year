#include <iostream>
#include <fstream>
using namespace std;

int a[50][50], d[50], pi[50];

void initializare(int s, int n){
    for (int v = 0; v < n; v++){
        pi[v] = -1;
        d[v] = 9999;
    }
    d[s] = 0;
}

void relax(int u, int v){
    if (d[v] > d[u] + a[u][v]){
        d[v] = d[u] + a[u][v];
        pi[v] = u;
    }
}

bool bellman_ford(int s, int n){
    initializare(s, n);
    for (int i = 0; i < n; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (a[u][v] != 0)
                    relax(u, v);
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (a[u][v] != 0 && d[v] > d[u] + a[u][v])
                return false;
    return true;
}

int main()
{
    int i, j, k, n, s;
    ifstream f ("in.txt");
    f >> n;
    while (f >> i >> j >> k)
        a[i][j] = k;
    cout << "Introduceti varful sursa:";
    cin >> s;
    bool ok = bellman_ford(s, n);
    if (ok == false)
        cout << "Nu exista solutie!" << endl;
    else{
        cout << "Costurile minime de la sursa " << s << " la celelalte varfuri sunt:"<<endl;
        for (int i = 0; i < n; i++)
            cout << s << "-" << i << ": " << d[i] << endl;
    }
    return 0;
}
