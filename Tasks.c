#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


struct Carte {
	int id;
	char* titlu;
	int nrEditii;
};

struct Carte initializare(int id, char* titlu, int nrEditii) {
	struct Carte c;
	c.id = id;
	c.titlu = malloc((strlen(titlu) + 1) * sizeof(char));
	strcpy_s(c.titlu, strlen(titlu) + 1, titlu);
	c.nrEditii = nrEditii;
	return c;
}

struct Carte citesteCarte() {
	struct Carte c;
	char buffer[100];

	printf("Introdu ID-ul cartii: ");
	scanf("%d", &c.id);
	getchar();

	printf("Introdu titlul cartii: ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = 0;

	c.titlu = (char*)malloc(strlen(buffer) + 1);
	strcpy(c.titlu, buffer);

	printf("Introdu numarul de editii: ");
	scanf("%d", &c.nrEditii);

	return c;
}

void afiseazaCarte(struct Carte c) {
	printf("\n--- Informatii Carte ---\n");
	printf("ID: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Numar editii: %d\n", c.nrEditii);
}

char* verificaPopularitatea(struct Carte c) {
	if (c.nrEditii >= 3) {
		return "Cartea are mai mult de 3 editii si este considerata populara.";
	}
	else {
		return "Cartea are mai putin de 3 editii si nu este considerata populara.";
	}
}

struct Carte* filtreazaPopulare(struct Carte* vector, int dim, int* dimRezultat) {

	*dimRezultat = 0;
	struct Carte* rezultat = (struct Carte*)malloc(dim * sizeof(struct Carte));

	for (int i = 0; i < dim; i++) {
		if (vector[i].nrEditii >= 3) {
			rezultat[*dimRezultat] = vector[i];
			(*dimRezultat)++;
		}
	}
	return rezultat;
}

void afiseazaVector(struct Carte* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afiseazaCarte(vector[i]);
	}
}

void modificaTitlu(struct Carte* c, const char* titluNou) {
	free(c->titlu);
	c->titlu = (char*)malloc(strlen(titluNou) + 1);
	strcpy_s(c->titlu, strlen(titluNou) + 1, titluNou);
}

int main() {
	//struct Carte carte = citesteCarte();
	//afiseazaCarte(carte);

	//modificaTitlu(&carte, "Ion");

	//afiseazaCarte(carte);

	//printf("\n%s\n",verificaPopularitatea(carte));

	int dim = 5;
	struct Carte* carti = (struct Carte*)malloc(dim * sizeof(struct Carte));

	if (carti) {
		carti[0] = initializare(1, "Sapho", 3);
		carti[1] = initializare(2, "La Medeleni", 1);
		carti[2] = initializare(3, "Mara", 2);
		carti[3] = initializare(4, "Invitatie la vals", 11);
		carti[4] = initializare(5, "1Q84", 10);
	}

	
	int dimPopulare = 0;
	struct Carte* populare = filtreazaPopulare(carti, dim, &dimPopulare);
	
	printf("\n=== Carti populare (nrEditii >= 3) ===\n");
	afiseazaVector(populare, dimPopulare);


	return 0;
}