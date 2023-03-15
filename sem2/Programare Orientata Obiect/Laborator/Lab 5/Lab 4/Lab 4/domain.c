#define _CRT_SECURE_NO_WARNINGS

#include "domain.h"

#include <stdlib.h>
#include <string.h>

Cheltuiala* creeaza_cheltuiala(int nrAp, double suma, char* tip)
{
	Cheltuiala* chelt = (Cheltuiala*)malloc(sizeof(Cheltuiala));

	if (chelt)
	{
		chelt->nrAp = nrAp;
		chelt->suma = suma;
		chelt->tip = (char*)malloc(sizeof(char) * (strlen(tip) + 1));

		if (chelt->tip)
			strcpy(chelt->tip, tip);
	}

	return chelt;
}


int get_nrAp(Cheltuiala* chelt)
{
	return chelt->nrAp;
}

double get_suma(Cheltuiala* chelt)
{
	return chelt->suma;
}

void get_tip(Cheltuiala* chelt, char* tip)
{
	strcpy(tip, chelt->tip);
}

void distruge_cheltuiala(Cheltuiala* chelt)
{
	free(chelt->tip);
	free(chelt);
}

Cheltuiala* copiaza_cheltuiala(Cheltuiala* chelt)
{
	return creeaza_cheltuiala(chelt->nrAp, chelt->suma, chelt->tip);
}