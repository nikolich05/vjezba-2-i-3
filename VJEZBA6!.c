#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#define min 10
#define max 100
typedef struct Node* Pozicija;
struct Node {
	int Element;
	Pozicija Next;
};
Pozicija createNode();
int ispis(Pozicija);
int PushStog(Pozicija, int);
int PopStog(Pozicija);
static int PushRed(Pozicija, int, short);
int PopRed(Pozicija);
int izbrisiListu(Pozicija);
int main() {
	Pozicija headStog = createNode();
	Pozicija headRed = createNode();
	if (headStog == NULL || headRed == NULL) {
		return 1;
	}
	int broj = 0;
	int odabir = 1;
	int odabir2 = 2;
	while (odabir != 0)
	{
		printf("\nPritisnite odgovarajuci broj za strukturu koju zelite raditi:\n");
		printf("1 - STOG\n");
		printf("2 - RED\n");
		printf("0 - KRAJ PROGRAMA!\n");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1: {
			do {
				printf("\nUnesite broj za radnju nad stogom!\n");
				printf("1 - Push(STOG)!\n");
				printf("2 - Push(STOG),RANDOM(OD 10 DO 100)\n");
				printf("3 - Pop(STOG)!\n");
				printf("4 - ISPIS STOGA!\n");
				scanf("%d", &odabir2);
				switch (odabir2) {
				case 1: {
					printf("Unesi broj: ");
					scanf_s(" %d", &broj);
					if (PushStog(headStog, broj) != 0)
						odabir2 = 0;
					break;
				}
				case 2: {
					srand((unsigned int)time(NULL));
					broj = rand() % (max - min + 1) + min;
					if (PushStog(headStog, broj) != 0)
						odabir2 = 0;
					else
						printf("Uspjesno je dodan element %d\n", broj);
					break;
				}
				case 3: {
					int rezultat = PopStog(headStog);
					if (rezultat == 0) {
						printf("Uspjesno izbrisan element sa stoga!\n");
					}
					else if (rezultat == 2) {
						break;
					}
					else if (rezultat == 1) {
						odabir2 = 0;
						break;
					}
					break;
				}
				case 4: {
					ispis(headStog);
					break;
				}
				default: {

					break;
				}
				}
			} while (odabir2 != 0);
			break;
		}
		case 2: {
			do {
				printf("\nUnesite broj za radnju nad redom!\n");
				printf("1 - Push(RED)!\n");
				printf("2 - Push(RED), RANDOM(OD 10 DO 100)\n");
				printf("3 - Pop(RED)!\n");
				printf("4 - ISPIS REDA!\n");
				scanf("%d", &odabir2);
				switch (odabir2) {
				case 1: {
					printf("Unesi broj: ");
					scanf_s(" %d", &broj);
					if (PushRed(headRed, broj,0) != 0)
						odabir2 = 0;
					break;

				}
				case 2: {
					srand((unsigned int)time(NULL));
					broj = rand() % (max - min + 1) + min;
					if (PushRed(headRed, broj,0) != 0)
						odabir2 = 0;
					else
						printf("Uspjesno je dodan element %d\n", broj);
					break;
				}
				case 3: {
					int rezultat = PopRed(headRed);
					if (rezultat == 0) {
						printf("Uspjesno izbrisan element sa stoga!\n");
					}
					else if (rezultat == 2) {
						break;
					}
					else if (rezultat == 1) {
						odabir2 = 0;
						break;
					}
					break;
				}
				case 4: {
					ispis(headRed);
					break;
				}
				default: {

					break;
				}
				}
			} while (odabir2 != 0);
			break;
		}
		case 0:
			printf("KRAJ!\n"); odabir = 0;
			break;
		default:
			printf("NEMA RADNJE ZA TAJ ODABIR, POKUSAJ PONOVNO!\n");
		}
	}
	izbrisiListu(headStog);
	free(headStog);
	PushRed(NULL, 0, 1);
	izbrisiListu(headRed);
	free(headRed);
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
int PushStog(Pozicija P, int broj) {

	Pozicija node = createNode();
	if (node == NULL) {
		printf("Pogreska pri alokaciji memorije!\n");
		return 2;
	}
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		free(node);
		return 1;
	}
	node->Element = broj;
	node->Next = P->Next;
	P->Next = node;
	return 0;
}

int PopStog(Pozicija P) {
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	if (P->Next != NULL) {
		Pozicija temp = 0;
		temp = P->Next->Next;
		free(P->Next);
		P->Next = temp;
		return 0;
	}
	else {
		printf("Stog je prazan\n");
		return 2;
	}
}
static int PushRed(Pozicija P, int broj, short resetLastNode) {

	static Pozicija lastnode = NULL;
	if (resetLastNode > 0) {
		lastnode = NULL;
		return 3;
	}
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	if (lastnode == NULL)
		lastnode = P;

	Pozicija node = createNode();
	if (node == NULL) {
		printf("Pogreska pri alokaciji memorije!\n");
		return 2;
	}
	node->Element = broj;
	node->Next = P->Next;
	P->Next = node;
	return 0;
}
int PopRed(Pozicija P) {
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	if (P->Next != NULL) {
		Pozicija temp = 0;
		temp = P->Next->Next;
		if (P->Next->Next == NULL)
			PushRed(NULL, 0, 1);
		P->Next = temp;
		return 0;
	}
	else {
		printf("Red je prazan\n");
		return 2;
	}
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