#include <iostream>
#include <fstream>
using namespace std;

int a[50][50], d[50], pi[50], q[50];

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

int extract_minim(int &k, int n){
    int d_min = 99999;
    int vf_min = n + 1;
    int poz = -1;
    int nod;
    for (int i = 0; i < k; i++){
        nod = q[i];
        if (d[nod] < d_min){
            poz = i;
            d_min = d[nod];
            vf_min = nod;
        }
    }
    for (int i = poz; i < k - 1; i++)
        q[i] = q[i + 1];
    q[k - 1] = 0;
    k--;
    return vf_min;

}

void dijkstra(int s, int n){
    int k, u, v;
    initializare(s, n);
    for (int nod = 0; nod < n; nod++)
        q[nod] = nod;
    k = n; //in k avem nr de vf din q
    while (k != 0){
        u = extract_minim(k, n);
        for (int v = 0; v < n; v++)
            if (a[u][v] != 0)
                relax(u, v);
    }

}

int main()
{
    int i, j, k, n, s;
    ifstream f ("graf.txt");
    f >> n;
    while (f >> i >> j >> k)
        a[i][j] = k;
    cout << "Introduceti varful sursa:";
    cin >> s;
    dijkstra(s, n);
    cout << "Costurile minime de la sursa " << s << "la celelalte varfuri sunt:"<<endl;
    for (int i = 0; i < n; i++)
        cout << s << "-" << i << ": " << d[i] << endl;
    return 0;
}
