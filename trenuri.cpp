#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <sstream>

using namespace std;

// Fisiere de Input + Output
const string INPUT_FILE = "trenuri.in";
const string OUTPUT_FILE = "trenuri.out";

// Variabile globale
string startCity, endCity;
int n;
unordered_map<string, int> cityMap;
vector<string> cityList;
vector<vector<int>> adjList;
vector<int> intDegree;

// Functie pentru impartirea unui string in tokenuri
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Functie pentru citirea inputului
void readInput() {
    ifstream inFile(INPUT_FILE);
    string line;
    // Citesc prima linie pentru a obtine orasele de start si final
    getline(inFile, line);
    auto cities = split(line, ' ');
    startCity = cities[0];
    endCity = cities[1];

    // Citesc a doua linie pentru a obtine numarul de drumuri
    getline(inFile, line);
    n = stoi(line);

    int index = 0;
    for (int i = 0; i < n; i++) {
        // Citesc fiecare linie => drum intre doua orase
        if (getline(inFile, line)) {
            cities = split(line, ' ');
            string from = cities[0];
            string to = cities[1];

            // Adaug orasele in cityMap daca nu sunt deja
            if (cityMap.find(from) == cityMap.end()) {
                cityMap[from] = index++;
                cityList.push_back(from);
                adjList.push_back({});
                intDegree.push_back(0);
            }
            if (cityMap.find(to) == cityMap.end()) {
                cityMap[to] = index++;
                cityList.push_back(to);
                adjList.push_back({});
                intDegree.push_back(0);
            }
            // Adaug drumul in lista de adiacenta
            adjList[cityMap[from]].push_back(cityMap[to]);
            intDegree[cityMap[to]]++;
        }
    }

    inFile.close();
}

// Functie de Sortare Topologica
// -> algoritmul lui Kahn - sortare topologica dupa
//                          1) Gradul interior al nodurilor
//                          2) Coada de procesare a nodurilor
vector<int> topologicalSort() {
    int V = cityMap.size();
    queue<int> q;
    vector<int> topoOrder;

    // Adaug in coada toate nodurile cu gradul int 0
    for (int i = 0; i < V; i++) {
        if (intDegree[i] == 0) {
            q.push(i);
        }
    }

    // Determinarea ordinii topologice
    // -Cat timp coada nu e goala:
    //      1. iau nodul din fata
    //      2. il adaug in topoOrder
    //      3. ii parcurg toti vecinii si le decrementez
    //         gradul interior
    //      4. daca un vecin are gradul int 0 il adaug in
    //         coada
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        // Reducem gradul int pentru vecini
        for (int v : adjList[u]) {
            intDegree[v]--;
            if (intDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return topoOrder;
}

// Functie pentru calcularea celui mai lung drum in graf
long longestPath() {
    int V = cityMap.size();
    vector<int> topoOrder = topologicalSort();
    vector<int> dist(V, INT_MIN);

    // Initializez distanta catre nodul de start cu 0
    dist[cityMap[startCity]] = 0;

    // Procesez nodurile dupa topoSort
    for (int u : topoOrder) {
        if (dist[u] != INT_MIN) {
            for (int v : adjList[u]) {
                if (dist[v] < dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                }
            }
        }
    }

    // Returnez rezultatul
    int endDist = dist[cityMap[endCity]];
    if (endDist == INT_MIN) {
        return -1;
    } else {
        return endDist + 1;
    }
}

// Functie pentru scrierea outputului
void writeOutput(long result) {
    ofstream outFile(OUTPUT_FILE);
    outFile << result << endl;
    outFile.close();
}

int main() {
    // Citesc inputul
    readInput();

    // Calculez cel mai lung drum
    long result = longestPath();

    // Scriu outputul
    writeOutput(result);

    return 0;
}
