#include "Matrix.h"
#include "List.h"
#include "Testing.h"

using namespace std;

class Menu{

private:
    Matrix matrix;
    List list;
    Testing testing;

    string firstMenu = "\nM - Matrix representation of the graph\nL - List representation of the graph\nT - Automatic tests\nQ - Quit program\n";
    string secondMenu = "\nR - Read graph from file\nG - Generate random graph\nS - Show graph\nP - Prim algorithm\nK - Kruskal algorithm\nD - shortestPath algorithm\nB - Bellman-Ford algorithm\nQ - Quit to menu\n";

    bool directed;
    bool exists;

    int size_n;

public:
    void menu();                                        //Główne menu propgramu

private:
    void create_ui(Graphs *g);                          //Obsługa losowego tworzenia grafu

    void prim(Graphs *g) const;                         //Obsługa algorytmu Prima
    void kruskal(Graphs *g) const;                      //Obsługa algorytmu Kruskala

    void dijkstra(Graphs *g) const;                     //Obsługa algorytmu Dijkstry
    void bellmanFord(Graphs *g) const;                  //Obsługa algorytmu Bellmana-Forda

    void autoTest();                                    //Obsługa testów

    void loadMenuList();                                //Obsługa wczytywania lista
    void loadMenuMatrix();                              //Obsługa wczytywania macierz

    void listMenu();                                    //Obsługa menu dla listy
    void matrixMenu();                                  //Obsługa menu dla macierzy
};