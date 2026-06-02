#include "../include/Graph.h"

/*
Dijkstra's Algorithm

Computes the shortest path from a source vertex to all
other vertices in a graph with non-negative weights.

Data Structure:
    Min Priority Queue (Min Heap)

Idea:
    Always expand the node with the smallest current
    distance.

Time Complexity:
    O((V + E) log V)
*/

vector<long long> Graph::dijkstra(int src){

    vector<long long> dist(V,LLONG_MAX/2);
    dist[src]=0;

    priority_queue<pair<long long,int>,
        vector<pair<long long,int>>,
        greater<>> pq;

    pq.push({0,src});

    while(!pq.empty()){

        auto [d,u]=pq.top();
        pq.pop();

        if(d>dist[u]) continue;

        for(auto [v,w]:adj[u]){

            if(dist[v] > dist[u]+w){

                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }

    return dist;
}

/*
Bellman-Ford Algorithm

Computes shortest paths from a source vertex and
supports negative edge weights.

Features:
    - Detects negative weight cycles.

Algorithm:
    Relax all edges V-1 times.

Time Complexity:
    O(V * E)
*/

vector<long long> Graph::bellmanFord(int src){

    vector<long long> dist(V,LLONG_MAX/2);
    dist[src]=0;

    for(int i=0;i<V-1;i++){

        for(int u=0;u<V;u++){

            for(auto [v,w]:adj[u]){

                if(dist[u]!=LLONG_MAX/2 &&
                   dist[v] > dist[u]+w){

                    dist[v]=dist[u]+w;
                }
            }
        }
    }

    return dist;
}

/*
Floyd-Warshall Algorithm

Computes shortest paths between ALL pairs of vertices.

Technique:
    Dynamic Programming.

Works With:
    - Negative edges
    - No negative cycles

Time Complexity:
    O(V^3)
*/

vector<vector<long long>> Graph::floydWarshall(){

    vector<vector<long long>> dist(V,
        vector<long long>(V,LLONG_MAX/2));

    for(int i=0;i<V;i++) dist[i][i]=0;

    for(int u=0;u<V;u++){
        for(auto [v,w]:adj[u]){
            dist[u][v]=min(dist[u][v],(long long)w);
        }
    }

    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                if(dist[i][k]<LLONG_MAX/2 &&
                   dist[k][j]<LLONG_MAX/2)
                    dist[i][j]=min(dist[i][j],
                                   dist[i][k]+dist[k][j]);

    return dist;
}




/*

====================== A* Algorithm ======================

A* (A-star) is a best-first search algorithm used to find the
shortest path between a start node and a goal node in a weighted graph.

It improves over Dijkstra by using a heuristic to guide the search.

Core idea:
    f(n) = g(n) + h(n)

Where:
- g(n): exact cost from the start node to current node n
- h(n): estimated cost from node n to the goal (heuristic)
- f(n): estimated total cost of the cheapest solution through n

------------------------------------------------------------
How it works:
- Always expands the node with the lowest f(n) value.
- Uses a priority queue to select the most promising node.
- Continuously updates the best known cost to each node.

------------------------------------------------------------
Optimality condition:
A* is guaranteed to find the optimal (shortest) path if the
heuristic h(n) is admissible, meaning:
    - It never overestimates the true cost to the goal.

If h(n) = 0:
    → A* becomes Dijkstra’s algorithm.

------------------------------------------------------------
Advantages:
- Faster than Dijkstra in practice (guided search)
- Finds optimal path with a good heuristic

Disadvantages:
- Performance depends heavily on heuristic quality
- Can behave like Dijkstra if heuristic is weak
*/

std::vector<int> Graph::aStar(int start, int goal)
{
    if (start < 0 || start >= V || goal < 0 || goal >= V) {
        std::cerr << "Error: Invalid start or goal vertex.\n";
        return {};
    }

    // gCost = cost from start to current node
    std::vector<long long> gCost(V, LLONG_MAX);
    std::vector<int> parent(V, -1);
    std::vector<bool> closed(V, false);

    // Priority queue: {fCost, vertex}
    using pii = std::pair<long long, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

    gCost[start] = 0;
    pq.push({0 + heuristic(start, goal), start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (closed[u]) continue;
        closed[u] = true;

        if (u == goal) {
            // Reconstruct and return path
            std::vector<int> path;
            int curr = goal;
            while (curr != -1) {
                path.push_back(curr);
                curr = parent[curr];
            }
            std::reverse(path.begin(), path.end());

            if (!path.empty() && path[0] == start)
                return path;
            else
                return {};
        }

        for (auto& edge : adj[u])
        {
            int v = edge.first;
            long long weight = edge.second;

            if (closed[v]) continue;

            long long tentativeG = gCost[u] + weight;

            if (tentativeG < gCost[v])
            {
                gCost[v] = tentativeG;
                parent[v] = u;

                long long fCost = tentativeG + heuristic(v, goal);
                pq.push({fCost, v});
            }
        }
    }

    return {}; // No path found
}

long long Graph::aStarCost(int start, int goal)
{
    std::vector<int> path = aStar(start, goal);
    if (path.empty() || path.size() == 1) return -1;

    long long totalCost = 0;

    for (size_t i = 0; i + 1 < path.size(); i++)
    {
        int u = path[i];
        int v = path[i + 1];

        for (auto& edge : adj[u])
        {
            if (edge.first == v)
            {
                totalCost += edge.second;
                break;
            }
        }
    }
    return totalCost;
}

// Simple heuristic (can be improved later)
long long Graph::heuristic(int u, int goal)
{
    return 0;   // Default: makes A* same as Dijkstra
}