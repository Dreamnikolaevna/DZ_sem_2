#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

#include "./bookdb.h"
#include "./studbookdb.h"
#include "./users.h"
#include "./logs.h"


typedef struct studbox {

	char nu[8];		 // Nu �������
	char surname[20];        // �������
	char name[20];		 // ���
	char fathername[20];	 // ��������
	char faculty[4];	 // ���������
	char spec[60];		 // �����
} studbox;

//---------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------���������� ��� ������������ ��-----------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------���� ��������------------------------------------------------------------


void printstud(studbox student) { 					 	// ����� ��������

	printf("| %-9s ", student.nu);
	printf("| %-31s ", student.surname);
	printf("| %-15s ", student.name);
	printf("| %-24s ", student.fathername);
	printf("| %-9s ", student.faculty);
	printf("| %-30s ", student.spec);
	printf("|\n");
}

void printstudbox(studbox* student, int m) {				 	// ����� ���������

	if (m == 0) { 								// ���� ��� ��� ���������, �������� �� ����

		printf("�� ������ �������� ��� �� ���������\n");
		return;
	}

	printf("|   �����   |             �������             |       ���       |         ��������         | ��������� |         �������������          |\n");
	printf("|-----------|---------------------------------|-----------------|--------------------------|-----------|--------------------------------|\n");

	for (int i = 0; i < m; i++) {

		 printstud(student[i]);						//����� ������� ��������
	}
}

studbox read_stud() { 								// ������ ����� ���������� � ��������

	studbox student; 							// �������� ������ ��������

	printf("������� ����� �������� ������: ");
		scanf("%[^\n]%*c", student.nu);

	printf("������� ������� ��������: ");
		scanf("%[^\n]%*c", student.surname);

	printf("������� ��� ��������: ");
		scanf("%[^\n]%*c", student.name);

	printf("������� �������� ��������: ");
		scanf("%[^\n]%*c", student.fathername);

	printf("������� ��������� ��������: ");
		scanf("%[^\n]%*c", student.faculty);

	printf("������� ������������� ��������: ");
		scanf("%[^\n]%*c", student.spec);

	return student; 							// ���������� ���������� ��������
}


studbox* addstudent(studbox* student, int* m) { 				// ���������� ����� �����

	printf("������� ���������� � ����� ��������\n");
	studbox studentA = read_stud(); 					// ��������� ������

	for (int i = 0; i < *m; i++) {     					// �������� �� ������� ����� �� ������ �������

		if (!strcmp(student[i].nu, studentA.nu)) {

			printf("������� � ������� '%s' ��� �������\n", studentA.nu);
			return student;
        }
    }

    student = (studbox*)realloc(student, (*m + 1) * sizeof(studbox));
    student[*m] = studentA;
    (*m)++;

    return student; 								// ���������� ���������� ������
}


//--------------------------------------------------�������� ��������--------------------------------------------------------------


void delstud(studbox* student, int* m, studbookbox* studbk, int* l) { 		// �������� ��������

	if (m == 0) {

		printf("�� ������ �������� ��� �� ���������\n");
		return;
	}

	char nu[8];
	printf("������� ����� �������� ������ ��������, �������� ������ �������: ");
	scanf("%[^\n]%*c", &nu); 						// ��������� ���� ��� ������

	for (int i = 0; i < *l; i++) {

		if (strcmp(studbk[i].nu, nu) == 0) {

			printf("������ ������� ����� �����, ��� ���������� �������\n");
			return;
		}
	}

	int markerstud = 0; 							// ������ ��� ������ ����������
	int j = 0; 								// ����� ������ ��� ��������� ����� ��������

	for (int i = 0; i < *m; i++) {

		if (strcmp(student[i].nu, nu) != 0) {

			student[j++] = student[i];
		}

		else {

			markerstud = 1;
		}
	}

	if (markerstud == 0) {

		printf("�������� � ������� '%s' �� ����������\n", nu);
	}

	*m = j; 								// ��������� ������
}


//---------------------------------------------����� �������� �� �������----------------------------------------------------

void findstud(studbox* student, int m) { // ����� ��������
    char surname[25];
    int flagst = 0;
    printf("������� �������, �������� ������ �����: ");
    scanf("%[^\n]%*c", surname);

    printf("|   �����   |             �������             |       ���       |         ��������         | ��������� |         �������������          |\n");
    printf("|-----------|---------------------------------|-----------------|--------------------------|-----------|--------------------------------|\n");

    for (int i = 0; i < m; i++) {
        if (strcmp(student[i].surname, surname) == 0) { // ���� ����� ��������
            printstud(student[i]);
            flagst++;
        }
    }
    if (flagst == 0) {
        printf("�������� � �������� '%s' �� ����������\n", surname);
    }
}
//
//----------------------------------�����-------------------------------------------------------------------------------
//
void createbackupst(studbox* student, int m) { // ����� ��������� � ����
    char backupname[50] = { 0 };

    if (m == 0) {
        printf("�� ������ �������� ��� �� ���������\n");
        return 0;
    }

    struct tm* t;
    time_t timer = time(NULL);
    t = localtime(&timer); // ������� � ����� ��� � ��������� ��� � ���������

    strftime(backupname, 50, "students_%d_%m_%Y; %H_%M_%S.csv", t);

    FILE* filestud = fopen(backupname, "w");
    if (filestud == 0) { // ���� �� ������� ������� ����
        printf("�� ������� ������� ���� '%s'\n", backupname);
        return NULL; // ���������� ������ ���������
    }

    for (int i = 0; i < m; i++) {
        fprintf(filestud, "%s;", student[i].nu);
        fprintf(filestud, "%s;", student[i].surname);
        fprintf(filestud, "%s;", student[i].name);
        fprintf(filestud, "%s;", student[i].fathername);
        fprintf(filestud, "%s;", student[i].faculty);
        fprintf(filestud, "%s", student[i].spec);

        if (i < m - 1)
            fprintf(filestud, "\n");
    }
    printf("����� ������\n");
    fclose(filestud);
}

studbox* loadbackupst(char* tablest, int* m) { // �������� ��������� �� �����
    char backupname[20];
    printf("������� �������� ����� ������, ������� �� ������ ���������: ");
    scanf("%[^\n]%*c", backupname);

    FILE* filestud = fopen(backupname, "r");

    if (filestud == 0) { // ���� �� ������� ������� ����
        printf("�� ������� ������� ���� '%s'\n", backupname);
        *m = 0;
        return NULL; // ���������� ������ ���������
    }

    studbox* student = (studbox*)malloc(sizeof(studbox)); // �������� ������ ��� ���� �������
    *m = 0; // ���������� ��������� ���

    while (feof(filestud) == 0) {
        fscanf(filestud, "%[^;]%*c", student[*m].nu);
        fscanf(filestud, "%[^;]%*c", student[*m].surname);
        fscanf(filestud, "%[^;]%*c;", student[*m].name);
        fscanf(filestud, "%[^;]%*c", student[*m].fathername);
        fscanf(filestud, "%[^;]%*c", student[*m].faculty);
        fscanf(filestud, "%[^\n]%*c;", student[*m].spec);
        *m = *m + 1; // ����������� ������
        student = (studbox*)realloc(student, (*m + 1) * sizeof(studbox)); // ���������������� ������
    }

    fclose(filestud);
    printf("���� ������\n");
    return student; // ���������� ��������� ������
}










//---------------------------------------------������ � ������ ���������----------------------------------------------------------


void saveboxst(char* boxst, studbox* student, int m) { 					// ���������� ��������� � ����

	if (m == 0) {

		printf("�� ������ �������� ��� �� ���������\n");
		return 0;
	}

	FILE* filestud = fopen(boxst, "w");

	for (int i = 0; i < m; i++) {

		fprintf(filestud, "%s;", student[i].nu);
		fprintf(filestud, "%s;", student[i].surname);
		fprintf(filestud, "%s;", student[i].name);
		fprintf(filestud, "%s;", student[i].fathername);
		fprintf(filestud, "%s;", student[i].faculty);
		fprintf(filestud, "%s", student[i].spec);

		if (i < m - 1) {

			fprintf(filestud, "\n");
		}
	}

	fclose(filestud);
}

studbox* loadboxst(char* boxst, int* m) { 						// �������� ��������� �� �����

	FILE* filestud = fopen(boxst, "r");

	if (filestud == 0) { 								// ���� �� ������� ������� ����

		printf("�� ������� ������� ���� '%s'\n", boxst);
		*m = 0;
		return NULL; 								// ���������� ������ ���������
	}

	studbox* student = (studbox*)malloc(sizeof(studbox)); 				// �������� ������ ��� ���� �������

	*m = 0; 									// ���������� ��������� ���

	while (feof(filestud) == 0) {

		fscanf(filestud, "%[^;]%*c", student[*m].nu);
		fscanf(filestud, "%[^;]%*c", student[*m].surname);
		fscanf(filestud, "%[^;]%*c", student[*m].name);
		fscanf(filestud, "%[^;]%*c", student[*m].fathername);
		fscanf(filestud, "%[^;]%*c", student[*m].faculty);
		fscanf(filestud, "%[^\n]%*c", student[*m].spec);

		*m = *m + 1; 								// ����������� ������
		student = (studbox*)realloc(student, (*m + 1) * sizeof(studbox)); 	// ���������������� ������
	}

	fclose(filestud);
	return student; 								// ���������� ��������� ������
}

