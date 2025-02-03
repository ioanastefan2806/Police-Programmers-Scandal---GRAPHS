#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>

using namespace std;

// Fisiere de Input + Output
const string INPUT_FILE = "scandal.in";
const string OUTPUT_FILE = "scandal.out";

// Variabile globale
int numNodes, numEdges, topoIndex, numComponents;
vector<int> values, visited, topoOrder, component;
vector<vector<int>> graph, transposedGraph, componentNodes;

// Functie pentru obtinerea unui nod pozitiv pt nodul negativ + return index
int getNodeIndex(int x) {
    return x < 0 ? numNodes + (-x) : x;
}

// Functie pentru adaugarea unei muchii in graf + graful transpus
void addEdge(int x, int y) {
    x = getNodeIndex(x);
    y = getNodeIndex(y);
    graph[x].push_back(y);
    transposedGraph[y].push_back(x);
}

// Functie pentru parcurgerea DFS iterativa + topoSort
void iterativeDFS(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int currentNode = s.top();

        if (visited[currentNode] == 0) {
            visited[currentNode] = 1;
        }

        bool hasUnvisitedChild = false;
        for (int neighbor : graph[currentNode]) {
            if (visited[neighbor] == 0) {
                s.push(neighbor);
                hasUnvisitedChild = true;
                break;
            }
        }

        if (!hasUnvisitedChild) {
            s.pop();
            topoOrder[++topoIndex] = currentNode;
        }
    }
}

// Functie pentru determinarea componentelor tare conexe
void iterativeSSC(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int currentNode = s.top();

        if (visited[currentNode] == 0) {
            visited[currentNode] = 1;
            componentNodes[numComponents].push_back(currentNode);
        }

        bool hasUnvisitedChild = false;
        for (int neighbor : transposedGraph[currentNode]) {
            if (visited[neighbor] == 0) {
                s.push(neighbor);
                hasUnvisitedChild = true;
                break;
            }
        }

        if (!hasUnvisitedChild) {
            s.pop();
        }
    }
}

// Functie pentru citirea inputului
void readInput() {
    ifstream inFile(INPUT_FILE);

    // Citesc dimensiunile grafului
    string line;
    getline(inFile, line);
    istringstream iss(line);
    iss >> numNodes >> numEdges;

    int totalNodes = 2 * numNodes + 1;

    // Redimensionez vectorii + grafuri
    values.resize(totalNodes);
    visited.resize(totalNodes);
    topoOrder.resize(totalNodes);
    component.resize(totalNodes);
    graph.resize(totalNodes);
    transposedGraph.resize(totalNodes);
    componentNodes.resize(totalNodes);

    // Citesc muchii + legaturi
    for (int i = 0; i < numEdges; i++) {
        getline(inFile, line);
        istringstream iss(line);
        int x, y, type;
        iss >> x >> y >> type;

        if (type == 1) {
            y = -y;
        } else if (type == 2) {
            x = -x;
        } else if (type == 3) {
            x = -x;
            y = -y;
        }

        // Adaug muchii in graf si in graful transpus
        addEdge(-x, y);
        addEdge(-y, x);
    }

    inFile.close();
}

// Functie pentru scrierea outputului
void writeOutput(int count, const vector<int>& result) {
    ofstream outputFile(OUTPUT_FILE);
    outputFile << count << endl;
    for (int i = 1; i <= numNodes; i++) {
        if (result[i] == 1) {
            outputFile << i << endl;
        }
    }
    outputFile.close();
}

// Functie pentru initializarea si rularea DFS-ului pentru topoSort
void runTopologicalSort() {
    topoIndex = 0;
    for (int i = 1; i <= 2 * numNodes; i++) {
        if (visited[i] == 0) {
            iterativeDFS(i);
        }
    }
}

// Functie pentru determinarea componentelor tare conexe
void findStronglyConnectedComponents() {
    fill(visited.begin(), visited.end(), 0);
    numComponents = 0;

    for (int i = 2 * numNodes; i >= 1; i--) {
        if (visited[topoOrder[i]] == 0) {
            numComponents++;
            iterativeSSC(topoOrder[i]);
        }
    }

    for (int i = 1; i <= numComponents; i++) {
        for (int node : componentNodes[i]) {
            component[node] = i;
        }
    }
}

// Functie pentru determinarea valorilor de adevar ale nodurilor
void determineValues() {
    for (int i = 1; i <= numNodes; i++) {
        values[i] = (component[i] > component[i + numNodes]) ? 1 : 0;
    }
}

// Functie pentru calcularea numarului de noduri cu valoarea 1
int countTrueNodes() {
    int count = 0;
    for (int i = 1; i <= numNodes; i++) {
        if (values[i] == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    readInput();
    runTopologicalSort();
    findStronglyConnectedComponents();
    determineValues();
    int count = countTrueNodes();
    writeOutput(count, values);
    return 0;
}
