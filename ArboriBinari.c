#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h> 

struct Avion {
	char* model;
	int nrLocuri;
	int nrLocuriOcupate;
	float* preturiBilete;
};
typedef struct Avion Avion;

struct Nod {
	Avion info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;



Avion initAvion(const char* model, int nrLocuri, int nrLocuriOcupate, float* preturiBilete) {
	Avion avion;
	avion.model = (char*)malloc(sizeof(char) * strlen(model) + 1);
	strcpy(avion.model, model);
	avion.nrLocuri = nrLocuri;
	avion.nrLocuriOcupate = nrLocuriOcupate;
	avion.preturiBilete = (float*)malloc(sizeof(float)* avion.nrLocuriOcupate);
	for (int i = 0; i < nrLocuriOcupate; i++) {
		avion.preturiBilete[i] = preturiBilete[i];
	}
	return avion;
}

void afisareAvion(Avion avion) {
	printf("Model avion:%s\n", avion.model);
	printf("Nr locuri: %d\n", avion.nrLocuri);
	printf("Nr locuri ocupate: %d\n", avion.nrLocuriOcupate);
	for (int i = 0; i < avion.nrLocuriOcupate;i++) {
		printf("Pret bilet %d: %5.2f\n",i+1, avion.preturiBilete[i]);

	}
	printf("\n");
}

Avion citesteAvionDinFisier(FILE* f) {
	Avion a;
	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, sizeof(buffer), f);
	char* aux = strtok(buffer, sep);
	a.model = (char*)malloc(strlen(aux) + 1);
	strcpy(a.model,aux);
	a.nrLocuri = atoi(strtok(NULL, sep));
	a.nrLocuriOcupate = atoi(strtok(NULL, sep));

	a.preturiBilete = (float*)malloc(sizeof(float) * a.nrLocuriOcupate);
	for (int i = 0; i < a.nrLocuriOcupate; i++) {
		a.preturiBilete[i] = atof(strtok(NULL, sep));
	}
	return a;
}

int calculeazaInaltimeArbore(Nod* rad) {
	if (rad) {
		int Hs = calculeazaInaltimeArbore(rad->st);
		int Hd = calculeazaInaltimeArbore(rad->dr);
		return 1 + (Hs > Hd ? Hs : Hd);
	}
	else {
		return 0;
	}
}



void inserareAvionInArbore(Nod** radacina, Avion aNou) {
	if (*radacina) {
		if (aNou.nrLocuri < (*radacina)->info.nrLocuri) {
			inserareAvionInArbore(&(*radacina)->st, aNou);
		}
		else {
			inserareAvionInArbore(&(*radacina)->dr, aNou);
		}

	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->st = NULL;
		nou->dr = NULL;
		nou->info = aNou;
		nou->info.model = (char*)malloc(sizeof(char) * (strlen(aNou.model) + 1));
		strcpy(nou->info.model, aNou.model);
		nou->info.preturiBilete = (float*)malloc(sizeof(float) * aNou.nrLocuriOcupate);
		for (int i = 0; i < aNou.nrLocuriOcupate; i++) {
			nou->info.preturiBilete[i] = aNou.preturiBilete[i];
		}
		(*radacina) = nou;
	}
}

Nod* citireArboreDeAvioaneDinFisier(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	Nod* nou = NULL;
	if (file) {
		while (!feof(file)) {
			Avion avionNou = citesteAvionDinFisier(file);
			inserareAvionInArbore(&nou, avionNou);
		}
	}
	
	fclose(file);

	return nou;
}

void afisareAvioaneInOrdine(Nod* radacina) {
	if (radacina) {
		afisareAvioaneInOrdine(radacina->st);
		afisareAvion(radacina->info);
		afisareAvioaneInOrdine(radacina->dr);
	}
}



int main() {

	/*float preturiBilete[] = { 10, 20, 30 };
	Avion avion = initAvion("A330", 300, 3, preturiBilete);*/

	//afisareAvion(avion);


	//FILE* file = fopen("avioane.txt", "r");
	//while (!feof(file)) {
	//	afisareAvion(citesteAvionDinFisier(file));
	//}
	 //fclose(file);

	Nod* radacina = citireArboreDeAvioaneDinFisier("avioane.txt");
	afisareAvioaneInOrdine(radacina);

	return 0;
}