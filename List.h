#pragma once
#ifndef List_h
#define List_h
#include "Graphs.h"
#include "Tests.h"

struct Node;
struct Edge;

struct Node{
	int index = 0;
	Edge *head = nullptr;
	Edge *tail = nullptr;
	Node *next = nullptr;
    Node *prev = nullptr;
	int connections = 0;
};

struct Edge{
	int weight = 0;
	Edge *next = nullptr;
	Node *target = nullptr;
	Node *source = nullptr;
};

class List : public Graphs, public Tests{

private:
	Node *head = nullptr;
	Node *tail = nullptr;

public:
    ~List();

	void create(int vertices, double density, double maxEdges, bool directed) override; //Funkcja losowo tworzaca graf
	void display();                                                                     //Funkcja wyswietlajaca graf

	void mstPrim(int start) override;                                                   //Funckja obslugujaca algorytm Prima
	void mstKruskal() override;                                                         //Funckja obslugujaca algorytm Kruskala

    void dijkstra(int start, int end) override;                                         //Funkcja obslugujaca algorytm Dijsktry
	void bellmanFord(int node, int end) override;                                       //Funkcja obslugujaca algorytm Bellmana-Forda

	void rekdel(Node *node);                                                             //Funkcja pomocnicza dla destruktora
	void edgedel(Edge *edge);                                                            //Funkcja pomocnicza dla destruktora

    int loadGraph(std::string filename, bool directed) override;                        //Wczytywanie z pliku

private:
	void spanningTree();                                                                //Funkcja towrzaca drzewo rozpinajace dla nieskierowanego
	int relax(int index);                                                               //Funkcja relaksujaca sasiadów
};
#endif
