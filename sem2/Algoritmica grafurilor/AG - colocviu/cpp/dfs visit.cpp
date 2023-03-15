#include <iostream>
#include <fstream>
using namespace std;

int a[51][51], v[51];

void dfs(int k, int n)
{
    v[k] = 1;
    for(int i = 1; i <= n; i++)
        if(a[k][i] == 1 && v[i] == 0)
            dfs(i, n);
}

int main()
{
    int i, j, sursa, n;
    ifstream f("in.txt");
    f >> n;
    while(f >> i >> j)
        a[i][j] = 1;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            cout<<a[i][j]<<"  ";
        cout<<endl;
    }
    cout << endl<< "Introduceti varful de pornire: ";
    cin >> sursa;
    dfs(sursa, n);

    cout<<endl<<"Noduri parcurse: ";
    for(i = 1; i <= n; i++)
        if(v[i] != 0)
            cout << i << " ";
    cout<<endl;
    return 0;
}
