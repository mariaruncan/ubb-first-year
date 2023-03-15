#include "lista.h"
#include "domain.h"

#include <stdlib.h>

Lista* creeaza_lista(int cap)
{
	Lista* lista;
	lista = malloc(sizeof(Lista));
	if (lista)
	{
		lista->cap = cap;
		lista->dim = 0;
		lista->vec = malloc(sizeof(Telem) * lista->cap);

	}
		
	return lista;
}

void distruge_lista_cheltuieli(Lista* lista) {
	distruge_lista(lista, distruge_cheltuiala);
}

void distruge_lista(Lista* lista, DestroyFunction destrF)
{
	for (int i = 0; i < lista->dim; i++)
		destrF(lista->vec[i]);

	free(lista->vec);
	free(lista);
}

void adauga_elem(Lista* lista, Telem elem)
{
	capacitate(lista);
	lista->vec[lista->dim] = elem;
	lista->dim++;
}

int sterge_elem(Lista* lista, int index)
{
	if (index < lista->dim)
	{
		distruge_cheltuiala(lista->vec[index]);
		if (index < lista->dim - 1)
			for (int i = index; i <= lista->dim - 2; i++)
			{
				lista->vec[i] = lista->vec[i + 1];
			}
		lista->dim--;
		return 1;
	}
		

	return 0;

}

void capacitate(Lista* lista)
{
	if (lista->cap > lista->dim)
		return;

	//alocare memorie dubla
	int cap_noua = lista->cap * 2;
	Telem* vec_nou = malloc(sizeof(Telem*) * cap_noua);


	//copiere elemente vectorul nou noua
	if (vec_nou) {
		for (int i = 0; i < lista->dim; i++)
			*(vec_nou + i) = lista->vec[i];
	}

	//dealocare

	free(lista->vec);

	//modificare capacitate si vector nou
	lista->cap = cap_noua;
	lista->vec = vec_nou;
}

int get_cap(Lista* lista)
{
	return lista->cap;
}

int get_dim(Lista* lista)
{
	return lista->dim;
}

Telem get_elem(Lista* lista, int index)
{
	return lista->vec[index];
}

int modifica_elem(Lista* lista, int index, Telem elem)
{
	if (index < lista->dim)
	{
		distruge_cheltuiala(lista->vec[index]);
		lista->vec[index] = elem;
		return 1;
	}
	return 0;
		
}

Lista* copiaza_lista(Lista* lista)
{

	Lista* copie;
	copie = malloc(sizeof(Lista));
	if (copie)
	{
		copie->cap = lista->cap;
		copie->dim = lista->dim;
		copie->vec = malloc(sizeof(Telem) * copie->cap);

		if (copie->vec) {
			for (int i = 0; i < copie->dim; i++)
				*(copie->vec + i) = copiaza_cheltuiala(lista->vec[i]);
		}
	}

	return copie;
}

