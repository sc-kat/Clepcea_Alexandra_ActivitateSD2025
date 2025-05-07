#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


struct Carte {
	int id;
	char* titlu;
	int nrEditii;
};

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

void modificaTitlu(struct Carte* c, const char* titluNou) {
	free(c->titlu);
	c->titlu = (char*)malloc(strlen(titluNou) + 1);
	strcpy_s(c->titlu, strlen(titluNou) + 1, titluNou);
}

int main() {
	struct Carte carte = citesteCarte();
	afiseazaCarte(carte);

	modificaTitlu(&carte, "Ion");

	afiseazaCarte(carte);

	printf("\n%s\n",verificaPopularitatea(carte));

	return 0;
}