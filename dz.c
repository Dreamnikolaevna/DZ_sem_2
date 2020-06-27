//Максимова Дарья ИУ4-22Б
//Вариант 10 ( 4 для первого файла, 6 для второго)


//Задачи 1,2,3:

//Добавление книг +
//Удаление книг +
//Найти книгу по автору +
//Сделать бэкап +
//Загрузить бэкап +

//Сверх нормы:
//Выдача книг на руки +
//Принятие книг +

//Добавить студента +
//удалить студента +
//Посмотреть информацию по студенту по фамилии +
//Сделать бэкап +
//Загрузить бэкап +

//Логин&&Пароль +
//Меню с доступом +

//Логи +

//Коментарии к 3 сложности:

//Нельзя удалить студента, у которого есть книги +
//Нельзя удалить книгу, которая есть у студентов +
//Нельзя изменять ISBN книг и номер зачетки студентов
//Каждый студент может посмотреть информацию по всем его книгам +
//Для каждой книги можно посмотреть информацию по студентам, которые ее взяли +
//При выдаче и сдаче книги студенту пользователь должен указать ISBN книги и номер зачетки студента +
//Если нет доступных книг для выдачи, необходимо выводить сообщение – когда будет сдана ближайшая книга +


//------------------------------------Подключаем библиотеки и наши заголовочные файлы-----------------------------------------------------------------------


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
	int basemarkA = 0, basemarkB = 0, basemarkC = 0;			//Флаги для проверки на изменение базы данных

	int m = 0, q = 0, k = 0, l = 0; 					// количество элементов в массиве
	char log[20], pass[20]; 						// логин и пароль

	studbox* student = loadboxst("students.csv", &m); 			// массив студентов
	bookbox* book = loadboxbook("books.csv", &q); 				// массив книг
	userbox* user = loadboxuser("users.csv", &k); 				// массив пользователей
	studbookbox* studbk = loadstudb("student_books.csv", &l); 		// массив студентов имеющих книги

	int lvl = 0; 								// уровень доступа к БД (1 - студенты, 2 - книги)
	int admlvl = 0; 							// уровень доступа к двум БД
	int pointstud, pointbook, pointadmin; 					// выбираемый пункт меню

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("Введите логин: ");
		scanf("%[^\n]%*c", log); 					// считываем логин

	printf("Введите пароль: ");
		scanf("%[^\n]%*c", pass); 					// считываем пароль

	printf("\n");

	for (int i = 0; i < k; i++) {

		if ((strcmp(user[i].login, log) == 0) && (strcmp(user[i].password, pass) == 0) && (user[i].statusstud == 1) && (user[i].statusbook == 0)) { //Сравниваем введенные логин и пароль с существующими в файле
																				// А так же, проверяем на доступ к базам данных
																				// 1 = есть доступ, 0 = нет доступа

			lvl = 1; 						// Выдаем 1 lvl, что значит - доступ только к базе данных студентов
			break;
		}

		else if ((strcmp(user[i].login, log) == 0) && (strcmp(user[i].password, pass) == 0) && (user[i].statusstud == 0) && (user[i].statusbook== 1)) {

			lvl = 2;						// Выдаем 2 lvl, что значит - доступ только к базе данных книг
			break;
		}

		else if ((strcmp(user[i].login, log) == 0) && (strcmp(user[i].password, pass) == 0) && (user[i].statusstud == 1) && (user[i].statusbook == 1)) {

			admlvl = 1;						// Выдаем 1 admin lvl, что значит - доступ к обоим базам данных
			break;
		}
	}

	if ((lvl == 0) && (admlvl == 0)) {					// Если lvl и admin lvl не изменились(остались равными нулю, то следовательно, такого пользователя не существует или у него нет доступа ни к чему

		printf("Такого пользователя не существует\n");
	       	free(user);
		free(student);
		free(book);
		free(studbk);

		return 0;
	}

	while (1) {

		if ((admlvl == 1) && (lvl == 0)) {

			printf("Меню доступа к БД\n");
			printf("1. База данных студентов библиотеки\n");
			printf("2. База данных книг библиотеки\n");
			printf("Выберите базу данных > ");
			scanf("%d%*c", &pointadmin); 				// считываем пункт меню

			while ((pointadmin < 1) || (pointadmin > 2)) { 		// проверка на верность введенного пункта меню

				printf("Неверный пункт меню, попробуйте еще раз > ");
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
				printf("Меню операций со студентами\n");
				printf("1. Вывод списка студентов\n");
				printf("2. Добавить нового студента\n");
				printf("3. Удалить студента\n");
				printf("4. Поиск студента по фамилии\n");
				printf("5. Информация о книгах студента\n");
				printf("6. Сделать бэкап\n");
				printf("7. Загрузить из бэкапа\n");
				printf("8. Сохранить и выйти\n");

				if (admlvl == 1) {

					printf("0. Выйти к меню с выбором БД\n");
				}

				printf("Введите пункт меню > ");
				scanf("%d%*c", &pointstud); 			// считываем пункт меню

				while (((pointstud < 1) || (pointstud > 8)) && (pointstud != 0)) {
										// проверка на верность введенного пункта меню

					printf("Неверный пункт меню, попробуйте еще раз > ");
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
							saveboxst("students.csv", student, m); // сохраняем студентов в файл
						}
						if (basemarkB != 0) {
							savestudb("student_books.csv", studbk, l);
						}
						logging(log, "save_student_changes");

						free(user);
						free(student);
						free(book);
						free(studbk); 					// освобождаем динамическую память
						return 0;

				}

				printf("\n");

			} while (pointstud != 0); 						// повторяем, пока не решим выйти

			logging(log, "back_to_main_menu");
			lvl = 0;
		}

		if (lvl == 2 ) {

			do {

				printf("Вы находитесь в базе данных книг библиотеки!\n");
				printf("1. Вывод всей библиотеки\n");
				printf("2. Добавить новую книгу в библиотеку\n");
				printf("3. Удалить книгу из библиотеки\n");
				printf("4. Получение книги\n");
				printf("5. Возврат книги\n");
				printf("6. Информация о владельцах книги\n");
				printf("7. Найти книгу по автору\n");
				printf("8. Сделать бэкап\n");
				printf("9. Загрузится из бэкапа\n");
				printf("10. Сохранить и выйти\n");

				if (admlvl == 1) {

					printf("0. Выйти к меню с выбором БД\n");
				}

				printf("Введите пункт меню > ");
					scanf("%d%*c", &pointbook); 		// считываем пункт меню

				while (((pointbook < 1) || (pointbook > 10)) && (pointbook != 0)) {
										// проверка на верность введенного пункта меню

					printf("Неверный пункт меню, попробуйте еще раз: ");
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
							savebox("books.csv", book, q); 	// сохраняем книги в файл
						}
						if (basemarkB != 0) {
							savestudb("student_books.csv", studbk, l);
						}
						logging(log, "save_book_changes");

						free(user);
						free(student);
						free(book);
						free(studbk); 				// освобождаем динамическую памят
						return 0;

				}

				printf("\n");

			} while (pointbook != 0);	 				// повторяем, пока не решим выйти

			logging(log, "back_to_main_menu");
			lvl = 0;
		}


	}


}
