#define _CRT_SECURE_NO_WARNINGS

#include "teste.h"
#include "domain.h"
#include "utils.h"
#include "valid.h"
#include "lista.h"
#include "service.h"
#include "ui.h"

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void run_domain_tests()
{
	int nrAp = 2;
	double suma = 3.5;
	char* tip = "apa";

	Cheltuiala* chelt = creeaza_cheltuiala(nrAp, suma, tip);

	char tip_c[100];
	get_tip(chelt, tip_c);

	assert(get_nrAp(chelt) == nrAp);
	assert(double_equ(get_suma(chelt), suma));
	assert(str_equ(tip_c, tip));

	distruge_cheltuiala(chelt);

	//copiaza
	nrAp = 2;
	suma = 3.5;
	char tip_init[20] = "apa";

	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	Cheltuiala* chelt1 = copiaza_cheltuiala(chelt);

	assert(chelt != chelt1);
	assert(get_nrAp(chelt1) == nrAp);
	assert(get_suma(chelt1) == suma);
	char tip_cop[20];
	get_tip(chelt1, tip_cop);
	assert(str_equ(tip_cop, tip_init) == 1);

	distruge_cheltuiala(chelt);
	distruge_cheltuiala(chelt1);
}

void run_utils_tests()
{
	double a = 1.25, b = 1.25;
	assert(double_equ(a, b));
	a = -1.25;
	b = -1.25;
	assert(double_equ(a, b));

	a = -1.25;
	b = 1.25;
	assert(double_equ(a, b) == 0);


	char c[10] = "abc", d[10] = "abc";
	assert(str_equ(c, d));
	char e[10] = "abc", f[10] = "abd";
	assert(str_equ(e, f) == 0);

}

void run_valid_tests()
{
	int nrAp;
	double suma;
	char tip[20]="aaaaaa";
	Cheltuiala* chelt;

	int rez;
	
	//1
	nrAp = 2;
	suma = 2.5;
	strcpy(tip, "apa");

	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	rez = valid_cheltuiala(chelt);

	assert(rez == 1);

	distruge_cheltuiala(chelt);

	//2
	nrAp = -2;
	suma = 2.5;
	strcpy(tip, "apa");

	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	rez = valid_cheltuiala(chelt);

	assert(rez % 3 == 0);

	distruge_cheltuiala(chelt);

	//3
	nrAp = 2;
	suma = -2.5;
	strcpy(tip, "apa");

	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	rez = valid_cheltuiala(chelt);

	assert(rez % 5 == 0);

	distruge_cheltuiala(chelt);

	//4
	nrAp = 2;
	suma = 2.5;
	strcpy(tip, "gresit");

	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	rez = valid_cheltuiala(chelt);

	assert(rez % 7 == 0);

	distruge_cheltuiala(chelt);
	
	//5
	nrAp = 0;
	suma = -2;
	strcpy(tip, "gresit");

	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	rez = valid_cheltuiala(chelt);

	assert(rez % 3 == 0 && rez % 5 == 0 && rez % 7 == 0);

	distruge_cheltuiala(chelt);
	
}

void run_lista_tests()
{
	Lista* lista;
	int cap = 10;


	//creeaza
	lista = creeaza_lista(cap);

	assert(lista->cap == cap);
	assert(lista->dim == 0);

	distruge_lista(lista, distruge_cheltuiala);

	//adauga
	int nrAp;
	double suma;
	char tip[20];

	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	Cheltuiala* chelt = creeaza_cheltuiala(nrAp, suma, tip);

	cap = 2;

	lista = creeaza_lista(cap);
	adauga_elem(lista, chelt);

	assert(lista->cap == cap);
	assert(lista->dim == 1);
	assert(lista->vec[0] == chelt);

	distruge_lista(lista, distruge_cheltuiala);

	//capacitate
	

	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	
	Cheltuiala* chelt1 = creeaza_cheltuiala(nrAp, suma, tip);
	Cheltuiala* chelt2 = creeaza_cheltuiala(nrAp, suma, tip);
	cap = 1;

	lista = creeaza_lista(cap);
	
	adauga_elem(lista, chelt1);
	adauga_elem(lista, chelt2);

	assert(lista->cap == cap*2);
	assert(lista->dim == 2);
	assert(lista->vec[0] == chelt1);
	assert(lista->vec[1] == chelt2);

	distruge_lista(lista, distruge_cheltuiala);


	//sterge
	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	cap = 2;


	lista = creeaza_lista(cap);
	adauga_elem(lista, chelt);

	assert(lista->cap == cap);
	assert(lista->dim == 1);
	assert(lista->vec[0] == chelt);

	sterge_elem(lista, 0);

	assert(lista->cap == cap);
	assert(lista->dim == 0);

	int rez = sterge_elem(lista, 0);

	assert(rez == 0);

	distruge_lista(lista, distruge_cheltuiala);

	//sterge lista mare

	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	cap = 10;

	lista = creeaza_lista(cap);
	adauga_elem(lista, chelt);

	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	adauga_elem(lista, chelt);

	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	adauga_elem(lista, chelt);

	assert(lista->cap == cap);
	assert(lista->dim == 3);

	rez = sterge_elem(lista, 1);

	assert(lista->cap == cap);
	assert(lista->dim == 2);
	assert(rez == 1);


	distruge_lista(lista, distruge_cheltuiala);

	//get_cap si get_dim

	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	cap = 2;

	lista = creeaza_lista(cap);

	assert(get_cap(lista) == cap);
	assert(get_dim(lista) == 0);

	adauga_elem(lista, chelt);

	assert(get_cap(lista) == cap);
	assert(get_dim(lista) == 1);


	distruge_lista(lista, distruge_cheltuiala);

	//get_cheltuiala

	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	cap = 2;

	lista = creeaza_lista(cap);
	adauga_elem(lista, chelt);

	chelt = get_elem(lista, 0);

	assert(get_nrAp(chelt) == nrAp);
	assert(get_suma(chelt) == suma);
	assert(str_equ(chelt->tip, tip));


	distruge_lista(lista, distruge_cheltuiala);

	//modifica
	nrAp = 1;
	suma = 2.5;
	strcpy(tip, "apa");
	chelt = creeaza_cheltuiala(nrAp, suma, tip);

	nrAp = 3;
	suma = 42.5;
	strcpy(tip, "gaz");
	Cheltuiala* chelt_mod = creeaza_cheltuiala(nrAp, suma, tip);
	cap = 2;

	lista = creeaza_lista(cap);
	adauga_elem(lista, chelt);

	modifica_elem(lista, 0, chelt_mod);

	assert(get_elem(lista, 0) == chelt_mod);

	rez = modifica_elem(lista, 2, chelt_mod);

	assert(rez == 0);

	distruge_lista(lista, distruge_cheltuiala);

	//copiaza lista
	
	nrAp = 1;
	suma = 1.5;
	strcpy(tip, "apa");
	Cheltuiala* chelt_1 = creeaza_cheltuiala(nrAp, suma, tip);
	
	nrAp = 2;
	suma = 2.5;
	strcpy(tip, "gaz");
	Cheltuiala* chelt_2 = creeaza_cheltuiala(nrAp, suma, tip);

	nrAp = 3;
	suma = 3.5;
	strcpy(tip, "incalzire");
	Cheltuiala* chelt_3 = creeaza_cheltuiala(nrAp, suma, tip);
	
	cap = 10;
	
	lista = creeaza_lista(cap);
	adauga_elem(lista, chelt_1);
	adauga_elem(lista, chelt_2);
	adauga_elem(lista, chelt_3);
	
	Lista* lista_copie = copiaza_lista(lista);
	
	assert(lista->cap == cap);
	assert(lista->dim == 3);
	assert(lista->vec[0] == chelt_1);
	assert(lista->vec[1] == chelt_2);
	assert(lista->vec[2] == chelt_3);
	
	assert(lista_copie->cap == cap);
	
	assert(lista_copie->dim == 3);
	assert(get_nrAp(lista_copie->vec[0]) == 1);
	assert(double_equ(get_suma(lista_copie->vec[0]), 1.5));
	
	distruge_lista(lista, distruge_cheltuiala);
	distruge_lista(lista_copie, distruge_cheltuiala);
}

void run_service_tests()
{
	//creeaza
	Lista* lista;
	Service* ser;
	int cap = 10;
	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	assert(ser->lista == lista);

	distruge_service(ser);
	
	//adauga corect

	int nrAp = 2;
	double suma = 3.5;
	char tip[20] = "apa";

	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	int rez = srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	assert(rez == 1);

	assert(get_dim(ser->lista) == 1);

	distruge_service(ser);
	
	//adauga gresit
	
	nrAp = -2;
	suma = -3.5;
	strcpy(tip,"gresit");

	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	rez = srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	assert(rez % 3 == 0 && rez % 5 == 0 && rez % 7 == 0);

	assert(get_dim(ser->lista) == 0);

	distruge_service(ser);
	
	//sterge incorect/corect
	nrAp = 2;
	suma = 3.5;
	strcpy(tip,"apa");

	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	rez = srv_adauga_cheltuiala(ser, nrAp, suma, tip);
	assert(rez == 1);

	int index = 3;
	rez = srv_sterge_cheltuiala(ser, index);
	assert(rez == 0);

	index = 0;
	rez = srv_sterge_cheltuiala(ser, index);
	assert(rez == 1);

	assert(get_dim(ser->lista) == 0);

	distruge_service(ser);

	//modifica corect
	
	nrAp = 2;
	suma = 3.5;
	strcpy(tip, "apa");

	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	nrAp = 2;
	suma = 3.5;
	strcpy(tip, "apa");
	index = 0;

	rez = srv_modifica_cheltuiala(ser, index, nrAp, suma, tip);

	assert(rez == 1);

	distruge_service(ser);

	//modifica gresit index
	
	nrAp = 2;
	suma = 3.5;
	strcpy(tip, "apa");

	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	nrAp = 2;
	suma = 3.5;
	strcpy(tip, "apa");
	index = 2;

	rez = srv_modifica_cheltuiala(ser, index, nrAp, suma, tip);

	assert(rez == 0);

	distruge_service(ser);

	//modifica gresit date
	
	nrAp = 2;
	suma = 3.5;
	strcpy(tip, "apa");

	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	nrAp = -2;
	suma = -3.5;
	strcpy(tip, "gresit");
	index = 0;

	rez = srv_modifica_cheltuiala(ser, index, nrAp, suma, tip);
	assert(rez % 3 == 0 && rez % 5 == 0 && rez % 7 == 0);

	distruge_service(ser);


	//filtrare
	
	cap = 10;
	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);

	nrAp = 1;
	suma = 20;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	nrAp = 1;
	suma = 10;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	nrAp = 3;
	suma = 15;
	strcpy(tip, "gaz");
	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	Lista* filtrata;
	
	//fitrare nrAp
	filtrata = srv_filtreaza_nrAp(ser, 1);
	
	assert(get_dim(filtrata) == 2);
	
	distruge_lista(filtrata, distruge_cheltuiala);
	
	//fitrare suma
	filtrata = srv_filtreaza_suma(ser, 10);

	assert(get_dim(filtrata) == 1);

	distruge_lista(filtrata, distruge_cheltuiala);

	//fitrare tip
	filtrata = srv_filtreaza_tip(ser, "apa");

	assert(get_dim(filtrata) == 2);


	distruge_lista(filtrata, distruge_cheltuiala);

	distruge_service(ser);

	
	//sortare
	cap = 10;
	lista = creeaza_lista(cap);
	ser = creeaza_service(lista);
	int reversed;

	nrAp = 1;
	suma = 20;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	nrAp = 1;
	suma = 10;
	strcpy(tip, "gaz");
	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	nrAp = 3;
	suma = 15;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ser, nrAp, suma, tip);

	Lista* sortata;

	
	//suma cresc
	reversed = 1;

	sortata = srv_sorteaza_suma(ser, reversed);


	assert(get_suma(sortata->vec[0]) == 10);
	assert(get_suma(sortata->vec[1]) == 15);
	assert(get_suma(sortata->vec[2]) == 20);
	
	distruge_lista(sortata, distruge_cheltuiala);

	//suma descresc
	reversed = 2;

	sortata = srv_sorteaza_suma(ser, reversed);

	assert(get_suma(sortata->vec[0]) == 20);
	assert(get_suma(sortata->vec[1]) == 15);
	assert(get_suma(sortata->vec[2]) == 10);

	distruge_lista(sortata, distruge_cheltuiala);

	//tip cresc
	
	reversed = 1;

	sortata = srv_sorteaza_tip(ser, reversed);
	
	char t0[20], t1[20], t2[20];
	get_tip(sortata->vec[0], t0);
	get_tip(sortata->vec[1], t1);
	get_tip(sortata->vec[2], t2);
	
	assert(str_equ(t0, "apa"));
	
	assert(str_equ(t1, "apa"));
	
	assert(str_equ(t2, "gaz"));

	distruge_lista(sortata, distruge_cheltuiala);

	//tip descresc

	reversed = 2;

	sortata = srv_sorteaza_tip(ser, reversed);


	get_tip(sortata->vec[0], t0);
	get_tip(sortata->vec[1], t1);
	get_tip(sortata->vec[2], t2);

	assert(str_equ(t0, "gaz"));

	assert(str_equ(t1, "apa"));

	assert(str_equ(t2, "apa"));

	distruge_lista(sortata, distruge_cheltuiala);

	distruge_service(ser);
	
}

void run_lista_de_liste_tests() {
	Lista* cheltuieli = creeaza_lista(2);
	adauga_elem(cheltuieli, creeaza_cheltuiala(1, 10, "apa"));
	adauga_elem(cheltuieli, creeaza_cheltuiala(1, 10, "apa"));

	Lista* cheltuieli2 = creeaza_lista(2);

	Lista* undo_list = creeaza_lista(4);
	adauga_elem(undo_list, cheltuieli);
	assert(get_dim(undo_list) == 1);
	adauga_elem(undo_list, cheltuieli2);
	assert(get_dim(undo_list) == 2);

	distruge_lista(undo_list, distruge_lista_cheltuieli);
}

void run_undo_test() {
	Service* srv = creeaza_service(creeaza_lista(2));
	assert(srv_undo(srv) == 1);
	srv_adauga_cheltuiala(srv, 1, 10.0, "apa");
	assert(get_dim(srv->undo_list) == 1);
	srv_adauga_cheltuiala(srv, 2, 20.0, "gaz");
	assert(get_dim(srv->undo_list) == 2);
	assert(srv_undo(srv) == 0);
	assert(get_dim(srv->undo_list) == 1);
	distruge_service(srv);
}
void test_filtreaza_suma_interval() {
	Service* srv = creeaza_service(creeaza_lista(2));
	srv_adauga_cheltuiala(srv, 1, 20.0, "apa");
	srv_adauga_cheltuiala(srv, 2, 70.0, "canal");
	srv_adauga_cheltuiala(srv, 3, 85.0, "incalzire");
	
	Lista* rez = srv_filtreaza_suma_interval(srv, 10.0, 90.0);
	assert(get_dim(rez) == 3);
	distruge_lista(rez, distruge_cheltuiala);

	rez = srv_filtreaza_suma_interval(srv, 10.0, 84.0);
	assert(get_dim(rez) == 2);
	distruge_lista(rez, distruge_cheltuiala);

	rez = srv_filtreaza_suma_interval(srv, 100.0, 230.0);
	assert(get_dim(rez) == 0);
	distruge_lista(rez, distruge_cheltuiala);

	distruge_service(srv);
}

void test_tip_sortat_suma() {
	Service* srv = creeaza_service(creeaza_lista(3));
	srv_adauga_cheltuiala(srv, 1, 120, "apa");
	srv_adauga_cheltuiala(srv, 2, 120, "incalzire");
	srv_adauga_cheltuiala(srv, 3, 20, "apa");
	srv_adauga_cheltuiala(srv, 4, 60, "apa");
	Lista* rez = srv_tip_sortat_suma(srv, "apa");
	assert(get_dim(rez) == 3);
	assert(get_suma(get_elem(rez, 0)) == 20);
	assert(get_suma(get_elem(rez, 1)) == 60);
	assert(get_suma(get_elem(rez, 2)) == 120);
	distruge_lista(rez, distruge_cheltuiala);
	distruge_service(srv);
}

void run_all_tests()
{
	run_utils_tests();
	run_domain_tests();
	run_valid_tests();
	run_lista_tests();
	run_lista_de_liste_tests();
	run_service_tests();
	run_undo_test();
	test_filtreaza_suma_interval();
	test_tip_sortat_suma();
}