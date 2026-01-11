#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct Node;
typedef struct Node* Pozicija;

struct Node
{
	int Element;
	Pozicija Next;
};
Pozicija createNode();
int unosP(Pozicija, Pozicija, int);
int unosK(Pozicija, Pozicija, int);
int postaviIza(Pozicija, Pozicija, int, int);
int postaviIspred(Pozicija, Pozicija, int, int);
int delete(Pozicija, Pozicija);
void ReadListFromFile(Pozicija);
int ispis(Pozicija);
int sortiraniUnos(Pozicija, Pozicija, int);
int postoji_u_listi(Pozicija, int);
Pozicija Presjek(Pozicija*);
Pozicija Unija(Pozicija*);
Pozicija ucitaj_sortiranu_listu_iz_datoteke(FILE*);
FILE* otvaranjeDatoteke();
int izbrisiListu(Pozicija);
int sortirati_polynom(Pozicija*);
int main()
{
	FILE* files[2] = { NULL };
	Pozicija heads[2];

	for (int i = 0; i < 2; i++)
	{
		printf("%d ", i + 1);
		files[i] = otvaranjeDatoteke();
		if (files[i] == NULL)
			i--;
	}

	for (int i = 0; i < 2; i++)
	{
		heads[i] = ucitaj_sortiranu_listu_iz_datoteke(files[i]);
		if (heads[i] == NULL) {
			printf("Pogreska prilikom citanja liste iz datoteke!");
			return 1;
		}
	}
	int odabir = 0;
	do
	{
		printf("\nUnesi broj za trazenu radnju:\n1) UNIJA  2) PRESJEK  0) KRAJ\n");
		scanf(" %d", &odabir);


		Pozicija newHead = NULL;

		switch (odabir)
		{
		case 1: {
			newHead = Unija(&heads);
			if (newHead == NULL)
				odabir = 0;
			printf("Nova lista: ");
			ispis(newHead);
			izbrisiListu(newHead);
			free(newHead);
			break;
		}
		case 2: {
			newHead = Presjek(&heads);
			if (newHead == NULL)
				odabir = 0;
			printf("Nova lista: ");
			ispis(newHead);
			izbrisiListu(newHead);
			free(newHead);
			break;
		}
		default:
			printf("Kraj programa!\n");
			break;
		}

	} while (odabir != 0);

	for (int i = 0; i < 2; i++)
	{
		if (files[i] != NULL)
			fclose(files[i]);
		if (heads[i] != NULL) {
			izbrisiListu(heads[i]);
			free(heads[i]);
		}
	}
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



void ReadListFromFile(Pozicija P)
{
	FILE* fp;
	char filename[128];
	Pozicija q, temp;

	printf("Unesite ime datoteke za citanje :\n ");
	scanf_s("%127s", filename);

	fp = fopen(filename, "r");
	if (fp == NULL)
		printf("Neuspjesno otvorena datoteka!\n");
	else
	{
		while (!feof(fp))
		{
			q = (Pozicija)malloc(sizeof(struct Node));
			if (q == NULL)
				printf("Greska! Memorija nije alocirana.\n");
			else
			{
				fscanf_s(fp, " %d", &q->Element);

				temp = P;

				while (temp->Next != NULL && temp->Next->Element < q->Element)
					temp = temp->Next;
				q->Next = temp->Next;
				temp->Next = q;
			}
		}
		fclose(fp);
	}
}

int ispis(Pozicija P) {
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	if (P->Next == NULL) {
		printf("Lista je prazna.\n");
		return 2;
	}
	else {
		Pozicija temp = P->Next;
		while (temp != NULL) {
			printf("%d ", temp->Element);
			temp = temp->Next;
		}

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
	printf("Osoba nije pronadjena!\n");
	return 1;
}
int postaviIza(Pozicija P, Pozicija node, int number, int target) {
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
			printf("Osoba uspjesno dodana nakon %d. elementa!\n", target);
			return 0;
		}
		temp = temp->Next;
		i++;
	}

	printf("Broj elementa nije pronadjen!\n");
	free(node);
	return 1;
}

int postaviIspred(Pozicija P, Pozicija node, int number, int target) {
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
			printf("Osoba uspjesno dodana prije %d. elementa!\n", target);
			return 0;
		}
		temp = temp->Next;
		i++;
	}
	printf("Broj elementa nije pronaden!\n");
	free(node);
	return 1;
}
int sortiraniUnos(Pozicija P, Pozicija node, int number) {
	if (P == NULL || node == NULL)
	{
		printf("Greska pri ucitavanju liste! (Pokazivac NULL)");
		return 1;
	}

	Pozicija q = P;
	while (q->Next != NULL) {
		if (number <= q->Next->Element)
			break;
		q = q->Next;
	}

	node->Element = number;
	node->Next = q->Next;
	q->Next = node;

	return 0;
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
		if (sortiraniUnos(newHead, q->Element, node) != 0) {
			printf("Greska pri dodavanju elemenata u novu listu!");
			return 3;
		}
		q = q->Next;
	}
	izbrisiListu(*P);
	*P = newHead;
	return 0;
}
int postoji_u_listi(Pozicija P, int number) {
	if (P == NULL)
	{
		printf("Greska pri ucitavanju liste! (Pokazivac NULL)");
		return -1;
	}

	Pozicija q = P->Next;

	while (q != NULL)
	{
		if (q->Element == number) {
			return 1;
		}
		q = q->Next;
	}
	return 0;
}
Pozicija Presjek(Pozicija* heads)
{
	if (heads == NULL)
	{
		printf("Greska pri ucitavanju liste! (Pokazivac NULL)");
		return NULL;
	}
	Pozicija newHead = createNode();
	if (newHead == NULL) {
		printf("Greska pri alokaciji cvora!");
		return NULL;
	}
	Pozicija node;
	Pozicija q = NULL;
	for (int i = 1; i < 2; i++)
	{
		if (heads[i] == NULL) {
			printf("Greska pri ucitavanju jedne liste u nizu! (Pokazivac NULL)");
			free(newHead);
			return NULL;
		}
		q = heads[i]->Next;
		while (q != NULL)
		{
			node = createNode();
			if (node == NULL) {
				printf("Greska pri alociranju cvora!");
				free(newHead);
				return NULL;
			}
			if (postoji_u_listi(heads[0], q->Element) == 1 && postoji_u_listi(newHead, q->Element) == 0)
				sortiraniUnos(newHead, node, q->Element);
			q = q->Next;
		}
	}
	return newHead;
}

Pozicija Unija(Pozicija* heads)
{
	if (heads == NULL)
	{
		printf("Greska pri ucitavanju liste! (Pokazivac NULL)");
		return NULL;
	}
	Pozicija newHead = createNode();
	if (newHead == NULL) {
		printf("Greska pri alokaciji cvora!");
		return NULL;
	}
	Pozicija node;
	Pozicija q = NULL;
	for (int i = 0; i < 2; i++)
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
				printf("Greska pri alokaciji cvora!");
				free(newHead);
				return NULL;
			}
			if (postoji_u_listi(newHead, q->Element) == 0)
				sortiraniUnos(newHead, node, q->Element);
			q = q->Next;
		}
	}
	return newHead;

}
Pozicija ucitaj_sortiranu_listu_iz_datoteke(FILE* fp) {
	if (fp == NULL) {
		printf("Greska, datoteka nije otvorena!\n");
		return NULL;
	}

	Pozicija P = createNode();
	if (P == NULL)
		return NULL;

	int num;
	Pozicija node = NULL;
	while (fscanf_s(fp, "%d", &num) == 1)
	{
		node = createNode();
		if (node == NULL) {
			izbrisiListu(P);
			free(P);
			return NULL;
		}
		sortiraniUnos(P, node, num);
	}

	return P;
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