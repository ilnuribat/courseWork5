#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<long>> A, S;
vector<long> removed;
//A - ������� ���������, S - ������� ��������������
long N;
//�����������
const long pMax = 1000;

//���� ������� � ����������� ����������� ������� ������ � ���������� ���������
//������� ��� �� ���� �������
long findMinVert()
{
	long Min = N, iMin;
	//������� ������ ����������� �������. ������ ��� ��������� ������ �����������
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

//����� �� �������������� �������
void init()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
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

// ���������� ������, ���� �������
void solve()
{
	//p - ���������� ����� �������� ������
	for (int p = 1; p < N; p++)
	{
		// �������, ������� ����� �������
		long Min = findMinVert();
		removed[Min] = p;

	}
}

int main()
{
	init();
	solve();
	return 0;
}