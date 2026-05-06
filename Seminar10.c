#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare

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

int calculeazaInaltimeArbore(NodArbore* root) {
    if (root) {
        return 1 + max(calculeazaInaltimeArbore(root->left), calculeazaInaltimeArbore(root->right));
    }
    else{
    return 0;
    }
}


//ALTE FUNCTII NECESARE:
// - aici veti adauga noile functii de care aveti nevoie.


char calculGE(NodArbore* root) {
    if(root){
        return calculeazaInaltimeArbore(root->left)-calculeazaInaltimeArbore(root->right);

    }
    else {
        return 0;
    }
}

void rotireStanga(NodArbore** root) {
    NodArbore* aux = (*root)->right;
    (*root)->right = aux->left;
    aux->left = (*root);
    (*root) = aux;
}

void rotireDreapta(NodArbore** root){
    NodArbore* aux = (*root)->left;
    (*root)->left = aux->right;
    aux->right = (*root);
    (*root) = aux;
}

void adaugaMasinaInArboreEchilibrat(NodArbore** root, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
	//dupa o anumita cheie pe care o decideti - poate fi ID
    if ((*root)) {
        if((*root)->info.id > masinaNoua.id) {
            adaugaMasinaInArboreEchilibrat(&(*root)->left, masinaNoua);
        }
        else {
            adaugaMasinaInArboreEchilibrat(&(*root)->right, masinaNoua);
        }
        int grad = calculGE((*root));
        if(grad == 2) {
            if(calculGE((*root)->left) == -1) {
                rotireStanga(&(*root)->left);
                rotireDreapta(&(*root));
            }
            else {
                rotireDreapta(&(*root));
            }
        }
        else if (grad == -2) {
            if(calculGE((*root)->right) == 1) {
                    rotireDreapta(&(*root)->right);
            }
            rotireStanga(root);
        }
    }
    else {
        NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore));
        nou->info = masinaNoua;
        nou->left = NULL;
        nou->right = NULL;
        (*root) = nou;
    }
}

NodArbore* citireArboreDeMasiniDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    NodArbore* root = NULL;
    if (f) {
        while (!feof(f)) {
            Masina masina = citireMasinaDinFisier(f);
            adaugaMasinaInArboreEchilibrat(&root, masina);
        }
        fclose(f);
    }
    return root;
}

void afisarePreordine(NodArbore* root) {
    if (root) {
        afisareMasina(root->info);
        afisarePreordine(root->left);
        afisarePreordine(root->right);
    }
}

void afisareInordine(NodArbore* root) {
    if (root) {
        afisareInordine(root->left);
        afisareMasina(root->info);
        afisareInordine(root->right);
    }
}

void afisarePostordine(NodArbore* root) {
    if (root) {
        afisarePostordine(root->left);
        afisarePostordine(root->right);
        afisareMasina(root->info);
    }
}

void afisareMasiniDinArbore(NodArbore* root) {
    printf("=== Preordine (radacina, stanga, dreapta) ===\n");
    afisarePreordine(root);
    printf("=== Inordine (stanga, radacina, dreapta) ===\n");
    afisareInordine(root);
    printf("=== Postordine (stanga, dreapta, radacina) ===\n");
    afisarePostordine(root);
}

void dezalocareArboreDeMasini(NodArbore** root) {
    if((*root)) {
        dezalocareArboreDeMasini(&(*root)->left);
        dezalocareArboreDeMasini(&(*root)->right);
        free((*root)->info.numeSofer);
        free((*root)->info.model);
        free(*root);
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
    return 0;
}

float calculeazaPretTotal(NodArbore* root) {
    if (root)
        return root->info.pret + calculeazaPretTotal(root->left) + calculeazaPretTotal(root->right);
    return 0;
}

float calculeazaPretulMasinilorUnuiSofer(NodArbore* root, const char* numeSofer)
{
    float sum = 0;
    if (root)
    {
        sum += calculeazaPretulMasinilorUnuiSofer(root->left,numeSofer);
        sum += calculeazaPretulMasinilorUnuiSofer(root->right, numeSofer);
        if (strcmp(root->info.numeSofer, numeSofer) == 0) {
            sum += root->info.pret;
        }
    }
    return sum;
}

int main() {

    NodArbore* root = citireArboreDeMasiniDinFisier("masini.txt");
    afisareMasiniDinArbore(root);

    printf("%f",calculeazaPretulMasinilorUnuiSofer(root, "Ionescu"));
    dezalocareArboreDeMasini(&root);
	return 0;
}