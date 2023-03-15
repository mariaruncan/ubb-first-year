#include "sortare.h"
#include "lista.h"
#include "service.h"

Lista* sorteaza_lista(Lista* lista, FunctieComparare cmp) 
{
	
	Cheltuiala* c1, * c2;

	int gasit = 1;
	while (gasit)
	{
		gasit = 0;
		for (int i = 0; i < get_dim(lista) - 1; i++)
		{
			c1 = lista->vec[i];
			c2 = lista->vec[i + 1];
			if (cmp(c1, c2))
			{
				//interschimbare
				lista->vec[i] = c2;
				lista->vec[i + 1] = c1;
				gasit = 1;
			}
		}
	}
	return lista;
}

