#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define V 8
#define M_PI 3.14159265358979323846

int graph[V][V];
int path[V];

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

int isSafe(int v, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

int hamCycleUtil(int pos) {
    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    for (int v = 1; v < V; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1) == 1)
                return 1;

            path[pos] = -1;
        }
    }

    return 0;
}

int hamCycle() {
    path[0] = 0;
    if (hamCycleUtil(1) == 0) {
        printf("Giai phap khong ton tai\n");
        return 0;
    }

    return 1;
}

void printSolution() {
    printf("Chu trinh Hamilton: ");
    for (int i = 0; i < V; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]);
}

void drawGraph() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int radius = 20;
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int angle = 360 / V;
    int positions[V][2];

    for (int i = 0; i < V; ++i) {
        int x = centerX + 100 * cos(i * angle * M_PI / 180);
        int y = centerY + 100 * sin(i * angle * M_PI / 180);
        positions[i][0] = x;
        positions[i][1] = y;
        circle(x, y, radius);
        char label[3];
        sprintf(label, "%d", i);
        outtextxy(x - radius / 2, y - radius / 2, label);
    }

    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (graph[i][j] == 1) {
                line(positions[i][0], positions[i][1], positions[j][0], positions[j][1]);
            }
        }
    }

    for (int i = 0; i < V - 1; ++i) {
        setcolor(RED);
        line(positions[path[i]][0], positions[path[i]][1], positions[path[i + 1]][0], positions[path[i + 1]][1]);
    }

    setcolor(RED);
    line(positions[path[V - 1]][0], positions[path[V - 1]][1], positions[path[0]][0], positions[path[0]][1]);

    getch();
    closegraph();
}

void readFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Không the mo file!\n");
        exit(1);
    }

    int u, v;
    while (fscanf(file, "%d %d", &u, &v) != EOF) {
        addEdge(u, v);
    }

    fclose(file);
}

void writeToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!hamCycle()) {
        fprintf(file, "Giai phap khong ton tai\n");
    } else {
        for (int i = 0; i < V; i++) {
            fprintf(file, "%d ", path[i]);
        }
        fprintf(file, "%d\n", path[0]);
    }
    fclose(file);
}
void measureHamiltonianCycle() 
{ 
	const int numRuns = 100;
	 long long totalDuration = 0; 
	 size_t memoryUsed = sizeof(graph) + sizeof(path); 
	 
	for (int i = 0; i < numRuns; ++i) { 
	  for (int j = 0; j < V; j++) { 
	  	for (int k = 0; k < V; k++){ 
	   			graph[j][k] = 0;
			} 
			   path[j] = -1; 
		} 
			   
		readFromFile("input.txt"); 
		
		auto start = high_resolution_clock::now(); 
		hamCycle(); 
		auto stop = high_resolution_clock::now(); 
		auto duration = duration_cast<microseconds>(stop - start); 
		totalDuration += duration.count(); 
	} 
		
	double averageDuration = static_cast<double>(totalDuration) / numRuns; 
	cout << "Thoi gian thuc hien trung binh: " << averageDuration << " microseconds\n"; 
	cout << "Bo nho su dung: " << memoryUsed << " bytes\n"; 
}

	
int main() {
  
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;
            
	
    for (int i = 0; i < V; i++)
		path[i] = -1;
		
	
    measureHamiltonianCycle();
    readFromFile("input.txt");
	
    
    if (hamCycle()) {
        printSolution();
        drawGraph();
    }
	
    
    writeToFile("output.txt");
	
    return 0;
}
