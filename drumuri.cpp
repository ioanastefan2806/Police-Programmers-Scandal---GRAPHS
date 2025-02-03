#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>
#include <climits>

using namespace std;

// Fisiere de Input + Output
const string INPUT_FILE = "drumuri.in";
const string OUTPUT_FILE = "drumuri.out";


// Structura pentru muchie
struct Edge {
    int node;          // nod destinatie
    long long cost;    // costul asociat
    Edge(int n, long long c) : node(n), cost(c) {}
};

// Variabile globale
int N, M, x, y, z;
// Grafur si Transpusul
vector<vector<Edge>> graph, transposeGraph;

// Functie pentru citirea inputului
void readInput() {
    ifstream inFile(INPUT_FILE);
    inFile >> N >> M;

    // Redimensionez grafurile
    graph.resize(N + 1);
    transposeGraph.resize(N + 1);

    // Citesc si populez graful si graful transpus
    for (int i = 0; i < M; ++i) {
        int a, b;
        long long c;
        inFile >> a >> b >> c;
        graph[a].emplace_back(b, c);
        transposeGraph[b].emplace_back(a, c);
    }

    // Citesc punctele de start
    inFile >> x >> y >> z;
    inFile.close();
}

// Functie pentru scrierea outputului
void writeOutput(long long result) {
    ofstream outFile(OUTPUT_FILE);
    outFile << result << endl;
    outFile.close();
}

// Functie pentru algoritmul Dijkstra
vector<long long> dijkstra(int start,
const vector<vector<Edge>>& graph) {
    // Coada de prioritati pentru noduri -> ordonata dupa cost
    priority_queue<pair<long long, int>,
    vector<pair<long long, int>>, greater<>> pq;

    // Vector pentru distante -> initializat cu LLONG_MAX
    vector<long long> dist(N + 1, LLONG_MAX);
    dist[start] = 0;  // Distanta de la start la start este 0
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [current_cost, node] = pq.top();
        pq.pop();

        // Sar peste nodurile cu cost mai mare decat cel curent
        if (current_cost > dist[node]) continue;

        // Actualizez distantele pentru vecinii nodului curent
        for (const Edge& edge : graph[node]) {
            long long newCost = current_cost + edge.cost;
            if (newCost < dist[edge.node]) {
                dist[edge.node] = newCost;
                pq.emplace(newCost, edge.node);
            }
        }
    }
    return dist;
}

// Functie pentru calcularea costului minim
long long calculateMinCost(const vector<long long>& distX,
const vector<long long>& distY,
const vector<long long>& distZ) {
    long long minCost = LLONG_MAX;

    // Parcurg toate nodurile si calculez costul minim
    for (int i = 1; i <= N; ++i) {
        if (distX[i] != LLONG_MAX && distY[i]
        != LLONG_MAX && distZ[i] != LLONG_MAX) {
            minCost = min(minCost, distX[i] + distY[i] + distZ[i]);
        }
    }
    return minCost;
}

int main() {
    // Citirea inputului
    readInput();

    // Pornesc cu Dijkstra din fiecare punct
    vector<long long> distX = dijkstra(x, graph);
    vector<long long> distY = dijkstra(y, graph);
    vector<long long> distZ = dijkstra(z, transposeGraph);

    // Calculez costului minim
    long long minCost = calculateMinCost(distX, distY, distZ);

    // Scriu rezultatul in output
    writeOutput(minCost);

    return 0;
}
