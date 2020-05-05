#include <bits/stdc++.h> // This is all in one include library
using namespace std;
//------------------------------------------------
#define db(a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<#a<<"\033[1;31m"<<" : "<<"\033[0m"<<a<<'\n';}
#define dbiter(...) dbgIter(#__VA_ARGS__, __VA_ARGS__)
template <class T> void dbgIter(const char *sdbg, T a, T b) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}
#define endl '\n'  // WARNING: REMOVE this is working on interactive programs
#define urange(_i, _startLimit, _endLimit) for(int64_t (_i) = (_startLimit); (_i) < (_endLimit); ++(_i))
#define ulimit(_i, _startLimit, _endLimit) for(int64_t (_i) = (_startLimit); (_i) <= (_endLimit); ++(_i))
#define dlimit(_i, _startLimit, _endLimit) for(int64_t (_i) = (_startLimit); (_i) >= (_endLimit); --(_i))
#define uall(arr_name) begin(arr_name),end(arr_name)
#define uiter(arr_name, iter_start, iter_end) next(begin(arr_name),iter_start),next(begin(arr_name),iter_end)
#define dall(arr_name) rbegin(arr_name),rend(arr_name)
#define diter(arr_name, iter_start, iter_end) make_reverse_iterator(next(begin(arr_name),iter_end)),make_reverse_iterator(next(begin(arr_name),iter_start))
#define short int16_t
#define int int32_t
#define long int64_t     // WARNING: REMOVE this when using `long double`
#define int128 __int128  // WARNING: Only works with few compilers
#define matrix(T,name,rows,cols,val) vector<vector<T>> name((rows),vector<T>((cols),(val)));
template<typename T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_heap = priority_queue<T>;
template<typename T, typename S> inline bool contains(const map<T,S> &map1, const S &value1) { return map1.find(value1) != map1.end(); }
template<typename T, typename S> inline bool contains(const T &container1, const S &value1) { return container1.find(value1) != container1.end(); }

//------------------------------------------------

void solve(){
    
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(20); cout << fixed;

    int T; cin>>T;
    while (T--)
        solve();

    return 0;
}
