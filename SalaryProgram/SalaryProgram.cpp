#pragma warning(disable : 4996) 
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstring>
#include <windows.h>
#include <stdlib.h>
#include <io.h>
#include "validation.h"
using namespace std;

struct Human // шаблон структуры 
{
	char FIO[30];
	int year;
	int group_number;
	double physics;
	double maths;
	double informatics;
	double chemistry;
	double s_ball;
};

int size = sizeof(Human); // размер записи
FILE* Fz, * Ft; // указатели файлов
char File_Zap[] = "zapisi.dat";
char File_Rez[] = "rezult.txt";
Human Stud;
void Out(Human);      //прототип функции
void Out_1(Human);
void View();

void main()
{
	setlocale(LC_ALL, "rus");
	int kod, // для выбора действия
		i = 0, // переменные
		D_f,
		kol; // кол-во записей
	long len; // объём файла
	int size = sizeof(Human);
	Human remStud, // элемент структуры
		* mas_Z; // указатель для массива 

	Ft = fopen(File_Rez, "w"); // открытие текстового файла для сохранения результатов

	while (true) {

		printf("\n\n\n\n\t---------------  | ГЛАВНОЕ МЕНЮ |  ---------------");
		printf("\n\n\t1 - Создать\n\t2 - Добавить\n\t3 - Просмотреть\n\t4 - Найти\n\t5 - Редактировать\n\t6 - Удалить\n\t7 - Индивидуальное задание (6)\n\t8 - Очистить\n\t0 - Выход\n");
		printf("\n\t---------------  | ------------ |  ---------------\n\n\n\t");

		scanf("%d", &kod);

		switch (kod) {
		case 0: // выход
		{
			fclose(Ft);
			exit(1);

		}
		case 1: // создание файла
		{
			system("cls");
			if ((Fz = fopen(File_Zap, "wb")) == NULL) {
				puts("\n\t Ошибка создания файла!\n");
				return;
			}
			fclose(Fz);
			puts("\n\n\tУспешное создание нового файла!\n");
			break;
		}
		case 2: // добавление записи 
		{
			system("cls");
			if ((Fz = fopen(File_Zap, "rb")) == NULL) {
				cout << "\n\t Ошибка открытия файла!\n" << endl;
				break;
			}

			int option;
			printf("\n\t1 - Добавить данные студента\n\t0 - Назад\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1: // добавить данные студента
			{
				Fz = fopen(File_Zap, "ab");
				printf("\n\tВведите Ф.И.О. - ");
				while (getchar() != '\n'); // очистка потока ввода
				gets_s(Stud.FIO);

				// год рождения
				cout << "\n\tВведите год рождения: ";
				Stud.year = inputNumber(LEFT_RANGE_OF_YEAR, RIGHT_RANGE_OF_YEAR);
				// номер группы
				cout << "\n\tВведите номер группы: ";
				Stud.group_number = inputNumber(LEFT_RANGE_OF_NUMBER, RIGHT_RANGE_OF_NUMBER);
				// физика
				cout << "\n\tОценка по физике: ";
				Stud.physics = inputNumber(LEFT_RANGE_OF_MARK, RIGHT_RANGE_OF_MARK);
				// математика
				cout << "\n\tОценка по математике: ";
				Stud.maths = inputNumber(LEFT_RANGE_OF_MARK, RIGHT_RANGE_OF_MARK);
				// информатика
				cout << "\n\tОценка по информатике: ";
				Stud.informatics = inputNumber(LEFT_RANGE_OF_MARK, RIGHT_RANGE_OF_MARK);
				// химия
				cout << "\n\tОценка по химии: ";
				Stud.chemistry = inputNumber(LEFT_RANGE_OF_MARK, RIGHT_RANGE_OF_MARK);

				Stud.s_ball = (Stud.physics + Stud.maths + Stud.informatics + Stud.chemistry) / 4;

				fwrite(&Stud, size, 1, Fz); // запись в файл
				fclose(Fz); //закрывает и разъединяет файл filestream
				system("cls");
				break;
			}
			case 0: // выход
				system("cls");
				break;
			default:
				printf("\n\tВы ввели некорректное число. Попробуйте ещё раз!");
				break;
			}
			break;
		}
		case 3: // просмотр 
		{
			system("cls");
			// открытие файла для чтения с проверкой
			if ((Fz = fopen(File_Zap, "rb")) == NULL) {
				cout << "\n\t Ошибка открытия файла!\n" << endl;
				break;
			}
			fclose(Ft);

			View(); // функция для просмотра студентов
			break;
		}
		case 4: // найти  
		{
			system("cls");
			// открытие файла для чтения с проверкой
			if ((Fz = fopen(File_Zap, "rb")) == NULL) {
				cout << "\n\t Ошибка открытия файла!\n" << endl;
				break;
			}
			fclose(Ft);

			int option;
			printf("\n\t1 - Найти данные студента\n\t0 - Назад\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1: // найти студента
			{
				Fz = fopen(File_Zap, "rb");
				D_f = fileno(Fz);
				len = filelength(D_f);
				kol = len / size;
				mas_Z = new Human[kol];
				for (int i = 0; i < kol; i++)
					fread((mas_Z + i), size, 1, Fz);
				fclose(Fz);

				Fz = fopen(File_Zap, "ab");

				printf("\n\n\tФ.И.О. искомого студента - ");
				while (getchar() != '\n');
				gets_s(remStud.FIO);
				// поиск данных студента
				int number;
				for (int i = 0; i < kol; i++)
				{
					bool verification = true;
					int count = 0;
					for (int j = 0; j < strlen(remStud.FIO); j++)
					{
						if (mas_Z[i].FIO[j] == remStud.FIO[j])
						{
							count++;
						}

						if (count == strlen(remStud.FIO))
						{
							verification = false;
						}
					}

					if (!verification)
					{
						number = i;
					}
				}

				for (int i = 0; i < kol; i++)
				{
					if (i == number)
					{
						printf("\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");
						fprintf(Ft, "\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");
						Out(mas_Z[i]);
					}
				}
				delete[]mas_Z;
				break;
			}
			case 0: // выход
				system("cls");
				break;
			default:
				printf("\n\tВы ввели некорректное число. Попробуйте ещё раз!");
				break;
			}
			break;
		}
		case 5: // редактировать
		{
			system("cls");
			// открытие файла для чтения с проверкой
			if ((Fz = fopen(File_Zap, "rb")) == NULL) {
				cout << "\n\t Ошибка открытия файла!\n" << endl;
				break;
			}
			fclose(Ft);

			View();

			int option;
			printf("\n\n\n\n\n\t1 - Редактировать данные студента\n\t0 - Назад\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1: // редактирование студента
			{
				Fz = fopen(File_Zap, "r");                //открытие файла для чтения
				len = filelength(fileno(Fz));               //присваивание переменной длину файла в байтах

				if (len == -1L)                 //проверка ( недействительный дескриптор файла )
				{
					return;
				}

				kol = len / size;                           //количество записей в файл
				mas_Z = new Human[kol];                        //создание динамического массива

				for (int i = 0; i < kol; i++)                      //считывает информацию в массив
					fread((mas_Z + i), size, 1, Fz);
				fclose(Fz);                                            //закрывает доступ к файлу и чистит буфер

				Fz = fopen(File_Zap, "ab");

				printf("\n\n\tВведите Ф.И.О. - ");
				while (getchar() != '\n');
				gets_s(remStud.FIO);
				// поиск данных студента
				int number;
				for (int i = 0; i < kol; i++)
				{
					bool verification = true;
					int count = 0;
					for (int j = 0; j < strlen(remStud.FIO); j++)
					{
						if (mas_Z[i].FIO[j] == remStud.FIO[j])
						{
							count++;
						}

						if (count == strlen(remStud.FIO))
						{
							verification = false;
						}
					}

					if (!verification)
					{
						number = i;
					}
				}
				printf("\n\n\n\n\t-------  | МЕНЮ РЕДАКТИРОВАНИЯ |  -------\n\t");
				puts("\n\t1 - Ф.И.О\n\t2 - Год рождения\n\t3 - Номер группы\n\t4 - Физика\n\t5 - Математика\n\t6 - Информатика\n\t7 - Химия\n\t0 - Отмена");
				printf("\n\t-------  | ------------------- |  -------\n\n\n\t");
				int key;
				scanf("%d", &key);
				switch (key)
				{
				case 1: // редактирование фамилии

					Fz = fopen(File_Zap, "w");
					Fz = fopen(File_Zap, "a");

					int j;
					for (int i = 0; i < kol; i++)
					{
						if (i == number)
						{
							printf("\n\tВведите Ф.И.О. - ");
							while (getchar() != '\n'); // очистка потока ввода
							gets_s(remStud.FIO);

							/*
							int compare; // сравнение
							if (strlen(mas_Z[i].FIO) > strlen(delStud.FIO))
							{
								compare = strlen(mas_Z[i].FIO);
							}
							else
							{
								compare = strlen(delStud.FIO);
							}
							*/

							int format = strlen(remStud.FIO);


							for (j = 0; j < format; j++)
							{
								mas_Z[i].FIO[j] = remStud.FIO[j];
							}

							mas_Z[i].FIO[j] = '\0';
						}

						fwrite(&mas_Z[i], size, 1, Fz);
						Out_1(mas_Z[i]);
						system("cls");
						printf("\n\tВы успешно отредактировали Ф.И.О студента!\n");
					}
					break;
				case 2: // редактирование даты рождения
				{

					Fz = fopen(File_Zap, "w");
					Fz = fopen(File_Zap, "a");

					for (int i = 0; i < kol; i++)
					{
						if (i == number)
						{
							printf("\n\tВведите дату рождения: ");
							cin >> remStud.year;
							mas_Z[i].year = remStud.year;
						}

						mas_Z[i].s_ball = (mas_Z[i].physics + mas_Z[i].maths + mas_Z[i].informatics + mas_Z[i].chemistry) / 4;

						fwrite(&mas_Z[i], size, 1, Fz);
						Out_1(mas_Z[i]);
						system("cls");
						printf("\n\tВы успешно отредактировали дату рождения студента!\n");
					}
					break;
				}
				case 3: // редактирование номера группы
				{
					Fz = fopen(File_Zap, "w");
					Fz = fopen(File_Zap, "a");

					for (int i = 0; i < kol; i++)
					{
						if (i == number)
						{
							printf("\n\tВведите номер группы: ");
							cin >> remStud.group_number;
							mas_Z[i].group_number = remStud.group_number;
						}

						mas_Z[i].s_ball = (mas_Z[i].physics + mas_Z[i].maths + mas_Z[i].informatics + mas_Z[i].chemistry) / 4;

						fwrite(&mas_Z[i], size, 1, Fz);
						Out_1(mas_Z[i]);
						system("cls");
						printf("\n\tВы успешно отредактировали номер группы студента!\n");
					}
					break;
				}
				case 4: // редактирование оценки по физике
				{
					Fz = fopen(File_Zap, "w");
					Fz = fopen(File_Zap, "a");

					for (int i = 0; i < kol; i++)
					{
						if (i == number)
						{
							printf("\n\tВведите оценку по физике: ");
							scanf("%lf", &remStud.physics);
							mas_Z[i].physics = remStud.physics;
						}

						mas_Z[i].s_ball = (mas_Z[i].physics + mas_Z[i].maths + mas_Z[i].informatics + mas_Z[i].chemistry) / 4;

						fwrite(&mas_Z[i], size, 1, Fz);
						Out_1(mas_Z[i]);
						system("cls");
						printf("\n\tВы успешно отредактировали оценку по физике студента!\n");
					}
					break;
				}
				case 5: // редактирование оценки по математике
				{
					Fz = fopen(File_Zap, "w");
					Fz = fopen(File_Zap, "a");

					for (int i = 0; i < kol; i++)
					{
						if (i == number)
						{
							printf("\n\tВведите оценку по математике: ");
							scanf("%lf", &remStud.maths);
							mas_Z[i].maths = remStud.maths;
						}
						mas_Z[i].s_ball = (mas_Z[i].physics + mas_Z[i].maths + mas_Z[i].informatics + mas_Z[i].chemistry) / 4;

						fwrite(&mas_Z[i], size, 1, Fz);
						Out_1(mas_Z[i]);
						system("cls");
						printf("\n\tВы успешно отредактировали оценку по математике студента!\n");
					}
					break;
				}
				case 6: // редактирование оценки по информатике
				{
					Fz = fopen(File_Zap, "w");
					Fz = fopen(File_Zap, "a");

					for (int i = 0; i < kol; i++)
					{
						if (i == number)
						{
							printf("\n\tВведите оценку по информатике: ");
							scanf("%lf", &remStud.informatics);
							mas_Z[i].informatics = remStud.informatics;
						}
						mas_Z[i].s_ball = (mas_Z[i].physics + mas_Z[i].maths + mas_Z[i].informatics + mas_Z[i].chemistry) / 4;

						fwrite(&mas_Z[i], size, 1, Fz);
						Out_1(mas_Z[i]);
						system("cls");
						printf("\n\tВы успешно отредактировали оценку по информатике студента!\n");
					}
					break;
				}
				case 7: // редактирование оценки по химии
				{
					Fz = fopen(File_Zap, "w");
					Fz = fopen(File_Zap, "a");

					for (int i = 0; i < kol; i++)
					{
						if (i == number)
						{
							printf("\n\tВведите оценку по химии: ");
							scanf("%lf", &remStud.chemistry);
							mas_Z[i].chemistry = remStud.chemistry;
						}
						mas_Z[i].s_ball = (mas_Z[i].physics + mas_Z[i].maths + mas_Z[i].informatics + mas_Z[i].chemistry) / 4;

						fwrite(&mas_Z[i], size, 1, Fz);
						Out_1(mas_Z[i]);
						system("cls");
						printf("\n\tВы успешно отредактировали оценку по химии студента!\n");
					}
					break;
				}
				case 0: // отмена
				{
					system("cls");
					break;
				}
				default:
				{
					system("cls");
					printf("\n\tВы ввели некорректное число. Попробуйте ещё раз!");
					break;
				}
				}

				fclose(Fz);
				delete[]mas_Z;
				break;
			}
			case 0: // выход из редактирования
				system("cls");
				break;
			default:
				printf("\n\tВы ввели некорректное число. Попробуйте ещё раз!");
				break;
			}
			break;
		}
		case 6: // удаление
		{
			system("cls");
			// открытие файла для чтения с проверкой
			if ((Fz = fopen(File_Zap, "rb")) == NULL) {
				cout << "\n\t Ошибка открытия файла!\n" << endl;
				break;
			}

			printf("\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");
			fprintf(Ft, "\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");

			while (1)
			{
				if (!fread(&Stud, size, 1, Fz)) break; // считывает из файла Fz по одной записи Zap 
				//до тех пор пока не дойдем до конца файла, т.е. пока результат функции fread не равен 0 
				Out(Stud); // вызов функции для вывода информации на экран и записи в текстовый файл
			}

			fclose(Fz); //закрывает и разъединяет файл filestream

			int option;
			printf("\n\n\n\n\n\t1 - Удалить данные студента\n\t0 - Назад\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1: // удалить студента

				Fz = fopen(File_Zap, "rb");
				len = filelength(fileno(Fz));

				if (len == -1L) // проверка
				{
					return;
				}

				kol = len / size;
				mas_Z = new Human[kol];

				for (int i = 0; i < kol; i++)
					fread((mas_Z + i), size, 1, Fz);
				fclose(Fz);

				Fz = fopen(File_Zap, "ab");
				printf("\n\n\tВведите Ф.И.О -  ");
				while (getchar() != '\n');
				gets_s(remStud.FIO);

				char input;
				while (true)
				{
					printf("\n\tВы действительно хотите удалить студента [Y(да)/N(нет)]? ");
					cin >> input;
					if (input == 'Y')
					{
						system("cls");
						Fz = fopen(File_Zap, "w");
						Fz = fopen(File_Zap, "a");

						for (int i = 0; i < kol; i++)
						{
							bool verification = true;
							int count = 0; // счетчик
							for (int j = 0; j < strlen(remStud.FIO); j++)
							{
								if (mas_Z[i].FIO[j] == remStud.FIO[j])
								{
									count++;
								}

								if (count == strlen(remStud.FIO))
								{
									verification = false;
								}
							}
							if (verification)
							{
								fwrite(&mas_Z[i], size, 1, Fz);
							}
						}
						puts("\n\n\tСтудент успешно удалён!\n");
						fclose(Fz);
						delete[]mas_Z;
						break;
					}
					if (input == 'N')
					{
						fclose(Fz);
						delete[]mas_Z;
						system("cls");
						break;
					}
				}
				break;

			case 0: // выход из удаления
				system("cls");
				break;
			default:
				printf("\n\tВы ввели некорректное число. Попробуйте ещё раз!");
				break;
			}
			break;
		}
		case 7: // индивидуальное задание
		{
			system("cls");
			Fz = fopen(File_Zap, "rb");
			//присваивание переменной длину файла в байтах
			D_f = fileno(Fz);
			len = filelength(D_f);
			kol = len / size;
			mas_Z = new Human[kol];
			for (int i = 0; i < kol; i++)
				fread((mas_Z + i), size, 1, Fz);
			fclose(Fz);
			printf("\n---— СОРТИРУЕМ ДАННЫЕ ФАМИЛИИ СТУДЕНТОВ, КОТОРЫЕ НАЧИНАЮТСЯ С БУКВ В, Г и Д ---—\n\n");
			printf("\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");

			fprintf(Ft, "\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");

			for (int i = 0; i < kol; i++)
			{
				if ((mas_Z[i].FIO[0] == 'В') || (mas_Z[i].FIO[0] == 'Г') || (mas_Z[i].FIO[0] == 'Д'))
				{
					Out(mas_Z[i]);
				}
				if ((mas_Z[i].FIO[0] == 'в') || (mas_Z[i].FIO[0] == 'г') || (mas_Z[i].FIO[0] == 'д'))
				{
					Out(mas_Z[i]);
				}
			}
			delete[]mas_Z;
			break;
		}
		case 8: // очистить консоль
		{
			system("cls");
			break;
		}
		default:
		{
			system("cls");
			puts("\n\tВведите корректное значение!\n");
			break;
		}
		}
	}
}
// функция вывода на экран данных студента
void Out(Human z)
{
	printf("\n %29s  %15.d %20.d %15.f %15.f %20.f %15.f %15.1f ", z.FIO, z.year, z.group_number, z.physics, z.maths, z.informatics, z.chemistry, z.s_ball);
	fprintf(Ft, "\n % 29s % 15.d %20.d % 15.f % 15.f % 20.f % 15.f % 15.1f ", z.FIO, z.year, z.group_number, z.physics, z.maths, z.informatics, z.chemistry, z.s_ball);
}
// функция вывода на экран данных студента
void Out_1(Human z)
{
	fprintf(Ft, "\n % 29s % 15.d %20.d % 15.f % 15.f % 20.f % 15.f % 15.1f ", z.FIO, z.year, z.group_number, z.physics, z.maths, z.informatics, z.chemistry, z.s_ball);
}
// функция для просмотра студентов
void View()
{
	int size = sizeof(Human);

	Ft = fopen(File_Rez, "w");
	Ft = fopen(File_Rez, "a");

	printf("\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");
	fprintf(Ft, "\n             Ф.И.О.                   ГОД РОЖДЕНИЯ        НОМЕР ГРУППЫ         ФИЗИКА         МАТЕМАТИКА          ИНФОРМАТИКА        ХИМИЯ      СРЕДНИЙ БАЛЛ\n");

	while (1)
	{
		if (!fread(&Stud, size, 1, Fz)) break; // считывает из файла Fz по одной записи Zap 
		//до тех пор пока не дойдем до конца файла, т.е. пока результат функции fread не равен 0 
		Out(Stud); // вызов функции для вывода информации на экран и записи в текстовый файл
	}
	fclose(Fz); //закрывает и разъединяет файл filestream
}