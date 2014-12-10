#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//������� ���������� � �������������
vector<vector<long>> A, S;
//������ ���������� - ������� �� �������?
vector<long> removed;
//������ ������� ��� ���������� �������
vector<long> neighbohoor;

//������ ����. ���� - ��������, � ������� ����� ����������� ���������� ����
vector<long> base;

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
			}
		}
	}
	
	for (int i = 1; i <= N; i++)
		if (removed[i] == 0)
			base.push_back(i);

	//������� �������� ������� ������
	for (int p = N - 2; p > 0; p--)
	{
		//����� �������, ������� ������� � p-��� ��������
		long Insert = -1;
		for (int i = 1; i <= N; i++)
			if (removed[i] == p)
				Insert = i;
		if (Insert < 0)
		{
			cout << "error: Insert index not found";
			return;
		}
		
		//��������������� ������ ������� � �����������
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
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	init();
	solve();
	return 0;
}