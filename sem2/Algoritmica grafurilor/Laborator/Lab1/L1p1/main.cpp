#include <iostream>
#include <fstream>

using namespace std;

int a[101][101];

int main()
{
    int n, m, x, y, i, j;
    ifstream f("graf.txt");
    f >> n >> m;

    for(i=1; i<=m; i++)
    {
        f >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1;
    }

    cout<< "Matricea de adiacenta" << endl;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl<< "Lista de vecini"<<endl;

    for(i=1; i<=n; i++)
    {
        cout<<i<<"   ";
        for(j=1;j<=n;j++)
            if(a[i][j] == 1)
                cout<<j<<" ";
        cout<<endl;
    }

    return 0;
}
