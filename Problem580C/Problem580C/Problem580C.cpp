#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

struct Vertex{
	bool cat;
	std::vector < int > neighbors;
};

std::vector < Vertex > graph;

void findCountApproprRest(int root, int &rest_cout);

int main()
{
	int n, patience; // Кол-во вершин, допустимое кол-во подряд идущих котов
     // Init graph
	std::cin >> n >> patience;
	graph.resize(n);
	// Inint cat 
	for (auto vertex : graph)
		cin >> vertex.cat;
	// Init edges
	for (int i = 0; i < n - 1; i++) {
		int a , b;
		std::cin >> a >> b;
		a--;
		b--;
		graph[a].neighbors.push_back(b);
		graph[b].neighbors.push_back(a);
	}

	
}

void findCountApproprRest(int root , int &rest_cout ) {

}
