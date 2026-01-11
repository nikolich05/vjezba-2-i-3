//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <math.h>
//#include <string.h>
//#include <ctype.h>
//#include <stdlib.h>
//#include <time.h>
//typedef struct Node* Pozicija;
//struct Osoba {
//	int god;
//	char ime[15];
//	char prezime[20];
//};
//typedef struct Osoba osoba;
//struct Node {
//	struct Osoba element;
//	Pozicija Next;
//};
//
//Pozicija createNode();
//int unosP(Pozicija, Pozicija, osoba);
//osoba podaci_osobe();
//int ispis(Pozicija);
//int unosK(Pozicija, Pozicija, osoba);
//char* unijeti_string();
//Pozicija findElementPrez(Pozicija,char*);
//int delete(Pozicija,Pozicija);
//int postaviIza(Pozicija,Pozicija,osoba,int);
//int postaviIspred(Pozicija,Pozicija,osoba,int);
//int upis_u_datoteku(Pozicija,FILE*);
//Pozicija citanje_iz_datoteke(FILE*);
//int izbrisiListu(Pozicija);
//int main() {
//	Pozicija head = createNode();
//	if (head == NULL)
//		return 1;
//	int odabir = 1;
//
//	while (odabir != 0)
//	{
//		printf("\nPritisnite odgovarajuci broj za radnju koju zelite obaviti:\n");
//		printf("0 - KRAJ PROGRAMA!\n");
//		printf("1 - DINAMICKI DODAJE NOVI ELEMENT NA POCETAK LISTE!\n");
//		printf("2 - ISPISUJE LISTU!\n");
//		printf("3 - DINAMICKI DODAJE NOVI ELEMENT NA KRAJ LISTE!\n");
//		printf("4 - PRONALAZI ELEMENT U LISTI (PO PREZIMENU)!\n");
//		printf("5 - BRISE ODREDJENI ELEMENT IZ LISTE!\n");
//		printf("6 - DINAMICKI DODAJE NOVI ELEMENT IZA ODREDJENOG ELEMENTA!\n");
//		printf("7 - DINAMICKI DODAJE NOVI ELEMENT ISPRED ODREDJENOG ELEMENTA!\n");
//		printf("8 - UPISUJE LISTU U DATOTEKU!\n");
//		printf("9 - CITA LISTU IZ DATOTEKE!\n");
//		scanf_s("%d", &odabir);
//
//		switch (odabir)
//		{
//		case 1: {
//
//			Pozicija node = createNode();
//			if (node != NULL)
//				unosP(head, node, podaci_osobe());
//			else
//				odabir = 0;
//			break;
//
//		}
//		case 2:
//			ispis(head);
//			break;
//		case 3: {
//
//			Pozicija node = createNode();
//			if (node != NULL)
//				unosK(head, node, podaci_osobe());
//			else
//				odabir = 0;
//			break;
//
//		}
//		case 4: {
//			char* surname = unijeti_string("Unesite prezime osobe:");
//			if (surname == NULL) {
//				odabir = 0;
//				break;
//			}
//			Pozicija node = findElementPrez(head, surname);
//			if (node == NULL)
//				printf("Osoba nije pronadjena!\n");
//			else
//				printf("Pronadena osoba: %s %s, %d\n", node->element.ime, node->element.prezime, node->element.god);
//			free(surname);
//			break;
//		}
//		case 5: {
//			char* surname = unijeti_string("Unesite prezime osobe:");
//			if (surname == NULL) {
//				odabir = 0;
//				break;
//			}
//			Pozicija node = findElementPrez(head, surname);
//			if (node == NULL)
//				printf("Osoba nije pronadjena!\n");
//			else
//				delete(head, node);
//			free(surname);
//			break;
//		}
//		case 6: {
//			int number;
//			printf("Unesite broj elementa u listi: ");
//			scanf_s("%d", &number);
//			Pozicija node = createNode();
//			if (node != NULL)
//				postaviIza(head, node, podaci_osobe(), number);
//			else
//				odabir = 0;
//			break;
//		}
//		case 7: {
//			int number;
//			printf("Unesite broj elementa u listi: ");
//			scanf_s("%d", &number);
//			Pozicija node = createNode();
//			if (node != NULL)
//				postaviIspred(head, node, podaci_osobe(), number);
//			else
//				odabir = 0;
//			break;
//		}
//		case 8: {
//			FILE* fp = NULL;
//			fopen_s(&fp, "Lista.txt","w");
//			upis_u_datoteku(head, fp);
//			break;
//		}
//		case 9: {
//			FILE* fp = NULL;
//			fopen_s(&fp, "Lista.txt", "r");
//			Pozicija readNode = citanje_iz_datoteke(fp);
//			if (readNode != NULL) {
//				izbrisiListu(head);
//				free(head);
//				head = readNode;
//			}
//			else
//				odabir = 0;
//			break;
//		}
//		case 0:
//			printf("KRAJ!\n"); odabir = 0;
//			break;
//		default:
//			printf("NEMA RADNJE ZA TAJ ODABIR, POKUSAJ PONOVNO!\n");
//		}
//	}
//	izbrisiListu(head);
//	free(head);
//	return 0;
//}
//Pozicija createNode() {
//	Pozicija node = malloc(sizeof(struct Node));
//	if (node == NULL) {
//		printf("Pogreska, nije moguce alocirati memoriju za cvor!\n");
//		return NULL;
//	}
//	node->Next = NULL;
//	return node;
//}
//int unosP(Pozicija P, Pozicija node, osoba person) {
//	if (P == NULL || node == NULL) {
//		printf("Pogreska! (NULL pokazivac)!\n");
//		return 1;
//	}
//	node->element = person;
//	node->Next = P->Next;
//	P->Next = node;
//	return 0;
//}
//osoba podaci_osobe() {
//	osoba person;
//	printf("Unesi ime osobe: ");
//	scanf("%14s", person.ime);
//
//	printf("Unesi prezime osobe: ");
//	scanf("%19s", person.prezime);
//
//	printf("Unesi godinu rodenja: ");
//	while (scanf_s("%d", &person.god) != 1) {
//		printf("Neispravan unos! Pokusaj ponovo: ");
//		while (getchar() != '\n');
//	}
//
//	return person;
//}
//int ispis(Pozicija P) {
//	if (P == NULL) {
//		printf("Pogreska! (NULL pokazivac)!\n");
//		return 1;
//	}
//	if (P->Next == NULL) {
//		printf("Lista je prazna.\n");
//		return 0;
//	}
//	else {
//		Pozicija temp = P->Next;
//		while (temp != NULL) {
//			printf("%s %s %d\t", temp->element.ime, temp->element.prezime, temp->element.god);
//			temp = temp->Next;
//		}
//
//	}
//
//	return 0;
//}
//int unosK(Pozicija P, Pozicija node, osoba person) {
//	if (P == NULL || node == NULL) {
//		printf("Pogreska! (NULL pokazivac)!\n");
//		return 1;
//	}
//	node->element = person;
//	node->Next = NULL;
//	Pozicija q = P;
//	while (q->Next != NULL)
//		q = q->Next;
//
//	q->Next = node;
//	return 0;
//}
//char* unijeti_string(char* str) {
//	printf("%s ", str);
//	char* string = malloc(20 * sizeof(char));
//	if (string == NULL) {
//		printf("Pogreska, nije moguce alocirati memoriju za string!\n");
//		return NULL;
//	}
//	scanf("%19s", string);
//	return string;
//}
//
//Pozicija findElementPrez(Pozicija P, char* prez) {
//	if (P == NULL || prez == NULL) {
//		printf("Pogreska! (NULL pokazivac)!\n");
//		return NULL;
//	}
//	Pozicija temp = P->Next;
//	while (temp != NULL) {
//		if (strcmp(temp->element.prezime, prez) == 0) {
//			printf("Prezime pronadjeno kod elementa: %s %s %d\n", temp->element.ime, temp->element.prezime, temp->element.god);
//			return temp;
//		}
//		temp = temp->Next;
//	}
//	return NULL;
//}
//
//
//int delete(Pozicija P, Pozicija node) {
//	if(P == NULL || node == NULL) {
//		printf("Pogreska! (NULL pokazivac)!\n");
//		return 1;
//	}
//	Pozicija q = P;
//	while (q->Next != NULL) {
//		if (q->Next == node) {
//			q->Next = node->Next;
//			free(node);
//			printf("Element je uspjesno izbrisan iz liste!\n");
//			return 0;
//		}
//		q = q->Next;
//	}
//	printf("Osoba nije pronadjena!\n");
//	return 1;
//}
//int postaviIza(Pozicija P, Pozicija node, osoba person, int broj) {
//	if (P == NULL || node == NULL) {
//		printf("Pogreska! (NULL pokazivac)!\n");
//		return 1;
//	}
//	Pozicija temp = P->Next;
//	int i = 0;
//	while (temp != NULL) {
//		if (i == broj) {
//			node->element = person;
//			node->Next = temp->Next;
//			temp->Next = node;
//			printf("Osoba uspjesno dodana nakon %d. elementa!\n", broj);
//			return 0;
//		}
//		temp = temp->Next;
//		i++;
//	}
//
//	printf("Broj elementa nije pronadjen!\n");
//	free(node);
//	return 1;
//}
//
//int postaviIspred(Pozicija P, Pozicija node, osoba person, int broj) {
//	if (P == NULL || node == NULL) {
//		printf("Pogreska! (NULL pokazivac)!\n");
//		return 1;
//	}
//	Pozicija temp = P;
//	int i = 0;
//	while (temp->Next != NULL) {
//		if (i == broj) {
//			node->element = person;
//			node->Next = temp->Next;
//			temp->Next = node;
//			printf("Osoba uspjesno dodana prije %d. elementa!\n", broj);
//			return 0;
//		}
//		temp = temp->Next;
//		i++;
//	}
//	printf("Broj elementa nije pronaden!\n");
//	free(node);
//	return 1;
//}
//int upis_u_datoteku(Pozicija P, FILE* fp) {
//	if (fp == NULL) {
//		printf("Datoteka neuspjesno otvorena!\n");
//		return 1;
//	}
//	if (P == NULL) {
//		printf("Pogreska, lista ne postoji!\n");
//		fclose(fp);
//		return 1;
//	}
//
//	Pozicija q = P->Next;
//	if (q == NULL) {
//		printf("Lista je prazna!\n");
//		fclose(fp);
//		return 1;
//	}
//
//	int i = 1;
//	while (q != NULL) {
//		fprintf(fp, "Osoba %d. : %s %s %d\n", i,q->element.ime,q->element.prezime,q->element.god);
//		i++;
//		q = q->Next;
//	}
//	fclose(fp);
//	printf("Uspjesno upisivanje u datoteku!\n");
//	return 0;
//}
//Pozicija citanje_iz_datoteke(FILE* fp) {
//	if (fp == NULL) {
//		printf("Neuspjesno otvaranje datoteke!\n");
//		return NULL;
//	}
//
//	Pozicija P = createNode();
//	if (P == NULL)
//		return NULL;
//
//	int id = 0;
//	osoba person = { "" };
//	while (fscanf(fp, "Osoba %d. : %14s %19s %d\n",&id, person.ime,person.prezime,&person.god) == 4) {
//		unosK(P, createNode(), person);
//	}
//	fclose(fp);
//	printf("Uspjesno ucitana lista iz datoteke!\n");
//	return P;
//}
//int izbrisiListu(Pozicija P) {
//	if (P == NULL) {
//		printf("Pogreska! (NULL header)!\n");
//		return 1;
//	}
//
//	Pozicija q = P->Next;
//	while (q != NULL) {
//		Pozicija iduci = q->Next;
//		free(q);
//		q = iduci;
//	}
//	P->Next = NULL;
//	return 0;
//}
