#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cmath>

#define MAX 10
#define M_PI 3.14159265358979323846

using namespace std;

int graph[MAX][MAX];
int degree[MAX];
int path[MAX];
int visitedEdges[MAX][MAX];
int pathIndex = 0;

void addEdge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
    degree[u]++;
    degree[v]++;
    visitedEdges[u][v] = 0;
    visitedEdges[v][u] = 0;
}

void findEulerPath(int u) {
    for (int v = 0; v < MAX; v++) {
        while (graph[u][v] > 0) {
            graph[u][v]--;
            graph[v][u]--;
            findEulerPath(v);
        }
    }
    path[pathIndex++] = u;
}

void drawGraph() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int radius = 20;
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int angle = 360 / 10;
    int positions[10][2];

    for (int i = 0; i < 10; ++i) {
        int x = centerX + 100 * cos(i * angle * M_PI / 180);
        int y = centerY + 100 * sin(i * angle * M_PI / 180);
        positions[i][0] = x;
        positions[i][1] = y;
        circle(x, y, radius);
        char label[3];
        sprintf(label, "%d", i);
        outtextxy(x - radius / 2, y - radius / 2, label);
    }

    for (int i = 0; i < MAX; ++i) {
        for (int j = i + 1; j < MAX; ++j) {
            if (visitedEdges[i][j] == 0 && graph[i][j] == 1) {
                line(positions[i][0], positions[i][1], positions[j][0], positions[j][1]);
                visitedEdges[i][j] = 1;
                visitedEdges[j][i] = 1;
            }
        }
    }

    for (int i = 0; i < pathIndex - 1; ++i) {
        setcolor(RED);
        line(positions[path[i]][0], positions[path[i]][1], positions[path[i + 1]][0], positions[path[i + 1]][1]);
    }

    getch();
    closegraph();
}

void readGraphFromFile(const char* filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Không th? m? file!" << endl;
        exit(1);
    }

    int u, v;
    while (infile >> u >> v) {
        addEdge(u, v);
    }

    infile.close();
}

void writeEulerPathToFile(const char* filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Không th? m? file!" << endl;
        exit(1);
    }

    for (int i = 0; i < pathIndex; i++) {
        outfile << path[i] << " ";
    }
    outfile << endl;
    outfile.close();
}

int main() {
    // Kh?i t?o d? th?
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            graph[i][j] = 0;
            visitedEdges[i][j] = 0;
        }
        degree[i] = 0;
    }

    // Ð?c d? li?u t? file
    readGraphFromFile("input.txt");

    // Tìm chu trình Euler b?t d?u t? d?nh 0
    findEulerPath(0);

    // In chu trình Euler ra màn hình
    cout << "Chu trình Euler: ";
    for (int i = 0; i < pathIndex; i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    // Ghi chu trình Euler ra file
    writeEulerPathToFile("output.txt");

    // V? d? th?
    drawGraph();

    return 0;
}

