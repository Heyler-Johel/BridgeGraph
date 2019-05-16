#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Edge {
	unsigned int v, w;
	Edge(unsigned int v, unsigned int w):
		v{v}, w{w} {}
};


class DenseGraph {
	string name;
	unsigned int Vcnt, Ecnt;
	bool digraph;
	vector<vector<bool>>adj;
	vector<vector<int>>Bridges;	//vector donde almacena las coordenadas de los puentes
	vector<int>begBridges();
public:
	DenseGraph(string, unsigned int, bool);
	unsigned int V() const { return Vcnt; }
	unsigned int E() const { return Ecnt; }
	bool directed() const { return digraph; }
	void insert(Edge);
	void remove(Edge);
	void isBridge(uint16_t& v, uint16_t& w);
	void print();
	string getName();
	bool edge(unsigned int, unsigned int);
	class adjIterator;
	friend class adjIterator;
	class BridgeIterator;
	friend class BridgetIterator;
};

class DenseGraph::adjIterator{
	const DenseGraph & G;
	unsigned int v;
	int i;
public:
	adjIterator(const DenseGraph &G, unsigned int v);
	unsigned int beg();
	unsigned int nxt();
	bool end();
};

class DenseGraph::BridgeIterator {
	const DenseGraph &G;
	int i;
	void vectores();
	bool puente(int v, int w);
	void DFS(Edge e);
public:
	BridgeIterator(const DenseGraph &G);
	unsigned int beg();
	unsigned int nxt();
	bool end();
};