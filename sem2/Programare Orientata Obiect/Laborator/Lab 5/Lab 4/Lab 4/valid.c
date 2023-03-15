#include "valid.h"
#include "domain.h"
#include "utils.h"

int valid_cheltuiala(Cheltuiala* chelt)
{
	int rez = 1;

	if (chelt->nrAp <= 0)
		rez *= 3;

	if (chelt->suma <= 0)
		rez *= 5;

	if (str_equ(chelt->tip, "apa") == 0 && str_equ(chelt->tip, "canal") == 0 && str_equ(chelt->tip, "gaz") == 0 && str_equ(chelt->tip, "incalzire") == 0)
		rez *= 7;


	return rez;
}