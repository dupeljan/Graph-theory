// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <set>

#define INPUT_PATCH "input.txt"
#define OUTPUT_PATCH "output.txt"
using namespace std;

//
int dfs(int v);
int dfs(int v, int color);

vector<int> dws(int v);

int find_parent(int v);
void union_set(int a, int b);

int count_components();
void out_count_comp();


void graph_input(int vertex, int edge);
void count_components(int n);
bool is_connect(int n);
void vect_out(vector<int> v);
void zero(int n);
//
struct vertex{
	//smth info;
	//smth weihgt;
	int color;
	int parent;
	int rank;
	vector<int> neigbors;
};

vector<vertex> graph;



int main(){
	int n, m;// кол-во вершин и ребер
	
	fstream in;
	in.open(INPUT_PATCH);

	if (!in)
		return 1;

	in >> n >> m;

	//graph_input(n, m);
	graph.resize(n);
	//Ввод Вершин
	zero(n);

	//Ввод ребер
	for (int i = 0; i < m; ++i) {

		int a, b;
		in >> a >> b;
		//
		a--;
		b--;
		//
		graph[a].neigbors.push_back(b);
		graph[b].neigbors.push_back(a);
		// Обьединим по ребрам
		union_set(a, b);
	}

	in << '\n';

	out_count_comp();
	//dfs(0);

	//cout << "connect " << is_connect(n) << '\n';

	//zero(n);

	//count_components(n);
	
	//zero(n);
	
	//Обход в ширину
	//vect_out(dws(0));

	cout << "Success"<<'\n';

	system("pause");

	
}

//Обход графа в глубину DFS
int dfs(int v) {
	if (graph[v].color)								//Если вершина посещена
		return 1;

	graph[v].color = 1;									//Посещаем вершину
	std::cout << v + 1 << '\n';
	for (int i = 0; i < graph[v].neigbors.size(); i++)  //Обходим соседей
		if (!graph[graph[v].neigbors[i]].color) {		//Если сосед не посещен
			dfs(graph[v].neigbors[i]);
		}

	return 0;

}

int dfs(int v, int color) {
	if (!graph[v].color) { // Если вершина не посещена
		graph[v].color = color;
		//std::cout << v + 1 << '\n';
		for (int i = 0; i < graph[v].neigbors.size(); i++) {
			if (!graph[graph[v].neigbors[i]].color) {
				dfs(graph[v].neigbors[i], color);
			}
		}
		return 0;
	}
}

// Алгоритм обхода графа в ширину dws
vector<int> dws(int v) {
	if (graph[v].color)
		return { 0 };

	vector<int> result = { v + 1 };
	graph[v].color = 1;			//Просмотрим верхушку

	for (int pointer = 0; pointer < result.size(); pointer++) {			//Пока pointer не дошел до конца
		int actual_vert = result[pointer] - 1;							//Номер текущей вершины
		for (int i = 0; i < graph[actual_vert].neigbors.size(); i++)  //Перебор всех соседей текущей вершины
			if (!graph[graph[actual_vert].neigbors[i]].color) {         //Если выбранный сосед не просмотрен
				graph[graph[actual_vert].neigbors[i]].color = 1;        //Просматриваем его
				result.push_back(graph[actual_vert].neigbors[i] + 1);	//Записываем номер в результат
			}
	}
	return result;
}

/*
int count_components() {
	vector <int> 
	for(int i = )
}
*/
void count_components(int n) {										//Находим кол-во компонент связности
	int count = 0;
	for (int i = 0; i < n; i++)
		if (!graph[i].color) {
			++count;
			dfs(i, count);
		}
	cout << "Count sviaznosti components " << count << '\n';

}
///==================================
int find_parent(int v) {
	if (graph[v].parent == v) return v;
	else
		return v = find_parent(graph[v].parent);
}


void swap(int a, int b) {
	int c = a;
	a = b;
	b = c;
}
void union_set(int a, int b) {
	a = find_parent(a);
	b = find_parent(b);
	if (a != b) {
		if (graph[a].rank < graph[b].rank)  
			swap(a, b);
		graph[b].parent = a;
		if (graph[a].rank = graph[b].rank)
			++graph[a].rank;

	}
}

bool connect(int a, int b) {
	return (find_parent(a) == find_parent(b)) ? true : false;
}

int total_count_comp() {
	set<int> parents;
	parents.insert(graph[0].parent);
	int result = 1;
	for ( int i = 1; i < graph.size(); i++ )
		if (parents.find(graph[i].parent) == parents.end()) { //Если нашли корень в множестве
			result++;
			parents.insert(graph[i].parent);
		}
	return result;
}
void out_count_comp() {
	fstream out;
	out.open(OUTPUT_PATCH, fstream::out);
	out << "Ver1, Ver2, Connect?"<<'\n';
	for (int i = 0; i < graph.size(); i++)
		for (int j = i; j < graph.size(); j++)
			out << i + 1 << " -> " << j + 1 << " : " << connect(i, j) << '\n';
	out << "Total: " << total_count_comp();
}
///==================================
bool is_connect(int n) {					//проверка на связность 
	bool full = true;
	for (int i = 0; i < n && full; i++)
		full = graph[i].color;
	return full;
}

void zero(int n) {                                                    //Обнулить вершины графа
	for (int i = 0; i < n; i++) {
		//std::cout << "vertex #" << i + 1;
		graph[i].color = 0;
		graph[i].parent = i;
		graph[i].rank = 0;
	}
}

void vect_out(vector<int> v) {
	for (int n : v)
		cout << n << '\n';
}

