#include <stdio.h>

int adauga_la_sir(char sirD[100], char sirS[100], int cont);

int main()
{
    FILE *descriptor;
    char numar[100], N[100], P[100];
    int cont_neg = 0, cont_poz = 0;
    
    /* deschidere fisier*/
    descriptor = fopen("numere.txt", "r");
    
    if(descriptor != NULL)
    {
        while(fgets(numar, 100, descriptor) != NULL)
            if(numar[0] == '-')
                cont_neg = adauga_la_sir(N, numar, cont_neg);
            else
                cont_poz = adauga_la_sir(P, numar, cont_poz);
    }
    N[cont_neg] = '\0';
    P[cont_poz] = '\0';
    fclose(descriptor);
    printf("Numere negative: %s", N);
    printf("\nNumere pozitive: %s", P);
    return 0;
}