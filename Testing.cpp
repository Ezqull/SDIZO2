#include "Testing.h"


void Testing::loopTests(Matrix mat, List list, int size)
{
    Tests testing;
    int *sizes = new int[32];

    for (int i = 0; i < 4; i++)
        sizes[i] = 0;

    for (int i = 4; i < 8; i++)
        sizes[i] = 100;

    for (int i = 8; i < 12; i++)
        sizes[i] = 200;

    for (int i = 12; i < 16; i++)
        sizes[i] = 300;

    for (int i = 16; i < 20; i++)
        sizes[i] = 400;

    for (int i = 20; i < 24; i++)
        sizes[i] = 500;

    for (int i = 24; i < 28; i++)
        sizes[i] = 600;

    for (int i = 28; i < 32; i++)
        sizes[i] = 700;

    int directed = size * (size - 1);
    int undirected = (size * (size - 1)) / 2;

    for (int j = 0; j < 100; j++)
    {
        std::cout << (j + 1) << std::endl;

        // 25% skierowany
        mat.create(size, 25, directed, true);
        list.create(size, 25, directed, true);

        // Testy macierzy Dijkstra
        testing.startTimer();
        mat.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 0);

        // Testy macierzy Bellman-Ford
        testing.startTimer();
        mat.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 1);

        // Testy listy Dijkstra
        testing.startTimer();
        list.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 16);

        // Testy lsity Bellman-Ford
        testing.startTimer();
        list.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 17);

        // 25% nieskierowany
        mat.~Matrix();
        list.~List();
        mat.create(size, 25, undirected, false);
        list.create(size, 25, undirected, false);

        // Testy macierzy Prim
        testing.startTimer();
        mat.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 2);

        // Testy macierzy Kruskal
        testing.startTimer();
        mat.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 3);

        // Testy listy Prim
        testing.startTimer();
        list.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 18);

        // Testy listy Kruskal
        testing.startTimer();
        list.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 19);

        // 50% skierowany
        mat.~Matrix();
        list.~List();
        mat.create(size, 50, directed, true);
        list.create(size, 50, directed, true);

        // Testy macierzy Dijkstra
        testing.startTimer();
        mat.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 4);

        // Testy macierzy Bellman-Ford
        testing.startTimer();
        mat.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 5);

        // Testy listy Dijkstra
        testing.startTimer();
        list.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 20);

        // Testy lsity Bellman-Ford
        testing.startTimer();
        list.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 21);

        // 50% nieskierowany
        mat.~Matrix();
        list.~List();
        mat.create(size, 50, undirected, false);
        list.create(size, 50, undirected, false);

        // Testy macierzy Prim
        testing.startTimer();
        mat.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 6);

        // Testy macierzy Kruskal
        testing.startTimer();
        mat.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 7);

        // Testy listy Prim
        testing.startTimer();
        list.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 22);

        // Testy listy Kruskal
        testing.startTimer();
        list.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 23);

        // 75% skierowany
        mat.~Matrix();
        list.~List();
        mat.create(size, 75, directed, true);
        list.create(size, 75, directed, true);

        // Testy macierzy Dijkstra
        testing.startTimer();
        mat.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 8);

        // Testy macierzy Bellman-Ford
        testing.startTimer();
        mat.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 9);

        // Testy listy Dijkstra
        testing.startTimer();
        list.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 24);

        // Testy lsity Bellman-Ford
        testing.startTimer();
        list.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 25);

        // 75% nieskierowany
        mat.~Matrix();
        list.~List();
        mat.create(size, 75, undirected, false);
        list.create(size, 75, undirected, false);

        // Testy macierzy Prim
        testing.startTimer();
        mat.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 10);

        // Testy macierzy Kruskal
        testing.startTimer();
        mat.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 11);

        // Testy listy Prim
        testing.startTimer();
        list.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 26);

        // Testy listy Kruskal
        testing.startTimer();
        list.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 27);

        // 99% skierowany
        mat.~Matrix();
        list.~List();
        mat.create(size, 99, directed, true);
        list.create(size, 99, directed, true);

        // Testy macierzy Dijkstra
        testing.startTimer();
        mat.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 12);

        // Testy macierzy Bellman-Ford
        testing.startTimer();
        mat.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 13);

        // Testy listy Dijkstra
        testing.startTimer();
        list.dijkstra(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addDijkstra(testing.measuredTime(), sizes, 28);

        // Testy lsity Bellman-Ford
        testing.startTimer();
        list.bellmanFord(0, rand()%mat.edges);
        testing.stopTimer();

        testing.addBellmanFord(testing.measuredTime(), sizes, 29);

        // 99% nieskierowany
        mat.~Matrix();
        list.~List();
        mat.create(size, 99, undirected, false);
        list.create(size, 99, undirected, false);

        // Testy macierzy Prim
        testing.startTimer();
        mat.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 14);

        // Testy macierzy Kruskal
        testing.startTimer();
        mat.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 15);

        // Testy listy Prim
        testing.startTimer();
        list.mstPrim(0);
        testing.stopTimer();

        testing.addPrim(testing.measuredTime(), sizes, 30);

        // Testy listy Kruskal
        testing.startTimer();
        list.mstKruskal();
        testing.stopTimer();

        testing.addKruskal(testing.measuredTime(), sizes, 31);
    }
    std::cout << "\nTesty zakończone!" << std::endl;
    getchar();

    testing.saveResults("mat25", 0);
    testing.saveResults("mat50", 100);
    testing.saveResults("mat75", 200);
    testing.saveResults("mat99", 300);

    testing.saveResults("list25", 400);
    testing.saveResults("list50", 500);
    testing.saveResults("list75", 600);
    testing.saveResults("list99", 700);
}