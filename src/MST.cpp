#include "../include/Graph.h"


/*
Kruskal's Minimum Spanning Tree Algorithm

Finds a tree connecting all vertices with minimum cost.

Algorithm:
    1. Sort edges by weight
    2. Add smallest edge that doesn't form a cycle
    3. Use DSU to detect cycles

Time Complexity:
    O(E log E)
*/

long long Graph::kruskalMST(){

    if(directed){
        cout<<"MST only for undirected graphs\n";
        return 0;
    }

    vector<tuple<int,int,int>> edges;

    for(int u=0;u<V;u++){

        for(auto [v,w]:adj[u]){

            if(u<v)
                edges.push_back({w,u,v});
        }
    }

    sort(edges.begin(),edges.end());

    DSU dsu(V);

    long long cost=0;

    int used=0;

    for(auto [w,u,v]:edges){

        if(dsu.unite(u,v)){

            cost+=w;
            used++;

            if(used==V-1) break;
        }
    }

    return cost;
}


vector<tuple<int, int, int>> Graph::primMST() {
    if (V == 0) return {};

    vector<bool> inMST(V, false); 
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);

    // Min-heap: {key, vertex}
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    key[0] = 0;
    pq.push({0, 0});

    std::vector<std::tuple<int, int, int>> mstEdges;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        // Add edge to MST (except for first vertex)
        if (parent[u] != -1) {
            // Find weight between parent[u] and u
            for (auto& edge : adj[parent[u]]) {
                if (edge.first == u) {
                    mstEdges.emplace_back(parent[u], u, edge.second);
                    break;
                }
            }
        }

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    return mstEdges;
}

long long Graph::primMSTCost() {
    auto edges = primMST();
    long long cost = 0;

    for (auto& [u, v, w] : edges) {
        cost += w;
    }
    return cost;
}