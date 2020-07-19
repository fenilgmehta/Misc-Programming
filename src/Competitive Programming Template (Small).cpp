#include <bits/stdc++.h> // This is all in one include library
using namespace std;
//------------------------------------------------
// #define db(a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<#a<<"\033[1;31m"<<" : "<<"\033[0m"<<a<<'\n'; cout.flush(); cerr.flush();}
template <typename Arg, typename... Args> inline void printErr(Arg&& arg, Args&&... args) { cerr << arg; (void)(int[]){0, (void(cerr << " "<<"\033[1;31m"<<"●"<<"\033[0m"<<" " << args),0)...}; cerr << '\n'; }
template<class T, class... U> void dbg(const char *sdbg, T h, U... a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<" "<<"\033[1;41m"<<"="<<"\033[0m"<<" "; printErr(h, a...); cout.flush(); cerr.flush();}
template <class T> void dbgIter(const char *sdbg, T a, T b) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n"; cout.flush(); cerr.flush();}
#define db(...)                         dbg(#__VA_ARGS__, __VA_ARGS__);
#define dbiter(...)                     dbgIter(#__VA_ARGS__, __VA_ARGS__);
#define GET_MACRO(a,b,c,d,NAME,...)     NAME
#define FORurange4(_i, _f, _l, _d)      for(int32_t _i = (_f), _i##ztEnd = (_l) ; _i < _i##ztEnd; _i+=(_d))
#define FORurange3(_i, _f, _l)          FORurange4(_i, _f, _l, 1)
#define FORurange2(_i, _l)              FORurange4(_i, 0, _l, 1)
#define FORurange1(_l)                  FORurange4(__i_temp__, 0, _l, 1)
#define FORulimit4(_i, _f, _l, _d)      FORurange4(_i, _f, _l+1, _d)
#define FORulimit3(_i, _f, _l)          FORurange4(_i, _f, _l+1, 1)
#define urange(...)                     GET_MACRO(__VA_ARGS__, FORurange4, FORurange3, FORurange2, FORurange1)(__VA_ARGS__)
#define ulimit(...)                     GET_MACRO(__VA_ARGS__, FORulimit4, FORulimit3)(__VA_ARGS__)
#define dlimit(_i, _f, _l)              for(int32_t _i = (_f), _i##ztEnd = (_l) ; _i >= _i##ztEnd; --_i)
#define FORiter(_it, _f, _l)    for(auto _it=(_f), _it##end=(_l); _it != _it##end; advance(_it,1))
#define foriter(_it, ...)       FORiter(_it, __VA_ARGS__)
#define uiter(arr, it_f, it_l)  next(begin(arr),it_f),next(begin(arr),it_l)
#define diter(arr, it_f, it_l)  make_reverse_iterator(next(begin(arr),it_l)),make_reverse_iterator(next(begin(arr),it_f))
#define gett(_tup, _n)          get<_n>(_tup)
#define short                   int16_t
#define int                     int32_t
#define long                    int64_t     // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: REMOVE this when using `long double`
#define int128                  __int128    // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: Only works with few compilers
#define newl                    '\n'        // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: do NOT use this when working on/with interactive programs
template<typename T, typename S> inline auto min(const T a, const S b) { return ((a < b) ? a : b); }
template<typename T, typename S> inline auto max(const T a, const S b) { return ((a > b) ? a : b); }
template<typename T, typename S> inline bool contains(const T &container1, const S &value1) { return container1.find(value1) != container1.end(); }
template<typename T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

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
    ulimit(i,1,T){
        solve();
    }

    return 0;
}
