#include <iostream>
#include <fstream>

using namespace std;

int a[51][51], grade[51], d[51][51], v[51];

void dfs(int k, int n)
{
    v[k] = 1;
    for(int i = 1; i <= n; i++)
        if(a[k][i] == 1 && v[i] == 0)
            dfs(i, n);
}

int main()
{
    int n, m, x, y, i, j, k;
    ifstream f("graf.txt");
    f >> n >> m;

    for(i = 1; i <= n; i++)
        for(j = 1; j<= n; j++)
            d[i][j] = 99;

    for(i = 1; i <= m; i++)
    {
        f >> x >> y;
        a[x][y] = 1;
        a[y][x] = 1;
        d[x][y] = 1;
        d[y][x] = 1;
    }

    cout<< "Matricea de adiacenta" << endl;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            cout<<a[i][j]<<"   ";
        cout<<endl;
    }

    cout<<endl<<"Varfuri izolate:";
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            if(a[i][j] == 1)
                grade[i]++;
        if(grade[i] == 0)
            cout<<i<<" ";
    }
    cout<<endl;

    int ok =1;
    for(i = 1; i <n; i++)
        if(grade[i] != grade[i + 1])
        {
                ok = 0;
                break;
        }
    cout<<endl<<"Graful este regular? ";
    if(ok == 1)
        cout<<"DA"<<endl;
    else
        cout<<"NU"<<endl;

    for(k = 1; k <= n; k++)
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                if(d[i][k] != 99 && d[k][j] != 99)
                    if(d[i][j] > d[i][k] + d[k][j])
                        d[i][j] = d[i][k] +d[k][j];
    for(i =1; i <= n; i++)
        d[i][i] = 0;
    cout<<endl<<"Matricea distantelor"<<endl;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            cout<<d[i][j]<<"   ";
        cout<<endl;
    }

    dfs(1, n);
    ok = 1;
    for(i = 1; i <= n; i++)
        if(v[i] == 0)
        {
            ok = 0;
            break;
        }
    cout<<endl<<"Graful este conex? ";
    if(ok == 1)
        cout<<"DA"<<endl;
    else
        cout<<"NU"<<endl;

}
