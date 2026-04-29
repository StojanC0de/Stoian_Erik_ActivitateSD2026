#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct NodArbore NodArbore;
struct NodArbore {
	Masina info;
	NodArbore* left;
	NodArbore* right;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


void adaugaMasinaInArbore(NodArbore** root, Masina masinaNoua) {
	if (*root) {
		if ((*root)->info.id > masinaNoua.id) {
			adaugaMasinaInArbore(&(*root)->left, masinaNoua);
		}
		else {
			adaugaMasinaInArbore(&(*root)->right, masinaNoua);
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
		nou->info = masinaNoua;
		nou->left = NULL;
		nou->right = NULL;
		*root = nou;
	}
}

NodArbore* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	NodArbore* root = NULL;
	if (f) {
		while (!feof(f)) {
			Masina m = citireMasinaDinFisier(f);
			adaugaMasinaInArbore(&root, m);
		}
	}
	fclose(f);
	return root;
}

void afisareMasiniDinArbore(NodArbore* root) {
	if (root) {
		afisareMasina(root->info);
		afisareMasiniDinArbore(root->left);
		afisareMasiniDinArbore(root->right);
	}
}

void afisareInOrdine(NodArbore* root) {
	if (root != NULL) {
		afisareInOrdine(root->left);
		afisareMasina(root->info);
		afisareInOrdine(root->right);
	}
}

void dezalocareArboreDeMasini(NodArbore** root) {
	if (*root) {
		dezalocareArboreDeMasini(&(*root)->left);
		dezalocareArboreDeMasini(&(*root)->right);
		free((*root)->info.model);
		free((*root)->info.numeSofer);
		free((*root));
		*root = NULL;
	}
}

Masina getMasinaByID(NodArbore* root, int id) {
	if (!root) {
		Masina m;
		m.id = -1;
		return m;
	}
	else if (id < root->info.id) {
		return getMasinaByID(root->left, id);
	}
	else if (id > root->info.id) {
		return getMasinaByID(root->right, id);
	}
	else {
		Masina m = root->info;
		m.model = malloc(strlen(root->info.model) + 1);
		strcpy(m.model, root->info.model);
		m.numeSofer = malloc(strlen(root->info.numeSofer) + 1);
		strcpy(m.numeSofer, root->info.numeSofer);
		return m;
	}
}

int determinaNumarNoduri(NodArbore* root) {
	if (root) 
		return 1 + determinaNumarNoduri(root->left) + determinaNumarNoduri(root->right);
	else
		return 0;
}

int calculeazaInaltimeArbore(NodArbore* root) {
	if (root) {
		return 1 + max(calculeazaInaltimeArbore(root->left), calculeazaInaltimeArbore(root->right));
	}
	return 0;
}

float calculeazaPretTotal(NodArbore* root) {
	if (root) {
		return root->info.pret + calculeazaPretTotal(root->left) + calculeazaPretTotal(root->right);
	}
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(NodArbore* root, const char* numeSofer) {
	if (root) {
		if (strcmp(root->info.numeSofer, numeSofer) == 0)
			return root->info.pret + calculeazaPretulMasinilorUnuiSofer(root->left, numeSofer) + calculeazaPretulMasinilorUnuiSofer(root->right, numeSofer);
		else {
			return calculeazaPretulMasinilorUnuiSofer(root->left, numeSofer)+calculeazaPretulMasinilorUnuiSofer(root->right, numeSofer);
		}
	}
	return 0;
}

int main() {
	NodArbore* root = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareInOrdine(root);
	printf("Masina cu id-ul 5: \n");
	afisareMasina(getMasinaByID(root, 5));
	printf("Numarul de noduri: %d\n", determinaNumarNoduri(root));
	printf("Inaltimea arborelui: %d\n", calculeazaInaltimeArbore(root));
	printf("Pretul total: %.2f\n", calculeazaPretTotal(root));
	printf("Pretul total al masinilor lui Ionescu: %.2f\n", calculeazaPretulMasinilorUnuiSofer(root, "Ionescu"));
	return 0;
}