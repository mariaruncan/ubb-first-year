#include <iostream>
#include <fstream>
using namespace std;

void codare_prufer(int k[], int fii[], int t[], int n, int& nr) {
    int copie = 0;
    bool gasit = false;
    while (!gasit) 
    {
        for (int i = 0; i < n; i++) 
        {
            gasit = true;
            if (fii[i] == 0) 
            {
                gasit = false;
                copie = i;
                fii[i]--;

                if (t[i] != -1)
                    fii[t[i]]--;
                k[nr++] = t[copie];
                break;
            }
        }
    }
}

int main()
{
    int n, t[50], fii[50] = { 0 }, k[50] = { 0 }, nr = 0, aux;
    ifstream fin("arbore.txt");
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> aux;
        t[i] = aux;
        if (t[i] != -1)
            fii[t[i]]++;
    }
            
    codare_prufer(k, fii, t, n, nr);
    cout << nr - 1 << "\n";
    for (int i = 0; i < nr - 1; i++)
        cout << k[i] << "  ";
    return 0;
}
