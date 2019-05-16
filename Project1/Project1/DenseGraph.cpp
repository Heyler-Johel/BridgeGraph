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
			if (puente(v, t)) {
				vector<int> a;
				a.push_back(v);	a.push_back(t);
				DenseGraph::begBridges.push_back(a);
			}
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

DenseGraph::BridgeIterator::BridgeIterator(static const DenseGraph &G):
	G{ G }, i{ 0 } {}

int cnt = 0;

void DenseGraph::vectores() {
	int x = 0;
	while (x<int(this->Vcnt)) {
		orden.push_back(-1);
		st.push_back(-1);
		visitadosasc.push_back(false);
		visitadosdes.push_back(false);
		x++;
	}
	return;
}


void DenseGraph::DFS(Edge e) {
	orden[e.w] = cnt++;
	st[e.w] = e.v;
	adjIterator Z(*this, e.w);
	for (unsigned int k = Z.beg(); !Z.end(); k = Z.nxt()) {
		if (orden[k] == -1) {
			DFS(Edge(e.w, k));
		}
	}
	return;
	for (int v = 0; v < this->Vcnt - 1; v++) {
		if (orden[v] = -1)DFS(Edge(v, v));
	}
}

bool DenseGraph::puente(unsigned int v, unsigned int w) {//Aqui se valida el puente 
	bool result = true;
	int auxi = w;
	if (orden[w] < orden[v]) {//se deja v como ancestro y w como descendiente
		w = v;
		v = auxi;
	}
	int auxw = w;
	bool f = true;
	while (w != 0 || f) {
		f = false;
		int padre = st[w];
		visitadosasc[w] = true;
		adjIterator Asc(*this, padre);//Ascendencia de w
		for (int hijopadre = Asc.beg(); !Asc.end(); hijopadre = Asc.nxt()) {
			//if (!visitadosasc[hijopadre]) {
				visitadosasc[hijopadre] = true;
				adjIterator Des(*this, auxw);//Descendencia de w
				for (int hijo = Des.beg(); !Des.end(); hijo = Des.nxt()) {
					if (hijo != st[auxw]) {
						adjIterator Deshijos(*this, hijo);
						for (int nieto = Deshijos.beg(); !Deshijos.end(); nieto = Deshijos.nxt()) {
							if (nieto != auxw) {
								if (nieto == hijopadre)
									return false;
							}
						}
						
						if (hijo == hijopadre)
							return false;
					}
				}
			//}
		}
		w = st[w];//padre de padre
	}
	return result;
}

unsigned int DenseGraph::BridgeIterator::beg() {
	i = 0; return i;
}

unsigned int DenseGraph::BridgeIterator::nxt() {
	return ++i;
}


bool DenseGraph::BridgeIterator::end() {
	return i==G.begBridges.size();
}
