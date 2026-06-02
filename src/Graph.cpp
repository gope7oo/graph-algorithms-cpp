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