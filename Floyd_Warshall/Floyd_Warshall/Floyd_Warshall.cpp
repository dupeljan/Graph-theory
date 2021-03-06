// Deigstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <vector>
#include <fstream>

#define INPUT_FILE_PATCH  "input1.txt"
#define OUTPUT_FILE_PATCH "output.txt"
using namespace std;

///
void min_vert_len(vector < vector < int > >); // Алгоритм Флойда - Уоршелла
void drop_vector(vector < vector <int> > a);
void drop_msg();
///


vector < vector < int > > w_matr; //Матрица кратчайших путей

int main()
{
	fstream file;
	if (!file)
		return 1;

	file.open(INPUT_FILE_PATCH);
	int n;  //кол-во вершин
	int m;  //кол-во ребер
	file >> n >> m;


	//Иницмалтзируем матрицу
	w_matr.resize(n);
	for (int i = 0; i < n; i++) {
		w_matr[i].resize(n);
		w_matr[i][i] = 0;
	}

	// Находим максимум веса
	int inf = 0;

	for (int i = 0; i < m; i++) {

		int a, b, w;				//Соединияем вершины a,b ребром веса w
		file >> a >> b >> w;
		//
		a--;
		b--;
		//
		w_matr[a][b] = w_matr[b][a] = w;

		inf += abs(w);
	}

	

	//Заполняем матрицу бесконечностями
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!w_matr[i][j] && (i != j))
				w_matr[i][j] = inf + 1;

	//Кидаем матрицу в алгоритм

	min_vert_len(w_matr);
	

	cout << "success!" << '\n';

	system("pause");
}
int min(int a, int b) {
	return (a <= b) ? a : b;
}


// Алгоритм Флойда заполняет матрицу, (w[i][j]) i,j=1..n 
// где (w[i][j]) - минимальное расстояние между вершиной i и j
void min_vert_len(vector < vector <int> > w) {
	for (int k = 0; k < w.size(); k++)
		for (int i = 0; i < w.size(); i++)
			for (int j = 0; j < w.size(); j++)
				w[i][j] = min(w[i][j], w[i][k] + w[k][j]);

	bool neg_cicle = false;
	for (int i = 0; i < w.size() && !neg_cicle; i++)
		neg_cicle = w[i][i] != 0;

	if (neg_cicle)
		drop_msg();
	else
		drop_vector(w);
}


int digit_count(int a) {
	int res = 0;
	do {
		res++;
		a /= 10;
	} while (a);

	return res;
}
void drop_vector(vector < vector <int> > a) {
	fstream out;
	out.open(OUTPUT_FILE_PATCH, fstream::out);
	int max_dig = 3;
	for (int i = 0; i < a.size(); i++) {
		for (int j = i; j < a[i].size(); j++) {
			out << i + 1 << "->" << j + 1 << ":"<< a[i][j]<<'\n';
			
		}
		out << '\n';
	}

	out.close();
}

void drop_msg() {
	fstream out;
	out.open(OUTPUT_FILE_PATCH, fstream::out);
	out << "There is  negative cycle.";
}