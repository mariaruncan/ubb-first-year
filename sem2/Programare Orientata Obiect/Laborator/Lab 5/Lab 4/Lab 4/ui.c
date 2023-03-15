#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "utils.h"
#include "service.h"
#include "lista.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


UI* creeaza_ui(Service* srv)
{
	UI* ui = malloc(sizeof(UI));
	if (ui)
		ui->srv = srv;

	return ui;
}

void distruge_ui(UI* ui)
{
	distruge_service(ui->srv);
	free(ui);
}

int read_int()
{
	/*
	int nr;
	char nr_s[100];
	scanf_s("%s", nr_s, 15);
	nr = atoi(nr_s);
	*/
	int nr;
	scanf_s("%d", &nr);

	return nr;
}

double read_double()
{
	/*
	double nr;
	char nr_s[100];
	scanf_s("%s", nr_s, 15);
	nr = atof(nr_s);
	*/
	double nr;
	scanf_s("%lf", &nr);

	return nr;
}

void afisare_meniu()
{
	
	printf("1: Adauga cheltuiala\n");
	printf("2: Sterge cheltuiala\n");
	printf("3: Modifica cheltuiala\n");
	printf("4: Afisare lista de cheltuieli\n");
	printf("5: Filtrare\n");
	printf("6: Sortare\n");
	printf("7. Undo\n");
	printf("8. Afisare cheltuieli de un anumit tip sortate dupa suma\n");
	printf("0: Iesire din aplicatie\n");
}

void afisare_cheltuiala(Cheltuiala* chelt)
{
	char tip[20];
	get_tip(chelt, tip);
	printf("Nr. Ap. = %d, Suma = %f lei, Tip = %s \n", get_nrAp(chelt), get_suma(chelt), tip);
}

void afisare_lista(Lista* lista)
{
	int i;
	printf("\nLista de cheltuieli:\n");
	for (i = 1; i <= lista->dim; i++)
	{
		printf("%d: ", i);
		afisare_cheltuiala(lista->vec[i-1]);
	}

	printf("\n");
}



int ui_adauga_cheltuiala(UI* ui)
{
	int nrAp;
	double suma;
	char tip[20];

	int rez = 1;

	printf("Numar Apartament = ");
	nrAp = read_int();

	printf("Suma = ");
	suma = read_double();

	printf("Tip (apa, canal, gaz, incalzire) = ");
	scanf_s("%s", tip, 20);

	if (nrAp == 0)
		rez *= 3;

	if (double_equ(suma, 0))
		rez *= 5;

	if (rez == 1)
		rez = srv_adauga_cheltuiala(ui->srv, nrAp, suma, tip);

	return rez; 
}



int ui_sterge_cheltuiala(UI* ui)
{
	int index, rez;
	rez = 1;
	printf("Element de sters: ");
	index = read_int();
	index--;

	rez = srv_sterge_cheltuiala(ui->srv, index);

	return rez;
}



int ui_modifica_cheltuiala(UI* ui)
{
	int index, nrAp;
	double suma;
	char tip[20];
	int rez = 1;

	printf("Element de modificat: ");
	index = read_int();
	index--;

	printf("Numar Apartament = ");
	nrAp = read_int();

	printf("Suma noua: ");
	suma = read_double();

	printf("Tipul nou (apa, canal, gaz, incalzire): ");
	scanf_s("%s", &tip, 20);

	if (nrAp == 0)
		rez *= 3;

	if (double_equ(suma, 0))
		rez *= 5;

	if (rez == 1)
		rez = srv_modifica_cheltuiala(ui->srv, index, nrAp, suma, tip);


	return rez;
}



void meniu_filtrare()
{
	printf("1: Filtrare dupa numar apartament\n");
	printf("2: Filtrare dupa suma\n");
	printf("3: Filtrare dupa tip\n");
	printf("4: Filtrare dupa suma (interval dat)\n");
}
void ui_filtrare(UI* ui)
{
	meniu_filtrare();

	Lista* lista;

	int cmd;
	cmd = read_int();

	int nrAp;
	double suma, suma2;
	char tip[20];

	switch (cmd)
	{
		case 1:
			printf("Numar Apartament: ");
			nrAp = read_int();
			lista = srv_filtreaza_nrAp(ui->srv, nrAp);
			afisare_lista(lista);
			distruge_lista(lista, distruge_cheltuiala);
			break;

		case 2:
			printf("Suma: ");
			suma = read_double();
			lista = srv_filtreaza_suma(ui->srv, suma);
			afisare_lista(lista);
			distruge_lista(lista, distruge_cheltuiala);
			break;

		case 3:
			printf("Tip: ");
			scanf_s("%s", tip,20);
			lista = srv_filtreaza_tip(ui->srv, tip);
			afisare_lista(lista);
			distruge_lista(lista, distruge_cheltuiala);
			break;

		case 4:
			printf("Suma minima: ");
			suma = read_double();
			printf("Suma maxima: ");
			suma2 = read_double();
			Lista* rez = srv_filtreaza_suma_interval(ui->srv, suma, suma2);
			afisare_lista(rez);
			distruge_lista(rez, distruge_cheltuiala);
			break;
		
		default:
			printf("Comanda invalida!\n");
			break;
	}
	
		
}

void meniu_sortare_1()
{
	printf("1: Sortare dupa suma\n");
	printf("2: Sortare dupa tip\n");
}
void meniu_sortare_2()
{
	printf("1: Crescator\n");
	printf("2: Descrescator\n");
}
void ui_sortare(UI* ui)
{
	Lista* lista;

	meniu_sortare_1();
	int cmd;
	cmd = read_int();

	meniu_sortare_2();
	int reversed;
	reversed = read_int();

	if (reversed != 1 && reversed != 2)
		cmd = 0;


	switch (cmd)
	{
	case 0:
		printf("Comanda invalida!\n");
		break;

	case 1:
		lista = srv_sorteaza_suma(ui->srv, reversed);
		afisare_lista(lista);
		distruge_lista(lista, distruge_cheltuiala);
		break;

	case 2:
		lista = srv_sorteaza_tip(ui->srv, reversed);
		afisare_lista(lista);
		distruge_lista(lista, distruge_cheltuiala);
		break;

	}
}

void ui_undo(UI* ui) {
	int error = srv_undo(ui->srv);
	if (error) {
		printf("Nu se mai poate face undo!\n\n");
	}
	else {
		printf("Undo a avut loc cu succes!\n\n");
	}
}

void ui_tip_sortat_suma(UI* ui) {
	printf("Tipul (apa, canal, gaz, incalzire):");
	char tip[20];
	scanf_s("%s", tip, 20);
	Lista* lista = srv_tip_sortat_suma(ui->srv, tip);
	afisare_lista(lista);
	distruge_lista(lista, distruge_cheltuiala);

}

void generare(UI* ui)
{
	int nrAp;
	double suma;
	char tip[20];

	nrAp = 1;
	suma = 20;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ui->srv,nrAp, suma, tip);

	nrAp = 2;
	suma = 10;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ui->srv, nrAp, suma, tip);

	nrAp = 3;
	suma = 15;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ui->srv, nrAp, suma, tip);

	nrAp = 1;
	suma = 10;
	strcpy(tip, "gaz");
	srv_adauga_cheltuiala(ui->srv, nrAp, suma, tip);

	nrAp = 1;
	suma = 20;
	strcpy(tip, "incalzire");
	srv_adauga_cheltuiala(ui->srv, nrAp, suma, tip);

	nrAp = 4;
	suma = 30;
	strcpy(tip, "apa");
	srv_adauga_cheltuiala(ui->srv, nrAp, suma, tip);

	nrAp = 2;
	suma = 10;
	strcpy(tip, "incalzire");
	srv_adauga_cheltuiala(ui->srv, nrAp, suma, tip);

}

void run(UI* ui)
{
	int cmd, rez;
	
	generare(ui);
	while (1)
	{

		afisare_meniu();
		printf(">>> ");
		
		cmd = read_int();

		rez = 1;

		if (cmd == 0)//iesire din aplicatie
			break;
		switch (cmd)
		{
			case 1://creeaza cheltuiala
				rez = ui_adauga_cheltuiala(ui);
				break;

			case 2://sterge cheltuiala
				rez = ui_sterge_cheltuiala(ui);
				break;

			case 3://modifica cheltuiala
				rez = ui_modifica_cheltuiala(ui);
				break;

			case 4://afisare lista
				afisare_lista(ui->srv->lista);
				break;

			case 5://filtrare
				ui_filtrare(ui);
				break;
			case 6://sortare
				ui_sortare(ui);
				break;
			case 7://undo
				ui_undo(ui);
				break;
			case 8:// cheltuieli de un anumit tip sortate dupa suma
				ui_tip_sortat_suma(ui);
				break;
			default:
				printf("Comanda invalida!\n");

		}

		if (rez != 1)
		{
			if (rez == 0)
				printf("Index invalid!\n");
			else
			{
				if (rez % 3 == 0)
					printf("Numar apartament invalid!\n");
				if (rez % 5 == 0)
					printf("Suma invalida!\n");
				if (rez % 7 == 0)
					printf("Tip invalid!\n");
			}
			
		}	
	}
}

