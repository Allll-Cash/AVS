#include <stdio.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <iostream>
#include <vector>
#include <locale>
#include<list>
using namespace std;

int n = 1000 + rand();
vector<int> A(n), B(n);
list<int> C;
int del = 1;

/// <summary>
/// Вычисление НОД 3 чисел, если он равен 1, то общий делитель едиснтвенный 1
/// </summary>
/// <param name="one">число массива A</param>
/// <param name="two">число массива B</param>
/// <param name="three">индекс</param>
/// <returns>НОД</returns>
int Nod(int one, int two, int three)
{
	for (int i = 1; i <= one; i++)
	{
		if (one % i == 0 && two % i == 0 && three % i == 0)
		{
			del = i;
		}
	}
	return del;
}

/// <summary>
/// Сравниваем НОД с 1 и запоминаем индекс
/// </summary>
/// <param name="param"></param>
/// <returns></returns>
void* NOD(void* param)
{
	int p = *(int*)param;

	if (Nod(A[p], B[p], p) == 1)
		C.push_back(p);

	return NULL;
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");

	pthread_t* mythread = new pthread_t[n];

	//Заполнение массивов 
	for (size_t i = 0; i < n; i++)
	{
		A[i] = 1 + rand();

		B[i] = 1 + rand();
	}

	int* num = new int[n];
	for (int i = 0; i < n; i++) num[i] = i;

	for (int i = 0; i < n; i++)
		pthread_create(&mythread[i], NULL, NOD, (void*)(num + i));
	for (int i = 0; i < n; i++)
		pthread_join(mythread[i], NULL);

	//Сортируем массив индексов и выводим
	for (int j : C)
	{
		cout << j << "\n";
	}


}