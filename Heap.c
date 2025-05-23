#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
	int id;
	char* titlu;
	int nrEditii;
};
typedef struct StructuraCarte Carte;

struct Heap {
	int lungime;
	Carte* vector;
	int nrCarti;
};
typedef struct Heap Heap;

void afiseazaCarte(Carte c) {
	printf("ID: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Numar editii: %d\n", c.nrEditii);
}

Carte citesteCarteDinFisier(FILE* f) {
	Carte c;
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

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrCarti = 0;
	heap.vector = (Carte*)malloc(sizeof(Carte) * lungime);

	return heap;
}

// fiuStanga = 2*pozitieNod+1
// fiuDreapta = 2*pozitieNod+2

void filtreazaHeap(Heap heap, int pozitieNod) {
	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (pozFiuSt < heap.nrCarti && heap.vector[pozMax].id < heap.vector[pozFiuSt].id) {
		pozMax = pozFiuSt;
	}
	if (pozFiuDr < heap.nrCarti && heap.vector[pozMax].id < heap.vector[pozFiuDr].id) {
		pozMax = pozFiuDr;
	}
	if (pozMax != pozitieNod) {
		Carte aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;
		//if(2*pozMax+1 <= heap.nrCarti-1)
		if (pozMax <= (heap.nrCarti - 2) / 2) {
			filtreazaHeap(heap, pozMax);
		}
	}
}

Heap citireHeapDeCartiDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	while (!feof(file)) {
		heap.vector[heap.nrCarti] = citesteCarteDinFisier(file);
		heap.nrCarti++;
	}
	fclose(file);

	for (int i = (heap.nrCarti - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}



int main() {

	for (int i = 0; i < 10; i++) {
		afiseazaCarte(citireHeapDeCartiDinFisier("carti_arbore.txt").vector[i]);
	}

	//citireHeapDeCartiDinFisier("carti_arbore.txt");

	return 0;
}