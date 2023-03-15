#pragma once
#include "domain.h"
#include "lista.h"

/// <summary>
/// definire functie de comparare
/// </summary>
typedef int(*FunctieComparare)(Cheltuiala* c1, Cheltuiala* c2);


/// <summary>
/// sorteaza lista dupa functia de comparare data
/// </summary>
/// <param name="lista">pointer catre lista
/// <param name="cmp">functie de comparare
Lista* sorteaza_lista(Lista* lista, FunctieComparare cmp);