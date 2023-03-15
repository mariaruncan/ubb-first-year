#pragma once

#include "lista.h"

/// <summary>
/// stocheaza pointer catre lista
/// </summary>
typedef struct
{
	Lista* lista;
	Lista* undo_list;
}Service;





/// <summary>
/// constructor de service alocat in heap
/// initializeaza cu o lista data
/// </summary>
/// <param name="lista">pointer catre lista alocata in heap
/// <returns>srv = pointer catre Service alocat in heap
Service* creeaza_service(Lista* lista);

/// <summary>
/// dealoca memoria service ului alocat in heap
/// </summary>
/// <param name="ser">pointer catre service ul care trebuie distrus
void distruge_service(Service* ser);

/// <summary>
/// creeaza cheltuiala si o valideaza
/// daca e valida o adauga in lista
/// </summary>
/// <param name="srv"> Service
/// <param name="nrAp">int
/// <param name="suma">double
/// <param name="tip">char*
/// <returns>rez
/// rez = 1 - daca toate date sunt valide
/// rez % 3 - daca nrAp e invalid (nrAp > 0)
/// rez % 5 - daca suma e invalida (suma > 0)
/// rez % 7 - daca tipul este invalid (tip apartine {apa, gaz, incalzire, canal}
int srv_adauga_cheltuiala(Service* srv, int nrAp, double suma, char* tip);

/// <summary>
/// sterge o cheltuiala
/// </summary>
/// <param name="srv">pointer catre service
/// <param name="index">indexul cheltuieli care va fi stearsa (index < capacitatea listei din service)
/// <returns>rez
/// rez = 1: daca index e valid
/// rez = 0: daca index nu e valid
int srv_sterge_cheltuiala(Service* srv, int index);

/// <summary>
/// modifica o cheltuiala cu valorile date
/// </summary>
/// <param name="srv">pointer catre service
/// <param name="index">indexul cheltuieli care va fi modificata
/// <param name="nrAp">int
/// <param name="suma">double
/// <param name="tip">char*
/// <returns>rez
/// rez = 1: daca cheltuiala a fost modificata
/// rez = 0: daca index e invalid
/// rez % 3 == 0: daca nrAp e invalid
/// rez % 5 == 0: daca suma e invalida
/// rez % 7 == 0: daca tipul e invalid
int srv_modifica_cheltuiala(Service* srv, int index, int nrAp, double suma, char* tip);

/// <summary>
/// filtreaza lista de cheltuieli dupa nrAp
/// </summary>
/// <param name="srv">pointer catre service
/// <param name="nrAp">int
/// <returns>pointer catre lista filtrata
Lista* srv_filtreaza_nrAp(Service* srv, int nrAp);

/// <summary>
/// filtreaza lista de cheltuieli dupa suma
/// </summary>
/// <param name="srv">pointer catre service
/// <param name="suma">double
/// <returns>pointer catre lista filtrata
Lista* srv_filtreaza_suma(Service* srv, double suma);

/// <summary>
/// filtreaza lista de cheltuieli dupa tip
/// </summary>
/// <param name="srv">pointer catre service
/// <param name="tip">char*
/// <returns>pointer catre o noua lista filtrata alocata in heap
Lista* srv_filtreaza_tip(Service* srv, char* tip);

// filtreaza lista de cheltuieli dupa suma
// date de intrare: srv - pointer catre un obiect de tip Service
//					s1, s2 - double
// returneaza un pointer catre o noua lista care va avea cheltuielile cu sumele din intervalul [s1, s2]
Lista* srv_filtreaza_suma_interval(Service* srv, double s1, double s2);

/// <summary>
/// sorteaza lista de cheltuieli dupa suma 
/// reversed == 1 => crescator
/// reversed == 2 => descrescator
/// </summary>
/// <param name="srv">pointer catre service
/// <param name="reversed"> 1 sau 2
/// <returns>pointer catre o noua lista filtrata alocata in heap
Lista* srv_sorteaza_suma(Service* srv, int reversed);

/// <summary>
/// sorteaza lista de cheltuieli dupa tip
/// reversed == 1 => crescator
/// reversed == 2 => descrescator
/// </summary>
/// <param name="srv">pointer catre service
/// <param name="reversed"> 1 sau 2
/// <returns>pointer catre o noua lista filtrata alocata in heap
Lista* srv_sorteaza_tip(Service* srv, int reversed);

/*
functie de undo
primeste ca parametru un pointer la un obiect de tipul Service
post: lista revine la forma de dinaintea ultimei stergei/adaugari/modificari
returneaza - 1 daca nu se poate face undo(lista este goala)
		   - 0 daca undo a fost realizat cu succes
*/
int srv_undo(Service* srv);

/*
functia returneaza o lista de cheltuieli care au tipul tip
post: lista este sortata crescator dupa suma
*/
Lista* srv_tip_sortat_suma(Service* srv, char* tip);
