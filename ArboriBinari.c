#include <stdio.h>
#include<malloc.h>

struct Avion {
	char* model;
	int nrLocuri;
	int nrLocuriOcupate;
	float* preturiBilete;
};
typedef struct Avion Avion;

Avion initAvion(const char* model, int nrLocuri, int nrLocuriOcupate, float* preturiBilete) {
	Avion avion;
	avion.model = (char*)malloc(sizeof(char) * strlen(model) + 1);
	strcpy(avion.model, model);
	avion.nrLocuri = nrLocuri;
	avion.nrLocuriOcupate = nrLocuriOcupate;
	avion.preturiBilete = (float*)malloc(sizeof(float));
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

void main() {

	float preturiBilete[] = { 10, 20, 30 };

	Avion avion = initAvion("A330", 300, 3, preturiBilete);

	afisareAvion(avion);

	return 0;
}