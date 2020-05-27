#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#define int int32_t

//####################################################################################################################

// REFER: https://cp-algorithms.com/data_structures/disjoint_set_union.html
// REFER: https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
// REFER: https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/tutorial/
// Applications:
//     1. determine the connected components in a graph
//     2. determine the cycles in the graph
//     3. improve speed of Kruskal's algorithm

struct DisjoinSetUnion{
    vector<int> p, s; // p -> parent, s -> subset size


    DisjoinSetUnion(const int t_size){
        p.resize(t_size), s.resize(t_size);
        iota(p.begin(), p.end(), 0);
        fill(s.begin(), s.end(), 1);
    }


    /* NOTE: this recursive approach makes all the child nodes directly point to the root of their subset
     * Time Complexity = O(n), Θ(1), Ω(1) ---> provided path compression is performed
     * */
    int find_set(const int v){
        return (p[v]==p[p[v]]) ? (p[v]) : (p[v] = find_set(p[v]));  // v==p[v]
    }
    /* Time Complexity = O(log n), Θ(log n), Ω(1) ---> provided path compression is performed */
    // int find_set(int v){
    //     // chase parent of current node until it reaches the root
    //     while(v != p[v]){
    //         // this line causes path compression, i.e. it sets the parent of current node as its grandparent.
    //         // remove the line to stop path compression
    //         p[v] = p[p[v]];
    //         v = p[v];
    //     }
    //     return v;
    // }


    /*
     * Weighted union
     *     Description: Make the subsets containing `t_a` and `t_b` part of same set
     *     Name is `union_sets` as `union` is a keyword
     *     Time Complexity = O(α(n)), where α(n) is the inverse Ackermann function
     *     Return: `true` if the subsets containing `t_a` and `t_b` are successfully unioned,
     *             `false` if the subsets `t_a` and `t_b` already belong to the same subset.
     * */
    bool union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if(a == b) return false;  // This will avoid increase in subset size if elements are is the same subset
        if(s[a] >= s[b]){
            p[b] = a;
            s[a] += s[b];
        } else {
            p[a] = b;
            s[b] += s[a];
        }
        return true;
    }


    /* Find whether t_a, t_b are connected/in same subset or not
     *     Time Complexity = O(α(n)), where α(n) is the inverse Ackermann function
     *     Return: `true` if `t_a` and `t_b` are connected
     * */
    bool in_same_set(const int t_v1, const int t_v2){
        return find_set(t_v1)==find_set(t_v2);
    }


    void debug(){
        cout << "p = [ "; for(auto &i: p) cout << i << ", "; cout << "]" << endl;
        cout << "s = [ "; for(auto &i: s) cout << i << ", "; cout << "]" << endl;
    }
};

//##########################################################

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

int main(){
    DisjoinSetUnion dsu(10);

    dsu.union_sets(8, 4);
    dsu.debug(); cout << endl;

    dsu.union_sets(4, 3);
    dsu.debug(); cout << endl;

    cout << "----------\n\n";

    DisjoinSetUnion dsu2(13);

    dsu2.union_sets(2, 10);
    dsu2.debug(); cout << endl;

    dsu2.union_sets(7, 3);
    dsu2.debug(); cout << endl;

    dsu2.union_sets(10, 5);
    dsu2.debug(); cout << endl;

    dsu2.union_sets(7, 2);
    dsu2.debug(); cout << endl;

    dsu2.union_sets(9, 12);
    dsu2.debug(); cout << endl;

    dsu2.union_sets(2, 12);
    dsu2.debug(); cout << endl;

    for(const int &i: {2,3,5,7,9,10,12}){
        for(const int &j: {2,3,5,7,9,10,12}){
            cout << boolalpha << "dsu2.is_same_set("<<i<<", "<<j<<") = " << dsu2.in_same_set(i,j) << endl;
        }
    }
    cout << endl;
    dsu2.debug(); cout << endl;

    return 0;
}