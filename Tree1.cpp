#include <iostream>
#include <cstdint>
#include <array>
#include <stdexcept>
using namespace std;

#define int int32_t

//####################################################################################################################

/* 
 * This class is used to store ANY TYPE of TREE in the form of array using 
 * fixed amount of storage, without using vector or linked lists.
 */

#define TREE1_CATCH_EXCEPTIONS

template<size_t vertices_count>
class Tree1{
public:
    int edges;
    // Array are used as 1-indexed, hence 1 is added.
    // 👇 stores head for each vertex
    array<int, vertices_count+1> head;
    // 👇 stores the linked list of edges in the array. format: pair<vertex number, link>
    array<pair<int,int>, 2*vertices_count-1> connection_list;
    // NOTE: size is `2*vertices_count-1` as for each edge, we have to make two entries

    /* Vertex count starts from 1 to `vertices_count` */
    Tree1(): edges{0}{
        fill(begin(head), end(head), -1);
    }

    void connect(const int v1, const int v2) {
    #ifdef TREE1_CATCH_EXCEPTIONS
        if(v1==v2) throw invalid_argument("Tree can NOT have loops");
        if(v1>vertices_count or v2>vertices_count) throw out_of_range("Vertex can have value in the range [1, "+to_string(vertices_count)+"]");
        if((edges+1) >= vertices_count) throw out_of_range("Only `vertices_count-1` edges are allowed in a tree");
        // WARNING: it is assumed that the user does NOT add edge between vertices which break properties of a tree
    #endif
        ++edges;
        connection_list[edges*2-1].first = v2;
        connection_list[edges*2-1].second = head[v1];  // update the link
        connection_list[edges*2].first = v1;
        connection_list[edges*2].second = head[v2];  // update the link
        head[v1] = edges*2-1;  // update the head
        head[v2] = edges*2;  // update the head
    }

    /* Countes the number of leaf nodes under the vertex `v1` 
     * WARNING: it is assumed that the user will select `v1` such that 1 <= v1 <= vertices_count
     */
    int dfs(const int &v1, const int &parent=-1){
        bool is_leaf = true;
        int sum = 0;
        for(int i = head[v1]; i != (-1); i = connection_list[i].second){
            if(connection_list[i].first == parent) continue;
            is_leaf = false;
            sum += dfs(connection_list[i].first, v1);
        }

        // db(is_leaf); db(sum);
        if(is_leaf) return 1;
        return sum;
    }
};

//####################################################################################################################

int main(){
    Tree1<8> t;      /*    Assuming 1 as root   */
    t.connect(2,3);  /*           1             */
    t.connect(4,1);  /*          /|\            */
    t.connect(1,5);  /*         4 5 2           */    
    t.connect(7,4);  /*        /    |\          */
    t.connect(8,2);  /*       7     8 3         */
    t.connect(2,1);  /*                \        */
    t.connect(3,6);  /*                 6       */
    cout << boolalpha << "t.dfs(1) = " << (t.dfs(1)==4) << endl;  // perform DFS assuming 1 as root
    cout << boolalpha << "t.dfs(4) = " << (t.dfs(4)==4) << endl;  // perform DFS assuming 4 as root
    cout << boolalpha << "t.dfs(7) = " << (t.dfs(7)==3) << endl;  // perform DFS assuming 7 as root
    cout << boolalpha << "t.dfs(5) = " << (t.dfs(5)==3) << endl;  // perform DFS assuming 5 as root
    cout << boolalpha << "t.dfs(2) = " << (t.dfs(2)==4) << endl;  // perform DFS assuming 2 as root
    cout << boolalpha << "t.dfs(3) = " << (t.dfs(3)==4) << endl;  // perform DFS assuming 3 as root
    
    try{
        t.connect(123,122);
    } catch (out_of_range e) {
        cout << "EXCEPTION: " << e.what() << endl;
    }

    return 0;
}