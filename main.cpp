#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<long>> A, S;
vector<long> removed;
vector<long> neighbohoor;
//A - матрица расто€ний, S - матрица последователей
long N;
//–азмерность
const long pMax = 1000;

//»щем вершину с минимальным количеством смежных вершин с остальными вершинами
//которые ещЄ не были удалены
long findMinVert()
{
	long Min = N, iMin;
	//Ќаходим первую неудаленную вершину. —тавим его начальной точкой приближени€
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

//«десь мы инициализируем матрицы
void init()
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	cin >> N;
	A.resize(N + 1);
	S.resize(N + 1);
	removed.resize(N + 1, 0);

	for (int i = 1; i <= N; i++)
	{
		A[i].resize(N + 1);
		S[i].resize(N + 1, 0);
		for (int j = 1; j <= N; j++){
			cin >> A[i][j];
			if (A[i][j] < 0)
				A[i][j] = pMax;
		}
	}
}

// —обственно говор€, само решение
void solve()
{
	//ѕроцесс удалени€ вершин
	//p - пор€дковый номер удалени€ вершин
	for (int p = 1; p < N - 1; p++)
	{
		// ¬ершина, которую будем удал€ть
		long Min = findMinVert();
		removed[Min] = p;
		
		//находим все смежные вершины, которые ещЄ не удалены
		neighbohoor.clear();
		for (int i = 1; i < N; i++)
		{
			// существует путь
			if (removed[i] == 0 && A[Min][i] < pMax)
				neighbohoor.push_back(i);
		}
		
		//пробегаем по всем из них, смотрим, не выполн€етс€ ли правило треугольника
		vector<long>::iterator I, J;
		for (I = neighbohoor.begin(); I != neighbohoor.end(); I++)
		{
			for (J = neighbohoor.begin(); J != neighbohoor.end(); J++)
			{
				
				//не выполн€етс€ правило треугольника
				if (A[*I][*J] > A[*I][Min] + A[Min][*J])
					A[*I][*J] = A[*I][Min] + A[Min][*J];
				//аналоги:
				//A[i][j] = A[i][j] > A[i][Min] + A[Min][j] ? A[i][Min] + A[Min][j] : A[i][j];
				//A[i][j] = min(A[i][j], A[i][Min] + A[Min][j]);
			}
		}
	}

	
}

int main()
{
	init();
	solve();
	return 0;
}