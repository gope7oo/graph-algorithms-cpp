#include "../include/Graph.h"

// constructor v - number of vertices, dir - true: directed, false: undirected
Graph::Graph(int v,bool dir) : V(v), directed(dir), adj(v) {}

// adds edge to the graph u->v with edge weight w (default = 1) if undirected u->v v->u
void Graph::addEdge(int u,int v,int w){
    adj[u].push_back({v,w});
    if(!directed) adj[v].push_back({u,w});
}

void Graph::printGraph(){
    cout<<"Graph:\n";
    for(int u=0;u<V;u++){
        cout<<u<<" : ";
        for(auto [v,w]:adj[u]){
            cout<<"("<<v<<","<<w<<") ";
        }
        cout<<endl;
    }
}

// ===== DSU =====

Graph::DSU::DSU(int n):par(n),rnk(n,0){
    iota(par.begin(),par.end(),0);
}

int Graph::DSU::find(int x){
    return par[x]==x ? x : par[x]=find(par[x]);
}

bool Graph::DSU::unite(int x,int y){
    x=find(x); y=find(y);
    if(x==y) return false;

    if(rnk[x]<rnk[y]) swap(x,y);

    par[y]=x;
    if(rnk[x]==rnk[y]) rnk[x]++;

    return true;
}

int Graph::degree(int v) {
    if (v < 0 || v >= V) {
        std::cerr << "Error: Vertex " << v << " is out of bounds.\n";
        return -1;
    }
    return adj[v].size();
}

int Graph::outDegree(int v) {
    return degree(v);
}

int Graph::inDegree(int v) {
    if (v < 0 || v >= V) {
        std::cerr << "Error: Vertex " << v << " is out of bounds.\n";
        return -1;
    }

    if (!directed) return degree(v); // undirected

    int cnt = 0;
    for (int u = 0; u < V; u++){
        for (auto& edge : adj[u]) {
            if (edge.first == v) {
                cnt++;
            }
        }
    }
    return cnt; 
}



// ====================== Vertex Cover & Edge Cover ======================
/*
Theory:
Detailed Approach (Greedy):
1. Sort all vertices in decreasing order of their degree.
2. Pick the vertex with highest degree.
3. Add it to the cover.
4. All edges connected to this vertex are now considered "covered".
5. Repeat until no uncovered edges remain.

Advantage: Simple and fast.
Disadvantage: Not always optimal (can be up to 2x larger than minimum in worst case).


Note: Finding the *minimum* Vertex Cover is NP-Hard. 
      We use a simple Greedy approach here (good enough for learning & many practical cases).
*/


vector<int> Graph::vertexCover()
{
    if (V == 0) return {};

    // mark uncovered edges
    vector<vector<bool>> edgeUsed(V, vector<bool>(V, false));

    for (int u = 0; u < V; u++)
    {
        for (auto [v, w] : adj[u])
        {
            edgeUsed[u][v] = true;
        }
    }

    vector<bool> inCover(V, false);
    vector<int> cover;

    // Greedy: keep picking vertex with most uncovered edges
    while (true)
    {
        int bestV = -1;
        int bestCount = 0;

        for (int i = 0; i < V; i++)
        {
            if (inCover[i]) continue;

            int cnt = 0;
            for (auto [v, w] : adj[i])
            {
                if (edgeUsed[i][v])
                    cnt++;
            }

            if (cnt > bestCount)
            {
                bestCount = cnt;
                bestV = i;
            }
        }

        // no uncovered edges left
        if (bestCount == 0)
            break;

        // add best vertex to cover
        inCover[bestV] = true;
        cover.push_back(bestV);

        // mark all its edges as covered
        for (auto [v, w] : adj[bestV])
        {
            edgeUsed[bestV][v] = false;
        }
    }

    return cover;
}
int Graph::minVertexCoverSize() {
    return vertexCover().size();
}

// ====================== Edge Cover ======================
/*
Detailed Approach (Greedy):
1. Iterate through all vertices.
2. If a vertex is not covered yet, find an edge connected to it.
3. Prefer edges that cover two uncovered vertices at once.
4. Add that edge to the cover and mark both endpoints as covered.
5. Repeat until all vertices with degree > 0 are covered.

Note: Isolated vertices (degree 0) cannot be covered.
*/

vector<pair<int,int>> Graph::edgeCover()
{
    if (V == 0) return {};

    vector<bool> covered(V, false);
    vector<pair<int,int>> coverEdges;

    for (int u = 0; u < V; u++)
    {
        if (covered[u]) continue;

        for (auto [v, w] : adj[u])
        {
            if (!covered[v])
            {
                coverEdges.emplace_back(u, v);
                covered[u] = true;
                covered[v] = true;
                break;
            }
        }
    }

    return coverEdges;
}

int Graph::minEdgeCoverSize() {
    return edgeCover().size();
}




/*
====================== Graph Isomorphism ======================

Two graphs G1 and G2 are isomorphic if there exists a bijection
between their vertex sets such that adjacency is preserved.

In simpler terms:
We can relabel the vertices of one graph to make it identical
to the other graph in structure.

------------------------------------------------------------
Formal condition:
There exists a mapping f: V(G1) → V(G2) such that:
- f is bijective (one-to-one and onto)
- (u, v) is an edge in G1 ⇔ (f(u), f(v)) is an edge in G2

------------------------------------------------------------
Approach used here:

1. Pruning (Fast rejection checks):
   - Different number of vertices → not isomorphic
   - Different number of edges → not isomorphic
   - Different degree sequences → not isomorphic

   These checks quickly eliminate impossible cases.

2. Backtracking search:
   - Try all possible bijections between vertices
   - Assign each vertex in G1 to a unique vertex in G2

3. Validation step:
   - After constructing a full mapping,
     verify that every edge in G1 exists in G2 under the mapping

------------------------------------------------------------
Complexity:
- Worst case: O(N!) (trying all permutations)
- Practical use: only feasible for small graphs (N ≤ 8–10)

------------------------------------------------------------
Note:
Graph isomorphism is a computationally difficult problem in general.
This implementation uses brute-force backtracking with pruning.
*/

bool Graph::isIsomorphic(Graph& other)
{
    // Quick checks
    if (V != other.V) return false;
    if (directed != other.directed) return false;

    // Count edges
    int edges1 = 0, edges2 = 0;
    for (int i = 0; i < V; i++) {
        edges1 += adj[i].size();
        edges2 += other.adj[i].size();
    }
    if (edges1 != edges2) return false;

    // Degree sequence check
    std::vector<int> deg1(V), deg2(V);
    for (int i = 0; i < V; i++) {
        deg1[i] = degree(i);
        deg2[i] = other.degree(i);
    }
    std::sort(deg1.begin(), deg1.end());
    std::sort(deg2.begin(), deg2.end());
    if (deg1 != deg2) return false;

    // Now try backtracking to find mapping
    std::vector<int> mapping(V, -1);
    std::vector<bool> used(V, false);

    return isIsomorphicUtil(0, mapping, used, other);
}

// Backtracking function
bool Graph::isIsomorphicUtil(int pos, vector<int>& mapping, vector<bool>& used, Graph& other)
{
    if (pos == V) {
        // Check if this mapping preserves all edges
        return checkMapping(mapping, other);
    }

    for (int v = 0; v < V; v++)
    {
        if (used[v]) continue;
        if (degree(pos) != other.degree(v)) continue;  // Degree must match

        mapping[pos] = v;
        used[v] = true;

        if (isIsomorphicUtil(pos + 1, mapping, used, other))
            return true;

        // Backtrack
        mapping[pos] = -1;
        used[v] = false;
    }
    return false;
}

// Check if current mapping is valid
bool Graph::checkMapping(vector<int>& mapping, Graph& other)
{
    for (int u = 0; u < V; u++)
    {
        int mappedU = mapping[u];

        for (auto& edge : adj[u])
        {
            int v = edge.first;
            int mappedV = mapping[v];

            // Check if edge exists in other graph
            bool found = false;
            for (auto& e2 : other.adj[mappedU])
            {
                if (e2.first == mappedV) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
    }
    return true;
}