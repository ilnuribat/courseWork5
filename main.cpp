#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<long>> A, S;
vector<long> removed;
vector<long> neighbohoor;
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

// ���������� ������, ���� �������
void solve()
{
	//������� �������� ������
	//p - ���������� ����� �������� ������
	for (int p = 1; p < N - 1; p++)
	{
		// �������, ������� ����� �������
		long Min = findMinVert();
		removed[Min] = p;
		
		//������� ��� ������� �������, ������� ��� �� �������
		neighbohoor.clear();
		for (int i = 1; i < N; i++)
		{
			// ���������� ����
			if (removed[i] == 0 && A[Min][i] < pMax)
				neighbohoor.push_back(i);
		}
		
		//��������� �� ���� �� ���, �������, �� ����������� �� ������� ������������
		vector<long>::iterator I, J;
		for (I = neighbohoor.begin(); I != neighbohoor.end(); I++)
		{
			for (J = neighbohoor.begin(); J != neighbohoor.end(); J++)
			{
				
				//�� ����������� ������� ������������
				if (A[*I][*J] > A[*I][Min] + A[Min][*J])
					A[*I][*J] = A[*I][Min] + A[Min][*J];
				//�������:
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