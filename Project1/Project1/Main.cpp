#include <iostream>
#include "DenseGraph.h"

using namespace std;

int main() {
	DenseGraph g("Grafo", 13, false);
	g.insert(Edge(0, 5));
	g.insert(Edge(0, 6));
	g.insert(Edge(0, 1));
	g.insert(Edge(1, 2));
	g.insert(Edge(2, 6));
	g.insert(Edge(6, 7));
	g.insert(Edge(7, 8));
	g.insert(Edge(7, 10));
	g.insert(Edge(8, 10));
	g.insert(Edge(5, 3));
	g.insert(Edge(5, 4));
	g.insert(Edge(3, 4));
	g.insert(Edge(4, 9));
	g.insert(Edge(4, 11));
	g.insert(Edge(9, 11));
	g.insert(Edge(11, 12));
	g.print();

	DenseGraph::adjIterator A(g, 0);
	cout << "\n Adyacentes al nodo 0 = ";
	for (unsigned int w = A.beg(); !A.end(); w = A.nxt()) {
		cout << w << " ";
	}
	cout <<"\n";

	DenseGraph::BridgeIterator B(g, 0);
	cout << "\n Puentes del grafo = ";
	for (unsigned int w = B.beg(); !B.end(); w = B.nxt()) {
		cout << w << " ";
	}
	cout << "\n\n";

	system("pause");
}