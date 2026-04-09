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
//
//typedef struct Nod Nod;
//struct Nod {
//	Masina masina;
//	Nod* next;
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
////STACK
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector
//void pushStack(Nod** stiva, Masina masina) {
//	Nod* temp = (Nod*)malloc(sizeof(Nod));
//	temp->masina = masina;
//	temp->next = (*stiva);
//	(*stiva) = temp;
//}
//
//Masina popStack(Nod** stiva) {
//	if ((*stiva) == NULL) {
//		Masina rezultat;
//		rezultat.id = -1;
//		return rezultat;
//	}
//	Masina rezultat = (*stiva)->masina;
//	Nod* temp = (*stiva)->next;
//	free(*stiva);
//	*stiva = temp;
//	return rezultat;
//
//}
//
//char isEmptyStack(Nod* stiva) {
//	return stiva == NULL;
//}
//
//void* citireStackMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	if (!file) {
//		return NULL;
//	}
//	Nod* stiva = NULL;
//	while (!feof(file)) {
//		Masina masina = citireMasinaDinFisier(file);
//		pushStack(&stiva, masina);
//	}
//	fclose(file);
//	return stiva;
//}
//
//void dezalocareStivaDeMasini(/*stiva*/) {
//	//sunt dezalocate toate masinile si stiva de elemente
//}
//
//int size(/*stiva*/) {
//	//returneaza numarul de elemente din stiva
//}
//
//typedef NodDublu NodDublu;
//struct NodDublu {
//	Masina info;
//	NodDublu* next;
//	NodDublu* prev;
//};
//
//typedef ListaDubla;
//struct ListaDubla {
//	NodDublu* first;
//	NodDublu* last;
//};
////QUEUE
////Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
////putem reprezenta o coada prin LSI, LDI sau vector
//void enqueue(ListaDubla* coada, Masina masina) {
//	NodDublu* NodNou = (NodDublu*)malloc(sizeof(NodDublu));
//	NodNou->info = masina;
//	NodNou->next = NULL;
//	NodNou->prev = coada->last;
//	if (coada->last) {
//		coada->last->next = NodNou;
//	}
//	else {
//		coada->first = NodNou;
//	}
//	coada->last = NodNou;
//}
//
//Masina dequeue(ListaDubla* coada) {
//	Masina rezultat;
//	rezultat.id = -1;
//	if (coada->first) {
//		rezultat = coada->first->info;
//		NodDublu* temp = coada->first;
//		coada->first = temp->next;
//		free(temp);
//	}
//	return rezultat;
//}
//
//ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//	ListaDubla coada;
//	coada.first = coada.last = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	if (f) {
//		while (!feof(f)) {
//			enqueue(&coada, citireMasinaDinFisier(f));
//		}
//		fclose(f);
//	}
//	return coada;
//}
//
//void dezalocareCoadaDeMasini(/*coada*/) {
//	//sunt dezalocate toate masinile si coada de elemente
//}
//
//
////metode de procesare
//Masina getMasinaByID(Nod** stiva, int id) {
//	Masina rezultat;
//	if ((*stiva) == NULL) {
//		Masina rezultat;
//		rezultat.id = -1;
//		return rezultat;
//	}
//	Nod* stivaNoua = NULL;
//	while ((*stiva)) {
//		Masina masinaNoua = popStack(stiva);
//		if (masinaNoua.id == id) {
//			rezultat = masinaNoua;
//			break;
//		}
//		else {
//			pushStack(&stivaNoua, masinaNoua);
//		}
//	}
//	while (stivaNoua) {
//		pushStack(stiva, popStack(&stivaNoua));
//	}
//	return rezultat;
//}
//
//float calculeazaPretTotal(/*stiva sau coada de masini*/);
//
//int main() {
//	Nod* stiva = citireStackMasiniDinFisier("masini.txt");
//	afisareMasina(popStack(&stiva));
//	afisareMasina(popStack(&stiva));
//
//	afisareMasina(getMasinaByID(&stiva, 4));
//
//	printf("COADA---------------------------------------\n");
//	ListaDubla coada = citireCoadaDeMasiniDinFisier("masini.txt");
//	afisareMasina(dequeue(&coada));
//	afisareMasina(dequeue(&coada));
//	return 0;
//}