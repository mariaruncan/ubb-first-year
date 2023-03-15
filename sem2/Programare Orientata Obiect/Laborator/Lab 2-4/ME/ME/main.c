#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "service.h"
#include <stdio.h>

void test_all() {
	test_create_destroy();
	test_validate();
	test_create_list();
	test_iterate_list();
	test_copy_list();
	test_resize();
	test_add();
	test_update();
	test_delete();
	test_sort();
	test_filter_producer();
	test_filter_price();
	test_filter_quantity();
	test_list_of_lists();
	test_undo();
}

int read_command() {
	printf("1. Adauga produs\n");
	printf("2. Actualizeaza produs\n");
	printf("3. Sterge produs\n");
	printf("4. Sorteaza produse\n");
	printf("5. Filtreaza produse\n");
	printf("6. Printeaza toate produsele\n");
	printf("7. Undo\n");
	printf("0. Iesire din aplicatie\n");
	printf("Introduceti comanda: ");
	int cmd;
	scanf_s("%d", &cmd);
	printf("\n");
	return cmd;
}

void ui_add(Inventory* inv, int* id) {
	char type[21];
	char producer[21];
	char model[21];
	float price;
	int quantity;
	printf("Tip: ");
	scanf_s("%s", type, 21);
	printf("Producator: ");
	scanf_s("%s", producer, 21);
	printf("Model: ");
	scanf_s("%s", model, 21);
	printf("Pret: ");
	scanf_s("%f", &price);
	printf("Cantitate: ");
	scanf_s("%d", &quantity);

	int error = add_product(inv, *id, type, producer, model, price, quantity);
	if (error == 0) { // returneaza 0 pt adaugare cu succes
		printf("Adaugat cu succes!\n\n");
		(*id)++;
	}
	else if (error == 1) // returneaza 1 pt produs invalid
		printf("Produs invalid!\n\n");
	else    // returneaza 2 pt stoc actualizat 
		printf("Acest produs se afla deja in lista. Cantitatea acestuia a fost actualizata la %d.\n\n", quantity);
}

void ui_print_list(List* l) {
	if (l->lg == 0)
		printf("Nu exista produse!\n\n");
	else {
		for (int i = 0; i < l->lg; i++) {
			Product* p = get_elem(l, i);
			printf("Id: %d\n", p->id);
			printf("Tip: %s\n", p->type);
			printf("Producator: %s\n", p->producer);
			printf("Model: %s\n", p->model);
			printf("Pret: %f\n", p->price);
			printf("Cantitate: %d\n\n", p->quantity);
		}
	}
}

void ui_update(Inventory* inv) {
	int cmd;
	int id;
	float price = -1;
	int quantity = -1;
	
	printf("Id-ul produsului de actualizat: ");
	scanf_s("%d", &id);
	printf("\nCe doriti sa actualizati?\n1. Pretul\n2. Catitatea\nIntroduceti comanda: ");
	scanf_s("%d", &cmd);
	if (cmd == 1 || cmd == 2) {
		if (cmd == 1) {
			printf("Pretul nou: ");
			scanf_s("%f", &price);
		}
		else {
			printf("Cantitatea noua: ");
			scanf_s("%d", &quantity);
		}
		int error = update_product(inv, id, price, quantity);
		if (error == 0)  // 0 - actualizat cu succes
			printf("Produs actualizat!\n\n");
		else if (error == 1) // 1 - pret cantitate noua invalida
			printf("Pret/cantitate invalida!\n\n");
		else // 2 - id invalid (nu exista produs cu id-ul dat)
			printf("Produsul cu id-ul %d nu exista!\n\n", id);
	}
	else
		printf("Comanda invalida!\n\n");
}

void ui_delete(Inventory* inv) {
	ui_print_list(inv->l);
	printf("Id-ul produsului de sters: ");
	int id;
	scanf_s("%d", &id);
	int error = delete_product(inv, id);
	if (error == 0)  //0 - sters cu succes
		printf("Produs sters!\n\n");
	else // 1 - nu exista produsul cu id-ul dat
		printf("Nu exista produsul cu id-ul %d!\n\n", id);
}

void ui_sort(Inventory* inv) {
	printf("1. Crescator dupa pret\n");
	printf("2. Descrescator dupa pret\n");
	printf("3. Crescator dupa cantitate\n");
	printf("4. Descrescator dupa cantitate\n");
	printf("Introduceti comanda : ");
	int cmd;
	scanf_s("%d", &cmd);
	if (cmd < 1 || cmd > 4)
		printf("Comanda invalida!\n\n");
	else {
		printf("\n");
		List* rez = sort_products(inv, cmd);
		ui_print_list(rez);
		destroy_list(rez, destroy_product);
	}
}

void ui_filter(Inventory* inv) {
	printf("1. Dupa producator\n");
	printf("2. Dupa pret\n");
	printf("3. Dupa cantitate\n");
	printf("Introduceti comanda : ");
	int cmd;
	scanf_s("%d", &cmd);
	if (cmd == 1) {
		printf("Producatorul: ");
		char producer[21];
		scanf_s("%s", producer, 21);
		printf("\n");
		List* rez = filter_producer(inv, producer);
		ui_print_list(rez);
		destroy_list(rez, destroy_product);
	}
	else if (cmd == 2) {
		float max_price, min_price;
		printf("Pretul minim: ");
		scanf_s("%f", &min_price);
		printf("Pretul maxim: ");
		scanf_s("%f", &max_price);
		printf("\n");
		List* rez = filter_price(inv, min_price, max_price);
		ui_print_list(rez);
		destroy_list(rez, destroy_product);
	}
	else if (cmd == 3) {
		printf("Cantitate minima: ");
		int quantity;
		scanf_s("%d", &quantity);
		printf("\n");
		List* rez = filter_quantity(inv, quantity);
		ui_print_list(rez);
		destroy_list(rez, destroy_product);
	}
	else
		printf("Comanda invalida!\n\n");
}

void ui_undo(Inventory* inv) {
	int error = undo(inv);
	if (error) {
		printf("Nu se mai poate face undo!\n\n");
	}
	else {
		printf("Undo facut cu succes!\n\n");
	}
}

void sample_products(Inventory* inv, int* id) {
	add_product(inv, *id, "laptop", "asus", "vivobook", 2999.99f, 12);
	(*id)++;
	add_product(inv, *id, "smartphone", "apple", "12Pro", 3419.99f, 20);
	(*id)++;
	add_product(inv, *id, "frigider", "samsung", "RT32K", 1999.99f, 5);
	(*id)++;
	add_product(inv, *id, "televizor", "LG", "43LMSmart", 1099.99f, 25);
	(*id)++;
	add_product(inv, *id, "laptop", "asus", "studiobook", 2599.99f, 8);
	(*id)++;
	add_product(inv, *id, "smartphone", "samsung", "a51", 1529.99f, 32);
	(*id)++;
}

void run() {
	printf("Aplicatie pentru gestiunea stocului de produse dintr-un magazin de electronice\n\n");
	Inventory* inv = create_inventory();
	int id = 1;
	sample_products(inv, &id);
	int cmd = -1;
	while (cmd) {
		cmd = read_command();
		switch (cmd) {
		case 1:
			ui_add(inv, &id);
			break;
		case 2:
			ui_update(inv);
			break;
		case 3:
			ui_delete(inv);
			break;
		case 4:
			ui_sort(inv);
			break;
		case 5:
			ui_filter(inv);
			break;
		case 6:
			ui_print_list(inv->l);
			break;
		case 7:
			ui_undo(inv);
			break;
		case 0:
			printf("Byeee :)\n");
			break;
		default:
			printf("Comanda invalida!\n");
		}
	}
	destroy_inventory(inv);
}

int main() {
	test_all();
	run(); // comment for OpenCPPCoverage
	_CrtDumpMemoryLeaks();
	return 0;
}
