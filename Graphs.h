#pragma once
#ifndef Graphs_h
#define Graphs_h
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

struct shortestPath {
	int index = 0;
	int distance = -1;
	int prev = -1;
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
    //Zmienne powiazane z algorytmem Dijkstry
	shortestPath *checked;
	shortestPath *notChecked;
	int shortestPathChecked, shortestPathUnchecked;
    //Zmiennie powiazane z algorytmem Prima (czesc dzielona z Kruskalem)
	Prim *solved;
	Prim *notSolved;
	int mstSolved, mstUnsolved;
	int mstSize;
    //Zmienne powiazane z algorytmem Kruskala
	Kruskal *line;
	Kruskal *result;
	int **tree;
	int t_size, cnt;
	int *sizes;
public:
	void switchTests();                                                                     //Wlanczanie/Wylaczanie testowania
	virtual void create(int nodes, double edges, double maxedges, bool directed) = 0;       //Funkcja losowo tworzaca graf

	virtual void mstPrim(int start) = 0;                                                    //Funckja obslugujaca algorytm Prima
	virtual void mstKruskal() = 0;                                                          //Funkcja obslugujaca algorytm Kruskala

    virtual void dijkstra(int start, int end) = 0;                                          //Funkcja obslugujaca algorytm Dijsktry
	virtual void bellmanFord(int start, int end) = 0;                                       //Funkcja obslugujaca algorytm Bellmana-Forda

	virtual int loadGraph(std::string filename, bool directed) = 0;                         //Wczytanie grafu

    int edges;
protected:
	void sort(Kruskal *target);                                                             //Funkcja sortujaca krawedzie
	void connect(int tab, int tab2);                                                        //laczenie dwoch zbiorow

    void displayPrim(Prim *list, int size);                                                 //Funckja drukujaca wynik dzialania algorytmu Prima
    void displayKruskal(Kruskal *list, int size);                                           //Funckja drukujaca wynik dzialania algorytmu Kruskala

	void displayShortestPath(shortestPath *list, int size, int start, int end);             //Funckja drukujaca wynik dzialania algorytmu najkrótszej œcie¿ki
};

#endif