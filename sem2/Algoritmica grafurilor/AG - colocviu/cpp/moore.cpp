#include <iostream>
#include <fstream>
using namespace std;

int a[51][51], l[51], p[51], q[51], drum[51];

void moore (int s, int n) {
    int i, x, y;
    for (i = 1; i <= n; i++)
        l[i] = 9999;
    l[s] = 0;
    int k = 0;
    q[k] = s;
    k++;
    while (k != 0)
    {
        x = q[0];
        for (i = 0; i < k-1; i++)
            q[i] = q[i+1];
        q[k-1] = 0;
        k--;
        for (y = 1; y <= n; y++) {
            if (a[x][y] == 1 && l[y] == 9999)
            {
                p[y] = x;
                l[y] = l[x] + 1;
                q[k] = y;
                k++;
            }
        }
    }
}

void moore_drum (int v) {
    int k = l[v];
    drum[k] = v;
    while (k != 0) {
        drum[k-1] = p[drum[k]];
        k--;
    }
}

int main()
{
    int n, i, j, s, v;
    ifstream f ("in.txt");
    f >> n;
    while (f >> i >> j)
        a[i][j] = 1;
    cout << "Introduceti varful sursa: ";
    cin >> s;
    moore (s, n);
    cout << "Distante din " << s <<": ";
    for (i = 1; i <= n; i++)
        cout << l[i] << " ";
    cout << endl << "Introduceti varful destinatie: ";
    cin >> v;
    if (l[v] == 9999)
        cout << "Nu exista!";
    else
    {
    moore_drum(v);
    cout << "Drumul din " << s << " in " << v <<": ";
        for (i = 0; i <= l[v]; i++)
            cout << drum[i] << " ";
    }
    cout << endl;
    return 0;
}
