#pragma once
#ifndef Tests_h
#define Tests_h
#include <iostream>
#include <chrono>

class Tests{
protected:
    const static int number = 1000;
    double dijkstraResults[number];
    double bellmanFordResults[number];
    double primResults[number];
    double kruskalResults[number];

public:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

    void saveResults(const std::string& filename, int index);
    void startTimer();
    void stopTimer();
    long measuredTime();
    void addDijkstra(long duration, int *index, int where);
    void addBellmanFord(long duration, int *index, int where);
    void addPrim(long duration, int *index, int where);
    void addKruskal(long duration, int *index, int where);
};

#endif