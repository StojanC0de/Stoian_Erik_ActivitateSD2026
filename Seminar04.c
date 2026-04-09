//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
////creare structura pentru un nod dintr-o lista simplu inlantuita
//struct Nod {
//	Masina info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* first) {
//	//afiseaza toate elemente de tip masina din lista simplu inlantuita
//	//prin apelarea functiei afisareMasina()
//	while (first) {
//		afisareMasina(first->info);
//		first = first->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod** first, Masina masinaNoua) {
//	//adauga la final in lista primita o noua masina pe care o primim ca parametru
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	if (!(*first)) {
//		*first = nou;
//	}
//	else {
//		Nod* pointer = *first;
//		while (pointer->next) {
//			pointer = pointer->next;
//		}
//		pointer->next = nou;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** first, Masina masinaNoua) {
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = *first;
//	*first = nou;
//}
//
//void* citireListaMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* first = NULL;
//	while (!feof(file)) {
//		adaugaMasinaInLista(&first, citireMasinaDinFisier(file));
//	}
//	fclose(file);
//	return first;
//}
//
//void dezalocareListaMasini(Nod** first) {
//	while (*first) {
//		free((*first)->info.numeSofer);
//		free((*first)->info.model);
//		Nod* temp = *first;
//		temp = (*first)->next;
//		free(*first);
//		*first = temp;
//	}
//
//}
//
//float calculeazaPretMediu(Nod* first) { 
//	if (first == NULL) 
//		return 0; 
//
//	float sumaPret = 0;
//	int nrMasini = 0;
//
//	while (first != NULL) {
//		sumaPret += first->info.pret;
//		nrMasini++;
//		first = first->next; 
//	}
//
//	return sumaPret / nrMasini;
//}
//
//void stergeMasiniDinSeria(Nod** first, char serieCautata) {
//	while ((*first) != NULL && (*first)->info.serie == serieCautata) {
//		Nod* aux = *first;
//		*first = (*first)->next;
//		free(aux);
//	}
//
//	Nod* precedent = *first;
//	Nod* actual = (*first)->next;
//	while (actual != NULL) {
//		if (actual->info.serie == serieCautata) {
//			precedent->next = actual->next;
//			free(actual);
//			actual = precedent->next;
//		}
//		else {
//			precedent = actual;
//			actual = actual->next;
//		}
//	}
//}
//
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* first, const char* numeSofer) {
//	float pretTotal = 0;
//	while (first != NULL){
//		if (strcmp(first->info.numeSofer, numeSofer) == 0) {
//			pretTotal += first->info.pret;
//		}
//		first = first->next;
//	}
//	return pretTotal;
//}
//
//int main() {
//	Nod* first = citireListaMasiniDinFisier("masini.txt");
//	Masina masinaNoua = { 11, 2, 50000, "Audi RS7", "Mihai", 'A' };
//	adaugaLaInceputInLista(&first, masinaNoua);
//	afisareListaMasini(first);
//	printf("\nPretul medu al masinilor este: %f", calculeazaPretMediu(first));
//	stergeMasiniDinSeria(&first, 'B');
//	afisareListaMasini(first);
//	char* numeSofer = "Gigel";
//	printf("\n Pretul mediu al soferului %c este: %f", numeSofer, calculeazaPretulMasinilorUnuiSofer(first, numeSofer));
//	return 0;
//}