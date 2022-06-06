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
    string secondMenu = "\nR - Read graph from file\nG - Generate random graph\nS - Show graph\nP - Prim algorithm\nK - Kruskal algorithm\nD - Dijkstra algorithm\nB - Bellman-Ford algorithm\nQ - Quit to menu\n";

    bool directed;
    bool exists;

    int size_n;

public:
    void menu();                                    //Główne menu propgramu
private:
    void create_ui(Graphs *g);                      //Obsługa losowego tworzenia grafu

    void prim(Graphs * gg);                         //Obsługa algorytmu Prima
    void kruskal(Graphs *gg);                       //Obsługa algorytmu Kruskala

    void dijkstra(Graphs *gg);                      //Obsługa algorytmu Dijkstry
    void bellmanFord(Graphs *gg);                   //Obsługa algorytmu Bellmana-Forda

    void autoTest();                                //Obsługa testów

    void loadMenuList();                                //Obsługa wczytywania
    void loadMenuMatrix();

    void listMenu();

    void matrixMenu();
};