//Implementacja metod klasy Matrix
#include "Matrix.h"

using namespace std;

Matrix::~Matrix() {
    for (int i = 0; i < nodes; i++) {
        delete[] pointer[i];
    }
    delete[] pointer;
}

//Funkcja losowo tworzaca graf
void Matrix::create(int vertices, double density, double maxEdges, bool directed){

	nodes = vertices;
	edges = int(maxEdges * (density / 100));
	bool found;
	int counter = nodes;
	int begin, end;
	int *visited = new int [nodes];
	pointer = new int *[nodes];

	for (int i = 0; i < nodes; i++){

		visited[i] = 0;
		pointer[i] = new int[nodes];

		for (int j = 0; j < nodes; j++){
			pointer[i][j] = 0;
		}
	}

	spanningtree(visited);

	if (!directed){
		for (int i = 0; i < nodes; i++){
			for (int j = 0; j < nodes; j++){
                if (pointer[i][j] != 0) {
                    pointer[j][i] = pointer[i][j];
                }
			}
		}
	}

	while (counter <= edges){

		found = false;
		begin = rand () % nodes;

		for (int i = 0; i < nodes; i++){
			if (i != begin && pointer[begin][i] == 0){
				found = true;
				end = i;
			}
		}

        if (!found) {
            continue;
        }
		pointer[begin][end] = (rand () % 50) + 1;

        if (!directed) {
            pointer[end][begin] = pointer[begin][end];
        }
		counter++;
	}

	delete[] visited;

    if (!testing) {
        display();
    }
}

//Funkcja wyœwietlajaca graf
void Matrix::display(){
    if (pointer == nullptr) {
        cout << "Graph doesn't exist" << endl;

    }else {
        cout << "\nVertices: " << nodes << ", Edges: " << edges;
        cout << "\nAdjacency matrix: " << endl;
        cout << "  ";
        for (int i = 0; i < nodes; i++) {
            if (i > 10) {
                cout << " ";
            } else {
                cout << "  ";
            }
            cout << i;
        }
        cout << "\n" << endl;
        for (int i = 0; i < nodes; i++) {
            cout << i;

            if (i < 10) {
                cout << " ";
            }

            for (int j = 0; j < nodes; j++) {
                if (j > 0) {
                    if (pointer[i][j - 1] >= 10) {
                        cout << " ";
                    } else {
                        cout << "  ";
                    }
                } else {
                    cout << "  ";
                }
                cout << pointer[i][j];
            }
            cout << endl;
        }
    }
}

//Funkcja towrzaca drzewo rozpinajace dla nieskierowanego
void Matrix::spanningtree(int *visited){
	bool check = true;
	int created = 1;
	int node = 0;
	int children, count, temp, rr;
	visited[node] = 1;

	do{
		count = 0;
		children = (rand() % 2) + 2;

		do{
            if (created == nodes) {
                return;
            }
			temp = rand() % nodes;
            if (temp == (node)) {
                continue;
            }
            if (visited[temp] != 0) {
                continue;
            }else {
                pointer[node][temp] = (rand() % 50) + 1;
                visited[temp] = 1;
            }

			count++;
			created++;

		} while (count != children);

		while(true){
			rr =  rand() % nodes;
			if (visited[rr] == 1){
				for (int j = 1; j < nodes; j++){
					if (pointer[rr][j] != 0) {
                        check = false;  break;
                    }
				}
                if (check) {
                    node = rr;
                    break;
                } else {
                    check = true;
                }
			}
		}
	} while (created != nodes);
}

//Funkcja obslugujaca algorytm Dijsktry
void Matrix::dijkstra(int start, int end) {

    if( start>=0 && start<= nodes-1 && (end>=0 && end<=nodes-1)) {
        int temp = start;
        shortestPathUnchecked = nodes;
        shortestPathChecked = 0;
        notChecked = new shortestPath[shortestPathUnchecked];
        for (int i = 0; i < shortestPathUnchecked; i++) {
            notChecked[i].index = i;
        }

        notChecked[temp].distance = 0;
        notChecked[temp].prev = -1;

        do {
            temp = relax(temp);
            shortestPathUnchecked--;
            shortestPathChecked++;
        } while (shortestPathUnchecked != 0);

        if (!testing) {
            displayShortestPath(checked, shortestPathChecked, start, end);
        }

        delete[] notChecked;
        delete[] checked;
    } else {
        cout << "Wrong starting vertex";
    }
}

//Funkcja relaksujaca sasiadow
int Matrix::relax(int index){
	shortestPath *temp;
	int loop;
	int fall = 0;
	int result;
	int mini;
	for (int i = 0; i < shortestPathUnchecked; i++){
		if (index == notChecked[i].index){
			fall = i;
			break;
		}
	}

	for (int i = 0; i < nodes; i++){
		if (pointer[index][i] != 0){
			for (int j = 0 ; j < shortestPathUnchecked; j++){
				if (notChecked[j].index == i){
					if ((notChecked[fall].distance + pointer[index][i]) < notChecked[j].distance || notChecked[j].distance == -1){
                        notChecked[j].distance = notChecked[fall].distance + pointer[index][i];
                        notChecked[j].prev = index;
					}
					break;
				}
			}
		}
	}

	temp = new shortestPath[shortestPathChecked + 1];

    if (shortestPathChecked == 0) {
        temp[0] = notChecked[fall];
    }else {
        loop = 0;
        for (int i = 0; i < shortestPathChecked; i++) {
            temp[i] = checked[i];
            loop++;
        }
        temp[loop] = notChecked[fall];
        delete[] checked;
    }

	loop = 0;
	checked = temp;
	temp = new shortestPath[shortestPathUnchecked - 1];

	for (int i = 0; i < (shortestPathUnchecked - 1); i++){

		if (i == fall){
			loop++;
			temp[i] = notChecked[loop];
        }else{
			temp[i] = notChecked[loop];
		}
		loop++;
	}

	delete[] notChecked;
    notChecked = temp;
	result = notChecked[0].index;
	mini = 10000000;

	for (int i = 0; i < (shortestPathUnchecked - 1); i++){
		if (notChecked[i].distance != -1){
			if (notChecked[i].distance < mini){
				result = notChecked[i].index;
				mini = notChecked[i].distance;
			}
		}
	}
	return result;
}

//Funckja obslugujaca algorytm prima
void Matrix::mstPrim(int start){
	Prim *temp;
	int min, loop, fall;
    mstSize = 0;
	fall = start;
    mstSolved = 0;
    mstUnsolved = nodes;
	notSolved = new Prim[mstUnsolved];

    for (int i = 0; i < mstUnsolved; i++) {
        notSolved[i].index = i;
    }

	while (mstSolved != nodes){
		for (int i = 0; i < nodes; i++){
			if (pointer[fall][i] != 0){
				for (int j = 0; j < mstUnsolved; j++){
					if (notSolved[j].index == i){
						if (notSolved[j].distance > pointer[fall][i] || notSolved[j].distance == 0){
							notSolved[j].distance = pointer[fall][i];
							notSolved[j].prev = fall;
						}
						break;
					}
				}
			}
		}

        mstSize = mstSize + notSolved[start].distance;
		mstSolved++;
		mstUnsolved--;

		//Zwiekszanie listy rozwiazanych

		temp = new Prim[mstSolved];
		loop = 0;

        if (mstSolved == 1) {
            temp[0] = notSolved[start];
        }else {
            for (int i = 0; i < (mstSolved - 1); i++) {
                temp[i] = solved[i];
                loop++;
            }
            temp[loop] = notSolved[start];
            delete[] solved;
        }

		solved = temp;

		//Zmiejszanie listy nie rozwiazanych

		loop = 0;
		temp = new Prim[mstUnsolved];

		for (int i = 0; i < mstUnsolved; i++){
			if (i == start){
				loop++;
				temp[i] = notSolved[loop];
            }else{
				temp[i] = notSolved[loop];
			}
			loop++;
		}

		delete[] notSolved;
		notSolved = temp;
		min = 100;

		for (int i = 0; i < mstUnsolved; i++){
			if (notSolved[i].distance < min && notSolved[i].distance != 0){
				start = i;
				fall = notSolved[i].index;
				min = notSolved[i].distance;
			}
		}
	}

    if (!testing) {
        displayPrim(solved, mstSolved);
    }

	delete[] solved;
}

//Funkcja obslugujaca algorytm Kruskala
void Matrix::mstKruskal(){

    int *temp;
    int ind, tab, tab2;
    mstSize = 0;
    cnt = 0;
    t_size = nodes;
    sizes = new int[t_size];
    tree = new int*[t_size];
    int index = 0;

    for (int i = 0; i < t_size; i++){
        temp = new int[1];
        temp[0] = i;
        tree[i] = temp;
        sizes[i] = 1;
    }

    line = new Kruskal[edges];
    for (int i = 0; i < nodes; i++){
        for (int j = i; j < nodes; j++){
            if (pointer[i][j] != 0){
                line[index].source = i;
                line[index].target = j;
                line[index].weight = pointer[i][j];
                index++;
            }

            if (index == edges) {
                break;
            }
        }

        if (index == edges) {
            break;
        }
    }

    sort(line);
    result = new Kruskal[(nodes - 1)];
    ind = -1;

    while (cnt != (nodes - 1)){

        ind++;

        for (int i = 0; i < t_size; i++){
            for (int j = 0; j < sizes[i]; j++){
                if (tree[i][j] == line[ind].source) {
                    tab = i;
                }

                if (tree[i][j] == line[ind].target) {
                    tab2 = i;
                }
            }
        }

        if (tab == tab2) {
            continue;
        }

        result[cnt] = line[ind];
        cnt++;

        if (tab > tab2) {
            connect(tab2, tab);
        } else {
            connect(tab, tab2);
        }
    }

    for (int i = 0; i < (nodes - 1); i++) {
        mstSize = mstSize + result[i].weight;
    }

    if (!testing) {
        displayKruskal(result, nodes - 1);
    }

    delete[] result;
    delete[] line;
    for (int i = 0; i < t_size; i++) {
        delete tree[i];
    }
    delete tree;
}

//Funkcja obslugujaca algorytm Forda-Bellmana
void Matrix::bellmanFord(int start, int end) {
    if(start >= 0 && start <=nodes-1) {
        int MAX_INT = 64000;
        shortestPathUnchecked = nodes;
        notChecked = new shortestPath[shortestPathUnchecked];
        for (int i = 0; i < shortestPathUnchecked; i++) {
            notChecked[i].index = i;
            notChecked[i].distance = MAX_INT;
            notChecked[i].prev = -1;
        }
        notChecked[start].distance = 0;
        for (int i = 1; i < (nodes - 1); i++) {
            for (int j = 0; j < nodes; j++) {
                for (int m = 0; m < nodes; m++) {
                    if (pointer[j][m] != 0 && m != start) {
                        if ((notChecked[j].distance + pointer[j][m]) < notChecked[m].distance) {
                            notChecked[m].distance = notChecked[j].distance + pointer[j][m];
                            notChecked[m].prev = j;
                        }
                    }
                }
            }
        }
        if (!testing) {
            displayShortestPath(notChecked, shortestPathUnchecked, start, end);
        }
        delete[] notChecked;
    } else {
        cout << "Wrong starting vertex";
        return;
    }
}

//Wczytanie grafu
int Matrix::loadGraph(string filename, bool directed){
	int *temp;
	int a, b, c;
	string line;
	ifstream plik(filename);
	if (plik.good()){

		plik >> a >> b;
		edges = a;
		nodes = b;
		pointer = new int*[nodes];

		for (int i = 0; i < nodes; i++){
			temp = new int[nodes];
			for (int j = 0; j < nodes; j++){
				temp[j] = 0;
			}
			pointer[i] = temp;
		}

		for (int i = 0; i < edges; i++){
			plik >> a >> b >> c;
			pointer[a][b] = c;
		}

		if (!directed){
			for (int i = 0; i < nodes; i++){
				for (int j = 0; j < nodes; j++){
                    if (pointer[i][j] != 0) {
                        pointer[j][i] = pointer[i][j];
                    }
				}
			}
		}
		plik.close();
	}
	else {
        cout << "ERROR" << endl;
        return -1;
    }
    return nodes;
}