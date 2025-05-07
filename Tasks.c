#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

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

	return 0;
}