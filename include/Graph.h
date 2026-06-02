/*
===============================================================
Graph Algorithms Library
---------------------------------------------------------------

Description:
    A general-purpose graph implementation supporting both
    directed and undirected graphs using adjacency lists.

Implemented Algorithms:
    Traversal
        - Breadth First Search (BFS)
        - Depth First Search (DFS) iterative
        - Depth First Search (DFS) recursive and iterative 

    Connectivity
        - Connected Components
        - Cycle Detection (Undirected)
        - Bipartite Graph Check
        - Bridges and Articulation Points (Tarjan)

    Shortest Paths
        - Dijkstra
        - Bellman-Ford
        - Floyd-Warshall

    Graph Structure
        - Topological Sort (Kahn's Algorithm)
        - Strongly Connected Components (Kosaraju)

    Minimum Spanning Tree
        - Kruskal (using Disjoint Set Union)

Graph Representation:
    Adjacency List

Complexity:
    Most algorithms operate in O(V + E) unless otherwise noted.

===============================================================
*/


#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <tuple>
#include <numeric>
#include <climits>

using namespace std;

/*
---------------------------------------------------------------
Graph Class

Represents a graph using an adjacency list.

Features:
    - Supports directed and undirected graphs
    - Supports weighted edges
    - Implements multiple classical graph algorithms

Internal Representation:
    adj[u] = list of (v, weight) edges

Where:
    V = number of vertices
    E = number of edges

---------------------------------------------------------------
*/

class Graph {
private:
    int V;
    bool directed;
    vector<vector<pair<int,int>>> adj;

    // ===== DSU for Kruskal =====
    struct DSU {
        vector<int> par, rnk;
        DSU(int n);
        int find(int x);
        bool unite(int x,int y);
    };

    // ===== Helpers =====
    void DFSRecursiveHelper(int u, vector<bool>& visited);
    bool dfsCycle(int u,int par,vector<bool>& vis);

    void dfsKos1(int u,vector<bool>& vis,stack<int>& st);
    void dfsKos2(int u,vector<bool>& vis,vector<int>& comp,const vector<vector<int>>& transpose);

    void dfsBridgeArt(int u,int par,vector<int>& disc,vector<int>& low,
                      vector<bool>& ap,vector<pair<int,int>>& bridges,int& timer);

public:

    // constructor v - number of vertices, dir - true: directed, false: undirected
    Graph(int v,bool dir=false);

    void addEdge(int u,int v,int w=1);

    void printGraph();

    
    int degree(int v); // for undirected
    int inDegree(int v); // for directed coming in a vertex
    int outDegree(int v);  // for directed coming out a vertex

    vector<int> vertexCover();
    vector<pair<int, int>> edgeCover();
    int minVertexCoverSize();
    int minEdgeCoverSize();

    // Traversal
    void bfs(int start);
    void DFS(int start);
    void DFSRecursive(int start);
    int isEulerian();
    bool isSemiEulerian();
    int isEulerianDirected(); 

    // Connectivity
    int connectedComponents(bool ignoreIsolated);
    bool hasCycleUndirected();
    bool hasCycleDirected(); 
    bool dfsCycleUtil(int, vector<int>& visited, vector<int>& recStack);
    bool isBipartite();

    pair<vector<pair<int,int>>,vector<int>> findBridgesArt();

    // Topological
    vector<int> topoSort();

    // Shortest path
    vector<long long> dijkstra(int src);
    vector<long long> bellmanFord(int src);
    vector<vector<long long>> floydWarshall();

    // MST
    long long kruskalMST();
    vector<tuple<int, int, int>> primMST(); // {u -> v, weight}
    long long primMSTCost(); // total cost 

    // SCC
    vector<vector<int>> kosarajuSCC();
};

#endif