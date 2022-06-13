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
	void create(int vertices, double density, double maxEdges, bool directed) override;      //Funkcja losowo tworzaca graf
	void display();                                                                     //Funkcja wyswietlajaca graf

	void mstPrim(int start) override;                                                   //Funckja obslugujaca algorytm Prima
	void mstKruskal() override;                                                         //Funckja obslugujaca algorytm Kruskala

	void bellmanFord(int node, int end) override;                                       //Funkcja obslugujaca algorytm Dijsktry
    void dijkstra(int start, int end) override;                                         //Funkcja obslugujaca algorytm Bellmana-Forda

    int loadGraph(std::string filename, bool directed) override;                        //Wczytywanie z pliku

private:
	void spanningtree(int *visited);                                                    //Funkcja towrzaca drzewo rozpinajace dla nieskierowanego
	int relax(int index);                                                               //Funkcja relaksujaca sasiadów
};

#endif