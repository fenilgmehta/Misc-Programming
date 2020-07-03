#include <iostream>
#include <cstdint>
#include <vector>
#include <set>
#include <stdexcept>
#include <numeric>
#include <queue>
#include <tuple>
#include <bitset>
using namespace std;

#define int int32_t
#define long int64_t

template<typename T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;

/* REFER: https://github.com/fenilgmehta/Misc-Programming/blob/master/src/Disjoint%20Set%20Union%20(Union%20Find).cpp */
struct DisjoinSetUnion_Small{
    vector<int> parent;
    DisjoinSetUnion_Small(int vertices){
        parent.resize(vertices);
        iota(begin(parent), end(parent), 0);
    }

    int find_set(int v) { return ((parent[v]==parent[parent[v]]) ? (parent[v]) : (parent[v] = find_set(parent[v]))); }

    bool union_sets(int v1, int v2) {
        int a=find_set(v1), b=find_set(v2);
        if(a==b) return false;
        parent[a] = b;
        return true;
    }

    bool is_same_set(const int v1, const int v2) { return find_set(v1)==find_set(v2);}
};

//####################################################################################################################

/* 
• Directed Unweighted Graph
• This is struct can be used as Directed as well as Un-Directed Graph.
*/
struct Graph{
    struct GraphNode{
        int vertex, link;
        GraphNode(int v1, int l1): vertex{v1}, link{l1} {}
    };
    vector<GraphNode> adj;
    vector<int> head;
    const int vertices;

    inline Graph(const int &t_vertices, const int &t_edges=-1): vertices{t_vertices} {
        head.resize(t_vertices, -1);
        adj.reserve((0 <= t_edges) ? t_edges : t_vertices);
    }

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
        inline bool operator!=(const GraphIter &t1){ return i != t1.i; }  // (((&t)==(&t1.t)) && (i!=t1.i))

        inline GraphIter& begin() {return *this;}
        inline GraphIter end() {return GraphIter(this->t);}
    };
    // NOTE: highly suggested to be used in range based for loops only
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

/* 
• The TIME COMPLEXITY of depth-first search(DFS) is O(n + m) where n is the number of
  nodes and m is the number of edges, because the algorithm processes each node and
  edge once.
• Assumes that the graph `g` is undirected graph
*/
bool dfs(const Graph &g, int v1, DFSData &d, bool parity){
    if(d.visited[v1]) {
        if(d.parity[v1] != parity) return false;
        return true;
    }
    d.visited[v1] = true;
    d.parity[v1] = parity;

    bool success = true;
    for(const Graph::GraphNode &i: g.edge_iterator(v1)){
        success &= dfs(g, i.vertex, d, not parity);
        // if(not success) return false;  // Uncomment this to avoid recursion if `g` is not a bipartite graph
    }
    return success;
}

//##########################################################

// Application of Depth First Search (DFS)

struct BipartiteGraphData{
    vector<bool> visited;
    vector<bool> color;
    BipartiteGraphData(const int &vertices){
        visited.resize(vertices, false);
        color.resize(vertices, false);
    }
};

bool bipartite_graph_color(const Graph &g, BipartiteGraphData &bgd, const int &v, const bool &color){
    if(bgd.visited[v]) {
        if(bgd.color[v] != color) return false;
        return true;
    }

    bgd.visited[v] = true;
    bgd.color[v] = color;

    bool is_possible = true;
    for(const Graph::GraphNode &i: g.edge_iterator(v)) {
        is_possible &= bipartite_graph_color(g, bgd, i.vertex, not color);
        if(not is_possible) return false;  // slight optimization
    }
    return is_possible;
}

/* Returns a pair<BipartiteGraphData, success/failure of bipartite graph coloring>,
        where success == `true` or failure == `false` for color assignment of the graph */
pair<BipartiteGraphData, bool> bipartite_graph_split(const Graph &g, const int &v_low, const int &v_high) {
    BipartiteGraphData bgd(g.vertices);
    bool is_possible = true;
    for(int i = v_low; i <= v_high; ++i)
        if(not bgd.visited[i]) {
            // color for first vertex is `0` == `false`
            is_possible &= bipartite_graph_color(g, bgd, i, false);
        }
    return make_pair(bgd, is_possible);
}

//##########################################################

struct CycleData{
    const int vertices;
    vector<bool> visited;
    vector<int> parent;
    bool has_cycle;
    int cycle_depth, cycle_head, cycle_tail;
    CycleData(const int &vertices): vertices{vertices} {
        has_cycle = false;
        cycle_depth = 0;
        cycle_head = cycle_tail = -1;
        visited.resize(vertices, false);
        parent.resize(vertices, -1);
    }
};

/* Acyclic Graph are Bipartite Graph */
bool detect_cycle(const Graph &g, CycleData &cd, const int &v, const int &parent){
    ++cd.cycle_depth;
    if(cd.visited[v]) {
        cd.cycle_head = v;
        cd.cycle_tail = parent;
        return true;
    }
    cd.visited[v] = true;
    cd.parent[v] = parent;
    for(const Graph::GraphNode &i: g.edge_iterator(v)){
        if(i.vertex == parent) continue;
        if(detect_cycle(g, cd, i.vertex, v)) return true;
    }
    --cd.cycle_depth;
    return false;
}

CycleData find_cycle(const Graph &g, const int &v_low, const int &v_high) {
    CycleData cd(g.vertices);
    for(int i = v_low; i <= v_high; ++i){
        if(cd.visited[i]) continue;
        if(detect_cycle(g, cd, i, -1)) {
            cd.has_cycle = true;
            return cd;
        }
    }
    cd.cycle_tail = cd.cycle_depth = -1;
    return cd;
}

vector<int> find_cycle(const CycleData &cd){
    if(cd.has_cycle == false) return vector<int>();

    vector<int> cycle_arr; 
    cycle_arr.reserve(cd.cycle_depth);
    cycle_arr.push_back(cd.cycle_head);
    for(int curr_v = cd.cycle_tail;
            curr_v != cycle_arr[0];
            curr_v = cd.parent[curr_v]) 
    {
        cycle_arr.push_back(curr_v);
    }
    cycle_arr.push_back(cycle_arr[0]);
    return cycle_arr;
}

//##########################################################

/* 
• the TIME COMPLEXITY of breadth-first search(BFS) is O(n + m),
  where n is the number of nodes and m is the number of edges.
• Can be used to find the SSSP (single-source shortest path)
  if the graph is unweighted. Use 0-1 BFS if the graph is weighted
  all weights are either 0 or 1
*/
void bfs(const Graph &g, int v1){
    vector<bool> visited(g.vertices);
    vector<int> dist(g.vertices);
    dist[v1] = 0;
    queue<int> q;
    q.push(v1);
    while(not q.empty()){
        int node = q.front();
        q.pop();
        visited[node] = true;
        for(const auto &i: g.edge_iterator(node)){
            if(visited[i.vertex] == true) continue;
            q.push(i.vertex);
            dist[i.vertex] = dist[node] + 1;
        }
    }
}

//####################################################################################################################

/* 
• Directed Weighted Graph
• This is a simpler version of the above `struct Graph`
*/
struct GraphVectorWeighted{
    struct Edge{
        int vertex, cost;
        Edge(const int &v, const int &c): vertex{v}, cost{c} {}
    };
    vector<vector<Edge>> adj;
    const int vertices;

    inline GraphVectorWeighted(const int &t_vertices): vertices{t_vertices} { adj.resize(t_vertices); }
    inline void add_edge(const int &v1, const int &v2, const int &cost){ adj[v1].emplace_back(v2, cost); }
    inline const vector<Edge>& edge_iterator(const int &vertex) const { return adj[vertex]; }
};

//##########################################################

/* 
• NOTE: It is assumed that the graph an UNDIRECTED Graph without self-loops
• In practice, Prim’s and Kruskal’s algorithms are both efficient, and the choice
  of the algorithm is a matter of taste. Still most competitive programmers
  use Kruskal’s algorithm.
• TIME COMPLEXITY = O(n + m log m)
*/
pair<GraphVectorWeighted, long> minimum_spanning_tree_kruskals(const GraphVectorWeighted &g){
    using Edge=pair<int,pair<int,int>>;  // {cost, src, dst};
    int vertices = g.adj.size();
    GraphVectorWeighted mst(vertices);
    DisjoinSetUnion_Small dsu(vertices);
    min_heap<Edge> edges;
    long total_cost = 0;

    for(int i = 0; i < vertices; ++i){
        for(const GraphVectorWeighted::Edge &j: g.edge_iterator(i)){
            if(j.vertex < i) continue;  // this ensures only one edge is added
            edges.emplace(j.cost, make_pair(i, j.vertex));
        }
    }

    while(--vertices && (not edges.empty())) {  // will execute min(vertices-1, number of edges) times
        while(not edges.empty()){
            Edge e = edges.top();
            edges.pop();
            int &cost = e.first, &src=e.second.first, &dst=e.second.second;
            if(dsu.is_same_set(src, dst)) continue;
            mst.add_edge(src, dst, cost);
            mst.add_edge(dst, src, cost);
            total_cost += cost;
            break;
        }
    }

    return make_pair(mst, total_cost);
}


/* 
TODO: Prim's  Algorhtm
• Like Dijkstra’s algorithm, Prim’s algorithm can be efficiently implemented using
  a priority queue. The priority queue should contain all nodes that can be connected
  to the current component using a single edge, in increasing order of the weights of
  the corresponding edges.
• TIME COMPLEXITY = O(n + m log m)
*/

/* TODO: Boruvka Algorithm */

/* 
• Advantage: Dijkstra’s algorithm finds shortest paths from the starting node to all nodes of the
             graph, like the Bellman–Ford algorithm. The benefit of Dijkstra’s algorithm is that it
             is more efficient and can be used for processing large graphs. 
• Disadvantage: The algorithm REQUIRES that there are NO NEGATIVE WEIGHT EDGES in the graph.
                Otherwise it give wrong results
• Dijkstra’s algorithm is efficient, because it only processes each edge in the graph
  once, using the fact that there are NO NEGATIVE EDGES. However, if the graph has a
  negative edge, the algorithm may give incorrect results.
• The only difference between the two is that Bellman-Ford is also capable of handling
  negative weights whereas Dijkstra Algorithm can only handle positives.
• Note that the distance to a node never changes after processing the node.
• TIME COMPLEXITY = O(n + m log m)    <-----    n vertices, m edges
• FASTER than Bellman-Ford algorithm when there are NO cycles and -ve edge weights
• TESTED & WORKING perfectly for all testcases of https://cses.fi/problemset/task/1671/

TODO verify this
• Finds shortest path in O( E+ V Log(V) ) if you use a min priority queue.
  This is true only if you implement priority queue with Fibonacci heap,
  then amortized operation over it will take O(1). Otherwise, if you use
  any other implementation of priority_queue (like standard C++ STL) it
  should take E log(E) + V. (courtesy Roman Iedemskyi)
*/
vector<long> dijkstras(const GraphVectorWeighted &g, const int &source/* , const int &destination */){
    constexpr long INFINITY_LONG = static_cast<long>(1) << 61;

    // vector<int> parent(g.vertices, -1);
    vector<long> cost(g.vertices, INFINITY_LONG);
    min_heap<pair<long, int>> min_q;  // pair of {distance, vertex}

    long current_cost;
    int current_vertex;
    cost[source] = 0;
    min_q.emplace(0, source);
    while(/* current_vertex != destination &&  */(not min_q.empty())){
        tie(current_cost, current_vertex) = min_q.top();
        min_q.pop();
        if(current_cost != cost[current_vertex]) continue;

        for(const GraphVectorWeighted::Edge &i: g.edge_iterator(current_vertex)){
            long temp_cost = current_cost + i.cost;
            if(temp_cost < cost[i.vertex]){
                cost[i.vertex] = temp_cost;
                // parent[i.vertex] = current_vertex;
                min_q.emplace(cost[i.vertex], i.vertex);
            }
        }
    }

    return cost;  // cost[destination];
}

/* 
• REFER: https://cp-algorithms.com/graph/bellman_ford.html
• REFER: https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
• The Bellman–Ford algorithm finds shortest paths from a starting node to all nodes
  of the graph. The algorithm can process all kinds of graphs, provided that the graph
  does not contain a cycle with negative length. If the graph contains a negative cycle,
  the algorithm can detect this.
• The TIME COMPLEXITY = O(nm), because the algorithm consists of
  n − 1 rounds and iterates through all m edges during a round. If there are no negative
  cycles in the graph, all distances are final after n − 1 rounds, because each shortest
  path can contain at most n − 1 edges.
• A negative cycle can be detected using the Bellman–Ford algorithm by running the 
  algorithm for n rounds. If the last round reduces any distance, the graph contains a
  negative cycle. Note that this algorithm can be used to search for a negative cycle
  in the entire graph regardless of the starting node.
• SPFA algorithm (”Shortest Path Faster Algorithm”) is a variant of the Bellman–Ford
  algorithm, that is often more efficient than the original algorithm. The SPFA algorithm
  does not go through all the edges on each round, but instead, it chooses the edges to
  be examined in a more intelligent way ---> when an edge a → b reduces a distance, node b
  is added to the queue.
• SLOWER than Dijkstras algorithm
• TESTED & WORKING perfectly for 14 testcases out of 17 and give Too Long Execution error
  for 3 testcases out of 17 : https://cses.fi/problemset/task/1671/
*/
struct BellmanFordData{
    static constexpr int INF1 = static_cast<int>(1'000'000'000);
    static constexpr long INF2 = static_cast<long>(1'000'000'000'000'000'000);
    vector<long> dist;
    vector<int> parent;
    bool has_negative_cycles;
    BellmanFordData(int vertices) {
        dist.resize(vertices, INF2);
        parent.resize(vertices, -1);
        has_negative_cycles = false;
    }
};

// 𝗡𝗢𝗧𝗘: this is a mixture of BellmanFord and SFPA because we are using queue to only work on relaxed vertices
BellmanFordData bellman_ford(const GraphVectorWeighted &g, const int &source){
    BellmanFordData bfdata(g.vertices);
    queue<int> q_to_process, q_next;

    bfdata.dist[source] = 0;
    q_to_process.push(source);
    for(int loop_count = 1; loop_count < g.vertices; ++loop_count){
        while(not q_to_process.empty()) {
            int current = q_to_process.front();
            q_to_process.pop();
            for(auto &i: g.edge_iterator(current)){
                long new_cost = bfdata.dist[current] + i.cost;
                if(new_cost < bfdata.dist[i.vertex]){
                    bfdata.dist[i.vertex] = new_cost;
                    bfdata.parent[i.vertex] = current;
                    q_next.push(i.vertex);
                }
            }
        }
        swap(q_to_process, q_next);
    }

    // a negative cycles is reachable from the source
    if(not q_to_process.empty())
        bfdata.has_negative_cycles = true;

    return bfdata;
}

/* 
• REFER: https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
• It finds shortest paths between all node pairs of the graph in a single run.
• The algorithm can only be used when the graph is so small that a cubic time complexity is fast enough.
• Works for Directed Graphs and Multi-Graphs as well
• TIME COMPLEXITY = O(n*n*n) = O(n³)
• TESTED & WORKING perfectly for all testcases of https://cses.fi/problemset/task/1672/
*/

template<typename T, typename S> inline auto min_custom(const T a, const S b) { return ((a < b) ? a : b); }
vector<vector<long>> floyds_warshalls(const GraphVectorWeighted &g){
    constexpr long INF = static_cast<long>(1'000'000'000'000'000'000);
    vector<vector<long>> dist(g.vertices, vector<long>(g.vertices, INF));
    for(int i = 0; i < g.vertices; ++i){
        for(const auto &j: g.edge_iterator(i)){
            // `min` is used to handle multi-graphs
            dist[i][j.vertex] = min_custom(dist[i][j.vertex], j.cost);
        }
        dist[i][i] = 0;
    }

    for(int k = 0; k < g.vertices; ++k){
        for(int i = 0; i < g.vertices; ++i){
            for(int j = 0; j < g.vertices; ++j){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}


/* 
• REFER: https://cp-algorithms.com/graph/01_bfs.html
• 0-1 BFS: a modified version of Dijkstra's Algorithm
• This function demonstrates how we can use BFS to solve the SSSP (single-source shortest path) problem in O(|E|), if the weights of each edge is either 0 or 1.
• In the SSSP (single-source shortest path) problem, we have to find shortest paths from a source vertex v to all other vertices in the graph.
• More generalized version of 0-1 BFS is Dial's algorithm which works if every edge in the graph has a weight <= k
*/
vector<int> bfs_0_1(const GraphVectorWeighted &g, const int &source){
    constexpr int INF = 999'999'999;
    vector<int> dist(g.vertices, INF);
    vector<bool> visited(g.vertices, false);
    deque<GraphVectorWeighted::Edge> q;
    q.emplace_back(source, 0);

    while(not q.empty()){
        GraphVectorWeighted::Edge e = q.front();
        q.pop_front();
        visited[e.vertex] = true;

        for(const auto &i: g.edge_iterator(e.vertex)){
            if(not visited[i.vertex]){
                if(i.cost == 1) 
                    q.emplace_back(i.vertex, e.cost + i.cost);  // cost == 1
                else
                    q.emplace_front(i.vertex, e.cost);  // cost == 0
            }
        }
    }
    return dist;
}

//####################################################################################################################

// 0-indexed
template<size_t N, size_t M>
struct GraphAdjMatrix{
    int rows, cols;
    char adjMat[N][M+1];  // we use M+1, because char string are null terminated
    std::bitset<M> visited[N];  // default value is false
    static constexpr auto direction_pairs = std::initializer_list<std::pair<int,int>>{{-1,0},{+1,0},{0,-1},{0,+1}};
    static constexpr auto direction_tuples = std::initializer_list<std::tuple<int,int,char>>{{-1,0,'D'},{+1,0,'U'},{0,-1,'R'},{0,+1,'L'}};
    static constexpr auto direction_tuples_opp = std::initializer_list<std::tuple<int,int,char>>{{-1,0,'U'},{+1,0,'D'},{0,-1,'L'},{0,+1,'R'}};

    inline GraphAdjMatrix(): rows{N}, cols{M} {}

    inline void set(const int &t_rows, const int &t_cols) {
        rows = t_rows;
        cols = t_cols;
    }

    inline void reset_visited() {
        for(int i = 0; i < N; ++i) this->visited[i].reset();
    }

    inline bool is_valid_point(const int &x, const int &y) const {
        return ((0 <= x && x < rows) and (0 <= y && y < cols));
    }
};

//####################################################################################################################

int main(){
    int vertices = 10;

    Graph g(vertices);
    g.add_edge(1,2); g.add_edge(2,1);
    g.add_edge(2,3); g.add_edge(3,2);
    // g.add_edge(1,3); g.add_edge(3,1);  // Uncomment this and the graph will NOT be a Bipartite Graph

    pair<BipartiteGraphData, bool> bipartite_result = bipartite_graph_split(g, 0, g.vertices-1);
    if(bipartite_result.second){
        const BipartiteGraphData &gdata = bipartite_result.first;
        cout << "\nThe graph is a Bipartite Graph :)";
        cout << "\nvertices in set 0: ";
        for(int i = 0; i < vertices; ++i)
            if(gdata.visited[i] && gdata.color[i]==false) cout << i << " ";
        cout << "\nvertices in set 1: ";
        for(int i = 0; i < vertices; ++i)
            if(gdata.visited[i] && gdata.color[i]==true) cout << i << " ";
        cout << "\n\n";
    } else {
        cout << "The graph is NOT a Bipartite Graph :(" << endl;
    }

    DFSData gdata(vertices);
    bool is_bipartite_graph = true;
    for(int i = 0; i < vertices; ++i){
        if(gdata.visited[i]) continue;
        if(dfs(g, i, gdata, 0) == false){
            cout << "\nThe graph is NOT a Bipartite Graph :(" << endl;
            is_bipartite_graph = false;
            break;
        }
    }
    if(is_bipartite_graph){
        cout << "\nThe graph is a Bipartite Graph :)";
        cout << "\nvertices in set 0: ";
        for(int i = 0; i < vertices; ++i)
            if(gdata.visited[i] && gdata.parity[i]==false) cout << i << " ";
        cout << "\nvertices in set 1: ";
        for(int i = 0; i < vertices; ++i)
            if(gdata.visited[i] && gdata.parity[i]==true) cout << i << " ";
        cout << "\n\n";
    }

    //--------------------------------

    Graph g1(4);                        //
    g1.add_edge(0,1); g1.add_edge(1,0); //   【𝟬】----------【𝟭】----------【𝟯】
    g1.add_edge(0,2); g1.add_edge(0,2); //     |             |       ____/  |
    g1.add_edge(1,2); g1.add_edge(1,2); //     |             |  ____/      |
    g1.add_edge(2,3); g1.add_edge(3,2); //     |             | /            |
    g1.add_edge(1,3); g1.add_edge(3,1); //     +-----------【𝟮】------------+
    g1.add_edge(2,3); g1.add_edge(3,2); //

    CycleData cd = find_cycle(g1, 0, g1.vertices-1);
    if(cd.has_cycle) {
        cout << "\nCycle exists in g1\n";
        vector<int> cycle_arr = find_cycle(cd);
        cout << "    len = " << cycle_arr.size() << "\n    cycle = ";
        for(int i = 0; i < cycle_arr.size(); ++i) cout << cycle_arr[i] << ' ';
    } else {
        cout << "\nCycle does NOT exist in g1";
    }
    cout << "\n\n\n";

    //--------------------------------

    GraphVectorWeighted g2(4);              //            6             9
    g2.add_edge(0,1,6); g2.add_edge(1,0,6); //   【𝟬】----------【𝟭】----------【𝟯】
    g2.add_edge(0,2,7); g2.add_edge(0,2,7); //     |             |       ____/  |
    g2.add_edge(1,2,8); g2.add_edge(1,2,8); //     |           8 |  ____/ 20    |
    g2.add_edge(2,3,2); g2.add_edge(3,2,2); //     |             | /            |
    g2.add_edge(1,3,9); g2.add_edge(3,1,9); //     +-----------【𝟮】------------+
    g2.add_edge(2,3,20); g2.add_edge(3,2,20); //          7             2

    pair<GraphVectorWeighted,long> g2_mst = minimum_spanning_tree_kruskals(g2);
    cout << "MST for g2, cost = " << g2_mst.second << endl;
    cout << "MST Edges:";
    for(int i = 0; i < g2.adj.size(); ++i){
        cout << "\n\t" << i << " : ";
        for(const auto &j: g2_mst.first.edge_iterator(i)) cout << "(" << j.vertex << "," << j.cost << ")" << " ";
    }
    cout << "\n\n";

    cout << "Dijkstra shortest path cost (0--->3) = " << dijkstras(g2, 0/* , 3 */)[3];

    cout << "\n\n";
    return 0;
}
