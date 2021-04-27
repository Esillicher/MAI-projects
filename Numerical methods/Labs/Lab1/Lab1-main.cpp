#include "libs.h"

int main()
{
	SetConsoleOutputCP(1251);
	int choice = 1;
	while (choice)
	{
		cout << "Введите номер задания или 0 для выхода: ";
		cin >> choice;
		switch (choice)
		{
		case 0: cout << "Вопросов больше нет, но вы держитесь, вам всего доброго, хорошего настроения и здоровья." << endl; break;
		case 1: LU_main(); break;
		case 2: Tridiagonal_main(); break;
		case 3: SimpleIteration_main(); break;
		case 4: Yakobi_main(); break;
		default: cout << "Номер некорректен или это задание ещё в разработке." << endl;
		}
	}
	return 0;
}