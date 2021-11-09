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
// REFER: https://medium.com/@RamkrishnaKulka/disjoint-set-union-union-find-the-same-blood-type-e67c51b1d2
// Applications:
//     1. determine the connected components in a graph
//     2. determine the cycles in the graph
//     3. improve speed of Kruskal's algorithm

// REFER - 4th question (Locked Doors)
// https://codingcompetitions.withgoogle.com/kickstart/submissions/000000000019ff08/YmVldC5haXp1
struct DisjointSetUnion {
    int num{};  // stores number of different sets
    vector<int> rr, pp;  // "rr" stores rank of a set (i.e. its size), "pp" stores the parent
    DisjointSetUnion() = default;

    explicit DisjointSetUnion(int n) : num(n), rr(n, 1), pp(n) {
        iota(pp.begin(), pp.end(), 0);
    }

    /*
     * NOTE: This recursive approach makes all the child nodes directly point to the root
     *       of their subset. The first condition used is "p[v] == p[p[v]]" to avoid useless
     *       recursive call when find_set(...) is called for a node directly connected to
     *       the root of the subset.
     * Time Complexity = O(n), Θ(1), Ω(1) ---> provided path compression is performed
     * */
    int find_set(int x) {
        return (pp[x] == pp[pp[x]]) ? pp[x] : (pp[x] = find_set(pp[x]));
    }
    /*
    // Time Complexity = O(log n), Θ(log n), Ω(1) ---> provided path compression is performed
    int find_set(int v){
        // chase parent of current node until it reaches the root
        while(v != p[v]){
            // this line causes path compression, i.e. it sets the parent of current node as its grandparent.
            // remove the line to stop path compression
            p[v] = p[p[v]];
            v = p[v];
        }
        return v;
    }
    */

    /*
     * Weighted union
     *     Description: Make the subsets containing `x` and `y` part of same set
     *     Name is `union_sets` as `union` is a keyword
     *     Time Complexity = O(α(n)), where α(n) is the inverse Ackermann function
     *     Return: `true` if the subsets containing `a` and `b` are successfully unioned,
     *             `false` if the subsets `a` and `b` already belong to the same subset.
     * */
    bool union_sets(int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x == y) return false;  // This will avoid increase in subset size if elements are is the same subset
        if (rr[x] < rr[y]) swap(x, y);
        rr[x] += rr[y];
        pp[y] = x;
        num--;
        return true;
    }

    /*
     * Find whether x, y are connected/in same subset or not
     *     Time Complexity = O(α(n)), where α(n) is the inverse Ackermann function
     *     Return: `true` if `x` and `y` are connected
     * */
    bool in_same_set(int x, int y) {
        return find_set(x) == find_set(y);
    }

    // returns size of set of "x"
    inline int size(int x) { return rr[find_set(x)]; }

    // returns count of distinct sets
    inline int count() const { return num; }

    void debug() {
        cout << "parent   = [ "; for (auto &i: pp) cout << i << ", "; cout << "]" << endl;
        cout << "set rank = [ "; for (auto &i: rr) cout << i << ", "; cout << "]" << endl;
    }
};

//####################################################################################################################

int main() {
    DisjointSetUnion dsu(10);

    dsu.union_sets(8, 4);
    dsu.debug(); cout << endl;

    dsu.union_sets(4, 3);
    dsu.debug(); cout << endl;

    cout << "----------\n\n";

    DisjointSetUnion dsu2(13);

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

    for (const int &i: {2, 3, 5, 7, 9, 10, 12}) {
        for (const int &j: {2, 3, 5, 7, 9, 10, 12}) {
            cout << boolalpha << "dsu2.in_same_set(" << i << ", " << j << ") = " << dsu2.in_same_set(i, j) << endl;
        }
    }
    cout << endl;
    dsu2.debug(); cout << endl;

    return 0;
}
