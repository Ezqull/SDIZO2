#pragma once
#ifndef Graphs_h
#define Graphs_h
#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <fstream>

struct Dijkstra {
	int index = 0;
	int distance = -1;
	int prev;
};

struct Prim {
	int index = 0;
	int distance = 0;
	int prev = -1;
};

struct Kruskal {
	int source;
	int weight;
	int target;
};

class Graphs {
protected:
	int nodes;
    bool testing = false;
	Dijkstra *checked;
	Dijkstra *notchecked;
	int dch, dnch;
	Prim *solved;
	Prim *notSolved;
	int sol, nsol;
	int mst_size;
	Kruskal *line;
	Kruskal *result;
	int **tree;
	int t_size, cnt;
	int *sizes;
public:
	void switch_test();
	virtual void create(int nodes, double edges, double maxedges, bool directed) = 0;
	virtual void dijkstra(int start, int end) = 0;
	virtual void mstPrim(int start) = 0;
	virtual void mstKruskal() = 0;
	virtual void bellmanFord(int start, int end) = 0;
	virtual int loadGraph(std::string filename, bool directed) = 0;

    int edges;
protected:
	void sort(Kruskal *target);
	void connect(int tab, int tab2);
	void displayDijkstra(Dijkstra *list, int size, int start, int end);
	void displayPrim(Prim *list, int size);
	void displayKruskal(Kruskal *list, int size);
};

#endif