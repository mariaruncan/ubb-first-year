#include <iostream>
#include <fstream>

using namespace std;

int t[51][51];

int main()
{
    int n, x, y;
    ifstream f("graf.txt");
    f >> n;
    while (f >> x >> y)
        t[x][y] = 1;

    for (int k= 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (t[i][j] == 0)
                    t[i][j] = (t[i][k] && t[k][j]);

    cout << "Matricea inchiderii tranzitive:"<< endl;
    for (int i = 1; i <= n; i++){
        for ( int j = 1; j <= n; j++)
            cout << t[i][j]<<"  ";
        cout << endl;
    }
    return 0;
}
