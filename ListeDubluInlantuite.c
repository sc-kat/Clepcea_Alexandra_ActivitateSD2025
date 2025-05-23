#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct Carte{
	int id;
	char* titlu;
	int nrEditii;
};
typedef struct Carte Carte;

struct Nod {
	Carte carte;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

void afiseazaCarte(struct Carte c) {
	printf("ID: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Numar editii: %d\n", c.nrEditii);
}

struct Carte citesteCarteDinFisier(FILE* f) {
	struct Carte c;
	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, sizeof(buffer), f);
	c.id = atoi(strtok(buffer, sep));;
	char* aux = strtok(NULL, sep);
	c.titlu = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.titlu, strlen(aux) + 1, aux);
	c.nrEditii = atoi(strtok(NULL, sep));

	return c;
}

void afisareListaCartiAsc(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afiseazaCarte(p->carte);
		p = p->next;
	}
}

void afisareListaCartiDesc(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afiseazaCarte(p->carte);
		p = p->prev;
	}
}

void adaugaCarteInLista(ListaDubla* lista, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->carte = carteNoua; //shallow copy
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;

}

void adaugaCarteLaInceputInLista(ListaDubla* lista, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->carte = carteNoua; //shallow copy
	nou->next = lista->first;
	nou->prev = NULL;
	if (lista->first) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	(lista->nrNoduri)++;
}

ListaDubla citireLDCarteDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	while (!feof(f)) {
		adaugaCarteInLista(&lista, citesteCarteDinFisier(f));
	}
	fclose(f);
	return lista;
}

int main() {
	ListaDubla lista = citireLDCarteDinFisier("carti.txt");
	afisareListaCartiAsc(lista);
	printf("-------------------------------\n");

	afisareListaCartiDesc(lista);

}



