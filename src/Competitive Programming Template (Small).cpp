#include <bits/stdc++.h> // This is all in one include library
using namespace std;
//------------------------------------------------
#ifndef ONLINE_JUDGE
template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "pair(" << p.first << "\033[1;31m" << ", " << "\033[0m" << p.second << ")";}
template <class T, size_t N>ostream& operator <<(ostream& os, const array<T,N>& p) {os << "\033[1;32m" << "array[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "\033[1;32m" << "vector[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "\033[1;32m" << "set[ "; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "\033[1;32m" << "map[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
template <class S, class T>ostream& operator <<(ostream& os, const unordered_map<S, T>& p) {os << "\033[1;32m" << "unordered_map[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
template <typename Arg, typename... Args> inline void printErr(Arg&& arg, Args&&... args) { cerr << arg; (void)(int[]){0, (void(cerr << " "<<"\033[5;31m"<<"●"<<"\033[0m"<<" " << args),0)...}; cerr << '\n'; }
template<class T, class... U> void dbg(const int line, const char *sdbg, T h, U... a) {cerr<<"\033[1;"<<to_string(35+line%2)<<"m"<<line<<":\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<" "<<"\033[1;31m"<<"="<<"\033[0m"<<" "; printErr(h, a...); cout.flush(); cerr.flush();}
template <class T> void dbgIter(const int line, const char *sdbg, T a, T b) {cerr<<"\033[1;"<<to_string(35+line%2)<<"m"<<line<<":\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n"; cout.flush(); cerr.flush();}
#define db1(a)                          if(#a[0]!='0'){dbg(__LINE__, #a, a);}
#define db11(a,b,c,d,e,f,g,h,i,j,k,...) {db1(a);db1(b);db1(c);db1(d);db1(e);db1(f);db1(g);db1(h);db1(i);db1(j);db1(k);}
#define db(...)                         db11(__VA_ARGS__,0,0,0,0,0,0,0,0,0,0,0)
#define dbiter(...)                     dbgIter(__LINE__, #__VA_ARGS__, __VA_ARGS__);
#else
#define db(...) ;
#define dbiter(...) ;
#endif
#define GET_MACRO(a,b,c,d,NAME,...)     NAME
#define FORurange4(_i, _f, _l, _d)      for(int32_t _i = (_f), _i##ztEnd = (_l) ; _i < _i##ztEnd; _i+=(_d))  // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: int32_t is used
#define FORurange3(_i, _f, _l)          FORurange4(_i, _f, _l, 1)
#define FORurange2(_i, _l)              FORurange4(_i, 0, _l, 1)
#define FORurange1(_l)                  FORurange4(__i_temp__, 0, _l, 1)
#define FORulimit4(_i, _f, _l, _d)      FORurange4(_i, _f, _l+1, _d)
#define FORulimit3(_i, _f, _l)          FORurange4(_i, _f, _l+1, 1)
#define urange(...)                     GET_MACRO(__VA_ARGS__, FORurange4, FORurange3, FORurange2, FORurange1)(__VA_ARGS__)
#define ulimit(...)                     GET_MACRO(__VA_ARGS__, FORulimit4, FORulimit3)(__VA_ARGS__)
#define dlimit(_i, _f, _l)              for(int32_t _i = (_f), _i##ztEnd = (_l) ; _i >= _i##ztEnd; --_i)     // 𝗪𝗔𝗥𝗡𝗜𝗡𝗚: int32_t is used
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
