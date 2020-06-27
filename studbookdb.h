#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

#include "./bookdb.h"
#include "./studdb.h"
#include "./users.h"
#include "./logs.h"











typedef struct studbookbox{
	char isbn[15];		 // ISBN
	char nu[8]; 		 // Nu �������
	 int day; 		 // ���� �����
	 int month; 		 // ����� �����
	 int year; 		 // ��� �����
} studbookbox;

//---------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------������ � students_books.csv-------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------

studbookbox* loadstudb(char* studb, int* l) { 						// �������� ������ ���� �� �����

	FILE* filestudb = fopen(studb, "r");

	if (filestudb == 0) { 								// ���� �� ������� ������� ����

		printf("�� ������� ������� ���� '%s'\n", studb);
		*l = 0;
		return NULL; 								// ���������� ������ ���������
	}

	studbookbox* studbk = (studbookbox*)malloc(sizeof(studbookbox)); 			// �������� ������ ��� ���� �������
	*l = 0; 									// ���������� ��������� ���

	while (feof(filestudb) == 0) {

		fscanf(filestudb, "%[^;]%*c", studbk[*l].isbn);
		fscanf(filestudb, "%[^;]%*c;", studbk[*l].nu);
		fscanf(filestudb, "%d%*c", &studbk[*l].day);
		fscanf(filestudb, "%d%*c", &studbk[*l].month);
		fscanf(filestudb, "%d%*c", &studbk[*l].year);

		*l = *l + 1; 								// ����������� ������
		studbk = (studbookbox*)realloc(studbk, (*l + 1) * sizeof(studbookbox)); 	// ���������������� ������
	}

	fclose(filestudb);
	return studbk; 									// ���������� ��������� ������
}

void savestudb(char* studb, studbookbox* studbk, int l) { 					// ���������� ������ ���� � ����

	FILE* filestudb = fopen(studb, "w");

	for (int i = 0; i < l; i++) {

		fprintf(filestudb, "%s;", studbk[i].isbn);
		fprintf(filestudb, "%s;", studbk[i].nu);
		fprintf(filestudb, "%d.", studbk[i].day);
		fprintf(filestudb, "%d.", studbk[i].month);
		fprintf(filestudb, "%d", studbk[i].year);

		if (i < l - 1) {

			fprintf(filestudb, "\n");
		}
	}

	fclose(filestudb);
}

