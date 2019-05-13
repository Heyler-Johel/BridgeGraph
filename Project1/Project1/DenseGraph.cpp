#include "DenseGraph.h"
#include <vector>
#include <string>

using namespace std;

DenseGraph::DenseGraph(string name, unsigned int V, bool digraph = false) :
	name{ name }, Vcnt{ V }, Ecnt{ 0 }, digraph{ digraph }{
	for (unsigned int i = 0; i < V; i++) {
		vector<bool> inter(V, false);
		adj.push_back(inter);
	}
}

void DenseGraph::insert(Edge e) {
	//cout << e.w;
	unsigned int v = e.v; unsigned int w = e.w;
	if (adj[v][w] == false) Ecnt++;
	adj[v][w] = true;
	if (!digraph) adj[w][v] = true;
}

void DenseGraph::remove(Edge e) {
	unsigned int v = e.v; unsigned int w = e.w;
	if (adj[v][w] == true) Ecnt--;
	adj[v][w] = false;
	if (!digraph) adj[w][v] = false;
}

string DenseGraph::getName() { return name; }

bool DenseGraph::edge(unsigned int v, unsigned int w) {
	return adj[v][w];
}

void DenseGraph::print() {
	cout << "=== Graph : [" << name << "]"
		 << " Size V = " << Vcnt
		 << "  E = " << Ecnt
		 << " ===\n";
	for (unsigned int v = 0; v < Vcnt; v++) {
		typename DenseGraph::adjIterator A(*this, v);
		bool primero = true;
		for (unsigned int t = A.beg(); !A.end(); t = A.nxt()) {
			if (primero) {
				printf("...%3d -> (%d", v, t); primero = false;
			}
			else
				cout << " " << t;
		}
		if (!primero) cout << ")\n";
	}
}

DenseGraph::adjIterator::adjIterator(const DenseGraph &G, unsigned int v) :
	G{G}, v{v}, i{0} {}

unsigned int DenseGraph::adjIterator::beg() {
	i = -1; return nxt();
}

unsigned int DenseGraph::adjIterator::nxt() {
	for (i++; i<int(G.V()); i++)
		if (G.adj[v][i]) { return i; }
	return G.V();
}

bool DenseGraph::adjIterator::end() {
	return i >= int(G.V());
}

DenseGraph::BridgeIterator::BridgeIterator(const DenseGraph &G, unsigned int v):
	G{ G }, v{ v }, i{ 0 } {}

unsigned int DenseGraph::BridgeIterator::beg() {
	return -1;
}

unsigned int DenseGraph::BridgeIterator::nxt() {
	return -1;
}

bool DenseGraph::BridgeIterator::end() {
	return -1;
}
