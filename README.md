# Graph Algorithms in C++

A comprehensive collection of graph algorithms and graph-theoretic utilities implemented in modern C++.

This project was created to study graph theory, algorithm design, data structures, and complexity analysis through practical implementations of classical graph algorithms. It supports both directed and undirected graphs, weighted and unweighted graphs, and includes algorithms for traversal, shortest paths, minimum spanning trees, connectivity analysis, graph properties, and advanced graph theory concepts.

---

## Features

### Graph Traversal

#### Breadth-First Search (BFS)
Explores vertices level by level from a starting vertex.

Applications:
- Shortest paths in unweighted graphs
- Connectivity analysis
- Network broadcasting

**Complexity:** `O(V + E)`

---

#### Depth-First Search (DFS)
Explores a graph by visiting vertices as deeply as possible before backtracking.

Applications:
- Graph traversal
- Cycle detection
- Component analysis

**Complexity:** `O(V + E)`

---

#### Recursive DFS
Recursive implementation of Depth-First Search.

**Complexity:** `O(V + E)`

---

## Shortest Path Algorithms

### Dijkstra's Algorithm
Computes shortest paths from a source vertex to all other vertices in graphs with non-negative edge weights.

**Complexity:** `O((V + E) log V)`

---

### Bellman-Ford Algorithm
Computes shortest paths and supports graphs with negative edge weights.

Features:
- Detects negative-weight cycles

**Complexity:** `O(VE)`

---

### Floyd-Warshall Algorithm
Computes shortest paths between all pairs of vertices.

**Complexity:** `O(V³)`

---

### A* (A-Star) Search
An informed shortest-path algorithm that combines actual path cost and heuristic estimation.

Formula:

```text
f(n) = g(n) + h(n)
```

Where:
- `g(n)` = actual cost from start to node `n`
- `h(n)` = estimated cost from `n` to the goal
- `f(n)` = estimated total cost

With a heuristic of zero, A* behaves like Dijkstra's algorithm.

---

## Minimum Spanning Tree Algorithms

### Kruskal's Algorithm
Builds a Minimum Spanning Tree (MST) by repeatedly selecting the smallest available edge.

Uses:
- Disjoint Set Union (DSU)

**Complexity:** `O(E log E)`

---

### Prim's Algorithm
Builds a Minimum Spanning Tree by expanding from an initial vertex.

**Complexity:** `O(E log V)`

---

### Disjoint Set Union (Union-Find)
Efficient data structure used for:
- Connectivity checks
- Kruskal's algorithm

Operations:
- Find
- Union

---

## Connectivity & Strong Connectivity

### Connected Components
Determines the number of connected components in a graph.

**Complexity:** `O(V + E)`

---

### Kosaraju's Algorithm
Finds all Strongly Connected Components (SCCs) in a directed graph.

**Complexity:** `O(V + E)`

---

### Tarjan's Algorithm
Finds Strongly Connected Components using DFS and low-link values.

**Complexity:** `O(V + E)`

---

## Graph Ordering

### Topological Sort
Produces a valid linear ordering of vertices in a Directed Acyclic Graph (DAG).

Applications:
- Dependency resolution
- Task scheduling
- Build systems

**Complexity:** `O(V + E)`

---

## Cycle Detection

### Cycle Detection in Undirected Graphs
DFS-based detection of cycles in undirected graphs.

**Complexity:** `O(V + E)`

---

### Cycle Detection in Directed Graphs
DFS recursion-stack approach for detecting directed cycles.

**Complexity:** `O(V + E)`

---

## Graph Property Analysis

### Degree Analysis

Supports:

- Degree
- In-Degree
- Out-Degree

Useful for:
- Graph characterization
- Eulerian graph analysis

---

### Bipartite Graph Check
Determines whether a graph can be colored using two colors such that adjacent vertices have different colors.

Applications:
- Matching problems
- Scheduling
- Network design

**Complexity:** `O(V + E)`

---

### Eulerian and Semi-Eulerian Graphs

Checks whether a graph contains:

#### Eulerian Circuit
A closed path that visits every edge exactly once.

#### Eulerian Path (Semi-Eulerian)
A path that visits every edge exactly once but may start and end at different vertices.

Supports:
- Directed graphs
- Undirected graphs

---

### Graph Isomorphism
Determines whether two graphs are structurally identical through a valid bijection between their vertex sets.

Approach:
- Vertex count check
- Edge count check
- Degree sequence comparison
- Backtracking search

**Worst-case Complexity:** `O(V!)`

---

### Planarity Check
Determines whether a graph satisfies fundamental planarity conditions.

Current implementation uses graph-theoretic planarity constraints based on Euler's formula and related properties.

---

## Cover Problems

### Vertex Cover
Greedy approximation algorithm for finding a vertex cover.

A vertex cover is a set of vertices such that every edge has at least one endpoint in the set.

Note:
- Minimum Vertex Cover is NP-Hard.
- This implementation uses a practical greedy heuristic.

---

### Edge Cover
Greedy algorithm for constructing an edge cover.

An edge cover is a set of edges such that every non-isolated vertex is incident to at least one selected edge.

---

## Graph Representation

The graph is represented using an adjacency list.

Example:

```cpp
vector<vector<pair<int,int>>> adj;
```

Where:

- First value = destination vertex
- Second value = edge weight

Advantages:

- Memory efficient
- Fast traversal
- Suitable for sparse graphs

---

## Supported Graph Types

- Directed Graphs
- Undirected Graphs
- Weighted Graphs
- Unweighted Graphs

---

## Complexity Summary

| Algorithm | Complexity |
|------------|------------|
| BFS | O(V + E) |
| DFS | O(V + E) |
| Recursive DFS | O(V + E) |
| Connected Components | O(V + E) |
| Dijkstra | O((V + E) log V) |
| Bellman-Ford | O(VE) |
| Floyd-Warshall | O(V³) |
| A* | Depends on heuristic |
| Kruskal | O(E log E) |
| Prim | O(E log V) |
| Kosaraju | O(V + E) |
| Tarjan | O(V + E) |
| Topological Sort | O(V + E) |
| Bipartite Check | O(V + E) |
| Cycle Detection | O(V + E) |
| Eulerian Check | O(V + E) |
| Graph Isomorphism | O(V!) |
| Vertex Cover (Greedy) | O(VE) |
| Edge Cover (Greedy) | O(E) |

---

## Technologies Used

- C++
- Standard Template Library (STL)

Main STL Components:

- `vector`
- `queue`
- `stack`
- `priority_queue`
- `set`
- `unordered_set`
- `unordered_map`
- `algorithm`

---

## Building and Running

Clone the repository:

```bash
git clone https://github.com/gope7oo/graph-algorithms-cpp.git
```

Navigate to the project directory:

```bash
cd graph-algorithms-cpp
```

Compile:

```bash
g++ -std=c++17 *.cpp -o graph
```

Run:

```bash
./graph
```

---

## Educational Purpose

This project was developed to gain practical experience with:

- Graph Theory
- Data Structures
- Algorithm Design
- Complexity Analysis
- Modern C++ Programming
- Classical Computer Science Algorithms

---

## Future Improvements

Potential future additions:

- Hamiltonian Path / Cycle Detection
- Maximum Flow Algorithms (Ford-Fulkerson, Edmonds-Karp)
- Exact Planarity Testing
- Graph Visualization

---

## Repository

GitHub:

https://github.com/gope7oo/graph-algorithms-cpp

---
