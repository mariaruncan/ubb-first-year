#include <iostream>
#include <fstream>
using namespace std;

int a[51][51], color[51], dist[51], pi[51], q[51];

void bfs (int s, int n) {
    for (int i = 1; i <= n; i++) {
        // 1 - alb, 2 - gri, 3 - negru
        color[i] = 1;
        dist[i] = 9999;
        pi[i] = 0;
    }
    color[s] = 2;
    dist[s] = 0;
    pi[s] = 0;
    int k = 0;
    q[k] = s;
    k++;
    while (k != 0) {
        int u = q[0];
        for (int i = 0; i < k-1; i++)
            q[i] = q[i+1];
        q[k-1] = 0;
        k--;
        for (int v = 1; v <= n; v++) {
            if (a[u][v] == 1 && color[v] == 1){
                color[v] = 2;
                dist[v] = dist[u] + 1;
                pi[v] = u;
                q[k] = v;
                k++;
            }
        }
        color[u] = 3;
    }
}

int main()
{
    int n, i, j, s;
    ifstream f("graf.txt");
    f >> n;
    while (f >> i >> j)
        a[i][j] = 1;
    cout << "Introduceti varful sursa: ";
    cin >> s;
    bfs(s, n);
    cout << "Varfurile descoperite si distantele fata de sursa:" << endl;
    for (i = 1; i <= n; i++)
        if (dist[i] != 9999)
            cout << i << " la distanta " << dist[i]<<endl;
    return 0;
}
