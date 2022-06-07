#pragma once
#ifndef Matrix_h
#define Matrix_h
#include "Graphs.h"
#include "Tests.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

class Matrix: public Graphs, public Tests{
private:
	int **pointer = nullptr;
public:
    ~Matrix();
	void create(int nodes, double edges, double maxedges, bool directed) override;
	void display();
	void dijkstra(int start, int end) override;
	void mstPrim(int start) override;
	void mstKruskal() override;
	void bellmanFord(int node, int end) override;
	int loadGraph(std::string filename, bool directed) override;
private:
	void spanningtree(int *visited);
	int relax(int index);
};

#endif