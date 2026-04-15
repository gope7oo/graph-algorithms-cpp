#include "../include/Graph.h"
/*
Kosaraju DFS - first pass

Performs DFS and stores vertices in stack based on
their finishing time.
*/
void Graph::dfsKos1(int u, vector<bool>& vis, stack<int>& st) {

    vis[u] = true;

    for (auto [v, w] : adj[u]) {
        if (!vis[v]) {
            dfsKos1(v, vis, st);
        }
    }

    st.push(u);
}

/*
Kosaraju DFS - second pass

Explores the transposed graph and collects all vertices
belonging to the same strongly connected component.
*/
void Graph::dfsKos2(int u, vector<bool>& vis,
                    vector<int>& comp,
                    const vector<vector<int>>& transpose) {

    vis[u] = true;
    comp.push_back(u);

    for (int v : transpose[u]) {
        if (!vis[v]) {
            dfsKos2(v, vis, comp, transpose);
        }
    }
}

/*
Kosaraju's Algorithm

Finds all Strongly Connected Components in a directed graph.

Steps:
1. Run DFS and store vertices by finish time.
2. Reverse the graph.
3. Process vertices in reverse finish order.

Time Complexity:
O(V + E)
*/
vector<vector<int>> Graph::kosarajuSCC() {

    if (!directed) {
        cout << "SCC for directed graphs only" << endl;
        return {};
    }

    vector<bool> visited(V, false);
    stack<int> st;

    // First DFS pass
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsKos1(i, visited, st);
        }
    }

    // Build transpose graph
    vector<vector<int>> transpose(V);

    for (int u = 0; u < V; u++) {
        for (auto [v, w] : adj[u]) {
            transpose[v].push_back(u);
        }
    }

    fill(visited.begin(), visited.end(), false);

    vector<vector<int>> sccs;

    // Second DFS pass
    while (!st.empty()) {

        int u = st.top();
        st.pop();

        if (!visited[u]) {

            vector<int> component;

            dfsKos2(u, visited, component, transpose);

            sccs.push_back(component);
        }
    }

    return sccs;
}

/*
Tarjan's Algorithm

Finds:
    - Bridges (critical edges)
    - Articulation points (critical vertices)

Idea:
    Uses discovery time and low-link values.

Applications:
    - Network reliability
    - Infrastructure analysis

Time Complexity:
    O(V + E)
*/

void Graph::dfsBridgeArt(
    int u,
    int parent,
    std::vector<int>& disc,
    std::vector<int>& low,
    std::vector<bool>& ap,
    std::vector<std::pair<int,int>>& bridges,
    int& timer
) {
    disc[u] = low[u] = timer++;
    int children = 0;

    for (auto [v, w] : adj[u]) {
        if (disc[v] == -1) {
            children++;
            dfsBridgeArt(v, u, disc, low, ap, bridges, timer);

            low[u] = std::min(low[u], low[v]);

            // Bridge condition
            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }

            // Articulation point condition
            if (parent != -1 && low[v] >= disc[u]) {
                ap[u] = true;
            }
        }
        else if (v != parent) {
            low[u] = std::min(low[u], disc[v]);
        }
    }

    // Root case
    if (parent == -1 && children > 1) {
        ap[u] = true;
    }
}

pair<vector<pair<int,int>>, vector<int>> Graph::findBridgesArt()
{
    if (directed)
    {
        cout << "For undirected graphs only!" << endl;
        return {{}, {}};
    }

    vector<int> disc(V, -1);
    vector<int> low(V, -1);

    vector<bool> ap(V, false);
    vector<pair<int,int>> bridges;

    int timer = 0;

    for (int i = 0; i < V; i++)
    {
        if (disc[i] == -1)
        {
            dfsBridgeArt(i, -1, disc, low, ap, bridges, timer);
        }
    }

    vector<int> articulationPoints;

    for (int i = 0; i < V; i++)
    {
        if (ap[i])
            articulationPoints.push_back(i);
    }

    return {bridges, articulationPoints};
}