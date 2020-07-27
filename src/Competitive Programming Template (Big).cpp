#include <bits/stdc++.h> // This is all in one include library
using namespace std;

//------------------------------------------------------------------------------------------------------------------

// INPUT/OUTPUT functions
template <typename Arg, typename... Args> inline void input(Arg& arg, Args&... args) { cin >> arg; (void)(int[]){0, (void(cin >> args),0)...}; }

#define printFunction(outStream, functionName, argDelimiter, lineDelimiter) template <typename Arg, typename... Args> inline void functionName(Arg&& arg, Args&&... args) { outStream << arg; (void)(int[]){0, (void(outStream << argDelimiter << args),0)...}; outStream << lineDelimiter; }
printFunction(cout, println, ' ', '\n');
printFunction(cout, printsp, ' ', ' ');

// DEBUG macros, to set the flag from commnad line, comment the below line and use `g++ name.cpp -DPRINT_DEBUG`
#define PRINT_DEBUG
#ifdef PRINT_DEBUG
    printFunction(cerr, printErr, " "<<"\033[1;31m"<<"●"<<"\033[0m"<<" ", '\n');
    #define db(...) dbg(#__VA_ARGS__, __VA_ARGS__);
    template<class T, class... U> void dbg(const char *sdbg, T h, U... a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<" "<<"\033[1;41m"<<"="<<"\033[0m"<<" "; printErr(h, a...); cout.flush(); cerr.flush();}
    template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "pair(" << p.first << "\033[1;31m" << ", " << "\033[0m" << p.second << ")";}
    template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "\033[1;32m" << "vector[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "\033[1;32m" << "set[ "; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "\033[1;32m" << "map[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    #define dbiter(...) dbgIter(#__VA_ARGS__, __VA_ARGS__);
    template <class T> void dbgIter(const char *sdbg, T a, T b) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n"; cout.flush(); cerr.flush();}
#else
    #define db(...) ;
    #define dbiter(...) ;
#endif

// NOTE: for loops
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

// NOTE: ITERATORS
#define ITuiter3(arr, it_f, it_l)   next(begin(arr),it_f),next(begin(arr),it_l)
#define ITuiter2(arr, it_l)         ITuiter3(arr,0,it_l)
#define ITuiter1(arr)               begin(arr),end(arr)
#define ITditer3(arr, it_f, it_l)   make_reverse_iterator(next(begin(arr),it_l)),make_reverse_iterator(next(begin(arr),it_f))
#define ITditer2(arr, it_l)         ITditer3(arr,0,it_l)
#define ITditer1(arr)               rbegin(arr),rend(arr)
#define uiter(...)                  GET_MACRO(__VA_ARGS__, 0, ITuiter3, ITuiter2, ITuiter1)(__VA_ARGS__)
#define diter(...)                  GET_MACRO(__VA_ARGS__, 0, ITditer3, ITditer2, ITditer1)(__VA_ARGS__)
#define FORiter(_it, _f, _l)    for(auto _it=(_f), _it##end=(_l); _it != _it##end; advance(_it,1))
#define foriter(_it, ...)       FORiter(_it, __VA_ARGS__)

#define gett(_tup, _n)      get<_n>(_tup)
#define short               int16_t
#define int                 int32_t
#define long                int64_t     // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: REMOVE this when using `long double`
#define int128              __int128    // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: Only works with few compilers
#define newl                '\n'        // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: do NOT use this when working on/with interactive programs

// DATA STRUCTURES
template<typename T> using min_heap = priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_heap = priority_queue<T>;
template<typename T, typename U> std::vector<T> MatrixVector(int n, U v){ return std::vector<T>(n, v);}
template<typename T, class... Args> auto MatrixVector(int n, Args... args){auto val = MatrixVector<T>(args...); return std::vector<decltype(val)>(n, move(val));}
// auto matrixM = MatrixVector<int32_t>(9,8,7,6,5)  // dimention = 9*8*7*6, default value=5
template<typename T1, typename T2> struct pair_alias : pair<T1, T2> { using pair<T1,T2>::pair; T1& aa = this->first; T2& bb = this->second; };
#define pair pair_alias

#define gett(_tup, _n) get<_n>(_tup)
template<typename T, typename S> inline bool contains(const T &container1, const S &value1) { return container1.find(value1) != container1.end(); }
template<typename T, typename S> inline auto min(const T a, const S b) { return ((a < b) ? a : b); }
template<typename T, typename S> inline auto max(const T a, const S b) { return ((a > b) ? a : b); }

/* WARNING: this only works when input is from getint(...) ONLY, NOT when intermixed with `cin` */
template<typename T>
inline T getint() {
    T val = 0;
    char c;
    bool neg = false;
    while ((c = getchar_unlocked()) && !('0' <= c && c <= '9'))
        neg |= c == '-';
    for(; '0' <= c && c <= '9'; c = getchar_unlocked())
        val = (val * 10) + c - '0';
    return val * (neg ? -1 : 1);
}

template<typename T> inline void getint(T& m) {m=getint<T>();}

template <typename Arg, typename... Args>
inline void getint(Arg& arg, Args&... args) { arg=getint<Arg>(); (void)(int[]){0, (void(getint(args)),0)...}; }
// template <typename T, typename... S> inline void getint(T& m, S&... s) {m=getint<T>(); getint(s...);}
// Advantage, on input of 10'000'000:
// cin         -> 2.01seconds and 83744k RAM
// getint(...) -> 0.72seconds and  6408k RAM

//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

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
