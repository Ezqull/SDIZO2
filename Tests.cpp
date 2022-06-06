#include "Tests.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

void Tests::saveResults(std::string filename, int index)
{
    std::ofstream file(filename + ".txt");
    if (file.good() == true)
    {
        file << "Dijkstra;Ford-Bellman;Prim;Kruskal" << std::endl;
        for (int i = 0; i < 100; i++)
        {
            file << dijkstraResults[index] << ";" << bellmanFordResults[index] << ";" <<
                 primResults[index] << ";" << kruskalResults[index] << std::endl;
            index++;
        }
        file.close();
    }
    else
    {
        std::cout << "B³¹d zapisu!" << std::endl;
        getchar();
    }
}

void Tests::startTimer()
{
    startTime = std::chrono::high_resolution_clock::now();
}

void Tests::stopTimer()
{
    endTime = std::chrono::high_resolution_clock::now();
}

long Tests::measuredTime()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>
            (Tests::endTime - Tests::startTime).count();
}

void Tests::addDijkstra(long duration, int *index, int where)
{
    dijkstraResults[index[where]] = duration;
    index[where]++;
}

void Tests::addBellmanFord(long duration, int *index, int where)
{
    bellmanFordResults[index[where]] = duration;
    index[where]++;
}

void Tests::addPrim(long duration, int *index, int where)
{
    primResults[index[where]] = duration;
    index[where]++;
}

void Tests::addKruskal(long duration, int *index, int where)
{
    kruskalResults[index[where]] = duration;
    index[where]++;
}
