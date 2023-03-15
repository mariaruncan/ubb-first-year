 #include "service.h"
#include "valid.h"
#include "lista.h"
#include "utils.h"
#include "ui.h"
#include "sortare.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Service* creeaza_service(Lista* lista)
{
	Service* ser;
	ser = malloc(sizeof(Service));
	if (ser) {
		ser->lista = lista;
		ser->undo_list = creeaza_lista(3);
	}
	return ser;
}

void distruge_service(Service* ser)
{
	distruge_lista(ser->lista, distruge_cheltuiala);
	distruge_lista(ser->undo_list, distruge_lista_cheltuieli);
	free(ser);
}

int srv_adauga_cheltuiala(Service* srv, int nrAp, double suma, char* tip)
{
	Cheltuiala* chelt = creeaza_cheltuiala(nrAp, suma, tip);
	int rez = valid_cheltuiala(chelt);

	if (rez == 1)
	{
		adauga_elem(srv->undo_list, copiaza_lista(srv->lista));
		adauga_elem(srv->lista, chelt);
	}
	else
		distruge_cheltuiala(chelt);

	return rez;
}

int srv_sterge_cheltuiala(Service* srv, int index)
{
	Lista* copie = copiaza_lista(srv->lista);
	int rez = sterge_elem(srv->lista, index);
	if (rez == 1) {
		adauga_elem(srv->undo_list, copie);
	}
	else {
		distruge_lista(copie, distruge_cheltuiala);
	}
	return rez;
}

int srv_modifica_cheltuiala(Service* srv, int index, int nrAp, double suma, char* tip)
{
	Cheltuiala* chelt = creeaza_cheltuiala(nrAp, suma, tip);
	int rez = valid_cheltuiala(chelt);
	if (rez != 1 || index >= get_dim(srv->lista)) {
		distruge_cheltuiala(chelt);
		rez = 0;
	}
	else {
		adauga_elem(srv->undo_list, copiaza_lista(srv->lista));
		rez = modifica_elem(srv->lista, index, chelt);
	}
	return rez;
}

Lista* srv_filtreaza_nrAp(Service* srv, int nrAp)
{
	Lista* lista = srv->lista;
	Lista* copie = copiaza_lista(lista);

	for (int i = 0; i < copie->dim; i++)
	{

		if (get_nrAp(copie->vec[i]) != nrAp)
		{
			sterge_elem(copie, i);
			i--;
		}
			
	}
	return copie;
}

Lista* srv_filtreaza_suma(Service* srv, double suma)
{
	Lista* copie = copiaza_lista(srv->lista);

	for (int i = 0; i < copie->dim; i++)
	{
		if (double_equ(get_suma(copie->vec[i]), suma) == 0)
		{
			sterge_elem(copie, i);
			i--;
		}
			
	}
	return copie;
}



Lista* srv_filtreaza_tip(Service* srv, char* tip)
{
	Lista* copie = copiaza_lista(srv->lista);
	char tip_c[20];
	for (int i = 0; i < copie->dim; i++)
	{
		get_tip(copie->vec[i], tip_c);
		if (str_equ(tip_c, tip) == 0)
		{
			sterge_elem(copie, i);
			i--;
		}
		
	}
	return copie;
}

Lista* srv_filtreaza_suma_interval(Service* srv, double s1, double s2) {
	Lista* rez = creeaza_lista(2);
	for (int i = 0; i < get_dim(srv->lista); i++) {
		Cheltuiala* che = get_elem(srv->lista, i);
		if (get_suma(che) >= s1 && get_suma(che) <= s2) {
			adauga_elem(rez, copiaza_cheltuiala(che));
		}
	}
	return rez;
}

/*
Lista* sorteaza_suma(Lista* lista, int reversed)
{
	Cheltuiala* c1, * c2;
	double semn = 1;
	if (reversed == 2)
		semn = -1;

	int gasit = 1;
	while (gasit)
	{
		gasit = 0;
		for (int i = 0; i < lista->dim - 1; i++)
		{
			c1 = lista->vec[i];
			c2 = lista->vec[i + 1];
			if (get_suma(c1) * semn > get_suma(c2) * semn)
			{
				lista->vec[i] = c2;
				lista->vec[i + 1] = c1;
				gasit = 1;
			}
		}
	}
	return lista;
}
*/

int compara_suma_cresc(Cheltuiala* c1, Cheltuiala* c2)
{
	int semn = 1;
	if (get_suma(c1) * semn > get_suma(c2) * semn)
		return 1;
	return 0;
}
int compara_suma_descresc(Cheltuiala* c1, Cheltuiala* c2)
{
	int semn = -1;
	if (get_suma(c1) * semn > get_suma(c2) * semn)
		return 1;
	return 0;
}
Lista* srv_sorteaza_suma(Service* srv, int reversed)
{
	Lista* copie = copiaza_lista(srv->lista);
	if (reversed == 1)
		copie = sorteaza_lista(copie, compara_suma_cresc);
	if (reversed == 2)
		sorteaza_lista(copie, compara_suma_descresc);

	return copie;
}

/*
Lista* sorteaza_tip(Lista* lista, int reversed)
{
	Cheltuiala* c1, * c2;
	char t1[20], t2[20];
	double semn = 1;
	if (reversed == 2)
		semn = -1;

	int gasit = 1;
	while (gasit)
	{
		gasit = 0;
		for (int i = 0; i < lista->dim - 1; i++)
		{
			c1 = lista->vec[i];
			c2 = lista->vec[i + 1];
			get_tip(c1, t1);
			get_tip(c2, t2);

			if (strcmp(t1, t2) * semn > 0)
			{
				lista->vec[i] = c2;
				lista->vec[i + 1] = c1;
				gasit = 1;
			}
		}
	}
	return lista;
}
*/
int compara_tip_cresc(Cheltuiala* c1, Cheltuiala* c2)
{
	char t1[20], t2[20];
	int semn = 1;
	get_tip(c1, t1);
	get_tip(c2, t2);
	if (strcmp(t1, t2) * semn > 0)
		return 1;
	return 0;
}
int compara_tip_descresc(Cheltuiala* c1, Cheltuiala* c2)
{
	char t1[20], t2[20];
	int semn = -1;
	get_tip(c1, t1);
	get_tip(c2, t2);
	if (strcmp(t1, t2) * semn > 0)
		return 1;
	return 0;
}
Lista* srv_sorteaza_tip(Service* srv, int reversed)
{
	
	Lista* copie = copiaza_lista(srv->lista);

	if (reversed == 1)
		copie = sorteaza_lista(copie, compara_tip_cresc);
	if (reversed == 2)
		copie = sorteaza_lista(copie, compara_tip_descresc);
	
	return copie;
}

int srv_undo(Service* srv) {
	if (get_dim(srv->undo_list) == 0) {
		return 1;
	}
	distruge_lista(srv->lista, distruge_cheltuiala);
	int index = get_dim(srv->undo_list) - 1;
	Lista* new_list = get_elem(srv->undo_list, index);
	srv->lista = new_list;
	srv->undo_list->dim--;
	return 0;
}

Lista* srv_tip_sortat_suma(Service* srv, char* tip) {
	Lista* lista = srv_filtreaza_tip(srv, tip);
	Service* srv_nou = creeaza_service(lista);
	Lista* rezultat = srv_sorteaza_suma(srv_nou, 1);
	distruge_service(srv_nou);
	return rezultat;
}
