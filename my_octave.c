// Copyright Andrei Maruntis 313CA

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MOD 10007
// functie care implementeaza aritmetica modulo 10007
// si asigura ca rezultatul este pozitiv
int modulo(int x)
{
	int rest = x % MOD;
	if (rest < 0)
		return rest + MOD;
	return rest;
}

// Observatii generale:
// - mereu cand trimit o variabila prin referinta, numele ei din functie
// va avea numele p_{nume} pentru a indica ca este un pointer catre
// variabila initiala
// - acolo unde nu este nevoie modificarea valorilor, transmitprin valoare
// si nu modific numele variabilei
// - acolo unde este cazul, in loc sa trimit intreg vectorul de matrici ca
// parametru, trimit o singura matrice etc.

// functie aloca memorie pentru o matrice, ii citeste elementele de la
// tastatura si returneaza un pointer catre matrice
int **citire_matrice(int *p_nr_linii, int *p_nr_coloane)
{
	int **matrice;
	scanf("%d %d", p_nr_linii, p_nr_coloane);
	int **aux2 = (int **)malloc(*p_nr_linii * sizeof(int *));
	if (aux2) {
		matrice = aux2;
	} else {
		fprintf(stderr, "Nu s-a putut aloca memorie");
		exit(-1);
	}
	int *aux1;
	for (int i = 0; i < *p_nr_linii; i++) {
		aux1 = (int *)malloc(*p_nr_coloane * sizeof(int));
		if (aux1) {
			matrice[i] = aux1;
		} else {
			fprintf(stderr, "Nu s-a putut aloca memorie");
			for (int k = 0; k < i; k++)
				free(matrice[k]);
			free(matrice);
			exit(-1);
		}
	}
	for (int i = 0; i < *p_nr_linii; i++)
		for (int j = 0; j < *p_nr_coloane; j++)
			scanf("%d", &matrice[i][j]);

	return matrice;
}

// functie care se apeleaza la citirea L care aloca memorie in vectorul de
// matrice pentru matricea care va fi returnata mai sus
// PROGRAMARE DEFENSIVA
// verific mai intai daca s-a alocat cu succes memoria
// daca da, aloc memoria in variabila destinatie
// altfel, dezaloc toata memoria alocata pana atunci in functie,
// afisez un mesaj de eroare si ies din functie
void generare_matrice(int *p_nr_matrici, int ****p_vector_matrici,
					  int **p_v_nr_linii, int **p_v_nr_coloane)
{
	int ***aux3;
	int **aux2;
	int *aux1l, *aux1c;
	if (*p_nr_matrici == 0) {
		aux3 = (int ***)malloc(sizeof(int **));
		if (aux3) {
			*p_vector_matrici = aux3;
		} else {
			fprintf(stderr, "Nu s-a putut aloca memorie");
			exit(-1);
		}
		aux1l = (int *)malloc(sizeof(int));
		if (aux1l) {
			*p_v_nr_linii  = aux1l;
		} else {
			fprintf(stderr, "Nu s-a putut aloca memorie");
			free(*p_vector_matrici);
			exit(-1);
		}
		aux1c = (int *)malloc(sizeof(int));
		if (aux1c) {
			*p_v_nr_coloane  = aux1c;
		} else {
			fprintf(stderr, "Nu s-a putut aloca memorie");
			free(*p_vector_matrici);
			free(*p_v_nr_linii);
			exit(-1);
		}
	} else {
		aux3 = (int ***)realloc(*p_vector_matrici,
								(*p_nr_matrici + 1) * sizeof(int **));
		aux1l = (int *)realloc(*p_v_nr_linii,
							   (*p_nr_matrici + 1) * sizeof(int));
		aux1c = (int *)realloc(*p_v_nr_coloane,
							   (*p_nr_matrici + 1) * sizeof(int));
		//aici este nevoie de aceasta structura nested pentru a nu pierde zona
		//de memorie alocata initial
		//spre exemplu, daca dau realloc (pentru +1 termeni) si operatia se e
		//fectueaza cu succes, dar esueaza o alta operatie in functie, pentru a
		//nu pierde datele alocate initial ar trebui sa fac un realloc
		//(pentru -1 termeni), ceea ce ar putea esua
		//astfel, aloc la final toate 3 valorile daca s-au executat cu succes
		//toate reallocurile
		if (aux3) {
			if (aux1l) {
				if (aux1c) {
					*p_vector_matrici = aux3;
					*p_v_nr_linii = aux1l;
					*p_v_nr_coloane = aux1c;
				} else {
					free(aux3);
					free(aux1l);
					fprintf(stderr, "Nu s-a putut aloca memorie");
					exit(-1);
				}
			} else {
				free(aux3);
				fprintf(stderr, "Nu s-a putut aloca memorie");
				exit(-1);
			}
		} else {
			fprintf(stderr, "Nu s-a putut aloca memorie");
			exit(-1);
		}
	}

	aux2 = citire_matrice(&(*p_v_nr_linii)[*p_nr_matrici],
						  &(*p_v_nr_coloane)[*p_nr_matrici]);
	if (aux2) {
		(*p_vector_matrici)[*p_nr_matrici] = aux2;
		(*p_nr_matrici)++;
	} else {
		free(aux3);
		free(aux1l);
		free(aux1c);
	}
}

// functie care se apeleaza la citirea P ce returneaza nr de linii si
// de coloane a unei matrici
void afisare_dimensiuni(int nr_matrici, int v_nr_linii[], int v_nr_coloane[])
{
	int index;
	scanf("%d", &index);
	if (index >= nr_matrici || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	printf("%d %d\n", v_nr_linii[index], v_nr_coloane[index]);
}

//functie care se apeleaza la citirea D ce afiseaza elementele unei matrici
void afisare_matrice(int nr_matrici, int ***vector_matrici,
					 int v_nr_linii[], int v_nr_coloane[])
{
	int index;
	scanf("%d", &index);
	if (index >= nr_matrici || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	for (int i = 0; i < v_nr_linii[index]; i++) {
		for (int j = 0; j < v_nr_coloane[index]; j++)
			printf("%d ", vector_matrici[index][i][j]);
		printf("\n");
	}
}

// functie care citeste de la tastatura liniile si coloanele care trebuie
// pastrate, aloca spatiu pentru noua matrice si elibereaza matricea veche
void trunchiere_matrice(int ***p_matrice_init,
						int *p_nr_linii, int *p_nr_coloane)
{
	int **aux2;
	int *aux1;
	int nr_linii_aux, nr_coloane_aux;
	int **matrice_aux;
	int *linii_dc, *coloane_dc;
	scanf("%d", &nr_linii_aux);
	aux1 = (int *)malloc(nr_linii_aux * sizeof(int));
	if (aux1) {
		linii_dc = aux1;
	} else {
		fprintf(stderr, "Nu s-a putut aloca memorie");
		exit(-1);
	}
	for (int i = 0; i < nr_linii_aux; i++)
		scanf("%d", &linii_dc[i]);
	scanf("%d", &nr_coloane_aux);
	aux1 = (int *)malloc(nr_coloane_aux * sizeof(int));
	if (aux1) {
		coloane_dc = aux1;
	} else {
		fprintf(stderr, "Nu s-a putut aloca memorie");
		free(linii_dc);
		exit(-1);
	}
	for (int i = 0; i < nr_coloane_aux; i++)
		scanf("%d", &coloane_dc[i]);

	aux2 = (int **)malloc(nr_linii_aux * sizeof(int *));
	if (aux2) {
		matrice_aux = aux2;
	} else {
		fprintf(stderr, "Nu s-a putut aloca memorie");
		free(linii_dc);
		free(coloane_dc);
		exit(-1);
	}
	for (int i = 0; i < nr_linii_aux; i++) {
		aux1 = (int *)malloc(nr_coloane_aux * sizeof(int));
		if (aux1) {
			matrice_aux[i] = aux1;
		} else {
			fprintf(stderr, "Nu s-a putut aloca memorie");
			for (int k = 0; k < i; k++)
				free(matrice_aux[k]);
			free(matrice_aux);
			free(linii_dc);
			free(coloane_dc);
			exit(-1);
		}
	}

	for (int  i = 0; i < nr_linii_aux; i++)
		for (int j = 0; j < nr_coloane_aux; j++)
			matrice_aux[i][j] = (*p_matrice_init)[linii_dc[i]][coloane_dc[j]];
	for (int i = 0; i < *p_nr_linii; i++)
		free((*p_matrice_init)[i]);
	free(*p_matrice_init);
	*p_matrice_init = matrice_aux;
	*p_nr_linii = nr_linii_aux;
	*p_nr_coloane = nr_coloane_aux;
	free(linii_dc);
	free(coloane_dc);
}

// functie care se apeleaza la citirea C care apoi apeleaza functia de mai sus
// pentru a trunchia matricea; de fapt functia doar verifica ca indicele
// este valid
void redimensionare_matrice(int nr_matrici, int ****p_vector_matrici,
							int **p_v_nr_linii, int **p_v_nr_coloane)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_matrici || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	trunchiere_matrice(&(*p_vector_matrici)[index],
					   &(*p_v_nr_linii)[index], &(*p_v_nr_coloane)[index]);
}

// functie care se apeleaza la citirea M si inmulteste doua matrice cu metoda
// clasica (P[i][j]=suma(A[i][k]*B[k][j])) si aloca memorie pentru adaugarea
// ei la finalul vectorului de matrici
void inmultire_matrice(int *p_nr_matrici, int ****p_vector_matrici,
					   int **p_v_nr_linii, int **p_v_nr_coloane)
{
	long produs;
	int index1, index2, suma;
	scanf("%d %d", &index1, &index2);
	if (index1 >= *p_nr_matrici) {
		printf("No matrix with the given index\n");
		return;
	}
	if (index2 >= *p_nr_matrici) {
		printf("No matrix with the given index\n");
		return;
	}
	if ((*p_v_nr_coloane)[index1] != (*p_v_nr_linii)[index2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	int **mat_produs;
	mat_produs = (int **)malloc((*p_v_nr_linii)[index1] * sizeof(int *));
	for (int i = 0; i < (*p_v_nr_linii)[index1]; i++)
		mat_produs[i] = (int *)malloc((*p_v_nr_coloane)[index2] * sizeof(int));
	for (int i = 0; i < (*p_v_nr_linii)[index1]; i++) {
		for (int j = 0; j < (*p_v_nr_coloane)[index2]; j++) {
			suma = 0;
			for (int k = 0; k < (*p_v_nr_coloane)[index1]; k++) {
				produs = modulo((long)(*p_vector_matrici)[index1][i][k]) *
					modulo((*p_vector_matrici)[index2][k][j]);
				suma = modulo(modulo(suma) + modulo(produs));
			}
			mat_produs[i][j] = suma;
		}
	}

	*p_vector_matrici = (int ***)realloc(*p_vector_matrici,
										 (*p_nr_matrici + 1) * sizeof(int **));
	*p_v_nr_linii =
		(int *)realloc(*p_v_nr_linii, (*p_nr_matrici + 1) * sizeof(int));
	*p_v_nr_coloane =
		(int *)realloc(*p_v_nr_coloane, (*p_nr_matrici + 1) * sizeof(int));
	(*p_vector_matrici)[*p_nr_matrici] = mat_produs;
	(*p_v_nr_linii)[*p_nr_matrici] = (*p_v_nr_linii)[index1];
	(*p_v_nr_coloane)[*p_nr_matrici] = (*p_v_nr_coloane)[index2];
	(*p_nr_matrici)++;
}

// functie auxiliara pentru sortarea matricilor, care calculeaza suma
// elementelor dintr-o matrice primita ca parametru
int suma_elemente(int **mat, int nr_linii, int nr_coloane)
{
	int suma = 0;
	for (int i = 0 ; i < nr_linii; i++)
		for (int j = 0; j < nr_coloane; j++)
			suma = modulo(modulo(suma) + modulo(mat[i][j]));
	return suma;
}

//functii auxiliare care inverseaza doua valori
void swap_mat(int ***p_mat1, int ***p_mat2)
{
	int **aux;
	aux = *p_mat1;
	*p_mat1 = *p_mat2;
	*p_mat2 = aux;
}

void swap_int(int *x1, int *x2)
{
	int aux;
	aux = *x1;
	*x1 = *x2;
	*x2 = aux;
}

// functia care se apeleaza la citirea O ce utilizeaza cele 3 functii de mai
// sus si sorteaza vectorul de matrici, respectivi vectorii de dimensiuni
// folosind metoda insert sort
void sortare_matrice(int nr_matrici, int ****p_vector_matrici,
					 int **p_v_nr_linii, int **p_v_nr_coloane)
{
	int *v_sume;
	v_sume = malloc(nr_matrici * sizeof(int));
	for (int i = 0; i < nr_matrici; i++)
		v_sume[i] = suma_elemente((*p_vector_matrici)[i], (*p_v_nr_linii)[i],
								  (*p_v_nr_coloane)[i]);
	for (int i = 0; i < nr_matrici - 1; i++) {
		for (int j = i + 1; j < nr_matrici; j++) {
			if (v_sume[i] > v_sume[j]) {
				swap_mat(&(*p_vector_matrici)[i], &(*p_vector_matrici)[j]);
				swap_int(&(*p_v_nr_linii)[i], &(*p_v_nr_linii)[j]);
				swap_int(&(*p_v_nr_coloane)[i], &(*p_v_nr_coloane)[j]);
				swap_int(&v_sume[i], &v_sume[j]);
			}
		}
	}
	free(v_sume);
}

// functie care se apeleaza la citirea T care calculeaza transpusa unei
// matrice intr-o matrice auxiliara pentru care se aloca mai intai memorie,
// apoi se inlocuieste matricea din vector cu cea noua si se elibereaza
// memoria alocata matricei vechi
void transpunere_matrice(int nr_matrici, int ****p_vector_matrici,
						 int **p_v_nr_linii, int **p_v_nr_coloane)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_matrici || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	int **mat_transpus;
	mat_transpus = (int **)malloc((*p_v_nr_coloane)[index] * sizeof(int *));
	for (int i = 0; i < (*p_v_nr_coloane)[index]; i++)
		mat_transpus[i] = (int *)malloc((*p_v_nr_linii)[index] * sizeof(int));

	for (int i = 0; i < (*p_v_nr_linii)[index]; i++)
		for (int j = 0; j < (*p_v_nr_coloane)[index]; j++)
			mat_transpus[j][i] = (*p_vector_matrici)[index][i][j];

	for (int i = 0 ; i < (*p_v_nr_linii)[index]; i++)
		free((*p_vector_matrici)[index][i]);
	free((*p_vector_matrici)[index]);
	(*p_vector_matrici)[index] = mat_transpus;
	swap_int(&(*p_v_nr_linii)[index], &(*p_v_nr_coloane)[index]);
}

// functie care se apeleaza la citirea F ce elibereaza memoria alocata unei
// matrici si deplaseaza toate elementele de dupa o pozitie spre stanga
void eliberare_matrice(int *p_nr_matrici, int ****p_vector_matrici,
					   int **p_v_nr_linii, int **p_v_nr_coloane)
{
	int index;
	scanf("%d", &index);
	if (index >= *p_nr_matrici || index < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	for (int i = 0 ; i < (*p_v_nr_linii)[index]; i++)
		free((*p_vector_matrici)[index][i]);
	free((*p_vector_matrici)[index]);
	for (int i = index; i < *p_nr_matrici - 1; i++) {
		(*p_vector_matrici)[i] = (*p_vector_matrici)[i + 1];
		(*p_v_nr_linii)[i] = (*p_v_nr_linii)[i + 1];
		(*p_v_nr_coloane)[i] = (*p_v_nr_coloane)[i + 1];
	}

	*p_vector_matrici = (int ***)realloc(*p_vector_matrici,
										 (*p_nr_matrici - 1) * sizeof(int **));
	*p_v_nr_linii =
		(int *)realloc(*p_v_nr_linii, (*p_nr_matrici - 1) * sizeof(int));
	*p_v_nr_coloane =
		(int *)realloc(*p_v_nr_coloane, (*p_nr_matrici - 1) * sizeof(int));
	(*p_nr_matrici)--;
}

//functie care se apeleaza la cititrea Q ce elibereaza toate resursele
void eliberare_total(int *p_nr_matrici, int ****p_vector_matrici,
					 int **p_v_nr_linii, int **p_v_nr_coloane)
{
	if (*p_nr_matrici == 0)
		return;
	//eliberez pe rand fiecare coloana de pe fiecare linie din fiecare matrice,
	//apoi liniile din fiecare matrice si intr-un final vectrul de matrice
	for (int k = 0; k < *p_nr_matrici; k++) {
		for (int i = 0 ; i < (*p_v_nr_linii)[k]; i++)
			free((*p_vector_matrici)[k][i]);
		free((*p_vector_matrici)[k]);
	}
	free(*p_vector_matrici);
	free(*p_v_nr_linii);
	free(*p_v_nr_coloane);
	*p_nr_matrici = 0;
}

int main(void)
{
	int nr_matrici = 0;
	int ***vector_matrici;
	int *v_nr_linii, *v_nr_coloane;
	char input;

	scanf("%c", &input);
	// continui sa citesc input pana cand primesc litera Q; ignor caracterele
	// care nu sunt litere
	while (input != 'Q') {
		switch (input) {
		case 'L':
			generare_matrice(&nr_matrici, &vector_matrici,
							 &v_nr_linii, &v_nr_coloane);
			break;
		case 'D':
			afisare_dimensiuni(nr_matrici, v_nr_linii, v_nr_coloane);
			break;
		case 'P':
			afisare_matrice(nr_matrici, vector_matrici,
							v_nr_linii, v_nr_coloane);
			break;
		case 'C':
			redimensionare_matrice(nr_matrici, &vector_matrici,
								   &v_nr_linii, &v_nr_coloane);
			break;
		case 'M':
			inmultire_matrice(&nr_matrici, &vector_matrici,
							  &v_nr_linii, &v_nr_coloane);
			break;
		case 'O':
			sortare_matrice(nr_matrici, &vector_matrici,
							&v_nr_linii, &v_nr_coloane);
			break;
		case 'T':
			transpunere_matrice(nr_matrici, &vector_matrici,
								&v_nr_linii, &v_nr_coloane);
			break;
		case 'F':
			eliberare_matrice(&nr_matrici, &vector_matrici,
							  &v_nr_linii, &v_nr_coloane);
			break;
		default:
			printf("Unrecognized command\n");
			break;
		}
		scanf("%c", &input);
		while (!isalpha(input))
			scanf("%c", &input);
	}

	eliberare_total(&nr_matrici, &vector_matrici, &v_nr_linii, &v_nr_coloane);

	return 0;
}
