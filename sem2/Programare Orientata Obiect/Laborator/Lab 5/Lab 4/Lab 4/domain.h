#pragma once

/// <summary>
/// stocheaza Cheltuiala
/// nrAp - nr natural nenul
/// suma - nr rational nenul
/// tip - {apa, canal, gaz, incalzire}
/// </summary>
typedef struct
{
	int nrAp;
	double suma;
	char* tip;

}Cheltuiala;

/// <summary>
/// creeaza o cheltuiala si o aloca in heap
/// </summary>
/// <param name="nrAp"> int
/// <param name="suma"> double
/// <param name="tip"> pointeri de caractere
/// <returns> chelt = pointer catre cheltuiala creata din heap
Cheltuiala* creeaza_cheltuiala(int nrAp, double suma, char* tip);

/// <summary>
/// dealoca cheltuiala din heap
/// </summary>
/// <param name="chelt"> pointer catre cheltuiala care trebuie stearsa
void distruge_cheltuiala(Cheltuiala* chelt);

/// <summary>
/// copiaza o cheltuiala si o aloca in heap
/// </summary>
/// <param name="chelt"></param>
/// <returns> chelt = pointer catre cheluiala copiata din heap
Cheltuiala* copiaza_cheltuiala(Cheltuiala* chelt);


/// <summary>
/// returneaza nrAp
/// </summary>
/// <param name="chelt"> pointer catre cheltuiala
/// <returns> int nrAp
int get_nrAp(Cheltuiala* chelt);

/// <summary>
/// returneaza suma
/// </summary>
/// <param name="chelt"> pointer catre cheltuiala
/// <returns> double nrAp
double get_suma(Cheltuiala* chelt);

/// <summary>
/// returneaza pointer catre tip
/// </summary>
/// <param name="chelt"> pointer catre cheltuiala
/// <returns> char* tip
void get_tip(Cheltuiala* chelt, char* tip);

