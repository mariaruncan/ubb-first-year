#include <stdio.h>

int v[20][2];

float radacina_patrata(float n) {
	/* functia calculeaza radacina patrata a unui numar real dat
	* date de intrare: n - nr real
	* date de iesire: aux - nr real
	*/
	float aux = n;
	for (int i = 0; i < 50; i++)
		aux = (aux + n / aux) / 2;
	return aux;
}

void pb_9() {
	{
		int p;
		float n, rad;
		printf("\nIntroduceti numarul n: ");
		scanf_s("%f", &n);
		printf("\nIntroduceti precizia: ");
		scanf_s("%d", &p);

		rad = radacina_patrata(n); // calculam radacina patrata

		int aux = rad;
		printf("Radacina patrata a numarului %f este: %i", n, aux); //afisam partea intreaga
		if (p < 1)
			return 0;
		else
			printf(".");
		rad = rad - aux; //pastram doar partea zecimala
		for (int i = 0; i < p; i++) {
			rad = rad * 10; // inaintea virgulei punem prima zecimala
			aux = rad; // aux de tip int pastreaza doar partea intreaga
			printf("%i", aux);
			rad = rad - aux; // din nou pastram doar partea zecimala
		}
		printf("\n");
	}
}

void pb_8() {
	int n, k, i, j, cop;

	printf("Introduceti numarul n: ");
	scanf_s("%d", &n);

	k = 0;

	for (i = 2; i <= n; i++) {
		cop = i;
		for (j = 0; j < k && cop != 1; j++)
			while (cop % v[j][0] == 0) {
				cop = cop / v[j][0];
				v[j][1]++;
			}
		if (cop != 1) {
			v[k][0] = cop;
			v[k][1] = 1;
			k++;
		}
	}

	for (i = 0; i < k; i++)
		printf("exponentul lui %d: %d\n", v[i][0], v[i][1]);
	printf("\n");
}

int main() {
	int cmd;
	while (1) {
		printf("1. Tipareste exponentul la care numarul prim p apare in descompunerea in factori primi a numarului N = 1 * 2 * ... * n (n natural nenul dat).\n");
		printf("2. Calculeaza o valoare aproximativa a radacinii patrate a unui numar real pozitiv, cu o precizie data.\n");
		printf("3. Exit\n");
		printf("Introduceti comanda:");
		scanf_s("%d", &cmd);
		printf("\n");
		if (cmd == 1)
			pb_8();
		else if (cmd == 2)
			pb_9();
		else if (cmd == 3)
			break;
		else
			printf("Comanda invalida!\n");
	}
	return 0;
}
