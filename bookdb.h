#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

#include "./users.h"
#include "./logs.h"



typedef struct bookbox {
	char isbn[15]; 		 // ISBN
	char author[20]; 	 // �����
	char title[30]; 	 // ��������
	 int all; 		 // ����� ����
	 int available; 	 // �� ��� ��������
} bookbox;

//---------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------���������� ��� ����-------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------���������� �����----------------------------------------------------------------


bookbox new_book() {				 		//������ ����� �����
	bookbox book;

	printf("������� ISBN (�� 15 ����): ");
		scanf("%[^\n]%*c", book.isbn);

	printf("������� ��� ������ (� ����������� �������: ������� �.�.): ");
		scanf("%[^\n]%*c", book.author);

	printf("������� �������� �����: ");
		scanf("%[^\n]%*c", book.title);

	printf("������� ����� ���������� ����: ");
		scanf("%d%*c", &book.all);

	printf("������� ���������� ���� � ������� (����������� ������ ������ ����� ����): ");
		scanf("%d%*c", &book.available);



		return book;

}

void printbook(bookbox book) { 			 		//����� �����

	printf("| %-10s ", book.isbn);
	printf("| %-30s ", book.author);
	printf("| %-25s ", book.title);
	printf("| %-5d ", book.all);
	printf("| %-7d ", book.available);
	printf("|\n");

}

void printbookbox(bookbox* book, int q) {	 		//����� ���� ����������
						 		//���� ���� ��� - ������� ��������������
	if (q == 0) {

		printf("��� ��� �� ����� �����\n");
		return;
}

	printf("|    ISBN    |             ������             |       �������� ����       | ����� | ������� |\n");
       	printf("|------------|--------------------------------|---------------------------|-------|---------|\n");

	for (int i = 0; i < q; i++) {

		printbook(book[i]);
	}
}

bookbox* createbook(bookbox* book, int* q) {	 		//���������� �����

	printf("������� ���������� � �����\n");
	bookbox nbook = new_book();
	if ((nbook.all > 0) && (nbook.available > -1)){

		for (int i = 0; i < *q; i++) {		 		//�������� �� ������������� ISBN

			if (strcmp(book[i].isbn, nbook.isbn) == 0) {

				printf("ISBN '%s' ��� ����������\n", nbook.isbn);
				return book;
			}
		}
	}
	else {

		printf ("����� ���� ������ ���� �� �������������\n");
		return book;
	}

	book = (bookbox*)realloc(book, (*q + 1) * sizeof(bookbox));
	book[*q] = nbook;
	(*q)++;

	return book;
}

//----------------------------------------------------�������� �����---------------------------------------------------------------


void deletebook(bookbox* book, int* q, studbookbox* studbk, int* l) {

	if (q == 0) {

		printf("�� ����� ����� ��� �� ���������\n");
		return;

	}

	char isbn[15];
	printf("������� ISBN �����, ������� ������ �������: ");
	scanf("%[^\n]", &isbn); 		 			// ��������� ���� ��� ������

	for (int i = 0; i < *l; i++) {

		if (strcmp(studbk[i].isbn, isbn) == 0) {

			printf("������ ����� ���������� �������, ��� ������� � ������� � ����-�� �� ���������\n");
            		return;
        	}
    	}

	int j = 0; 		 		 			// ����� ������ ��� ����� ��������

	for (int i = 0; i < *q; i++) {

		if (strcmp(book[i].isbn, isbn) == 0) {

			book[j++] = book[i];
		}
		else {
			printf("����� � ISBN '%s' �� ����������\n", isbn); ;
		}
	}

	*q = j; 				  			//���������
}

//---------------------------------------------------������ �����------------------------------------------------------------------


void givebook(bookbox* book, int q, studbox* student, int* m, studbookbox* studbk, int* l) {

	int existence = 0;			  			// �������� �� ������������� ��������
	int daymin = 31, monthmin = 12, yearmin = 2025;
	int studsum, min;
	char isbn[15], nu[8];

	printf("������� ISBN ����������� �����: ");
		scanf("%[^\n]%*c", isbn);

	printf("������� ����� ������� ��������, ������� �������� ������: ");
		scanf("%[^\n]%*c", nu);

	for (int i = 0; i < q; i++) {

		if (strcmp(student[i].nu, nu) == 0) {
			existence++;
		}
	}

	if (existence == 0) {

		printf("�������� � ����� ������� ������� �� ����������\n");
		return 0;
	}

	for (int i = 0; i < q; i++) {

		if (strcmp(book[i].isbn, isbn) == 0) { 			// ���� ����� �����

			if (book[i].available == 0) {  			// �������� ��

				for (int j = 0; j < *l; j++) {

					if (strcmp(studbk[j].isbn, isbn) == 0) {

						studsum = studbk[j].year * 10000 + studbk[j].month * 100 + studbk[j].day;
						min = yearmin * 10000 + monthmin * 100 + daymin;

						if (studsum < min) {

							daymin = studbk[j].day;
							monthmin = studbk[j].month;
							yearmin = studbk[j].year;
						}
					}
				}

				printf("� ���������, ������ ����� ��� � ���������������� ����� ����� ����� %d.%d.%d\n", daymin, monthmin, yearmin);
			}

			else {
				book[i].available--;

				studbk = (studbookbox*)realloc(studbk, (*l + 1) * sizeof(studbookbox));
				strcpy(studbk[*l].isbn, isbn);
				strcpy(studbk[*l].nu, nu);

				studbk[*l].day = 31;
				studbk[*l].month = 06;
				studbk[*l].year = 2020;

				(*l)++;

				printf("����� ������\n");
			}
			return 0;
		}
	}
	printf("����� � ISBN '%s' �� ����������\n", isbn);
}

//---------------------------------------------------------����� �����-------------------------------------------------------------


void returnbook(bookbox* book, int q, studbox* student, int* m, studbookbox* studbk, int* l) {	 // ������� �����

	int existenceA = 0, existenceB = 0; 		 					 // �������� �� �������������
	char isbn[15], nu[8];

	printf("������� ISBN �����, ������� ������ �������: ");
		scanf("%[^\n]%*c", isbn);

	printf("������� ����� ������� ��������, ������� ���������� ������: ");
		scanf("%[^\n]%*c", nu);

	for (int i = 0; i < q; i++) {

		if (strcmp(student[i].nu, nu) == 0) {

			existenceA++;
		}
	}

	if (existenceA == 0) {

		printf("�������� � ����� ������� ������� �� ����������\n");
		return 0;
	}

	for (int i = 0; i < *l; i++) {

		if ((strcmp(studbk[i].nu, nu) == 0) && (strcmp(studbk[i].isbn, isbn) == 0)) {

			existenceB++;
		}
	}

	if (existenceB == 0) {

		printf("������� � ����� ������� �� ����� � ������� ����� �����\n");
		return 0;
	}

	for (int i = 0; i < q; i++) {

		if (strcmp(book[i].isbn, isbn) == 0) {	 			// ���� ����� �����

			if (book[i].all == book[i].available) {

				printf("���������� ������� ��� ����� - � ���������� ��� ������� ��� ����������\n");
			}

			else {
				book[i].available++;
				int j = 0; 		 			// ����� ������ ��� ��������� ����� ��������

				for (int i = 0; i < *l; i++) {

					if ((strcmp(studbk[i].isbn, isbn) != 0) || (strcmp(studbk[i].nu, nu) != 0)) {
						studbk[j++] = studbk[i];
					}
				}

				*l = j; 		 			// ��������� ������
				printf("����� ������� ����������\n");
			}

			return 0;
		}
	}

	printf("����� � ISBN '%s' �� ����������\n", isbn);
}

//-----------------------------------------------------������ � ���������, ������� �����-------------------------------------------


void bookinfo(studbox* student, int m, bookbox* book, int q, studbookbox* studbk, int l) {

	char isbn[15];
	int marker= 0;

	printf("������� ����� ISBN, ����� ����������� ��� ���������� � ���������� �����: ");
		scanf("%[^\n]%*c", isbn);

	printf("|   �����   |             �������             |       ���       |         ��������         | ��������� |         �������������          |  ���� ��������  \n");
	printf("|-----------|---------------------------------|-----------------|--------------------------|-----------|--------------------------------|-----------------\n");

	for (int i = 0; i < m; i++) {

		if (strcmp(book[i].isbn,isbn) == 0) {						 // ���� ����� �����

			for (int j = 0; j < l; j++) {

				if (strcmp(studbk[j].isbn, isbn) == 0) {			 // ���� ����� �������� � ������

					for (int r = 0; r < q; r++) {

						if (strcmp(student[r].nu, studbk[j].nu) == 0) {	 // ����� �������� � �������

							printf("| %-9s ", student[r].nu);
							printf("| %-31s ", student[r].surname);
							printf("| %-15s ", student[r].name);
							printf("| %-24s ", student[r].fathername);
							printf("| %-9s ", student[r].faculty);
							printf("| %-30s ", student[r].spec);
							printf("| %d.%d.%d ", studbk[j].day, studbk[j].month, studbk[j].year);
							printf("\n");
						}
					}
				}
			}

			marker++;
		}
	}

	if (marker == 0) {

		printf("����� � ISBN '%s' ��� �� � ���� �� ���������\n", isbn);
	}
}

//--------------------------------------------����� �� ������-------------------------------------------------------------------

void findbooksurname(bookbox* book, int q) { // ����� ������
    char author[25];
    int flagbk = 0;
    int i = 0;
    printf("������� �������, �������� ������ �����: ");
    scanf("%[^\n]%*c", author);

    printf("|    ISBN    |             ������             |       �������� ����       | ����� | ������� |\n");
    printf("|------------|--------------------------------|---------------------------|-------|---------|\n"); // ������� ����� �������
    for (int i = 0; i < q; i++) {

    	if (strcmp(book[i].author, author) == 0) { // ���� ����� ��������

		printbook(book[i]);
        	flagbk++;
        }
    }

    if (flagbk == 0) {

	printf("������ � �������� '%s' �� ����������\n", author);
    }
}

//------------------------------------------------------------------�����---------------------------------------------------------




void createbackupbk(bookbox* book, int q) { // ����� ���� � ����
    char backupname[50] = { 0 };

    if (q == 0) {
        printf("�� ����� ����� ��� �� ���������\n");
        return;
    }

    struct tm* t;
    time_t timer = time(NULL);
    t = localtime(&timer); // ������� � ����� ��� � ��������� ��� � ���������
    strftime(backupname, 50, "books_%d_%m_%Y; %H_%M_%S.csv", t);
    FILE* filebook = fopen(backupname, "w");
    if (filebook == 0) { // ���� �� ������� ������� ����
        printf("�� ������� ������� ���� '%s'\n", backupname);
        return NULL; // ���������� ������ ���������
    }

    for (int i = 0; i < q; i++) {
        fprintf(filebook, "%s;", book[i].isbn);
        fprintf(filebook, "%s;", book[i].author);
        fprintf(filebook, "%s;", book[i].title);
        fprintf(filebook, "%d;", book[i].all);
        fprintf(filebook, "%d", book[i].available);

        if (i < q - 1)
            fprintf(filebook, "\n");
    }
    printf("����� ������\n");
    fclose(filebook);
}






bookbox* loadbackupbk(char* tablebook, int* q) { // �������� ���� �� �����
    char backupname[20];
    printf("������� �������� ����� ������, ������� �� ������ ���������: ");
    scanf("%[^\n]%*c", backupname);

    FILE* filebook = fopen(backupname, "r");


    if (filebook == 0) { // ���� �� ������� ������� ����
        printf("�� ������� ������� ���� '%s'\n", tablebook);
        *q = 0;
        return NULL; // ���������� ������ ���������
    }

    bookbox* book = (bookbox*)malloc(sizeof(bookbox)); // �������� ������ ��� ���� �������
    *q = 0; // ���������� ��������� ���

    while (feof(filebook) == 0) {
        fscanf(filebook, "%[^;]%*c", book[*q].isbn);
        fscanf(filebook, "%[^;]%*c", book[*q].author);
        fscanf(filebook, "%[^;]%*c;", book[*q].title);
        fscanf(filebook, "%d%*c", &book[*q].all);
        fscanf(filebook, "%d%*c", &book[*q].available);
        *q = *q + 1; // ����������� ������
        book = (bookbox*)realloc(book, (*q + 1) * sizeof(bookbox)); // ���������������� ������
    }

    fclose(filebook);

    printf("���� ������\n");
    return book; // ���������� ��������� ������
}

//-------------------------------------------------------������ � ������ ����------------------------------------------------------


void savebox(char* boxbk, bookbox* book, int q) {	 			 // ���������� ���� � ����

	if (q == 0) {



		printf("�� ����� ����� ��� �� ���������\n");
       		return 0;
       	}

	FILE* filebook = fopen(boxbk, "w"); 		 			 // ��������� ���� �� ������

	for (int i = 0; i < q; i++) {

		fprintf(filebook, "%s;", book[i].isbn);
		fprintf(filebook, "%s;", book[i].author);
		fprintf(filebook, "%s;", book[i].title);
		fprintf(filebook, "%d;", book[i].all);
		fprintf(filebook, "%d", book[i].available);

		if (i < q - 1) {

			fprintf(filebook, "\n");
		}
	}

	fclose(filebook); 				 			 // ��������� ����
}

bookbox* loadboxbook(char* boxbk, int* q) { 		 			 // �������� ���� �� �����

	FILE* filebook = fopen(boxbk, "r"); 		 			 // ��������� ���� �� ������

	if (filebook == 0) { 				 			 // ���� �� ������� ������� ����

		printf("�� ������� ������� ���� '%s'\n", boxbk);
		*q = 0;
		return NULL; 				 			 // ���������� ������ ���������
	}

	bookbox* book = (bookbox*)malloc(sizeof(bookbox)); 			 // �������� ������ ��� ���� �������

	*q = 0; 					 			 // ���������� ��������� ���


	while (feof(filebook) == 0) {

		fscanf(filebook, "%[^;]%*c", book[*q].isbn);
		fscanf(filebook, "%[^;]%*c", book[*q].author);
		fscanf(filebook, "%[^;]%*c;", book[*q].title);
		fscanf(filebook, "%d%*c", &book[*q].all);
		fscanf(filebook, "%d%*c", &book[*q].available);

		*q = *q + 1; 				 			 // ����������� ������

		book = (bookbox*)realloc(book, (*q + 1) * sizeof(bookbox)); 	 // ���������������� ������
	}

	fclose(filebook);

	return book; 								 // ���������� ��������� ������
}



//------------------------------------------------���������� �� ������ ��������----------------------------------------------------

void studinfo(studbox* student, int m, bookbox* book, int q, studbookbox* studbk, int l) {

	char nu[8];
	int marker = 0;

	printf("������� ����� �������� ������, ����� ����������� ��� ���������� � ����� ������: ");
		scanf("%[^\n]%*c", nu);

	printf("|    ISBN    |             ������             |       �������� ����       |  ���� ��������  \n");
	printf("|------------|--------------------------------|---------------------------|-----------------\n");

	for (int i = 0; i < m; i++) {

		if (strcmp(student[i].nu, nu) == 0) { 						// ���� ����� ��������

			for (int j = 0; j < l; j++) {

				if (strcmp(studbk[j].nu, nu) == 0) { 				// ���� ����� ����� � ��������

					for (int r = 0; r < q; r++) {

						if (strcmp(book[r].isbn, studbk[j].isbn) == 0) { // ����� ����� � ��������

							printf("| %-10s ", book[r].isbn);
							printf("| %-30s ", book[r].author);
							printf("| %-25s ", book[r].title);
							printf("| %d.%d.%d ", studbk[j].day, studbk[j].month, studbk[j].year);
							printf("\n");
						}
					}
				}
			}

			marker++;
		}
	}

	if (marker == 0) {
		printf("�������� � ������� ������� '%s' �� ����������\n", nu);
	}
}
