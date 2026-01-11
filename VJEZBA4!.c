#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node* Pozicija;
struct Broj {
	float eksponent;
	float koeficijent;
};
struct Node {
	struct Broj Element;
	Pozicija Next;
};
Pozicija createNode();
int unosP(Pozicija, Pozicija, struct Broj);
int unosK(Pozicija, Pozicija, struct Broj);
int ispis(Pozicija);
int delete(Pozicija, Pozicija);
int postaviIza(Pozicija, Pozicija, struct Broj, int);
int postaviIspred(Pozicija, Pozicija, struct Broj, int);
Pozicija readListFromFile(FILE*);
int sortiraniUnos(Pozicija, Pozicija, struct Broj);
FILE* otvaranjeDatoteke();
int sortirati_polynom(Pozicija*);
int polynom_uredjivanje(Pozicija*);
Pozicija spojiListe(Pozicija*, unsigned short);
Pozicija Calculate(Pozicija*, unsigned short);
int main() {
	short a = 0;

	do
	{
		printf("Unesi broj polinoma nad kojim ce se vrsiti neka operacija: ");
		scanf_s(" %hd", &a);
	} while (a <= 0);

	FILE** files = malloc(sizeof(FILE*) * a);
	Pozicija* heads = malloc(sizeof(struct Node*) * a);

	for (int i = 0; i < a; i++)
	{
		printf("%d ", i + 1);
		files[i] = otvaranjeDatoteke();
		if (files[i] == NULL)
			i--;
	}

	char odabir = '0';
	do
	{
		for (int i = 0; i < a; i++)
		{
			heads[i] = readListFromFile(files[i]);
			if (heads[i] == NULL) {
				printf("Pogreska prilikom citanja liste iz datoteke!");
				return 1;
			}
		}

		printf("\nUnesi znak za trazenu radnju:\n");
		printf("+ ZA ZBRAJANJE POLINOMA\n");
		printf("* ZA MNOZENJE POLINOMA\n");
		printf("X - ZA KRAJ PROGRAMA\n");
		scanf_s(" %c", &odabir);

		switch (odabir)
		{
		case '+': {

			Pozicija joinedListHeader = spojiListe(heads, a);
			if (joinedListHeader == NULL)
				break;
			if (polynom_uredjivanje(&joinedListHeader) == 0) {
				printf("Rezultat zbrajanja je:\t");
				ispis(joinedListHeader);
			}
			izbrisiListu(joinedListHeader);
			free(joinedListHeader);
			printf("\n");
			break;
		}
		case '*': {
			Pozicija outputHeader = Calculate(heads, a);
			if (outputHeader != NULL) {
				ispis(outputHeader);
				izbrisiListu(outputHeader);
				free(outputHeader);
			}
			break;
		}
		default:
			break;
		}

	} while (odabir != 'x');

	for (int i = 0; i < a; i++)
	{
		if (files[i] != NULL)
			fclose(files[i]);
		if (heads[i] != NULL) {
			izbrisiListu(heads[i]);
			free(heads[i]);
		}
	}
	free(files);
	free(heads);
	return 0;

}
Pozicija createNode() {
    Pozicija node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Pogreska, nije moguce alocirati memoriju za cvor!\n");
        return NULL;
    }
    node->Next = NULL;
    return node;
}
int unosP(Pozicija P, Pozicija node, struct Broj number) {
	if (P == NULL || node == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	node->Element = number;
	node->Next = P->Next;
	P->Next = node;
	return 0;
}
int unosK(Pozicija P, Pozicija node, struct Broj number) {
	if (P == NULL || node == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	node->Element = number;
	node->Next = NULL;
	Pozicija q = P;
	while (q->Next != NULL)
		q = q->Next;

	q->Next = node;
	return 0;
}
int ispis(Pozicija P) {
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	Pozicija q = P->Next;
	int i = 1;
	if (q == NULL) {
		printf("Lista je prazna.\n");
		return 2;
	}

	while (q != NULL) {
		if (q->Element.eksponent == 0)
			printf("%.2f ", q->Element.koeficijent);
		else
			printf("%.2fx^%.2f ", q->Element.koeficijent, q->Element.eksponent);
		if (q->Next != NULL)
			printf("+ ");
		q = q->Next;
	}
	return 0;
}
int delete(Pozicija P, Pozicija node) {
	if (P == NULL || node == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	Pozicija q = P;
	while (q->Next != NULL) {
		if (q->Next == node) {
			q->Next = node->Next;
			free(node);
			printf("Element je uspjesno izbrisan iz liste!\n");
			return 0;
		}
		q = q->Next;
	}
	printf("Broj nije pronadjen!\n");
	return 1;
}
int postaviIza(Pozicija P, Pozicija node, struct Broj number, int target) {
	if (P == NULL || node == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	Pozicija temp = P->Next;
	int i = 0;
	while (temp != NULL) {
		if (i == target) {
			node->Element = number;
			node->Next = temp->Next;
			temp->Next = node;
			printf("Broj uspjesno dodan nakon %d. elementa!\n", target);
			return 0;
		}
		temp = temp->Next;
		i++;
	}

	printf("Broj elementa nije pronadjen!\n");
	free(node);
	return 1;
}

int postaviIspred(Pozicija P, Pozicija node, struct Broj number, int target) {
	if (P == NULL || node == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	Pozicija temp = P;
	int i = 0;
	while (temp->Next != NULL) {
		if (i == target) {
			node->Element = number;
			node->Next = temp->Next;
			temp->Next = node;
			printf("Broj uspjesno dodan prije %d. elementa!\n", target);
			return 0;
		}
		temp = temp->Next;
		i++;
	}
	printf("Broj elementa nije pronaden!\n");
	free(node);
	return 1;
}
Pozicija readListFromFile(FILE* fp) {
	if (fp == NULL) {
		printf("Greska: datoteka nije otvorena!\n");
		return NULL;
	}

	Pozicija head = createNode();
	if (head == NULL)
		return NULL;

	int id = 0;
	struct Broj number;
	while (fscanf_s(fp, "%f %f", &number.koeficijent, &number.eksponent) == 2)
	{
		unosK(head, createNode(), number);
	}

	return head;
}
int sortiraniUnos(Pozicija P, Pozicija node, struct Broj number) {
	if (P == NULL || node == NULL)
	{
		printf("Greska pri ucitavanju liste! (Pokazivac NULL)");
		return 1;
	}

	Pozicija q = P;
	while (q->Next != NULL) {
		if (number.eksponent >= q->Next->Element.eksponent)
			break;
		q = q->Next;
	}

	node->Element = number;
	node->Next = q->Next;
	q->Next = node;

	return 0;
}
FILE* otvaranjeDatoteke() {
	FILE* fp = NULL;
	printf("Unesi ime datoteke:\n ");
	char filename[128] = "";
	scanf(" %127s", filename);

	fopen_s(&fp, filename, "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
	}
	return fp;
}
int sortirati_polynom(Pozicija* P) {
	if (P == NULL || *P == NULL)
	{
		printf("Greska pri ucitavanju liste! (Pokazivac NULL)");
		return 1;
	}
	if ((*P)->Next == NULL) {
		printf("Lista je prazna!");
		return 0;
	}

	Pozicija newHead = createNode();
	if (newHead == NULL)
		return 2;

	Pozicija q = (*P)->Next;
	Pozicija node = NULL;
	while (q != NULL)
	{
		node = createNode();
		if (node == NULL)
			return 2;
		if (sortiraniUnos(newHead, node, q->Element) != 0) {
			printf("Greska pri dodavanju elemenata u novu listu!");
			return 3;
		}
		q = q->Next;
	}
	izbrisiListu(*P);
	*P = newHead;
	return 0;
}
int polynom_uredjivanje(Pozicija* P) {
	if (P == NULL || *P == NULL)
	{
		printf("Greska prilikom ucitavanja liste! (Pokazivac NULL)");
		return 1;
	}
	if ((*P)->Next == NULL) {
		printf("Lista je prazna!");
		return 0;
	}
	sortirati_polynom(P);

	Pozicija newHead = createNode();
	if (newHead == NULL)
		return 2;

	Pozicija q = (*P)->Next;

	Pozicija node = NULL;

	struct Broj temp = { q->Element.koeficijent, q->Element.eksponent };

	while (q != NULL)
	{
		if (q->Next != NULL && q->Next->Element.eksponent == q->Element.eksponent)
			temp.koeficijent += q->Next->Element.koeficijent;
		else {
			node = createNode();
			if (node == NULL)
				return 2;
			temp.eksponent = q->Element.eksponent;
			sortiraniUnos(newHead, node, temp);
			if (q->Next != NULL)
				temp.koeficijent = q->Next->Element.koeficijent;
		}
		q = q->Next;
	}

	izbrisiListu(*P);
	*P = newHead;
	return 0;
}
Pozicija spojiListe(Pozicija* heads, unsigned short arr_length) {
	if (heads == NULL)
	{
		printf("Greska pri ucitavanju niza! (Pokazivac NULL)");
		return NULL;
	}
	Pozicija newHead = createNode();
	if (newHead == NULL) {
		printf("Greska pri alokaciji cvora!\n");
		return NULL;
	}
	Pozicija node;
	Pozicija q = NULL;
	for (int i = 0; i < arr_length; i++)
	{
		if (heads[i] == NULL) {
			printf("Greska prilikom ucitavanja jedne liste u nizu! (Pokazivac NULL)");
			free(newHead);
			return NULL;
		}
		q = heads[i]->Next;
		while (q != NULL)
		{
			node = createNode();
			if (node == NULL) {
				printf("Greska pri alokaciji cvora!\n");
				free(newHead);
				return NULL;
			}
			unosP(newHead, node, q->Element);
			q = q->Next;
		}
	}
	return newHead;
}
Pozicija Calculate(Pozicija* heads, unsigned short arr_length) {
	if (heads == NULL)
	{
		printf("Greska pri ucitavanju niza! (Pokazivac NULL)");
		return NULL;
	}
	if (arr_length < 2) {
		printf("Nije moguce mnoziti bez min. 2 polinoma!");
		return NULL;
	}
	Pozicija newHeader = createNode();
	if (newHeader == NULL) {
		printf("Greska pri alokaciji cvora!\n");
		return NULL;
	}

	Pozicija node = NULL;
	Pozicija currI = NULL;
	Pozicija currJ = NULL;

	struct Broj temp = { 0, 0 };

	for (int i = 1; i < arr_length; i++)
	{
		currI = heads[0]->Next;
		while (currI != NULL) {
			currJ = heads[i]->Next;
			while (currJ != NULL) {
				node = createNode();
				if (node == NULL) {
					printf("Greska pri alokaciji cvora!");
					izbrisiListu(newHeader);
					free(newHeader);
					return NULL;
				}
				temp.koeficijent = currI->Element.koeficijent * currJ->Element.koeficijent;
				temp.eksponent = currI->Element.eksponent + currJ->Element.eksponent;
				unosP(newHeader, node, temp);
				currJ = currJ->Next;
			}
			currI = currI->Next;
		}
	}

	if (polynom_uredjivanje(&newHeader) != 0)
		return NULL;
	return newHeader;
}
int izbrisiListu(Pozicija P) {
	if (P == NULL) {
		printf("Pogreska! (NULL header)!\n");
		return 1;
	}

	Pozicija q = P->Next;
	while (q != NULL) {
		Pozicija iduci = q->Next;
		free(q);
		q = iduci;
	}
	P->Next = NULL;
	return 0;
}