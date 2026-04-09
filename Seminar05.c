//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
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
//typedef struct Nod Nod;
//typedef struct ListaDubla ListaDubla;
//
//struct Nod {
//	Masina info;
//	Nod* next;
//	Nod* prev;
//};
//
//struct ListaDubla {
//	Nod* first;
//	Nod* last;
//};
//
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
//void afisareListaMasini(ListaDubla lista) {
//	Nod* p = lista.first;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->next;
//	}
//}
//
//void afisareInversa(ListaDubla lista) {
//	Nod* p = lista.last;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->prev;
//	}
//}
//
//void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	nou->prev = lista->last;
//	if (lista->last) {
//		lista->last->next = nou;
//	}
//	else {
//		lista->first = nou;
//	}
//	lista->last = nou;
//}
//
//void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	nou->prev = lista->first;
//	if (lista->first) {
//		lista->first->prev = nou;
//	}
//	else {
//		lista->last = nou;
//	}
//	lista->first = nou;
//}
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	if (f) {
//		ListaDubla lista;
//		lista.first = lista.last = NULL;
//		while (!feof(f)) {
//			adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
//		}
//		fclose(f);
//		return lista;
//	}
//}
//
//void dezalocareLDMasini(ListaDubla* lista) {
//	while (lista->first && lista->first->next) {
//		free(lista->first->info.numeSofer);
//		free(lista->first->info.model);
//		lista->first = lista->first->next;
//		free(lista->first->prev);
//	}
//	if (lista->first) {
//		free(lista->first->info.numeSofer);
//		free(lista->first->info.model);
//		free(lista->first);
//	}
//	lista->first = lista->last = NULL;
//}
//
//float calculeazaPretMediu(ListaDubla lista) {
//	if (lista.first == NULL)
//		return 0;
//	float sumaPret = 0;
//	int nrMasini = 0;
//	while (lista.first) {
//		sumaPret += lista.first->info.pret;
//		nrMasini++;
//		lista.first = lista.first->next;
//	}
//	return sumaPret / nrMasini;
//}
//
//void stergeMasinaDupaID(ListaDubla* ld, int id) {
//	//sterge masina cu id-ul firstit.
//	//tratati situatia ca masina se afla si pe firsta pozitie, si pe lasta pozitie
//	if (ld->first && ld->first->info.id == id) {
//		free(ld->first->info.model);
//		free(ld->first->info.numeSofer);
//		ld->first = ld->first->next;
//		if (ld->first)
//		{
//			free(ld->first->prev);
//		}
//		else
//		{
//			free(ld->last);
//			ld->last = NULL;
//		}
//		return;
//	}
//	else {
//		Nod* p = ld->first;
//		while (p && p->info.id != id) {
//			p = p->next;
//		}
//		if (p)
//		{
//			if (p->prev) {
//				p->prev->next = p->next;
//			}
//			if (p->next)
//			{
//				p->next->prev = p->prev;
//			}
//			else {
//				p->prev->next = NULL;
//				ld->last = p->prev;
//			}
//			free(p->info.model);
//			free(p->info.numeSofer);
//			free(p);
//		}
//	}
//
//}
//
//char* getNumeSoferMasinaScumpa(ListaDubla lista) {
//	float maxPret = 0;
//	char* numeSoferMax = NULL;
//	if (lista.first == NULL)
//		return 0;
//	while (lista.first) {
//		if (lista.first->info.pret > maxPret) {
//			maxPret = lista.first->info.pret;
//			if (numeSoferMax != NULL)
//				free(numeSoferMax);
//			numeSoferMax = (char*)malloc(strlen(lista.first->info.numeSofer) + 1);
//			if(numeSoferMax!=NULL)
//				strcpy(numeSoferMax,lista.first->info.numeSofer);
//			
//		}
//		lista.first = lista.first->next;
//	}
//	return numeSoferMax;
//}
//
//int main() {
//	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	printf("Pretul mediu al masinilor este: %f", calculeazaPretMediu(lista));
//	printf("\n Soferul cu masina cea mai scumpa este: %s\n", getNumeSoferMasinaScumpa(lista));
//	stergeMasinaDupaID(&lista, 10);
//	afisareListaMasini(lista);
//	return 0;
//}