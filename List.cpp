//Implementacja metdo klasy List
#include <iostream>
#include <string>
#include <cstdlib>
#include "List.h"

using namespace std;

List::~List(){
    if (head != nullptr) {
        rekdel(head);
    }
}

void List::rekdel(Node *node){
    if (node->next != nullptr) {
        rekdel(node->next);
    }

    if (node->head != nullptr) {
        edgedel(node->head);
    }
    delete node;
}

void List::edgedel(Edge *edge){
    if (edge->next != nullptr) {
        edgedel(edge->next);
    }
    delete edge;
}

//Funkcja losowo tworzaca graf
void List::create(int vertices, double density, double maxEdges, bool directed){

	Edge *els;
	Edge *newEdge;
	Edge *revEdge;
	nodes = vertices;
	edges = int(maxEdges * (density / 100));
	Node **vNodes = new Node*[nodes];
	int *visited = new int[nodes];
	head = new Node();
	int counter = nodes;
	int begin, end;

    spanningTree();

	Node *temp = head;
	for (int i = 0; i < nodes; i++){
        vNodes[i] = temp;
		temp = temp->next;
	}

	if (!directed){

		temp = head;

		while (temp != nullptr){
			els = temp->head;
			while (els != nullptr){
				if (els->target->index > temp->index){
					newEdge = new Edge();
					newEdge->target = els->source;
					newEdge->source = els->target;
					newEdge->weight = els->weight;

					if (els->target->head == nullptr){
						els->target->head = newEdge;
						els->target->tail = newEdge;

					}else{
						els->target->tail->next = newEdge;
						els->target->tail = newEdge;
					}

                    revEdge = new Edge();
                    revEdge->target = newEdge->source;

					els->target->connections++;
				}
				els = els->next;
			}
			temp = temp->next;
		}
	}

	while (counter <= edges){
		for (int i = 0; i < nodes; i++) visited[i] = 0;
		begin = rand() % nodes;
		temp = vNodes[begin];

        if (temp->connections == (nodes - 1)) {
            continue;
        }

		els = temp->head;
		for (int i = 0; i < (temp->connections); i++){
			visited[els->target->index] = 1;
			els = els->next;
		}

		for (end = 0; end < (temp->connections + 1); end++){
			if (end != (temp->index) && visited[end] == 0) break;
		}

		newEdge = new Edge();
		newEdge->weight = (rand() % 50) + 1;
		newEdge->source = temp;
		newEdge->target = vNodes[end];

		if (temp->head == nullptr){
			temp->head = newEdge;
			temp->tail = newEdge;

		}else{
			temp->tail->next = newEdge;
			temp->tail = newEdge;
		}

		if (!directed){
			revEdge = new Edge();
			revEdge->target = newEdge->source;
			revEdge->source = newEdge->target;
			revEdge->weight = newEdge->weight;

			if (revEdge->source->head == nullptr){
				revEdge->source->head = revEdge;
				revEdge->source->tail = revEdge;

			}else{
				revEdge->source->tail->next = revEdge;
				revEdge->source->tail = revEdge;
			}
			revEdge->source->connections++;
		}
		temp->connections++;
		counter++;
	}

    if (!testing) {
        display();
    }

	delete[] visited;
	delete[] vNodes;
}

//Funkcja wyswietlajaca graf
void List::display(){
    if (head == nullptr) {
        cout << "Graph doesn't exist" << endl;
    }else {
        cout << "\nVertices: " << nodes << ", Edges: " << edges;
        cout << "\nList:\n" << endl;
        Node *temp = head;
        while (temp != nullptr) {
            cout << temp->index << ": ";
            Edge *out = temp->head;
            while (out != nullptr) {
                cout << out->target->index << "|" << out->weight << " ";
                out = out->next;
            }
            temp = temp->next;
            cout << endl;
        }
    }
}

//Funkcja towrzaca drzewo rozpinajace dla nieskierowanego
void List::spanningTree(){

	tail = head;
	Node *create = head;
	Node *newNode;
	Edge *child;
	int children, count, rr, ii;
	int created = 1;

	do{
		count = 0;
		children = (rand() % 2) + 2;

		do{
			child = new Edge();
			child->source = create;
			newNode = new Node();
			child->target = newNode;
			newNode->index = created;
			created++;
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			child->weight = (rand() % 50) + 1;

			if (create->head == nullptr){
				create->head = child;
				create->tail = child;

			}else{
				create->tail->next = child;
				create->tail = child;
			}

			create->connections++;
			count++;

            if (created == nodes) {
                return;
            }
		} while (count != children);

		while (create->head != nullptr){
			rr = rand() % (created);
			create = head;
			for (ii = 0; ii < rr; ii++){
				create = create->next;
			}
		}
	} while (created != nodes);

}

//Funkcja obslugujaca algorytm Dijsktry
void List::dijkstra(int start, int end) {

    if((start>=0 && start<=nodes-1) && (end>=0 && end<=nodes-1)) {
        int temp = start;
        shortestPathUnchecked = nodes;
        shortestPathChecked = 0;
        notChecked = new shortestPath[shortestPathUnchecked];

        for (int i = 0; i < shortestPathUnchecked; i++) {
            notChecked[i].index = i;
        }

        notChecked[start].distance = 0;

        do {
            temp = relax(temp);
            shortestPathUnchecked--;
            shortestPathChecked++;
        } while (shortestPathUnchecked != 0);

        if (!testing) {
            displayShortestPath(checked, shortestPathChecked, start, end);
        }
    } else {
        cout << "Wrong value of vertex";
        return;
    }
}

//Funkcja relaksujaca sasiadow
int List::relax(int index){

	shortestPath *temp;
	Node *iter = head;
	Edge *els;
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

    for (int i = 0; i < index; i++) {
        iter = iter->next;
    }

	els = iter->head;

	while (els != nullptr){
		for (int i = 0; i < shortestPathUnchecked; i++){
			if (notChecked[i].index == els->target->index){
				if ((notChecked[fall].distance + els->weight) < notChecked[i].distance || notChecked[i].distance == -1){
                    notChecked[i].distance = notChecked[fall].distance + els->weight;
                    notChecked[i].prev = index;
				}
				break;
			}
		}
		els = els->next;
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
void List::mstPrim(int start){

	Prim *temp;
	Node *iter;
	Edge *edge;
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
		iter = head;
        for (int i = 0; i < fall; i++) {
            iter = iter->next;
        }

        edge = iter->head;
		while (edge != nullptr){
			if (edge->weight != 0){
				for (int j = 0; j < mstUnsolved; j++){
					if (notSolved[j].index == edge->target->index){
						if (notSolved[j].distance > edge->weight || notSolved[j].distance == 0){
							notSolved[j].distance = edge->weight;
							notSolved[j].prev = edge->source->index;
						}
						break;
					}
				}
			}
            edge = edge->next;
		}

        mstSize = mstSize + notSolved[start].distance;
		mstSolved++;
		mstUnsolved--;

		temp = new Prim[mstSolved];
		loop = 0;

        for (int i = 0; i < (mstSolved - 1); i++) {
            temp[i] = solved[i];
            loop++;
        }
        temp[loop] = notSolved[start];
        delete[] solved;

		solved = temp;

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
}

//Funkcja obslugujaca algorytm Kruskala
void List::mstKruskal(){

	Node *iter = head;
	Edge *els;
	bool found;
	int *temp;
	int index2, ind, tab, tab2;
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
		els = iter->head;
		while (els != nullptr){
			if (els->target->index < i){
				line[index].source = i;
				line[index].target = els->target->index;
				line[index].weight = els->weight;
				index++;
			}
			els = els->next;
		}
		iter = iter->next;
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
	delete[] tree;
}

//Funkcja obslugujaca algorytm Forda-Bellmana
void List::bellmanFord(int start, int end) {

    if((start>=0 && start <= nodes-1) && (end>=0 && end <= nodes-1)) {

        Node *temp = head;
        Edge *els;
        shortestPathUnchecked = nodes;
        int MAX_INT = 64000;
        notChecked = new shortestPath[shortestPathUnchecked];

        for (int i = 0; i < shortestPathUnchecked; i++) {
            notChecked[i].index = i;
            notChecked[i].distance = MAX_INT;
        }

        notChecked[start].distance = 0;

        for (int i = 0; i < start; i++) {
            temp = temp->next;
        }

        for (int i = 1; i < (nodes - 1); i++) {
            temp = head;
            for (int j = 0; j < nodes; j++) {
                els = temp->head;
                while (els != nullptr) {
                    if (els->target->index != start) {
                        if ((notChecked[els->source->index].distance + els->weight) <
                            notChecked[els->target->index].distance) {
                            notChecked[els->target->index].distance =
                                    notChecked[els->source->index].distance + els->weight;
                            notChecked[els->target->index].prev =
                                    els->source->index;
                        }
                    }
                    els = els->next;
                }
                temp = temp->next;
            }
        }

        if (!testing) {
            displayShortestPath(notChecked, shortestPathUnchecked, start, end);
        }

        delete[] notChecked;
    } else {
        cout << "Wrong value of vertex";
    }

}

int List::loadGraph(string filename, bool directed){
	Node *temp, *prev;
	Edge *els, *iter, *newEdge, *revEdge;
	int a, b, c;
	string line;
	ifstream file(filename);

	if (file.good()){

		file >> a >> b;
		edges = a;
		nodes = b;
		prev = new Node();
		prev->index = 0;
		head = prev;
		temp = tail;

		for (int i = 1; i < nodes; i++){
			temp = new Node();
			temp->prev = prev;
			prev->next = temp;
			temp->index = i;
			prev = temp;
		}

		tail = temp;

		for (int i = 0; i < edges; i++){
			temp = head;
			file >> a >> b >> c;

            for (int j = 0; j < a; j++) {
                temp = temp->next;
            }

			els = new Edge();
			els->weight = c;
			els->source = temp;

			if (temp->connections == 0){
				temp->head = els;
				temp->tail = els;

			}else{
				iter = temp->tail;
				iter->next = els;
				temp->tail = els;
			}

			temp->connections++;
			temp = head;

            for (int j = 0; j < b; j++) {
                temp = temp->next;
            }
			els->target = temp;
		}

		if (!directed){
			temp = head;
			while (temp != nullptr){
				els = temp->head;
				while (els != nullptr){
					if (els->target->index > temp->index){
						newEdge = new Edge();
						newEdge->target = els->source;
						newEdge->source = els->target;
						newEdge->weight = els->weight;

						if (els->target->head == nullptr){
							els->target->head = newEdge;
							els->target->tail = newEdge;

						}else{
							els->target->tail->next = newEdge;
							els->target->tail = newEdge;
						}

						if (!directed){
							revEdge = new Edge();
							revEdge->target = newEdge->source;
						}

						els->target->connections++;
					}
					els = els->next;
				}
				temp = temp->next;
			}
		}
		file.close();
	}
	else {
        cout << "ERROR" << endl;
        return -1;
    }

    return nodes;
}