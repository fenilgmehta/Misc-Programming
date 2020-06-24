#include <bits/stdc++.h> // This is all in one include library
using namespace std;
//------------------------------------------------
#define db(a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<#a<<"\033[1;31m"<<" : "<<"\033[0m"<<a<<'\n'; cout.flush(); cerr.flush();}
#define dbiter(...) dbgIter(#__VA_ARGS__, __VA_ARGS__)
template <class T> void dbgIter(const char *sdbg, T a, T b) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n"; cout.flush(); cerr.flush();}
#define endl '\n'  // WARNING: REMOVE this is working on interactive programs
#define ulimit(_i, _startLimit, _endLimit) for(int32_t _i = (_startLimit), _i ## ztempEnd = (_endLimit) ; _i <= _i##ztempEnd; ++_i)
#define dlimit(_i, _startLimit, _endLimit) for(int32_t _i = (_startLimit), _i ## ztempEnd = (_endLimit) ; _i >= _i##ztempEnd; --_i)
#define IN(type, arr, starti, endi) { type(ztempzi, starti, endi) cin>>arr[ztempzi]; }
#define OUT(type, arr, starti, endi, sep) { type(ztempzo, starti, endi) cout<<arr[ztempzo]<<sep; }
#define uall(arr_name) begin(arr_name),end(arr_name)
#define uiter(arr_name, iter_start, iter_end) next(begin(arr_name),iter_start),next(begin(arr_name),iter_end)
#define dall(arr_name) rbegin(arr_name),rend(arr_name)
#define diter(arr_name, iter_start, iter_end) make_reverse_iterator(next(begin(arr_name),iter_end)),make_reverse_iterator(next(begin(arr_name),iter_start))
#define gett(_tup, _n) get<_n>(_tup)
#define short int16_t
#define int int32_t
#define long int64_t     // WARNING: REMOVE this when using `long double`
#define int128 __int128  // WARNING: Only works with few compilers
template<typename T, typename S> inline auto min(const T a, const S b) { return ((a < b) ? a : b); }
template<typename T, typename S> inline auto max(const T a, const S b) { return ((a > b) ? a : b); }
template<typename T, typename S> inline bool contains(const T &container1, const S &value1) { return container1.find(value1) != container1.end(); }
template<typename T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_heap = priority_queue<T>;
template<typename T, typename U> std::vector<T> MatrixVector(int n, U v){ return std::vector<T>(n, v);}
template<typename T, class... Args> auto MatrixVector(int n, Args... args){auto val = MatrixVector<T>(args...); return std::vector<decltype(val)>(n, move(val));}
// auto matrixM = MatrixVector<int32_t>(9,8,7,6,5)  // dimention = 9*8*7*6, default value=5

//------------------------------------------------

void solve(){
    
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(20); cout << fixed;

    int T = 1;
    // TODO: remove below statement if only single testcase
    cin>>T;
    while (T--)
        solve();

    return 0;
}
