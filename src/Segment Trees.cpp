#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;

#define db(a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<#a<<"\033[1;31m"<<" : "<<"\033[0m"<<a<<'\n'; cout.flush(); cerr.flush();}
#define dbiter(...) dbgIter(#__VA_ARGS__, __VA_ARGS__)
template <class T> void dbgIter(const char *sdbg, T a, T b) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n"; cout.flush(); cerr.flush();}
#define endl '\n'  // WARNING: REMOVE this is working on interactive programs
#define int int32_t
#define long int64_t     // WARNING: REMOVE this when using `long double`

//####################################################################################################################

/*

Also known as Statistic Tree
A similar data structure is the interval tree.

𝗥𝗘𝗙𝗘𝗥: https://codeforces.com/blog/entry/18051
𝗥𝗘𝗙𝗘𝗥: https://cp-algorithms.com/data_structures/segment_tree.html  // NEW

• Anything that can be done using a Binary Index Tree(BIT, i.e. Fenwick Tree) can also be done using a segment tree
• 𝗡𝗢𝗧𝗘: all index values in method parameters are assumed to be 𝟬-𝗶𝗻𝗱𝗲𝘅𝗲𝗱
• 𝗡𝗢𝗧𝗘: the working is quite similar to C++ STL function and algorithms
• 𝗡𝗢𝗧𝗘: query(...) range [l, r), the right end is not included
• TESTED and WORKING

• 𝗡𝗢𝗧𝗘: It is 𝗺𝗮𝗻𝗱𝗮𝘁𝗼𝗿𝘆 to make CombinerFuntion to be "const member functions"

*/
template<typename T, size_t N, typename CombinerFunction>
struct SegmentTree{
    T arr[2*N];
    size_t n;
    T default_value;
    CombinerFunction combine;

    SegmentTree(const T &t_default_value=T()): n{N}, default_value{t_default_value}, combine() { this->reset(); }

    inline size_t size() const { return n; }
    inline void resize(const size_t new_size) { n = new_size; }
    inline void reset() { fill(arr, arr + 2*n, default_value); }

    /* Returns base array value at index `idx` */
    inline T& operator [](const size_t idx) { return arr[n+idx]; }

    // NOTE: we use `int` in the for loop to handle cases where n <= 0
    void build() {
        for(int i = n-1; i > 0; --i) arr[i] = combine(arr[i<<1], arr[(i<<1)^1]);
    }

    void build_idx(size_t idx) {
        // NOTE: `(idx|1)^1` is always the left child and `idx|1` is always the right child
        for(idx += n; idx > 1 ; idx >>= 1) arr[idx >> 1] = combine(arr[(idx|1)^1], arr[idx|1]);
    }

    void modify(size_t idx, const T &new_value) {
        // NOTE: `(idx|1)^1` is always the left child and `idx|1` is always the right child
        for(arr[idx += n] = new_value; idx > 1 ; idx >>= 1) arr[idx >> 1] = combine(arr[(idx|1)^1], arr[idx|1]);
    }

    void update(size_t idx, const T &diff) {
        modify(idx, combine(this->operator[](idx), diff));
    }

    /* the result is equivalent to applying combine on the range [l, r), note that r is excluded */
    T query(size_t l, size_t r) const {
        T resl = default_value, resr = default_value;
        for(l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if(l & 1) resl = combine(resl, arr[l++]);
            if(r & 1) resr = combine(arr[--r], resr);
        }
        return combine(resl, resr);
    }

    /* Returns the first index where element >= value, NOTE: only useful for MAX Segment Tree
     * Used in ---> Hotel Queries: https://cses.fi/problemset/task/1143/
     * */
    int query_idx(const T &value) const {
        int i = n;
        while(i > 0) {
            while(not (i & 1)) i >>= 1;  // keep going to the parent if `i` is even

            // now `i` is odd, i.e. it is root of the sub-SegmentTree
            while(i < n && arr[i] >= value) {
                if(arr[i << 1] >= value) i <<= 1;  // left child
                else i = i << 1 | 1;               // right child
            }

            if(i >= n && arr[i] >= value) return i - n;

            if(i==1) break;
            ++i;
        }
        return -1;
    }
};

//####################################################################################################################

/* The last level of the tree is filled with actual elements and the
 * parents store the value after combining the value at both the children.
 **/
template<typename T, typename CombinerFunction>
struct SegmentTreeSimple{
    vector<T> tree;
    size_t n, n_base;
    const T default_value;
    CombinerFunction combine;

    SegmentTreeSimple(const size_t t_n, const T &t_default_value):
        n_base{t_n}, default_value{t_default_value}, n{calculate_size(t_n)}, combine() 
    {
        this->reset();
    }

    inline size_t size() const { return n_base; }
    inline void resize(const size_t new_size) { n_base = new_size, n = calculate_size(new_size); }
    inline void reset() { tree.assign(n, default_value); }

    /* Returns base array value at index `idx` */
    inline T& operator [](const size_t idx) { return tree[(n>>1) + idx]; }

    void build() { 
        for(size_t i = (n >> 1)-1; i > 0; --i) tree[i] = combine(tree[i << 1], tree[(i << 1) ^ 1]);
    }

    void modify(size_t idx, const T &new_value) {
        idx += (n >> 1);
        tree[idx] = new_value;
        for(idx >>= 1; idx > 0; idx >>= 1) tree[idx] = combine(tree[idx << 1], tree[(idx << 1) ^ 1]);
    }

    void update(const size_t idx, const T &diff) {
        modify(idx, combine(this->operator[](idx), diff));
    }

    /* the result is equivalent to applying combine on the range [l, r), note that r is excluded */
    T query(size_t l, size_t r) const {
        T resl = default_value, resr = default_value;
        l += (n>>1);
        r += (n>>1);
        for(; l < r; l>>=1, r>>=1){
            if(l&1) resl = combine(resl, tree[l++]);
            if(r&1) resr = combine(tree[--r], resr);
        }
        return combine(resl, resr);
    }

    /* Returns size of complete binary tree to build segment tree for array of size `n` */
    template<typename SizeT>
    static inline SizeT calculate_size(const SizeT n){
        // return 2 * pow(2, ceil(log2(n)));
        return (static_cast<SizeT>(1) << static_cast<SizeT>(ceil(log2(n)))) << 1;
    }
};

//####################################################################################################################

template<typename T, typename CombinerFunction>
struct [[deprecated("Replaced by `SegmentTreeSimple`, which is faster, uses iterative algorithms, has an improved interface and provides more functionalities.")]]
SegmentTreeSimpleRecursive{
    vector<T> tree;
    size_t n, n_base;
    const T default_value;
    CombinerFunction combine;

    SegmentTreeSimpleRecursive(const size_t t_n, const T &t_default_value):
        n_base{t_n}, default_value{t_default_value}, n{calculate_size(t_n)}, combine() 
    {
        this->reset();
    }

    inline size_t size() const { return n_base; }
    inline void resize(const size_t new_size) { n_base = new_size, n = calculate_size(new_size); }
    inline void reset() { tree.assign(n, default_value); }

    // NOTE: we use `int` in the for loop to handle cases where n <= 0
    template<typename RandomIt>
    void build(const RandomIt first, const size_t node_idx, const size_t u, const size_t v){
        if(u > v) return;
        if(u == v) {
            tree[node_idx] = *next(first, u);
            return;
        }
        const size_t uv_by_2 = (u+v) >> 1;
        build(first, node_idx << 1, u, uv_by_2);
        build(first, (node_idx << 1) ^ 1, uv_by_2+1, v);
        tree[node_idx] = combine(tree[node_idx << 1], tree[(node_idx << 1) ^ 1]);
    }

    template<typename RandomIt>
    void build(const RandomIt first) { build(first, 1, 0, n_base-1); }

    void modify(const size_t idx, const T &new_value, const size_t node_idx, const size_t u, const size_t v){
        if(idx < u || v < idx) return;
        if(u==v && idx==u){
            tree[node_idx] = new_value;
            return;
        }
        const size_t uv_by_2 = (u+v) >> 1;
        if(idx <= uv_by_2) modify(idx, new_value, node_idx << 1, u, uv_by_2);
        else modify(idx, new_value, (node_idx << 1) ^ 1, uv_by_2+1, v);

        tree[node_idx] = combine(tree[node_idx << 1], tree[(node_idx << 1) ^ 1]);
    }

    void modify(const size_t idx, const T &new_value) { modify(idx, new_value, 1, 0, n_base-1); }

    T query(const size_t l, const size_t r, const size_t node_idx, const size_t u, const size_t v){
        if(r < u || v < l) return default_value;
        if(l <= u && v <= r) return tree[node_idx];
        const size_t uv_by_2 = (u+v) >> 1;
        return combine(query(l, r, node_idx << 1, u, uv_by_2), query(l, r, (node_idx << 1) ^ 1, uv_by_2+1, v));
    }

    /* the result is equivalent to applying combine on the range [l, r), note that r is excluded */
    T query(const size_t l, const size_t r) { return query(l, r-1, 1, 0, n_base-1); }

    /* Returns size of complete binary tree to build segment tree for array of size `n` */
    template<typename SizeT>
    static inline SizeT calculate_size(const SizeT n){
        // return 2 * pow(2, ceil(log2(n)));
        return (static_cast<SizeT>(1) << static_cast<SizeT>(ceil(log2(n)))) << 1;
    }
};

//####################################################################################################################

struct MyCombinerMin {
    template<typename T, typename S>
    inline auto operator()(const T &a, const S &b) const { return ((a < b) ? a : b); }
};

struct MyCombinerMax {
    template<typename T, typename S>
    inline auto operator()(const T &a, const S &b) const { return ((a > b) ? a : b); }
};

// 𝗡𝗢𝗧𝗘: the below solution to 2D Segment Tree and Fenwick Tree is 𝘁𝗼𝗼 slow
// template<typename T, size_t N, typename CombinerFunction>
// struct SegmentTreeCombiner{
//     auto operator()(const SegmentTree<T, N, CombinerFunction> &a, const SegmentTree<T, N, CombinerFunction> &b) const {
//         SegmentTree<T, N, CombinerFunction> st_res(0);
//         for(size_t i = 0; i < 2*N; ++i) st_res.arr[i] = st_res.combine(a.arr[i], b.arr[i]);
//         // for(int i = 0; i < N; ++i) st_res[i] = a[i] + b[i];
//         // st_res.build();
//         return st_res;
//     }
// };
// 
// SegmentTree<
//     SegmentTree<int, 1001, plus<int>>,
//     1001,
//     SegmentTreeCombiner<int, 1001, plus<int>>
// > bit2d(0);

// template<typename T, typename CombinerFunction = plus<T>, typename SplitterFunction = minus<T>>
// struct BinaryIndexTreeCombiner{
//     auto operator()(const BinaryIndexTree<T, CombinerFunction, SplitterFunction> &a,
//                     const BinaryIndexTree<T, CombinerFunction, SplitterFunction> &b) const {
//         BinaryIndexTree<T, CombinerFunction, SplitterFunction> st_res(a.size());
//         for(int32_t i = 0; i < st_res.n; ++i) st_res.bit[i] = st_res.combine(a.bit[i], b.bit[i]);
//         // for(int i = 0; i < N; ++i) st_res[i] = a[i] + b[i];
//         // st_res.build();
//         return st_res;
//     }
// };
// 
// SegmentTree<
//     BinaryIndexTree<int, plus<int>, minus<int>>,
//     1001,
//     BinaryIndexTreeCombiner<int, plus<int>, minus<int>>
// > bit2d(BinaryIndexTree<int, plus<int>, minus<int>>(1001, 0));

//####################################################################################################################

// constexpr int INF = static_cast<int>(1) << 30;
// constexpr int MAX_N =  2'00'001;  // used 8 for debugging
// SegmentTree<int, MAX_N, INF, MyCombinerMin<int> > st;

int main() {
    // 𝗡𝗢𝗧𝗘: do not forget to call build after filling the tree with values

    // const int ST_SIZE = 9;
    // SegmentTree<int, ST_SIZE, numeric_limits<int>::max(), MyCombinerMin> st;  // range max query
    // SegmentTree<int, ST_SIZE, numeric_limits<int>::min(), MyCombinerMax> st;  // range min query
    // SegmentTree<int, ST_SIZE, 0, plus<int>> st;        // range binary sum query
    // SegmentTree<int, ST_SIZE, 1, multiplies<int>> st;  // range binary product query
    // SegmentTree<int, ST_SIZE, 0, bit_xor<int>> st;     // range binary xor query
    // SegmentTree<int, ST_SIZE, 0, bit_or<int>> st;      // range binary or query
    // SegmentTree<int, ST_SIZE, numeric_limits<int>::max(), bit_and<int>> st;   // range binary AND query

    SegmentTree<int, 9, MyCombinerMin> st(999'999);
    tie(st[0], st[1], st[2], st[3], st[4], st[5], st[6], st[7], st[8]) = make_tuple(1,3,2,4,5,1,1,5,3);
                                                                        // index -> 0 1 2 3 4 5 6 7 8
    
    cout << endl;
    st.build();
    cout << "Segment Tree for query on MINIMUM element in a range" << endl;
    cout << "Successfully executed `st.build();`" << endl;
    cout << endl;

    cout << "NOTE: the array is 0-indexed, and the range is [left, right)" << endl;
    cout << "Array = {1, 3, 2, 4, 5, 1, 1, 5, 3}" << endl;
    cout << endl;
    cout << boolalpha << "st.query(2,4+1) == 2   --->   " << (st.query(2,4+1) == 2) << endl;
    cout << boolalpha << "st.query(5,6+1) == 1   --->   " << (st.query(5,6+1) == 1) << endl;
    cout << boolalpha << "st.query(1,8+1) == 1   --->   " << (st.query(1,8+1) == 1) << endl;
    cout << boolalpha << "st.query(3,3+1) == 4   --->   " << (st.query(3,3+1) == 4) << endl;
    cout << endl;

    st.modify(5, -99);
    cout << "Successfully executed `st.modify(5, -99);`" << endl;
    cout << boolalpha << "st.query(1, 8+1) == -99   --->   " << (st.query(1, 8+1) == -99) << endl;
    cout << endl;

    return 0;
}
