#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#define WR printf
#define FOR(i, k, n) for(long i = (k); i <= (n); i ++)
using namespace std;

//матрицы расстояний и послдователей
vector<vector<long>> A, S;

//массив стостояний - удалена ли вершина?
vector<long> removed;

//Массив соседей для конкретной вершины
vector<long> neighbohoor;

//Массив БАЗЫ. БАЗА - элементы, в котором точно установлено кратчайшие пути
vector<long> base;

//Размерность
long N;

//Максимальное отличние расстояний между городами
const long gMax = 100;

//Расстояние, если между вершинами графа нету ребер.
const long pMax = 99;

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
			if (count <= Min){
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

//Генерация графа, приближенного к реальному городу
void generationCity()
{
	srand(time(NULL));
	
	for (int i = 1; i <= N; i++) A[i][i] = 0;

	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			if (j - i > 2) {
				A[i][j] = pMax;
				A[j][i] = pMax;
			}
			else {
				A[i][j] = rand() % gMax + 51;
				A[j][i] = A[i][j];
			}
}


//Здесь мы инициализируем матрицы
void init()
{
	//Очистка переменных
	//cin >> N;
	N = 7;
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

	int aa[7][7] = { 
			{ 0, 3, 2, pMax, 10, pMax, pMax },
			{ 3, 0, 5, 4, pMax, pMax, pMax },
			{ 2, 5, 0, pMax, pMax, pMax, pMax },
			{ pMax, 4, pMax, 0, 2, pMax, 6 },
			{ 10, pMax, pMax, 2, 0, 4, 3 },
			{ pMax, pMax, pMax, pMax, 4, 0, 2 },
			{ pMax, pMax, pMax, 6, 3, 2, 0 } };
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			A[i + 1][j + 1] = aa[i][j];
	//Инициализация матрицы последователей
	FOR(i, 1, N)
		FOR(j, 1, N)
			if (A[i][j] < pMax)
				S[i][j] = j;
			else S[i][j] = pMax;
	//generationCity();
}

// Собственно говоря, само решение
void solve()
{
	//Процесс удаления вершин
	//p - порядковый номер удаления вершин
	WR("Starting delete procedure:\n");
	for (int p = 1; p < N - 1; p++)
	{	
		// Вершина, которую будем удалять
		long Min = findMinVert();
		removed[Min] = p;
		WR("\tdeleting vertex: %d\n", Min);

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
				if (A[*I][*J] > A[*I][Min] + A[Min][*J]) {
					A[*I][*J] = A[*I][Min] + A[Min][*J];
					//Через Min топать будет быстрее
					S[*I][*J] = Min;
					S[*I][*J] = Min;
				}
			}
		}

		WR("after deleting the vertex:\n");
		FOR(ii, 1, 7) {
			FOR(jj, 1, 7)
				WR("%d\t", A[ii][jj]);
			WR("\n");
		}
		WR("================================\n");
		WR("ways\n");
		FOR(ii, 1, 7) {
			FOR(jj, 1, 7)
				WR("\t%d", S[ii][jj]);
			WR("\n");
		}
		WR("================================\n");
	}
	
	for (int i = 1; i <= N; i++)
		if (removed[i] == 0)
			base.push_back(i);

	//Процесс обратной вставки вершин
	WR("\n\n================================\n\n");
	WR("starting proccess of adding vertexes\n");
	for (int p = N - 2; p > 0; p--)
	{
		//найти вершину, которую удалили в p-той итерации
		long Insert = -1;
		for (int i = 1; i <= N; i++)
			if (removed[i] == p)
				Insert = i;
		WR("Adding the vertex: %d\n", Insert);
		
		//Восстанавливаем статус вершины в неудаленную
		removed[Insert] = 0;

		vector<long>::iterator I, J;
		for (I = base.begin(); I != base.end(); I++)
		{
			for (J = base.begin(); J != base.end(); J++)																																							
			{
				if (A[Insert][*I] > A[Insert][*J] + A[*J][*I]) {
					A[Insert][*I] = A[Insert][*J] + A[*J][*I];
					S[Insert][*I] = *J;
					S[*I][Insert] = *J;
				}
			}
		}
		base.push_back(Insert);
		WR("after adding the vertex:\n");
		FOR(ii, 1, 7) {
			FOR(jj, 1, 7) {
				A[ii][jj] = min(A[ii][jj], A[jj][ii]);
				WR("%d\t", A[ii][jj]);
			}
			WR("\n");
		}
		WR("================================\n");
		WR("ways\n");
		FOR(ii, 1, 7) {
			FOR(jj, 1, 7)
				WR("\t%d", S[ii][jj]);
			WR("\n");
		}
		WR("================================\n");
	}
	printf("new algorithm:\n");
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			A[i][j] = min(A[i][j], A[j][i]);
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
}

//Всем известный алгоритм Флойда.
void solveFloid()
{
	//printf("Floid's algorithm:\n");
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++)
				A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
	/*for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			printf("%d\t", A[i][j]);
		printf("\n");
	}*/

}

int main()
{
	freopen("output.txt", "w", stdout);
	//while (1) 
	{
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