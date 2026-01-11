#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

struct Node;
typedef struct Node* Pozicija;

struct Node
{
	int Element;
	Pozicija Next;
};
Pozicija createNode();
int ispis(Pozicija);
int izbrisiListu(Pozicija);
int PushStog(Pozicija, int);
int PopStog(Pozicija, int*);
int Calculate(char*, int*);

int main() {
	printf("Unesite ime datoteke: ");
	char filename[100] = "";
	scanf("%99s", filename);

	int rezultat = 0;
	if (Calculate(filename, &rezultat) == 0)
	{
		printf("Uspjesno izracunat postfix izraz iz datoteke.\nRezultat operacija: %d", rezultat);
	}

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

int PopStog(Pozicija P, int* output) {
	if (P == NULL) {
		printf("Pogreska! (NULL pokazivac)!\n");
		return 1;
	}
	if (P->Next != NULL) {
		Pozicija temp = 0;
		int output1 = P->Next->Element;
		temp = P->Next->Next;
		free(P->Next);
		P->Next = temp;
		*output = output1;
		return 0;
	}
	else {
		printf("Stog je prazan\n");
		return 2;
	}
}

int Calculate(char* filename, int* rezultat)
{
	FILE* fp = NULL;
	fopen_s(&fp, filename, "r");
	if (fp == NULL) {
		printf("Pogreska: datoteka je NULL!\n");
		return 1;
	}

	if (fgetc(fp) == EOF)
	{
		printf("Pogreska: datoteka je prazna!\n");
		fclose(fp);
		return 5;
	}
	else
		rewind(fp);

	Pozicija stogHead = createNode();
	if (stogHead == NULL) {
		printf("Pogreska prilikom alokacije memorije za stog!\n");
		fclose(fp);
		return 2;
	}
	char ch = EOF;
	int number = 0;
	int previousDigit = 0;


	while ((ch = fgetc(fp)) != EOF && ch != '\n')
	{
		if (ch >= '0' && ch <= '9') {
			number *= 10;
			number += ch - '0';
			previousDigit = 1;
		}
		else if (ch == ' ') {
			if (previousDigit == 1) {
				if (PushStog(stogHead, number) != 0) {
					izbrisiListu(stogHead);
					free(stogHead);
					fclose(fp);
					return 7;
				}
				number = 0;
				previousDigit = 0;
			}
			continue;
		}
		else {
			if (previousDigit == 1) {
				if (PushStog(stogHead, number) != 0) {
					izbrisiListu(stogHead);
					free(stogHead);
					fclose(fp);
					return 7;
				}
				number = 0;
			}
			previousDigit = 0;
			int operand1 = 0;
			int operand2 = 0;
			if (PopStog(stogHead, &operand2) == 2 || PopStog(stogHead, &operand1) == 2)
			{
				printf("Pogreska: izraz nije ispravan, nedostaje operand.\n");
				izbrisiListu(stogHead);
				free(stogHead);
				fclose(fp);
				return 3;
			}
			int result = 0;
			switch (ch) {
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				if (operand2 == 0) {
					printf("Pogreska: dijeljenje s nulom!\n");
					fclose(fp);
					izbrisiListu(stogHead);
					free(stogHead);
					return 3;
				}
				result = operand1 / operand2;
				break;
			default:
				printf("Pogreska: nepoznat operator %c\n", ch);
				izbrisiListu(stogHead);
				free(stogHead);
				fclose(fp);
				return 4;
			}
			if (PushStog(stogHead, result) != 0) {
				izbrisiListu(stogHead);
				free(stogHead);
				fclose(fp);
				return 7;
			}
		}
	}
	if (previousDigit == 1) {
		if (PushStog(stogHead, number) != 0) {
			izbrisiListu(stogHead);
			free(stogHead);
			fclose(fp);
			return 7;
		}
		number = 0;
	}
	if (stogHead->Next->Next != NULL)
	{
		printf("Pogreska: izraz nije ispravan, postoji visak operatora.\n");
		izbrisiListu(stogHead);
		free(stogHead);
		fclose(fp);
		return 5;
	}
	PopStog(stogHead, rezultat);
	izbrisiListu(stogHead);
	free(stogHead);
	fclose(fp);
	return 0;
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