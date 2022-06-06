#pragma once
#ifndef List_h
#define List_h
#include "Graphs.h"
#include "Tests.h"

struct Node;
struct Edge;

struct Node
{
	int index = 0;
	Edge *head = nullptr;
	Edge *tail = nullptr;
	Node *next = nullptr;
	Node *prev = nullptr;
	int connections = 0;
};

struct Edge
{
	int weight = 0;
	Edge *next = nullptr;
	Node *target = nullptr;
	Node *source = nullptr;
};

class List : public Graphs, public Tests
{
private:
	Node *head = nullptr;
	Node *tail = nullptr;
public:
    ~List();
	void create(int nodes, double edges, double maxedges, bool directed) override;
	void display();
	void dijkstra(int start, int end) override;
	void mstPrim(int start) override;
	void mstKruskal() override;
	void bellmanFord(int node, int end) override;
	void rekdel(Node *nod);
	void edgedel(Edge *edg);
    int loadGraph(std::string filename, bool directed) override;
private:
	void spanningtree();
	int relax(int index);
};
#endif
