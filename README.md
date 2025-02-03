# 🎓 Copyright Ioana Stefan 322CA - 2024  

# 📌 README - Tema2: Police, Programmers & Scandal - GRAPHS 🚔👨‍💻🔥

## 🚀 Problem 1: COUNTING 🔢

We compute the number of **common elementary paths** from node **1 to N** in two **Directed Acyclic Graphs (DAGs)** using **topological sorting** and **dynamic programming**.

### 🛠 Algorithm Logic

1️⃣ **Topological Sorting**:
   - For each graph, we apply **Kahn's Algorithm** to perform topological sorting.
   - We compute the **in-degree** of each node and use it to determine the topological order.

2️⃣ **Path Counting**:
   - We use **dynamic programming** to calculate the number of paths from **node 1** to each node in the **topological order** for both graphs.

3️⃣ **Common Paths Verification**:
   - We check if the **two topological orderings** are identical.
   - We create an `unordered_set` to **quickly check edge existence** in the second graph.
   - We use the previously computed values to find the number of **common paths** using dynamic programming.

### ⏳ Complexity Analysis

- **Topological Sorting**: **O(N + M)** (N = nodes, M = edges)
- **Path Calculation**: **O(N + M)**
- **Common Path Verification**: **O(N + M)**
- **Total Complexity**: **O(N + M)**

### 📚 References
1. [Topological Sorting](https://www.geeksforgeeks.org/topological-sorting/)
2. [Dynamic Programming](https://www.geeksforgeeks.org/dynamic-programming/#dynamic-programming-dp-algorithm)
3. [Topological Sorting - Indegree Solution](https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)

---

## 🚆 Problem 2: TRAINS 🚂

We compute the **longest path** in a **DAG** representing a train network between cities using **topological sorting** and **dynamic programming**.

### 🛠 Algorithm Logic

1️⃣ **Input Reading**:
   - Parse the input file to extract **start city, destination city**, and number of train routes.
   - Construct the **adjacency list** and compute the **in-degree** for each node.

2️⃣ **Topological Sorting**:
   - Apply **Kahn's Algorithm** using a queue to process nodes with **in-degree 0**.

3️⃣ **Longest Path Calculation**:
   - Initialize **dist[start] = 0** and others to **INT_MIN**.
   - Process nodes in **topoSort order** and update distances dynamically.

4️⃣ **Result Computation**:
   - Check if the destination node is reachable.
   - Return the longest distance or `-1` if unreachable.

### ⏳ Complexity Analysis

- **Topological Sorting**: **O(N + M)**
- **Longest Path Computation**: **O(N + M)**
- **Total Complexity**: **O(N + M)**

### 📚 References
1. [Topological Sorting](https://www.geeksforgeeks.org/topological-sorting/)
2. [Dynamic Programming](https://www.geeksforgeeks.org/dynamic-programming/#dynamic-programming-dp-algorithm)
3. [Longest Path in DAG](https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/)

---

## 🛣️ Problem 3: ROADS 🏙️🚖

We compute the **minimum cost of common paths** between three starting points in a **DAG** using **Dijkstra's Algorithm**.

### 🛠 Algorithm Logic

1️⃣ **Input Reading**:
   - Parse the input file to extract **N (nodes), M (edges)**.
   - Construct **adjacency lists** for the main graph and its **transposed graph**.
   - Extract the **three starting points (x, y, z)**.

2️⃣ **Dijkstra's Algorithm**:
   - Run **Dijkstra** from **x and y** in the main graph.
   - Run **Dijkstra** from **z** in the **transposed graph**.
   - This helps compute distances to a **common node (NC)** from all three starting points.

3️⃣ **Minimum Cost Calculation**:
   - Compare the computed distances and find the minimum **combined path cost**.

4️⃣ **Output Result**:
   - Write the computed result to the output file.

### ⏳ Complexity Analysis

- **Dijkstra's Algorithm**: **O((N + M) log N)** per start point.
- **Minimum Cost Calculation**: **O(N)**.
- **Total Complexity**: **O((N + M) log N)**.

### 📚 References
1. [Dijkstra's Algorithm](https://www.geeksforgeeks.org/introduction-to-dijkstras-shortest-path-algorithm/#pseudo-code-for-dijkstras-algorithm)
2. [Graph Transposition](https://www.geeksforgeeks.org/transpose-graph/)

---

## 🔥 Problem 4: SCANDAL 😡

We solve the **2-SAT (2-Satisfiability Problem)** using **Kosaraju's Algorithm** to find **Strongly Connected Components (SCCs)** in a directed graph.

### 🛠 Algorithm Logic

1️⃣ **Input Reading**:
   - Parse the input to extract **nodes, edges**, and construct adjacency lists for both **main and transposed graphs**.

2️⃣ **Implication Graph Construction**:
   - Represent each **literal** and its **negation** as distinct nodes.
   - Add implication edges to correctly model the **2-SAT constraints**.

3️⃣ **Kosaraju's Algorithm**:
   - **First DFS Traversal** → Compute **topological order**.
   - **Second DFS Traversal** → Identify **SCCs**.
   - Check if a **literal and its negation** exist in the same SCC (logical contradiction).

4️⃣ **Truth Assignment**:
   - Determine the truth values of variables based on SCC order.

5️⃣ **Output Result**:
   - Compute and write the number of variables assigned `True`.

### ⏳ Complexity Analysis

- **Kosaraju's Algorithm**: **O(N + M)**.
- **Truth Value Assignment**: **O(N)**.
- **Total Complexity**: **O(N + M)**.

### 📚 References
1. [Strongly Connected Components (SCC)](https://www.geeksforgeeks.org/strongly-connected-components/)
2. [2-SAT Problem](https://www.geeksforgeeks.org/2-satisfiability-2-sat-problem/)

---

🚀 **Enjoy coding and solving graph problems!** 👨‍💻📊🔥
