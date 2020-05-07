#include <iostream>
#include <cstdint>
#include <vector>
#include <stdexcept>
using namespace std;

#define int int32_t

//####################################################################################################################


/* This is struct can be used as Directed as well as Un-Directed Graph. */
struct Graph{
    struct GraphNode{
        int vertex, link;
        GraphNode(int v1, int l1): vertex{v1}, link{l1} {}
    };
    vector<GraphNode> adj;
    vector<int> head;

    inline Graph(const int &vertices){ head.resize(vertices, -1); }

    /* Adds an edge v1 ---> v2 . Call the function `add_edge(v2, v1)` to make the graph undirected */
    inline void add_edge(const int &v1, const int &v2){
        adj.emplace_back(v2, head[v1]);
        head[v1] = adj.size() - 1;
    }

    struct GraphIter{
        const Graph &t;
        int i;

        inline GraphIter(const Graph &t1): t{t1}, i{-1} {}
        inline GraphIter(const Graph &t1, const int &vertex1): t(t1), i{t.head[vertex1]} { }
        inline GraphIter& operator ++(){ i = t.adj[i].link; return *this; }
        inline const Graph::GraphNode& operator*(){ return t.adj[i]; }
        inline bool operator!=(const GraphIter &t1){ return (((&t)!=(&t1.t)) || (i!=t1.i)); }

        inline GraphIter& begin() {return *this;}
        inline GraphIter end() {return GraphIter(this->t);}
    };
    inline GraphIter edge_iterator(const int &vertex) const { return GraphIter(*this, vertex); }
};

//##########################################################

struct DFSData{
    vector<bool> visited;
    vector<bool> parity;
    DFSData(int vertices){
        visited.resize(vertices, false);
        parity.resize(vertices, false);
    }
};

/* return success(true) or failure(false) of parity assignment for a Bipartite graph */
bool dfs(const Graph &g, int v1, DFSData &d, bool parity){
    if(d.visited[v1]) {
        if(d.parity[v1] != parity) return false;
        return true;
    }
    d.visited[v1] = true;
    d.parity[v1] = parity;

    bool success = true;
    for(const Graph::GraphNode &i: g.edge_iterator(v1)){
        success &= dfs(g, i.vertex, d, !parity);
    }

    return success;
}

//####################################################################################################################

int main(){
    int vertices = 10;

    Graph g(vertices);
    g.add_edge(1,2); g.add_edge(2,1);
    g.add_edge(2,3); g.add_edge(3,2);
    // g.add_edge(1,3); g.add_edge(3,1);  // Uncomment this and the graph will NOT be a Bipartite Graph

    DFSData gdata(vertices);
    for(int i = 0; i < vertices; ++i){
        if(gdata.visited[i]) continue;
        if(dfs(g, i, gdata, 0) == false){
            cout << "The graph is NOT a Bipartite Graph :(" << endl;
            return 0;
        }
    }

    cout << "The graph is a Bipartite Graph :)" << endl;
    cout << "vertices in set 0: ";
    for(int i = 0; i < vertices; ++i)
        if(gdata.visited[i] && gdata.parity[i]==false) cout << i << " ";
    cout << endl;
    cout << "vertices in set 1: ";
    for(int i = 0; i < vertices; ++i)
        if(gdata.visited[i] && gdata.parity[i]==true) cout << i << " ";
    cout << endl;

    return 0;
}