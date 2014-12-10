#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

//матрицы расстояний и послдователей
vector<vector<long>> A, S;
//массив стостояний - удалена ли вершина?
vector<long> removed;
//Массив соседей для конкретной вершины
vector<long> neighbohoor;

//Массив БАЗЫ. БАЗА - элементы, в котором точно установлено кратчайшие пути
vector<long> base;

long N;
//Размерность

const long gMax = 100;
const long pMax = 100000;
//Ищем вершину с минимальным количеством смежных вершин с остальными вершинами
//которые ещё не были удалены
long findMinVert()
{
	long Min = N, iMin;
	//Находим первую неудаленную вершину. Ставим его начальной точкой приближения
	for (int i = 1; i <= N; i++)
		if (removed[i] == 0)
		{
			iMin = i;
			break;
		}

	for (int i = 1; i <= N; i++)
	{
		if (removed[i] == 0)
		{
			long count = 0;
			for (int j = 1; j <= N; j++)
			{
				if (removed[j] == 0 && A[i][j] < pMax)
					count++;
			}
			if (count < Min){
				Min = count;
				iMin = i;
			}
		}
	}
	return iMin;
}

//Генерация графа, точнее матрицы
//Граф неориентированный
void generation()
{
	srand(time(NULL));
	for (int i = 1; i <= N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			if (rand() % 100 > 40) {
				A[i][j] = pMax;
				A[j][i] = pMax;
			}
			else {
				A[i][j] = rand() % gMax + 51;
				A[j][i] = A[i][j];

			}
		}
	}
}

//Здесь мы инициализируем матрицы
void init()
{
	//Очистка переменных
	A.clear();
	S.clear();
	removed.clear();
	base.clear();

	A.resize(N + 1);
	S.resize(N + 1);
	removed.resize(N + 1, 0);

	for (int i = 1; i <= N; i++)
	{
		A[i].resize(N + 1);
		S[i].resize(N + 1, 0);
		for (int j = 1; j <= N; j++) 
		{
			if (A[i][j] < 0)
				A[i][j] = pMax;
		}
	}
	generation();
}


// Собственно говоря, само решение
void solve()
{
	//Процесс удаления вершин
	//p - порядковый номер удаления вершин
	for (int p = 1; p < N - 1; p++)
	{
		// Вершина, которую будем удалять
		long Min = findMinVert();
		removed[Min] = p;
		
		//находим все смежные вершины, которые ещё не удалены
		neighbohoor.clear();
		for (int i = 1; i < N; i++)
		{
			// существует путь
			if (removed[i] == 0 && A[Min][i] < pMax)
				neighbohoor.push_back(i);
		}
		
		//пробегаем по всем из них, смотрим, не выполняется ли правило треугольника
		vector<long>::iterator I, J;
		for (I = neighbohoor.begin(); I != neighbohoor.end(); I++)
		{
			for (J = neighbohoor.begin(); J != neighbohoor.end(); J++)
			{
				
				//не выполняется правило треугольника
				if (A[*I][*J] > A[*I][Min] + A[Min][*J])
					A[*I][*J] = A[*I][Min] + A[Min][*J];
			}
		}
	}
	
	for (int i = 1; i <= N; i++)
		if (removed[i] == 0)
			base.push_back(i);

	//Процесс обратной вставки вершин
	for (int p = N - 2; p > 0; p--)
	{
		//найти вершину, которую удалили в p-той итерации
		long Insert = -1;
		for (int i = 1; i <= N; i++)
			if (removed[i] == p)
				Insert = i;
		if (Insert < 0)
		{
			cout << "error: Insert index not found";
			return;
		}
		
		//Восстанавливаем статус вершины в неудаленную
		removed[Insert] = 0;

		vector<long>::iterator I, J;
		for (I = base.begin(); I != base.end(); I++)
		{
			for (J = base.begin(); J != base.end(); J++)
			{
				if (A[Insert][*I] > A[Insert][*J] + A[*J][*I])
					A[Insert][*I] = A[Insert][*J] + A[*J][*I];
			}
		}
		base.push_back(Insert);
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			A[i][j] = min(A[i][j], A[j][i]);
			//printf("%d\t", A[i][j]);
		}
		//printf("\n");
	}
}

void solveFloid()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++)
				A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
}

int main()
{
	while (1) {
		cin >> N;
		init();
		long timeStart = clock();
		solve();
		long timeNew = (clock() - timeStart), timeFloid;
		cout <<  timeNew / (double)CLOCKS_PER_SEC << "\t\t - new Algorithm\n";
		init();
		timeStart = clock();
		solveFloid();
		timeFloid = (clock() - timeStart);
		cout << timeFloid / (double)CLOCKS_PER_SEC << "\t\t - Floid Alogorithm\n";
		cout << 100 - (timeNew * 100) / (double)timeFloid << "\t\t  - Acceleration\n";
		cout << "=============================\n";
	}
	return 0;

}