#pragma once
#include "service.h"

typedef struct
{
	Service* srv;
}UI;

/// <summary>
/// creeaza un ui cu service dat
/// </summary>
/// <param name="srv">pointer catre service
/// <returns>returneaza pointer catre ui creat in heap
UI* creeaza_ui(Service* srv);

/// <summary>
/// ruleaza aplicatia
/// </summary>
/// <param name="ui">pointer catre ui
void run(UI* ui);

/// <summary>
/// distruge ui din heap
/// </summary>
/// <param name="ui"></param>
void distruge_ui(UI* ui);


///afiseaza lista data ca parametru
/// <param name="lista">pointer catre lista din heap
void afisare_lista(Lista* lista);