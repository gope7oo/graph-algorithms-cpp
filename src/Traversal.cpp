#include "../include/Graph.h"

/*
Breadth First Search (BFS)

Explores the graph level by level starting from a source node.

Applications:
    - Shortest path in unweighted graphs
    - Connectivity testing
    - Level order traversal

Algorithm:
    1. Start from the source vertex
    2. Visit all its neighbors
    3. Continue expanding level by level

Time Complexity:
    O(V + E)

Space Complexity:
    O(V)
*/

void Graph::bfs(int start){

    queue<int> q;
    vector<bool> visited(V,false);

    q.push(start);
    visited[start]=true;

    cout<<"BFS: ";

    while(!q.empty()){

        int cur=q.front();
        q.pop();

        cout<<cur<<" ";

        for(auto [v,w]:adj[cur]){
            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }

    cout<<endl;
}

/*
Depth First Search (Iterative)

Same as BFS but using a stack not a queue
Uses a stack to simulate recursion and explore as deep
as possible before backtracking.

Time Complexity:
    O(V + E)
*/

void Graph::DFS(int start){

    vector<bool> visited(V,false);
    stack<int> st;

    st.push(start);
    visited[start]=true;

    cout<<"DFS: ";

    while(!st.empty()){

        int cur=st.top();
        st.pop();

        cout<<cur<<" ";

        for(auto [v,w]:adj[cur]){
            if(!visited[v]){
                visited[v]=true;
                st.push(v);
            }
        }
    }

    cout<<endl;
}

/*
Depth First Search (Recursive)

Recursive implementation of DFS.

Uses system call stack to explore nodes until a dead end
is reached, then backtracks.

Helper Function:
    DFSRecursiveHelper()

Time Complexity:
    O(V + E)
*/

void Graph::DFSRecursiveHelper(int u,vector<bool>& visited){

    visited[u]=true;
    cout<<u<<" ";

    for(auto [v,w]:adj[u]){
        if(!visited[v]){
            DFSRecursiveHelper(v,visited);
        }
    }
}

void Graph::DFSRecursive(int start){

    vector<bool> visited(V,false);

    cout<<"DFS: ";

    DFSRecursiveHelper(start,visited);

    cout<<endl;
}


// Returns 0 for NO, 1 for eulerian circuit, 2 for eulerian path
/*
Theory:
- An Eulerian Circuit exists if we can traverse every edge exactly once and return to start.
- An Eulerian Path exists if we can traverse every edge exactly once (may start and end at different vertices).
*/

int Graph::isEulerian() {
    if (V == 0) return 0;

    if (directed) return isEulerianDirected();

    // for undirected 

    int oddDegreeCount = 0;
    for (int i = 0; i < V; i++) {
        if (degree(i) % 2 != 0) {
            oddDegreeCount++;
        }
    }

    if (oddDegreeCount == 0) {
        return 1; // eulerian circuit
    } else if (oddDegreeCount == 2) return 2; // eulerian path
    else {
        return 0; // no eulerian path or circle
    }
}

bool Graph::isSemiEulerian() {
    return isEulerian() == 2;
}

/*
For Directed Graphs:
- Eulerian Circuit → Every vertex has equal in-degree and out-degree.
- Eulerian Path → Exactly one vertex has out = in + 1 (start), one has in = out + 1 (end), and all others are equal.
*/
int Graph::isEulerianDirected() {
    if (V == 0) return 0;

    vector<int> in(V, 0), out(V, 0);

    // calculate indegree and outdegree for each v
    for (int u = 0; u < V; u++) {
        out[u] = degree(u); 
        for (auto& edge : adj[u]) {
            in[edge.first]++;
        }
    }

    int startCount = 0, endCount = 0, balanced = 0;

    for (int i = 0; i < V; i++) {
        if (in[i] == out[i]) balanced++;
        else if (out[i] == in[i] + 1) startCount++; // potential starting vertex
        else if (in[i] == out[i] + 1) endCount++; //potential ending vertex
        else return 0; // impossible if diff > 1 
    }

    if (balanced == V) return 1; //eulerian circuit
    if (startCount == 1 && endCount == 1) return 2; // eulerian path
    return 0;
}