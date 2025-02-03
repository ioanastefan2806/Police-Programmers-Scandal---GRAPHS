#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Fisiere de Input si Output + MOD
const string INPUT_FILE = "numarare.in";
const string OUTPUT_FILE = "numarare.out";
const long long MOD = 1000000007;

// Variabile globale -> acces global
int N, M;
vector<vector<int>> adj1, adj2;

// Functie de Sortare Topologica
// -> algoritmul lui Kahn - sortare topologica dupa
//                          1) Gradul interior al nodurilor
//                          2) Coada de procesare a nodurilor

vector<int> topologicalSort(const vector<vector<int>>& adj) {
    // Initializare grad interior
    vector<int> intDegree(N + 1, 0);

    // Calcularea gradului interior pt. fiecare nod
    for (int i = 1; i <= N; ++i) {
        for (int neighbor : adj[i]) {
            intDegree[neighbor]++;
        }
    }

    // Initializarea cozii si se adauga toate
    // nodurile cu grad int 0
    queue<int> q;
    for (int i = 1; i <= N; ++i) {
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
    vector<int> topoOrder;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);
        for (int neighbor : adj[node]) {
            intDegree[neighbor]--;
            if (intDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return topoOrder;
}

vector<long long> computePaths(const vector<vector<int>>& adj,
const vector<int>& topoOrder) {
    vector<long long> dp(N + 1, 0);
    dp[1] = 1;

    for (int node : topoOrder) {
        for (int neighbor : adj[node]) {
            dp[neighbor] = (dp[neighbor] + dp[node]) % MOD;
        }
    }

    return dp;
}

// Functie care calculeza nr de drumuri comune de la
// nodul 1 la N
long long countCommonPaths() {
    // Fac sortare topologica pe cele doua grafuri
    vector<int> topoOrder1 = topologicalSort(adj1);
    vector<int> topoOrder2 = topologicalSort(adj2);

    // Daca sortarile topologice difera => nu exista drumuri comune
    if (topoOrder1 != topoOrder2) {
        return 0;
    }
    // DP - pentru a stoca nr de drumuri pana la fiecare nod
    // Apelez auxiliara pt. calcul efectiv
    vector<long long> dp1 = computePaths(adj1, topoOrder1);
    vector<long long> dp2 = computePaths(adj2, topoOrder2);

    // Vector de rezultat initializat cu 0
    // Nr de drumuri comune care ajung la nodul 1 este 1
    vector<long long> dpCommon(N + 1, 0);
    dpCommon[1] = 1;

    // Cream unordered_set pe graful 2 pentru a
    // verifica daca un nod este vecin (complexitate mai mica decat Find)
    vector<unordered_set<int>> adj2Set(N + 1);
    for (int i = 1; i <= N; ++i) {
        for (int neighbor : adj2[i]) {
            adj2Set[i].insert(neighbor);
        }
    }

    // Calculez nr de drumuri comune intre cele doua grafuri
    for (int node : topoOrder1) {
        for (int neighbor : adj1[node]) {
            if (adj2Set[node].count(neighbor)) {
                dpCommon[neighbor] = (dpCommon[neighbor]
                + dpCommon[node]) % MOD;
            }
        }
    }

    // Returnez rezultatul
    return dpCommon[N];
}

// Functie pentru scrierea Outputului
void writeOutput(long long result) {
    ofstream outFile(OUTPUT_FILE);
    outFile << result << endl;
    outFile.close();
}

int main() {
    ifstream inFile(INPUT_FILE);
    inFile >> N >> M;

    // Ajustez dimensiunile listelor de adiacenta
    adj1.resize(N + 1);
    adj2.resize(N + 1);

    // Populez listele de adiacenta
    for (int i = 0; i < M; ++i) {
        int u, v;
        inFile >> u >> v;
        adj1[u].push_back(v);
    }
    for (int i = 0; i < M; ++i) {
        int u, v;
        inFile >> u >> v;
        adj2[u].push_back(v);
    }
    inFile.close();

    // Calculez nr de drumuri comune
    // si scriu rezultatul in Output
    long long result = countCommonPaths();
    writeOutput(result);

    return 0;
}
