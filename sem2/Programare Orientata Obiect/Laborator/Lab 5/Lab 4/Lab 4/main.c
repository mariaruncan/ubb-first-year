#define _CRTDBG_MAP_ALLOC

#include "teste.h"
#include "domain.h"
#include "service.h"
#include "lista.h"
#include "ui.h"
#include "utils.h"

#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	run_all_tests();

	int cap = 10;
	Lista* lista = creeaza_lista(cap);
	Service* srv = creeaza_service(lista);
	UI* ui = creeaza_ui(srv);

	run(ui);

	distruge_ui(ui);

	_CrtDumpMemoryLeaks();
}