#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<long>> A, S;
vector<long> removed;
//A - матрица растояний, S - матрица последователей
long N;
//Размерность
const long pMax = 1000;

//Ищем вершину с минимальным количеством смежных вершин с остальными вершинами
//которые ещё не были удалены
long findMinVert()
{
	long Min = N, iMin;
	for (int i = 0; i < N; i++)
		if (removed[i] == 0)
		{
			iMin = i;
			break;
		}

	for (int i = 0; i < N; i++)
	{
		if (removed[i] == 0)
		{
			long count = 0;
			for (int j = 0; j < N; j++)
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
	return 0;
}

void init()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> N;
	A.resize(N);
	S.resize(N);
	removed.resize(N);

	for (int i = 0; i < N; i++)
	{
		A[i].resize(N);
		S[i].resize(N);
		for (int j = 0; j < N; j++){
			cin >> A[i][j];
			if (A[i][j] < 0)
				A[i][j] = pMax;
		}
	}
}

int main()
{
	
	init();
	return 0;
}