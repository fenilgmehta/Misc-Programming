#include <iostream>
#include <cstdint>
#include <vector>
#include <stdexcept>
using namespace std;

#define int int32_t

//####################################################################################################################

/* 
 * This struct is used to store ANY TYPE of TREE in the form of array using 
 * fixed amount of storage, without using vector or linked lists.
 * 
 * The tree is 0-Indexed, hence valid vertices are 0 <= v < vertex_count
 * 
 */

#define TREE1_CATCH_EXCEPTIONS

struct Tree1{
    struct TreeNode{
        int vertex, link;
        TreeNode(): vertex{-1}, link{-1} {}
        TreeNode(int v, int l): vertex{v}, link{l} {}
    };
    vector<TreeNode> edge_list;  // stores the linked list of edges in the array.
    vector<int> head;  // stores head for each vertex
    int vertex_count, edges;

    /* Vertex count starts from 0 to `vertex_count-1` */
    Tree1(int t_vertex_count): vertex_count{t_vertex_count}, edges{0} {
        head.resize(vertex_count, -1);
        edge_list.resize(2*(vertex_count-1));  // NOTE: size is `2*(vertex_count-1)` as for each edge, we have to make two entries
    }

    void add_edge(const int v1, const int v2) {
        #ifdef TREE1_CATCH_EXCEPTIONS
            if(v1==v2) throw invalid_argument("Tree can NOT have loops");
            if(v1>=vertex_count or v2>=vertex_count) throw invalid_argument("Vertex can have value in the range [0, "+to_string(vertex_count)+")");
            if((edges+1) >= vertex_count) throw invalid_argument("Only `vertex_count-1` edges are allowed in a tree");
            // WARNING: it is assumed that the user does NOT add edge between vertices which break properties of a tree
        #endif
        ++edges;
        edge_list[edges*2-2] = {v2, head[v1]};  // update the link
        edge_list[edges*2-1] = {v1, head[v2]};  // update the link
        head[v1] = edges*2-2;  // update the head
        head[v2] = edges*2-1;  // update the head
    }

    struct Tree1Iter{
        const Tree1 &t;
        int i;

        inline Tree1Iter(const Tree1 &t1): t{t1}, i{-1} {}
        inline Tree1Iter(const Tree1 &t1, const int &vertex1): t(t1), i{t.head[vertex1]} { }
        inline Tree1Iter& operator ++(){ i = t.edge_list[i].link; return *this; }
        inline const Tree1::TreeNode& operator*(){ return t.edge_list[i]; }
        inline bool operator!=(const Tree1Iter &t1){ return (((&t)!=(&t1.t)) || (i!=t1.i)); }

        inline Tree1Iter& begin() {return *this;}
        inline Tree1Iter end() {return Tree1Iter(this->t);}
    };
    inline Tree1Iter edge_iterator(const int &vertex) const { return Tree1Iter(*this, vertex); }
};


//##########################################################

/* Countes the number of leaf nodes under the vertex `v1` 
 * WARNING: it is assumed that the user will select `v1` such that 0 <= v1 < vertex_count
 * NOTE: we mark the vertex as visited after popping it from the stack
 */
int dfs(const Tree1 &tree, const int &v1, const int &parent=-1){
    bool is_leaf = true;
    int sum = 0;

    for(const Tree1::TreeNode &i: tree.edge_iterator(v1)){
        if(i.vertex == parent) continue;
        is_leaf = false;
        sum += dfs(tree, i.vertex, v1);
    }

    if(is_leaf) return 1;
    return sum;
}

/*
- BFS
  - REFER: https://leetcode.com/problems/binary-tree-level-order-traversal/
- Binary tree from Preorder and Inorder Traversal
  - REFER: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
- Binary Tree from Inorder and Postorder Traversal
  - REFER: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
*/

//####################################################################################################################

int main(){
    Tree1 t(9);      /*    Assuming 1 as root      */
    t.add_edge(2,3);  /*                 1          */
    t.add_edge(4,1);  /*        0       /|\         */
    t.add_edge(1,5);  /*               4 5 2        */    
    t.add_edge(7,4);  /*              /    |\       */
    t.add_edge(8,2);  /*             7     8 3      */
    t.add_edge(2,1);  /*                      \     */
    t.add_edge(3,6);  /*                       6    */
    cout << "Head = "; for(auto &i: t.head) cout << i << ", "; cout << endl;
    cout << "Adj = "; for(auto &i: t.edge_list) cout << "(" << i.vertex << "," << i.link << ") "; cout << endl;
    cout << boolalpha << "t.dfs(0) == 1 : " << (dfs(t, 0)==1) << endl;  // perform DFS assuming 0 as root
    cout << boolalpha << "t.dfs(1) == 4 : " << (dfs(t, 1)==4) << endl;  // perform DFS assuming 1 as root
    cout << boolalpha << "t.dfs(4) == 4 : " << (dfs(t, 4)==4) << endl;  // perform DFS assuming 4 as root
    cout << boolalpha << "t.dfs(7) == 3 : " << (dfs(t, 7)==3) << endl;  // perform DFS assuming 7 as root
    cout << boolalpha << "t.dfs(5) == 3 : " << (dfs(t, 5)==3) << endl;  // perform DFS assuming 5 as root
    cout << boolalpha << "t.dfs(2) == 4 : " << (dfs(t, 2)==4) << endl;  // perform DFS assuming 2 as root
    cout << boolalpha << "t.dfs(3) == 4 : " << (dfs(t, 3)==4) << endl;  // perform DFS assuming 3 as root
    
    try{
        t.add_edge(123,122);
    } catch (invalid_argument e) {
        cout << "EXCEPTION: " << e.what() << endl;
    }

    return 0;
}