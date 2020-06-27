//��������� ����� ��4-22�
//������� 10 ( 4 ��� ������� �����, 6 ��� �������)


//������ 1,2,3:

//���������� ���� +
//�������� ���� +
//����� ����� �� ������ +
//������� ����� +
//��������� ����� +

//����� �����:
//������ ���� �� ���� +
//�������� ���� +

//�������� �������� +
//������� �������� +
//���������� ���������� �� �������� �� ������� +
//������� ����� +
//��������� ����� +

//�����&&������ +
//���� � �������� +

//���� +

//���������� � 3 ���������:

//������ ������� ��������, � �������� ���� ����� +
//������ ������� �����, ������� ���� � ��������� +
//������ �������� ISBN ���� � ����� ������� ���������
//������ ������� ����� ���������� ���������� �� ���� ��� ������ +
//��� ������ ����� ����� ���������� ���������� �� ���������, ������� �� ����� +
//��� ������ � ����� ����� �������� ������������ ������ ������� ISBN ����� � ����� ������� �������� +
//���� ��� ��������� ���� ��� ������, ���������� �������� ��������� � ����� ����� ����� ��������� ����� +


//------------------------------------���������� ���������� � ���� ������������ �����-----------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

#include "./bookdb.h"
#include "./studdb.h"
#include "./studbookdb.h"
#include "./users.h"
#include "./logs.h"




//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------

int main() {
	int basemarkA = 0, basemarkB = 0, basemarkC = 0;			//����� ��� �������� �� ��������� ���� ������

	int m = 0, q = 0, k = 0, l = 0; 					// ���������� ��������� � �������
	char log[20], pass[20]; 						// ����� � ������

	studbox* student = loadboxst("students.csv", &m); 			// ������ ���������
	bookbox* book = loadboxbook("books.csv", &q); 				// ������ ����
	userbox* user = loadboxuser("users.csv", &k); 				// ������ �������������
	studbookbox* studbk = loadstudb("student_books.csv", &l); 		// ������ ��������� ������� �����

	int lvl = 0; 								// ������� ������� � �� (1 - ��������, 2 - �����)
	int admlvl = 0; 							// ������� ������� � ���� ��
	int pointstud, pointbook, pointadmin; 					// ���������� ����� ����

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("������� �����: ");
		scanf("%[^\n]%*c", log); 					// ��������� �����

	printf("������� ������: ");
		scanf("%[^\n]%*c", pass); 					// ��������� ������

	printf("\n");

	for (int i = 0; i < k; i++) {

		if ((strcmp(user[i].login, log) == 0) && (strcmp(user[i].password, pass) == 0) && (user[i].statusstud == 1) && (user[i].statusbook == 0)) { //���������� ��������� ����� � ������ � ������������� � �����
																				// � ��� ��, ��������� �� ������ � ����� ������
																				// 1 = ���� ������, 0 = ��� �������

			lvl = 1; 						// ������ 1 lvl, ��� ������ - ������ ������ � ���� ������ ���������
			break;
		}

		else if ((strcmp(user[i].login, log) == 0) && (strcmp(user[i].password, pass) == 0) && (user[i].statusstud == 0) && (user[i].statusbook== 1)) {

			lvl = 2;						// ������ 2 lvl, ��� ������ - ������ ������ � ���� ������ ����
			break;
		}

		else if ((strcmp(user[i].login, log) == 0) && (strcmp(user[i].password, pass) == 0) && (user[i].statusstud == 1) && (user[i].statusbook == 1)) {

			admlvl = 1;						// ������ 1 admin lvl, ��� ������ - ������ � ����� ����� ������
			break;
		}
	}

	if ((lvl == 0) && (admlvl == 0)) {					// ���� lvl � admin lvl �� ����������(�������� ������� ����, �� �������������, ������ ������������ �� ���������� ��� � ���� ��� ������� �� � ����

		printf("������ ������������ �� ����������\n");
	       	free(user);
		free(student);
		free(book);
		free(studbk);

		return 0;
	}

	while (1) {

		if ((admlvl == 1) && (lvl == 0)) {

			printf("���� ������� � ��\n");
			printf("1. ���� ������ ��������� ����������\n");
			printf("2. ���� ������ ���� ����������\n");
			printf("�������� ���� ������ > ");
			scanf("%d%*c", &pointadmin); 				// ��������� ����� ����

			while ((pointadmin < 1) || (pointadmin > 2)) { 		// �������� �� �������� ���������� ������ ����

				printf("�������� ����� ����, ���������� ��� ��� > ");
				scanf("%d%*c", &pointadmin);
			}

			switch (pointadmin) {

				case 1: lvl = 1;
					logging(log, "stud_menu_move");
					break;

				case 2: lvl = 2;
					logging(log, "book_menu_move");
					break;
			}

			printf("\n");

		}

		if (lvl == 1) {

			do {
				printf("���� �������� �� ����������\n");
				printf("1. ����� ������ ���������\n");
				printf("2. �������� ������ ��������\n");
				printf("3. ������� ��������\n");
				printf("4. ����� �������� �� �������\n");
				printf("5. ���������� � ������ ��������\n");
				printf("6. ������� �����\n");
				printf("7. ��������� �� ������\n");
				printf("8. ��������� � �����\n");

				if (admlvl == 1) {

					printf("0. ����� � ���� � ������� ��\n");
				}

				printf("������� ����� ���� > ");
				scanf("%d%*c", &pointstud); 			// ��������� ����� ����

				while (((pointstud < 1) || (pointstud > 8)) && (pointstud != 0)) {
										// �������� �� �������� ���������� ������ ����

					printf("�������� ����� ����, ���������� ��� ��� > ");
					scanf("%d%*c", &pointstud);
				}

				switch (pointstud) {


					case 1:
						printstudbox(student, m);
						logging(log, "print_students_table");
						break;

					case 2:
						student = addstudent(student, &m);
						logging(log, "add_student");
						basemarkA++;
						break;

					case 3:
						delstud(student, &m, studbk, &l);
						logging(log, "delete_student");
						basemarkA++;
						break;


					case 4:
						findstud(student, m);
						logging(log, "find_student");
						break;

					case 5:
						studinfo(student, m, book, q, studbk, l);
						logging(log, "student_info");
						break;
			                case 6:
                    				createbackupst(student, m);
                    				logging(log, "createbackupst");
                   				break;

					case 7:

						loadbackupst(student, &m);
                    				logging(log, "loadbackupst");
                    				break;

					case 8:
						if (basemarkA != 0){
							saveboxst("students.csv", student, m); // ��������� ��������� � ����
						}
						if (basemarkB != 0) {
							savestudb("student_books.csv", studbk, l);
						}
						logging(log, "save_student_changes");

						free(user);
						free(student);
						free(book);
						free(studbk); 					// ����������� ������������ ������
						return 0;

				}

				printf("\n");

			} while (pointstud != 0); 						// ���������, ���� �� ����� �����

			logging(log, "back_to_main_menu");
			lvl = 0;
		}

		if (lvl == 2 ) {

			do {

				printf("�� ���������� � ���� ������ ���� ����������!\n");
				printf("1. ����� ���� ����������\n");
				printf("2. �������� ����� ����� � ����������\n");
				printf("3. ������� ����� �� ����������\n");
				printf("4. ��������� �����\n");
				printf("5. ������� �����\n");
				printf("6. ���������� � ���������� �����\n");
				printf("7. ����� ����� �� ������\n");
				printf("8. ������� �����\n");
				printf("9. ���������� �� ������\n");
				printf("10. ��������� � �����\n");

				if (admlvl == 1) {

					printf("0. ����� � ���� � ������� ��\n");
				}

				printf("������� ����� ���� > ");
					scanf("%d%*c", &pointbook); 		// ��������� ����� ����

				while (((pointbook < 1) || (pointbook > 10)) && (pointbook != 0)) {
										// �������� �� �������� ���������� ������ ����

					printf("�������� ����� ����, ���������� ��� ���: ");
				 		scanf("%d%*c", &pointbook);
				}

				switch (pointbook) {



					case 1:
						printbookbox(book, q);
						logging(log, "print_book_table");
						break;

					case 2:
						book = createbook(book, &q);
						logging(log, "add_book");
						basemarkC++;
						break;

					case 3:
						deletebook(book, &q, studbk, &l);
						logging(log, "delete_book");
						basemarkC++;
						break;

					case 4:
						givebook(book, q, student, &m, studbk, &l);
						logging(log, "giveout_book");
						basemarkB++;
						basemarkC++;
						break;

					case 5:
						returnbook(book, q, student, &m, studbk, &l);
						logging(log, "return_book");
						basemarkB++;
						basemarkC++;
						break;
					case 6:
						bookinfo(student, m, book, q, studbk, l);
						logging(log, "book_info");
						break;

					case 7:

						findbooksurname(book, q);
                   	 			logging(log, "findbookauthor");
                    				break;


					case 8:
						createbackupbk(book, q);
                    				logging(log, "createbackupbooks");
                    				break;


					case 9:
						loadbackupbk(book, &q);
                    				logging(log, "loadbackupbooks");
                    				break;



					case 10:
						if (basemarkC != 0) {
							savebox("books.csv", book, q); 	// ��������� ����� � ����
						}
						if (basemarkB != 0) {
							savestudb("student_books.csv", studbk, l);
						}
						logging(log, "save_book_changes");

						free(user);
						free(student);
						free(book);
						free(studbk); 				// ����������� ������������ �����
						return 0;

				}

				printf("\n");

			} while (pointbook != 0);	 				// ���������, ���� �� ����� �����

			logging(log, "back_to_main_menu");
			lvl = 0;
		}


	}


}
