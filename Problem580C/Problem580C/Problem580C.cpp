#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

struct Vertex{
	int cat;
	std::vector < int > neighbors;
};

std::vector < Vertex > graph;


void findCountApproprRest(int root, int catCount, int patience);
int result = 0;

int main()
{
	int n, patience; // Кол-во вершин, допустимое кол-во подряд идущих котов
     // Init graph
	std::cin >> n >> patience;
	graph.resize(n);
	// Inint cat 
	for (int i = 0; i < n; i++)
		cin >> graph[i].cat;
	// Init edges
	for (int i = 0; i < n - 1; i++) {
		int a , b;
		std::cin >> a >> b;
		a--;
		b--;
		graph[a].neighbors.push_back(b);
		//graph[b].neighbors.push_back(a);
	}

	findCountApproprRest(0, 0, patience);
	cout << result ;
	system("pause");

}

void findCountApproprRest(int root , int catCount, int patience ) {
	if (graph[root].cat)
		catCount++;
	else
		catCount = 0;
	if (catCount <= patience) { // Обходим
		if (!graph[root].neighbors.size()) // Если лист
			result++;
		else
			for (auto vertex : graph[root].neighbors)
				findCountApproprRest(vertex, catCount, patience);
	}
}
