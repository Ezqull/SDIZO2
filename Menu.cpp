#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "List.h"
#include "Menu.h"
#include "Testing.h"

using namespace std;

void Menu::create_ui(Graphs *gg){
    int nodes, edge;
    double maxedge;
    double mindensity;
    char input;

    cout << "Enter number of vertices: ";
    cin >> nodes;
    if (nodes <= 1) {
        cout << "\nNumber of vertices must be higher than 1" << endl;
        return;
    }

    cout << "\nCreate graph:\nD - Directed\nU - Undirected" << endl;
    cin >> input;

    switch (input) {
        case 'd':{
            directed = true;
            maxedge = nodes * (nodes - 1);
            break;
        }

        case 'u':{
            directed = false;
            maxedge = (nodes * (nodes - 1))/2;
            break;
        }
    }

    mindensity = ceil((((double)nodes - 1) * 100) / maxedge);

    cout << "Enter desired density, > " << mindensity << "%" << endl;
    cin >> edge;
    if(edge < mindensity || edge > 100) {
        return;
    }

    size_n = nodes;
    exists = true;
    gg->create(nodes, edge, maxedge, directed);
}

void Menu::prim(Graphs *gg){
    int node;
    if (directed) {
        cout << "\nGraph can't be directed" << endl;
        return;

    }else {
        if (!exists) {
            cout << "\nGraph doesn't exist" << endl;
            return;

        }else {
            cout << "Enter beginning vertex [0 - " << size_n - 1 << "]:" << endl;
            cin >> node;

            if((node < 0 || node > (size_n - 1))){
                return;
            }

            gg->mstPrim(node);
        }
    }
}

void Menu::kruskal(Graphs *gg)
{
    if (directed) {
        cout << "\nGraph can't be directed" << endl;
    }else {
        if (!exists) {
            cout << "\nGraph doesn't exist" << endl;
        } else {
            gg->mstKruskal();
        }
    }
}

void Menu::dijkstra(Graphs *gg)
{
    int start;
    int end;
    if (!directed) {
        cout << "\nGraph can't be undirected" << endl;
    }else {
        if (!exists) {
            cout << "\nGraph doesn't exist" << endl;
        } else {
            cout << "Enter beginning vertex [0 - " << size_n - 1 << "]:" << endl;
            cin >> start;

            if((start < 0 || start > (size_n - 1))){
                return;
            }

            cout << "Enter ending vertex [0 - " << size_n - 1 << "]:" << endl;
            cin >> end;

            if((end < 0 || end > (size_n - 1))){
                return;
            }

            gg->dijkstra(start, end);
        }
    }
}

void Menu::bellmanFord(Graphs *gg){
    int start;
    int end;
    if (!directed) {
        cout << "\nGraph can't be undirected" << endl;
    }else {
        if (!exists) {
            cout << "\nGraph doesn't exist" << endl;
        } else {
            cout << "Enter beginning vertex [0 - " << size_n - 1 << "]:" << endl;
            cin >> start;

            if((start < 0 || start > (size_n - 1))){
                return;
            }

            cout << "Enter ending vertex [0 - " << size_n - 1 << "]:" << endl;
            cin >> end;

            if((end < 0 || end > (size_n - 1))){
                return;
            }

            gg->bellmanFord(start, end);
        }
    }
}

void Menu::autoTest() {
    matrix.switch_test();
    list.switch_test();
    int ii;
    cout << "[MAX 2000] Graph size: ";
    cin >> ii;
    if (ii > 2000 || ii < 1) {
        cout << "\nWrong value" << endl;
    } else {
        testing.loopTests(matrix, list, ii);
    }
    matrix.switch_test();
    list.switch_test();
}

void Menu::loadMenuList() {
    string filename;
    char input;
    cout << "Enter file name: ";
    cin >> filename;
    cout << filename;

    cout << "\nCreate graph:\nD - Directed\nU - Undirected" << endl;
    cin >> input;

    switch (input) {
        case 'd':{
            directed = true;
            break;
        }

        case 'u':{
            directed = false;
            break;
        }

        default:
            break;
    }
    size_n = list.loadGraph(filename, directed);
    exists = true;
}

void Menu::loadMenuMatrix() {
    string filename;
    char input;
    cout << "Enter file name: ";
    cin >> filename;
    cout << filename;

    cout << "\nCreate graph:\nD - Directed\nU - Undirected" << endl;
    cin >> input;

    switch (input) {
        case 'd':{
            directed = true;
            break;
        }

        case 'u':{
            directed = false;
            break;
        }

        default:
            break;
    }

    size_n = matrix.loadGraph(filename, directed);
    exists = true;
}

void Menu::listMenu(){
    while(1){
        cout << secondMenu;
        char input1;
        cin >> input1;

        switch (input1) {

            case 'r':{
                loadMenuList();
                break;
            }

            case 'g':{
                create_ui(&list);
                break;
            }

            case 's':{
                list.display();
                break;
            }


            case 'p':{
                prim(&list);
                break;
            }

            case 'k':{
                kruskal(&list);
                break;
            }

            case 'd':{
                dijkstra(&list);
                break;
            }

            case 'b':{
                bellmanFord(&list);
                break;
            }

            case 'q':{
                return;
            }

            default:
                break;
        }
    }
}

void Menu::matrixMenu(){
    while (1){
        cout << secondMenu;
        char input1;
        cin >> input1;

        switch (input1) {

            case 'r':{
                loadMenuMatrix();
                break;
            }

            case 'g':{
                create_ui(&matrix);
                break;
            }

            case 's':{
                matrix.display();
                break;
            }


            case 'p':{
                prim(&matrix);
                break;
            }

            case 'k':{
                kruskal(&matrix);
                break;
            }

            case 'd':{
                dijkstra(&matrix);
                break;
            }

            case 'b':{
                bellmanFord(&matrix);
                break;
            }

            case 'q':{
                return;
            }

            default:
                break;
        }
    }
}

void Menu::menu() {

    while (true){
        cout << firstMenu;
        char input;
        cin >> input;

        switch (input) {

            case 'm':{
                matrixMenu();
                break;
            }

            case 'l':{
                listMenu();
                break;
            }

            case 't':{
                autoTest();
                break;
            }

            case 'q':{
                return;
            }
        }
    }
}
