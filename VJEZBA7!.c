#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
static unsigned int max = 0;
static unsigned int current = 0;
typedef struct Node* Pozicija;
struct Node {
	int Element;
	short prioritet;
	Pozicija Next;
};
Pozicija createNode();
int ispis(Pozicija);
int PushStog(Pozicija, int);
int PopStog(Pozicija);
int PushRed(Pozicija, int);
int PopRed(Pozicija);
int izbrisiListu(Pozicija);

int main() {
	Pozicija head = createNode();
	if (head == NULL) {
		return 1;
	}
	int broj = 0;
	int odabir = 1;
	int odabir2 = 2;
	while (odabir != 0)
	{
		printf("\nPritisnite odgovarajuci broj za strukturu koju zelite raditi:\n");
		printf("1 - CIRKULARNI STOG\n");
		printf("2 - RED S PRIORITETOM\n");
		printf("0 - KRAJ PROGRAMA!\n");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1: {
			printf("Unesite maksimalni broj elemenata cirkularnog stoga:\t");
			scanf(" %u", &max);
			do {
				printf("Unesite broj za radnju nad cirkularnim stogom!\n");
				printf("1 - Push(STOG)!\n");
				printf("2 - Push(STOG),RANDOM(OD 10 DO 100)\n");
				printf("3 - Pop(STOG)!\n");
				printf("4 - ISPIS STOGA!\n");
				scanf("%d", &odabir2);
				switch (odabir2) {
				case 1: {
					printf("Unesi broj: ");
					scanf_s(" %d", &broj);
					int output = PushStog(head, broj);
					if (output != 0 && output != 3)
						odabir2 = 0;
					break;
				}
				case 2: {
					srand((unsigned int)time(NULL));
					broj = rand() % (100 - 10 + 1) + 10;
					int output = PushStog(head, broj);
					if (output != 0 && output != 3)
						odabir2 = 0;
					else if (output == 3) {
						break;
					}else
						printf("Uspjesno je dodan element %d\n", broj);
					break;
				}
				case 3: {
					int rezultat = PopStog(head);
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
					ispis(head);
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
				printf("Unesite broj za radnju nad redom s prioritetom!\n");
				printf("1 - Push(RED)!\n");
				printf("2 - Push(RED), RANDOM(OD 10 DO 100)\n");
				printf("3 - Pop(RED)!\n");
				printf("4 - ISPIS REDA!\n");
				scanf("%d", &odabir2);
				switch (odabir2) {
				case 1: {
					printf("Unesi broj: ");
					scanf_s(" %d", &broj);
					int output = PushRed(head, broj);
					if (output < 0)
						odabir2 = 0;
					else
						printf("Uspjesno dodan element %d s prioritetom %d\n",broj,output);
					break;

				}
				case 2: {
					srand((unsigned int)time(NULL));
					broj = rand() % (100 - 10 + 1) + 10;
					int output = PushRed(head, broj);
					if (output < 0)
						odabir2 = 0;
					else
						printf("Uspjesno je dodan element %d s prioritetom %d\n", broj,output);
					break;
				}
				case 3: {
					int rezultat = PopRed(head);
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
					ispis(head);
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
	izbrisiListu(head);
	free(head);
	return 0;
}
Pozicija createNode() {
	Pozicija node = malloc(sizeof(struct Node));
	if (node == NULL) {
		printf("Pogreska: nije moguce alocirati memoriju za cvor!\n");
		return NULL;
	}
	srand((unsigned)time(NULL));
	node->prioritet = rand() % (5 - 1 + 1) + 1;
	node->Next = NULL;
	return node;
}
int PushStog(Pozicija P, int broj) {
	if (max > 0 && current >= max) {
		printf("Stog je pun, maksimalan broj elemenata je %u\n", max);
		return 3;
	}
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
	current++;
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
		current--;
		return 0;
	}
	else {
		printf("Stog je prazan!\n");
		return 2;
	}
}
int PushRed(Pozicija P, int broj) {
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return -1;
	}
	Pozicija node = createNode();
	if (node == NULL) {
		printf("Pogreska pri alokaciji memorije!\n");
		return -2;
	}
	Pozicija q = P;
	while (q->Next != 0) {
		if (node->prioritet > q->Next->prioritet)
			break;
		q = q->Next;
	}
	node->Element = broj;
	node->Next = q->Next;
	q->Next = node;
	return node->prioritet;
}
int PopRed(Pozicija P) {
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
		printf("Red je prazan\n");
		return 2;
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
	printf("\n");
	return 0;
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