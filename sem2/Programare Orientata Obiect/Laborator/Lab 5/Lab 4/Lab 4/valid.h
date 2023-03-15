#pragma once

#include "domain.h"


/// <summary>
/// valideaza id, nrAp, suma si tipul cheltuielii date prin pointerul chelt
/// </summary>
/// <param name="chelt"> pointer catre cheltuiala alocata in heap
/// <returns> rez
/// rez = 1 - daca toate date sunt valide
/// rez % 3 - daca nrAp e invalid (nrAp > 0)
/// rez % 5 - daca suma e invalida (suma > 0)
/// rez % 7 - daca tipul este invalid (tip apartine {apa, gaz, incalzire, canal}
int valid_cheltuiala(Cheltuiala* chelt);



