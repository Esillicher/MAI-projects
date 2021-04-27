/*Conway's Game of Life.
Правила:
1) в пустой (мёртвой) клетке, рядом с которой ровно три живые клетки, зарождается жизнь;
2) если у живой клетки есть две или три живые соседки, клетка продолжает жить; иначе клетка умирает.

Управление:
N - число строк поля;
M - число столбцов поля;
int field1[N][M] - массив для задания начальной конфигурации;
enter, space - следующая итерация;
esc - выход.

Функциональность:
управление клавишами;
произвольный размер поля (чётность значения не имеет);
отслеживание условий завершения игры: смерть клеток, стабильная конфигурация, циклическая конфигурация (только чередование);
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int const N = 10, M = 10;
int field1[N][M] = {
	{ 0, 2, 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
	{ 0, 2, 1, 0, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 2, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 2, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 2, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
int field2[N][M] = { 1 };

void print(int step);
void printtable(int field[N][M]);
int living_neighbours(int field[N][M], int i, int j);
void nextstate(int from[N][M], int to[N][M], int *exitcode);

int main()
{
	setlocale(LC_ALL, "Russian");
	system("title Игра \"Жизнь\"");
	int step = 0, exitcode = 0;
	int symb;

	print(step);
	while ((symb = _getch()) != 27)
	{
		if (symb == 13 || symb == ' ')
		{
			++step;
			if (step % 2)
				nextstate(field1, field2, &exitcode);
			else
				nextstate(field2, field1, &exitcode);
		}

		system("cls");
		print(step);

		if (exitcode)
			break;
	}

	switch (exitcode)
	{
	case 0:
		cout << "Вы вышли из игры." << endl;
		break;
	case 1:
		cout << "Все клетки погибли. Конец игры." << endl;
		break;
	case 2:
		cout << "Сформировалась стабильная конфигурация. Конец игры." << endl;
		break;
	case 3:
		cout << "Стоило добавить парочку живых клеток. Конец игры." << endl;
		break;
	case 4:
		cout << "Сформировалась периодическая конфигурация. Конец игры." << endl;
		break;
	default:
		cout << "Неизвестная причина остановки игры (" << exitcode << "). Воспользуйтесь отладчиком." << endl;
	}

	return 0;
}

void print(int step)
{
	if (!step)
		cout << "Исходное состояние поля:" << endl;
	else
		cout << step << "-ая итерация:" << endl;

	if (!(step % 2))
		printtable(field1);
	else
		printtable(field2);
}

void printtable(int field[N][M])
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (field[i][j] == 0 || field[i][j] == 1)
			{
				if (field[i][j] == 1)
					cout << '0';

				else
					cout << '.';
			}
		}
		cout << endl;
	};
}

int living_neighbours(int field[N][M], int i, int j)
{
	int summ = 0;
	if (field[i][j] == 0 || field[i][j] == 1)
	{

		if (i != N - 1)	//вниз
		{
			if (field[i + 1][j] == 1)
				summ += field[i + 1][j];
		}

		if (i != N - 1 && j != M - 1) //вниз вправо
		{
			if (field[i + 1][j + 1] == 1)
				summ += field[i + 1][j + 1];
		}

		if (j != M - 1) //вправо
		{
			if (field[i][j + 1] == 1)
				summ += field[i][j + 1];
		}

		if (i != 0 && j != M - 1) //вверх вправо
		{
			if (field[i - 1][j + 1] == 1)
				summ += field[i - 1][j + 1];
		}

		if (i != 0) //вверх
		{
			if (field[i - 1][j] == 1)
				summ += field[i - 1][j];
		}

		if (i != 0 && j != 0) //вверх влево
		{
			if (field[i - 1][j - 1] == 1)
				summ += field[i - 1][j - 1];
		}

		if (j != 0) //влево
		{
			if (field[i][j - 1] == 1)
				summ += field[i][j - 1];
		}

		if (i != N - 1 && j != 0) //вниз влево
		{
			if (field[i + 1][j - 1] == 1)
				summ += field[i + 1][j - 1];

			summ += 0;
		}


		//углы
		if (i == 0 && j == 0)
		{
			if (field[N - 1][M - 1] == 1)
				summ -= field[N - 1][M - 1];

			summ += 0;
		}
		if (i == N - 1 && j == M - 1)
		{
			if (field[0][0] == 1)
				summ -= field[0][0];

			summ += 0;
		}
		if (i == 0 && j == M - 1)
		{
			if (field[N - 1][0] == 1)
				summ -= field[N - 1][0];

			summ += 0;
		}

		if (i == N - 1 && j == 0)
		{
			if (field[0][M - 1] == 1)
				summ -= field[0][M - 1];

			summ += 0;
		}

	}
	return summ;
}

void nextstate(int from[N][M], int to[N][M], int *exitcode)
{
	bool allzero = true, allsame = true, prevstate = true;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			
			int summ = living_neighbours(from, i, j);

			if ((from[i][j] == 0 && summ == 3) || (from[i][j] == 1 && (summ == 3 || summ == 2)))
			{
				if (to[i][j] == 0)
					prevstate = false;

				to[i][j] = 1;
				allzero = false;
			}
			else
			{
				if (to[i][j] == 1)
					prevstate = false;

				to[i][j] = 0;
			}

			if (from[i][j] != to[i][j])
				allsame = false;
		}
	}

	if (allzero)
		++*exitcode;
	if (allsame)
		*exitcode += 2;
	if (prevstate)
		*exitcode += 4;
}