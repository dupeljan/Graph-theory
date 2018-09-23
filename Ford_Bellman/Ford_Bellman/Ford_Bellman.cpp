// Ford_Bellman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>

#define INPUT_FILE_PATCH  "input.txt"
#define OUTPUT_FILE_PATCH "output.txt"
#define ORIENTED		  0
#define ROOT			  0

using namespace std;

//
vector < int > Ford_Bellman(int v, int vertex_n, int edges_m, int inf);
void output(vector < int > x);
//

struct  edge{
	int a, b, cost;
};

vector< edge > edges;
int main()
{
	fstream file;

	file.open(INPUT_FILE_PATCH);
	if (!file)
		return 1;

	int n;  //кол-во вершин
	int m;  //кол-во ребер
	int inf = 0; // Относительная бесконечность
	
	file >> n >> m;

	//Заполняем вектор орентированных ребер
#if ! ORIENTED 
	m *= 2;
	
#endif
	edges.resize(m);
	for (int i = 0; i < m; i++) {

		int a, b, w;//Соединияем вершины a,b ребром веса w
		
		file >> a >> b >> w;
		//
		a--;
		b--;
		//
		edges[i].a = a;
		edges[i].b = b;
		edges[i].cost = w;

#if ! ORIENTED 
		i++;
		edges[i].a = b;
		edges[i].b = a;
		edges[i].cost = w;
#endif

		inf += abs(edges[i].cost);
	}
	
	inf++;

	output ( Ford_Bellman(ROOT, n, m, inf) );

	cout << "Success!" << '\n';
	system("pause");
}

vector < int > Ford_Bellman(int v, int vertex_n, int edges_m, int inf) {
	vector < int > d;
	d.resize(vertex_n);
	for (int i = 0; i < vertex_n; i++)
		d[i] = inf;
	d[v] = 0;
	bool changes;
	do {
		changes = false;
		for ( int j = 0; j < edges_m; j++ )
			if ( d[ edges[j].a ] < inf )
				if (d[edges[j].b] > d[edges[j].a] + edges[j].cost) {
					d[edges[j].b] = d[edges[j].a] + edges[j].cost;
					changes = true;
				}
	} while (changes);

	return d;
}

void output(vector < int > x) {
	fstream out;
	out.open(OUTPUT_FILE_PATCH, fstream::out);
	for (int i = 0; i < x.size(); i++)
		out << ROOT + 1 << " -> " << i+ 1 << " : " << x[i] << '\n';

}