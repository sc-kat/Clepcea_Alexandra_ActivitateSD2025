#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <string.h>


struct Carte {
	int id;
	char* titlu;
	int nrEditii;
};

typedef struct Carte Carte;

struct Nod {
	Carte info;
	struct Nod* next;
};

typedef struct Nod Nod;

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

void afiseazaCarte(struct Carte c) {
	printf("ID: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Numar editii: %d\n", c.nrEditii);
}

void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afiseazaCarte(cap->info);
		cap = cap->next;
	}
}

void adaugaCarteInLista(Nod* *cap, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua; //shallow copy
	nou->next = NULL;

	if (*cap) {
		Nod* p = *cap;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	} 
	else {
		*cap = nou;
	}
}

void adaugaCarteLaInceputDeLista(Nod* *cap, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->next = *cap;
	*cap = nou;
	
}

Nod* citireListaCartiDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			Carte c = citesteCarteDinFisier(f);
			adaugaCarteInLista(&cap, c);
		}
	}
	fclose(f);
	return cap;
}

void dezalocareListaCarti(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		if (p->info.titlu) {
			free(p->info.titlu);
		}
		free(p);
	}
}

//struct Carte initializare(int id, char* titlu, int nrEditii) {
//	struct Carte c;
//	c.id = id;
//	c.titlu = (char*)malloc((strlen(titlu) + 1) * sizeof(char));
//	strcpy_s(c.titlu, strlen(titlu) + 1, titlu);
//	c.nrEditii = nrEditii;
//	return c;
//}

//struct Carte citesteCarte() {
//	struct Carte c;
//	char buffer[100];
//
//	printf("Introdu ID-ul cartii: ");
//	scanf("%d", &c.id);
//	getchar();
//
//	printf("Introdu titlul cartii: ");
//	fgets(buffer, sizeof(buffer), stdin);
//	buffer[strcspn(buffer, "\n")] = 0;
//	
//	c.titlu = (char*)malloc(strlen(buffer) + 1);
//	strcpy(c.titlu, buffer);
//
//	printf("Introdu numarul de editii: ");
//	scanf("%d", &c.nrEditii);
//
//	return c;
//}

//void afiseazaVector(struct Carte* vector, int dim) {
//	for (int i = 0; i < dim; i++) {
//		afiseazaCarte(vector[i]);
//	}
//}

//void inserareCarteVector(struct Carte** vector, int* dim, struct Carte carte) {
//	struct Carte* aux = (struct Carte*)malloc(sizeof(struct Carte) * (*dim + 1));
//	for (int i = 0; i < *dim; i++) {
//		aux[i] = (*vector)[i];
//	}
//	aux[*dim] = carte;
//	aux[*dim].titlu = (char*)malloc(strlen(carte.titlu) + 1);
//	strcpy_s(aux[*dim].titlu, strlen(carte.titlu) + 1, carte.titlu);
//
//	free(*vector);
//	*vector = aux;
//	(*dim)++;
//}

//struct Carte* citireVectorDinFisier(const char* numeFisier, int* dim) {
//	FILE* f = fopen(numeFisier, "r");
//	struct Carte* vector = NULL;
//	(*dim) = 0;
//
//	if (!f) {
//		printf("Eroare la deschiderea fisierului!\n");
//		return NULL;
//	}
//
//	while (!feof(f)) {
//		struct Carte c = citesteCarteDinFisier(f);
//		inserareCarteVector(&vector, dim, c);
//	}
//	fclose(f);
//	return vector;
//}

//char* verificaPopularitatea(struct Carte c) {
//	if (c.nrEditii >= 3) {
//		return "Cartea are mai mult de 3 editii si este considerata populara.";
//	}
//	else {
//		return "Cartea are mai putin de 3 editii si nu este considerata populara.";
//	}
//}

//struct Carte* filtreazaPopulare(struct Carte* vector, int dim, int* dimRezultat) {
//
//	*dimRezultat = 0;
//	struct Carte* rezultat = (struct Carte*)malloc(dim * sizeof(struct Carte));
//
//	for (int i = 0; i < dim; i++) {
//		if (vector[i].nrEditii >= 3) {
//			rezultat[*dimRezultat] = vector[i];
//			(*dimRezultat)++;
//		}
//	}
//	return rezultat;
//}

//struct Carte* filtreazaTitluLung(struct Carte* vector, int dim, int* dimRezultat) {
//	*dimRezultat = 0;
//	struct Carte* rezultat = (struct Carte*)malloc(dim * sizeof(struct Carte));
//
//	for (int i = 0; i < dim; i++) {
//		if (strlen(vector[i].titlu) > 10) {
//			rezultat[*dimRezultat] = vector[i];
//			(*dimRezultat)++;
//		}
//	}
//	return rezultat;
//}

//struct Carte* concateneazaVectori(struct Carte* v1, struct Carte* v2, int dim1, int dim2, int* dimRezultat) {
//
//	*dimRezultat = dim1 + dim2;
//	struct Carte* rezultatConcatenare = (struct Carte*)malloc((*dimRezultat) * sizeof(struct Carte));
//
//	for (int i = 0; i < dim1; i++) {
//		rezultatConcatenare[i] = v1[i];
//	}
//	for (int i = 0; i < dim2; i++) {
//		rezultatConcatenare[dim1 + i] = v2[i];
//	}
//
//	return rezultatConcatenare;
//}

//void modificaTitlu(struct Carte* c, const char* titluNou) {
//	free(c->titlu);
//	c->titlu = (char*)malloc(strlen(titluNou) + 1);
//	strcpy_s(c->titlu, strlen(titluNou) + 1, titluNou);
//}

//void dezalocareVectorCarti(struct Carte** vector, int* dim) {
//	for (int i = 0; i < *dim; i++) {
//		free((*vector)[i].titlu);
//	}
//
//	free(*vector);
//	*vector = NULL;
//	*dim = 0;
//}

/*int main()*/ {
	//struct Carte carte = citesteCarte();
	//afiseazaCarte(carte);

	//modificaTitlu(&carte, "Ion");

	//afiseazaCarte(carte);

	//printf("\n%s\n",verificaPopularitatea(carte));


	/*int dim = 5;
	struct Carte* carti = (struct Carte*)malloc(dim * sizeof(struct Carte));*/

	//if (carti) {
	//	carti[0] = initializare(1, "Sapho", 3);
	//	carti[1] = initializare(2, "La Medeleni", 1);
	//	carti[2] = initializare(3, "Mara", 2);
	//	carti[3] = initializare(4, "Invitatie la vals", 11);
	//	carti[4] = initializare(5, "1Q84", 10);
	//}

	//
	//int dimPopulare = 0;
	//struct Carte* populare = filtreazaPopulare(carti, dim, &dimPopulare);
	//
	//printf("\n=== Carti populare (nrEditii >= 3) ===\n");
	//afiseazaVector(populare, dimPopulare);

	//int dimTitluLung = 0;
	//struct Carte* titluLung = filtreazaTitluLung(carti, dim, &dimTitluLung);

	//printf("\n=== Carti cu titlu mai lung de 10 caractere ===\n");
	//afiseazaVector(titluLung, dimTitluLung);


	//int dimConcatenare = 0;
	//struct Carte* concatenare = concateneazaVectori(populare, titluLung, dimPopulare, dimTitluLung, &dimConcatenare);

	//printf("\n=== Vector concatenat (populare + titlu lung) ===\n");
	//afiseazaVector(concatenare, dimConcatenare);

	//FILE* f = fopen("carti.txt", "r");
	//struct Carte c = citesteCarteDinFisier(f);
	//afiseazaCarte(c);

	/*struct Carte* carti = NULL;
	int nrCarti = 0;
	carti = citireVectorDinFisier("carti.txt", &nrCarti);*/
	/*afiseazaVector(carti, nrCarti);

	dezalocareVectorCarti(&carti, &nrCarti);*/

//	Nod* cap = citireListaCartiDinFisier("carti.txt");
//	afisareListaCarti(cap);
//	
//	dezalocareListaCarti(&cap);
//
//
//	return 0;
//}