#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#define min 10
#define max 100
struct cvor;
typedef struct cvor* Pozicija;
struct cvor {
	int el;
	Pozicija next;
};
int slucajnoGenerirano(int, int);
void PushRed(Pozicija, int);
void PushStog(Pozicija, int);
void Pop(Pozicija);
void ispis(Pozicija);

int main() {

	struct cvor stog, red;
	stog.next = NULL;
	red.next = NULL;

	int odabir = 1;

	while (odabir != 0)
	{
		printf("\nPritisnite odgovarajuci broj za radnju koju zelite obaviti:\n");
		printf("0 - KRAJ PROGRAMA!\n");
		printf("1 - Push(STOG)!\n");
		printf("2 - Pop(STOG)!\n");
		printf("3 - Push(RED)!\n");
		printf("4 - Pop(RED)!\n");
		scanf("%d", &odabir);

		switch (odabir)
		{
		case 1:
			PushStog(&stog, slucajnoGenerirano(min, max));
			ispis(stog.next);
			break;
		case 2:
			Pop(&stog);
			ispis(stog.next);
			break;
		case 3:
			PushRed(&red, slucajnoGenerirano(min, max));
			ispis(red.next);
			break;
		case 4:
			Pop(&red);
			ispis(red.next);
			break;
		case 0:
			printf("KRAJ!\n"); odabir = 0;
			break;
		default:
			printf("NEMA RADNJE ZA TAJ ODABIR, POKUSAJ PONOVNO!\n");
		}
	}

	return 0;
}
int slucajnoGenerirano(int minValue, int maxValue)
{
	int broj;
	broj = rand() % (maxValue - minValue) + minValue;

	return broj;
}

void ispis(Pozicija P) {
	printf("Ispis:\n");

	while (P != NULL)
	{
		printf("%d ", P->el);
		P = P->next;
	}
}
void PushStog(Pozicija P, int broj) {

	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(struct cvor));

	if (temp) {
		temp->el = broj;
		temp->next = P->next;
		P->next = temp;

		printf("\nBroj %d se dodjeljuje stogu\n", broj);
	}
}

void PushRed(Pozicija P, int broj) {

	Pozicija temp;
	static Pozicija q;

	if (P->next == NULL)
		q = P;

	temp = (Pozicija)malloc(sizeof(struct cvor));
	if (temp)
	{
		temp->el = broj;
		temp->next = q->next;
		q->next = temp;
		q = temp;

		printf("\nBroj %d se dodjeljuje redu\n", broj);
	}

}
void Pop(Pozicija P) {

	Pozicija temp;

	if (P->next != NULL) {
		temp = P->next;
		printf("\nObrisan je broj %d\n", temp->el);

		P->next = temp->next;
		free(temp);
	}
}
	







