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
#include "./studbookdb.h"
#include "./logs.h"














typedef struct userbox {
	char login[20];		 // Nu �������
	char password[20]; 	 // �������
	 int statusstud; 	 // ������ � ���������� ����������
	 int statusbook;	 // ������ � ���������� �������
} userbox;

//---------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------�����/������-------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------


userbox* loadboxuser(char* boxuser, int* k) { 						//�������� ������������� �� �����

	FILE* fileuser = fopen(boxuser, "r");

	if (fileuser == 0) { 								// ���� �� ������� ������� ����

		printf("�� ������� ������� ���� '%s'\n", boxuser);
		*k = 0;
		return NULL; 								// ���������� ������ ���������
	}

	userbox* user = (userbox*)malloc(sizeof(userbox)); 				// �������� ������ ��� ���� �������
	*k = 0; 									// ���������� ��������� ���

	while (feof(fileuser) == 0) {

		fscanf(fileuser, "%[^;]%*c", user[*k].login);
		fscanf(fileuser, "%[^;]%*c;", user[*k].password);
		fscanf(fileuser, "%d%*c", &user[*k].statusstud);
		fscanf(fileuser, "%d%*c", &user[*k].statusbook);

		*k = *k + 1; 								// ����������� ������

		user = (userbox*)realloc(user, (*k + 1) * sizeof(userbox)); 		// ���������������� ������
	}

	fclose(fileuser);
	return user; 									// ���������� ��������� ������

}
