#include "Tests.h"
#include <iostream>
#include <fstream>
#include <chrono>

void Tests::saveResults(const std::string& filename, int index){
    std::ofstream file(filename + ".txt");
    if (file.good()){
        file << "Prim;Kruskal;Dijkstra;Bellman-Ford" << std::endl;
        for (int i = 0; i < 100; i++){
            file  << primResults[index] << ";" << kruskalResults[index] << ";" << dijkstraResults[index] << ";" << bellmanFordResults[index] << std::endl;
            index++;
        }
        file.close();

    }else{
        std::cout << "ERROR" << std::endl;
        getchar();
    }
}

void Tests::startTimer(){
    startTime = std::chrono::high_resolution_clock::now();
}

void Tests::stopTimer(){
    endTime = std::chrono::high_resolution_clock::now();
}

long Tests::measuredTime(){
    return std::chrono::duration_cast<std::chrono::microseconds>(Tests::endTime - Tests::startTime).count();
}

void Tests::addDijkstra(long duration, int *index, int where){
    dijkstraResults[index[where]] = duration;
    index[where]++;
}

void Tests::addBellmanFord(long duration, int *index, int where){
    bellmanFordResults[index[where]] = duration;
    index[where]++;
}

void Tests::addPrim(long duration, int *index, int where){
    primResults[index[where]] = duration;
    index[where]++;
}

void Tests::addKruskal(long duration, int *index, int where){
    kruskalResults[index[where]] = duration;
    index[where]++;
}
