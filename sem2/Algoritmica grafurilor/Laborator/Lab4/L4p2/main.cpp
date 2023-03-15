#include <iostream>
#include <fstream>
using namespace std;

int minim_din_secventa(int k[], int n){
    int x = 0;
    while(true){
        int ap = 0;
        for(int i = 0; i < n; i++){
            if(k[i] == x)
            ap++;
        }
        if(ap == 0)
            return x;
        else
            x++;
    }
}

void decodare_prufer(int k[], int t[], int n){
    for(int i = 0; i < n; i++){
        int x = k[0];
        int y = minim_din_secventa(k, n);
        t[y] = x;
        for(int i = 0; i < n - 1; i++)
            k[i] = k[i+1];
        k[n - 1] = y;
    }
}

int main()
{
    ifstream fin("secventa.txt");
    int n;
    fin >> n;
    int k[20];
    for (int i = 0; i < n; i++)
        fin >> k[i];
    int t[20]={-1};
    decodare_prufer(k, t, n);
    cout << n + 1 << "\n";
    for(int i = 0; i <= n; i++ )
        cout << t[i] << "  ";
    return 0;
}
