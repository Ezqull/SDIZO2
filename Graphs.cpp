//Implementacja metod klasy Graphs
#include "Graphs.h"


using namespace std;

//Wlanczanie/Wylanczanie testowania
void Graphs::switch_test(){
	testing = !testing;
}

//Funckja drukujaca wynik dzialania algorytmu Disjkstry i Bellmana-Forda
void Graphs::displayShortestPath(Dijkstra *list, int size, int start, int end){

    Dijkstra *path = new Dijkstra[size];

    for (int i = 0; i < size; i++) {
        if(list[i].index == end){
            path[0] = list[i];
        }
    }

    int k = 0;
    int fail = 0;

    do{
        for (int i = 0; i < size; i++) {
            if (path[k].prev == list[i].index) {
                k++;
                path[k] = list[i];
                break;
            }else {
                fail++;
            }
        }

        if (fail == size){
            cout << "Path doesn't exist" << endl;
            return;
        }

    }while (path[k].index != start);


    cout << "Solution:" << endl;
    for (int i = k; i >= 0; i--)
    {
        cout << "\nIndex: " << path[i].index << endl;;
        cout << "Dist: " << path[i].distance << endl;
        cout << "Prev: " << path[i].prev << endl;
    }
}

//Funckja drukujaca wynik dzialania algorytmu Primy
void Graphs::displayPrim(Prim *list, int size){
	cout << "Solution:" << endl;
	cout << "Total mst size: " << mst_size << endl;
	cout << "\nInde:  ";
	for (int i = 0; i < size; i++){

		cout << list[i].index;

        if (list[i].index > 9) {
            cout << " ";
        } else {
            cout << "  ";
        }
	}

	cout << "\nDist:  ";

	for (int i = 0; i < size; i++){
		cout << list[i].distance;
        if (list[i].distance > 9) {
            cout << " ";
        } else {
            cout << "  ";
        }
	}

	cout << "\nPrev:";

	for (int i = 0; i < size; i++){
        if (list[i].prev == -1) {
            cout << " ";

        } else if (list[i].prev < 9) {
            cout << "  ";

        } else {
            cout << " ";
        }

		cout << list[i].prev;
	}
}

//Funkcja sortujaca krawedzie
void Graphs::sort(Kruskal *target){
	Kruskal temp;
	for (int j = 1; j < edges; j++){
		for (int i = j; i < edges; i++){
			if (target[i].weight < target[j - 1].weight){
				temp = target[j - 1];
				target[j - 1] = target[i];
				target[i] = temp;
			}
		}
	}
}

//Funkcja laczaca dwa podzbiory w algorytmie Kruskala
void Graphs::connect(int tab, int tab2){
	int loop = 0;
	int *temp;
	int **temp2;
	int *temp3;
	int start = sizes[tab];
	int ind = 0;
	sizes[tab] = sizes[tab] + sizes[tab2];
	temp = new int[sizes[tab]];
	for (int i = 0; i < sizes[tab]; i++){

		if (i < start){
			temp[i] = tree[tab][i];

		}else{
			temp[i] = tree[tab2][ind];
			ind++;
		}
	}

	delete[] tree[tab];
	tree[tab] = temp;
	t_size--;
	temp2 = new int*[t_size];
	temp3 = new int[t_size];

	for (int i = 0; i < t_size; i++){

		if (i == tab2){
			loop++;
			temp2[i] = tree[loop];
			temp3[i] = sizes[loop];

		}else{
			temp2[i] = tree[loop];
			temp3[i] = sizes[loop];
		}

		loop++;
	}
	delete[] sizes;
	delete[] tree;
	sizes = temp3;
	tree = temp2;
}

//Funckja drukujaca wynik dzialania algorytmu Kruskala
void Graphs::displayKruskal(Kruskal *list, int size){

	cout << "Solution:" << endl;
	cout << "Total mst size: " << mst_size << endl;
	cout << "\nList of used edges: " << endl;

	for (int i = 0; i < size; i++){
		cout << "\nConnection from" << list[i].source << " to " << list[i].target << ", weight " << list[i].weight;
	}
}