#pragma once

#include "domain.h"

// TAD oarecare
typedef void* Telem;

//TAD pentru o functie de distrugere
typedef void (*DestroyFunction)(Telem);

/// <summary>
/// stocheaza o lista de pointeri catre obiecte de tip Telem
/// </summary>
typedef struct
{
	int cap;
	int dim;
	Telem* vec;
}Lista;

/// <summary> 
/// creeaza o lista goala de cheltuieli cu capacitatea data si o aloca in heap
/// </summary>
/// <param name="cap"> int
/// <returns> returneaza pointer catre lista din heap
Lista* creeaza_lista(int cap);

// functia distruge o lista de cheltuieli
// primeste ca parametru un pointer la o lista de cheltuieli
void distruge_lista_cheltuieli(Lista* lista);

/// <summary>
/// distruge lista alocata in heap
/// </summary>
/// <param name="lista">pointer catre lista
/// destrFct este o functie de distrugere a elementelor din cadrul listei
void distruge_lista(Lista* lista, DestroyFunction destrFct);

/// <summary>
/// adauga in lista un Telem
/// </summary>
/// <param name="lista"> pointer catre lista
/// <param name="chelt"> un obiect de tipul Telem
void adauga_elem(Lista* lista, Telem el);


/// <summary>
/// sterge elementul de pe pozitia 'index' din lista
/// </summary>
/// <param name="lista">pointer catre lista
/// <param name="index">indexul elementului care trebuie sters(int)
/// <returns>rez
/// rez = 1 : exista indexul dat
/// rez = 0 : nu exista indexul dat
int sterge_elem(Lista* lista, int index);

/// <summary>
/// aloca spatiu in heap daca lista nu are suficienta capacitate
/// </summary>
/// <param name="lista">pointer catre lista
void capacitate(Lista* lista);

/// <summary>
/// returneaza capacitatea listei
/// </summary>
/// <param name="lista"> pointer catre lista
/// <returns> int cap
int get_cap(Lista* lista);

/// <summary>
/// returneaza dimensiunea listei (numarul de elemente ce se afla in lista)
/// </summary>
/// <param name="lista"> pointer catre lista
/// <returns> int dim
int get_dim(Lista* lista);

/// <summary>
/// returneaza elementul de pe pozitia 'index' din lista
/// </summary>
/// <param name="lista"> pointer catre lista
/// <param name="index"> indexul elementului care trebuie returnat
/// <returns> Telem elem
Telem get_elem(Lista* lista, int index);

/// <summary>
/// modifica din lista elementul 'index' cu elementul dat
/// </summary>
/// <param name="lista"> pointer catre lista
/// <param name="index"> indexul elementului care trebuie modificat
/// <param name="elem"> noua valoare a elementului de pe pozitia 'index'
/// <returns> rez
/// rez = 1: exista indexul dat
/// rez = 0: nu exista indexul dat
int modifica_elem(Lista* lista, int index, Telem elem);

/// <summary>
/// creeaza o copie a listei si o aloca in heap
/// </summary>
/// <param name="lista"> pointer catre lista
/// <returns> copie = pointer catre noua lista creata in heap

Lista* copiaza_lista(Lista* lista);

