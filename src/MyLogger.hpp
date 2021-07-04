#ifndef MYLOGGER_H
#define MYLOGGER_H

#include <iostream>
#include <iomanip>
#include <tuple>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>

// For list of C++ library, frameworks, ..., REFER: https://github.com/fffaraz/awesome-cpp
// Another good debugging library: https://github.com/sharkdp/dbg-macro

// For debugging multi-threaded programs
// REFER: https://github.com/fenilgmehta/CS744-PA4-Key-Value-Store/blob/master/src/MyDebugger.hpp

#define MY_LOGGING_ON
// TODO: comment the above line when:
//       1. doing performance testing
//       2. using IDE CMakeLists.txt
//       3. using `g++ name.cpp -DMY_LOGGING_ON`


#define printFunction(outStream, functionName, argDelimiter, lineDelimiter) template<typename Arg, typename... Args> inline void functionName(Arg&& arg, Args&&... args) { outStream << arg; (void)(int[]){0, (void(outStream << argDelimiter << args),0)...}; outStream << lineDelimiter; }
#ifdef MY_LOGGING_ON
    printFunction(std::cerr, printErr, " "<<"\033[1;34m"<<"●"<<"\033[0m"<<" ", '\n');
    template<class T, class... U> void dbg(int32_t lineNo, const char *sdbg, T h, U... a) {std::cerr<<"\033[1;"<<std::to_string(35+lineNo%2)<<"m"<<lineNo<<":\033[1;31m"<<"Debug: "<<"\033[0m"; std::cerr<<std::setw(15)<<sdbg; std::cerr<<" "<<"\033[1;31m"<<"="<<"\033[0m"<<" "; printErr(h, a...); std::cout.flush(); std::cerr.flush();}
    template <class S, class T> std::ostream& operator <<(std::ostream& os, const std::pair<S, T>& p) {return os << "pair(" << p.first << "\033[1;31m" << ", " << "\033[0m" << p.second << ")";}
    template <class T, size_t N> std::ostream& operator <<(std::ostream& os, const std::array<T,N>& p) {os << "\033[1;32m" << "array[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    template <class T> std::ostream& operator <<(std::ostream& os, const std::vector<T>& p) {os << "\033[1;32m" << "vector[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    template <class T> std::ostream& operator <<(std::ostream& os, const std::set<T>& p) {os << "\033[1;32m" << "set[ "; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    template <class S, class T> std::ostream& operator <<(std::ostream& os, const std::map<S, T>& p) {os << "\033[1;32m" << "map[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    template <class S, class T> std::ostream& operator <<(std::ostream& os, const std::unordered_map<S, T>& p) {os << "\033[1;32m" << "unordered_map[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    template <class T> void dbgIter(int32_t lineNo, const char *sdbg, T a, T b) {std::cerr<<"\033[1;"<<std::to_string(35+lineNo%2)<<"m"<<lineNo<<":\033[1;31m"<<"Debug: "<<"\033[0m"; std::cerr<<std::setw(15)<<sdbg; std::cerr<<"\033[1;31m"<<" = "<<"\033[0m"; std::cerr << "["; for (T i = a; i != b; ++i) {if (i != a) std::cerr << ", "; std::cerr << *i;} std::cerr << "]\n"; std::cout.flush(); std::cerr.flush();}
    #define db1(a)                          if(#a[0]!='0'){dbg(__LINE__, #a, a);}
    #define db11(a,b,c,d,e,f,g,h,i,j,k,...) {db1(a);db1(b);db1(c);db1(d);db1(e);db1(f);db1(g);db1(h);db1(i);db1(j);db1(k);}
    #define db(...)                         db11(__VA_ARGS__,0,0,0,0,0,0,0,0,0,0,0)
    #define dbl(...)                        dbg(__LINE__, #__VA_ARGS__, __VA_ARGS__)
    #define dbiter(...) dbgIter(__LINE__, #__VA_ARGS__, __VA_ARGS__);
#else
    // template<class T, class... U> void dbg(int32_t lineNo, const char *sdbg, T h, U... a) {}
    // template <class T> void dbgIter(int32_t lineNo, const char *sdbg, T a, T b) {}
    #define db(...) ;
    #define dbl(...);
    #define dbiter(...) ;
#endif  // end MY_LOGGING_ON

namespace fm {
    printFunction(std::cout, print, "", "");
    printFunction(std::cout, println, ' ', '\n');
    printFunction(std::cout, printsp, ' ', ' ');

    // NOTE: the termination condition of the below loops is fixed
    //       during initialization of the loop variables. Hence,
    //       it will not be possible to update the termination
    //       condition inside the loop. For such cases, use normal
    //       "for", "while", "do...while" loops

    // NOTE: for loops
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

    /* Do NOT use this for interactive programs */
    inline void fastio() {
        // REFER: https://codeforces.com/blog/entry/90775
        // std::cout is already tied to nullptr
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    inline void initfloat() {
        std::cout.precision(20); std::cout << std::fixed;
    }

    inline void initcp() {
        fastio();
        initfloat();
    }

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

    template<typename T, typename U> std::vector<T> MatrixVector(int n, U v){ return std::vector<T>(n, v);}
    template<typename T, class... Args> auto MatrixVector(int n, Args... args){auto val = MatrixVector<T>(args...); return std::vector<decltype(val)>(n, move(val));}
    // auto matrixM = MatrixVector<int32_t>(9,8,7,6,-1)  // dimention = 9*8*7*6, default value=-1

    template<typename T1, typename T2> struct pair : std::pair<T1, T2> { using std::pair<T1,T2>::pair; T1& aa = this->first; T2& bb = this->second; };

    template<typename T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
    template<typename T> using max_heap = std::priority_queue<T>;
    template<typename T, typename S> inline bool contains(const T &container1, const S &value1) { return container1.find(value1) != container1.end(); }
    template<typename T, typename S> inline auto min(const T a, const S b) { return ((a < b) ? a : b); }
    template<typename T, typename S> inline auto max(const T a, const S b) { return ((a > b) ? a : b); }
};

#undef printFunction

// REFER: https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
enum Code {
    FG_RED      = 31,
    FG_GREEN    = 32,
    FG_YELLOW   = 33,
    FG_BLUE     = 34,
    FG_DEFAULT  = 39,

    BG_RED      = 41,
    BG_GREEN    = 42,
    BG_YELLOW   = 43,
    BG_BLUE     = 44,
    BG_DEFAULT  = 49
};

#define color(enum_code) "\033[" << enum_code << "m"


#ifdef MY_LOGGING_ON

// REFER: https://stackoverflow.com/questions/7432100/how-to-get-integer-thread-id-in-c11
// (std::this_thread::get_id())

    /* Blue message */
    template <typename T>
    void log_info(const T& msg, bool prependNewLine = false, bool appendExtraNewLine = false) {
        if(prependNewLine) std::cout << '\n';
        std::cout << color(FG_BLUE) << "INFO : " << color(FG_DEFAULT) << msg << '\n';
        if(appendExtraNewLine) std::cout << '\n';
        std::cout.flush();
    }

    /* Yellow message */
    template <typename T>
    void log_warning(const T& msg, bool prependNewLine = false, bool appendExtraNewLine = false) {
        if(prependNewLine) std::cerr << '\n';
        std::cerr << color(FG_YELLOW) << "WARNING : " << color(FG_DEFAULT) << msg << '\n';
        if(appendExtraNewLine) std::cerr << '\n';
        std::cerr.flush();
    }

#else

    template<typename T>
    void log_info(const T& msg, bool prependNewLine = false, bool appendExtraNewLine = false) {}

    template <typename T>
    void log_warning(const T& msg, bool prependNewLine = false, bool appendExtraNewLine = false) {}

#endif

/* Green message */
template <typename T>
void log_success(const T& msg, bool prependNewLine = false, bool appendExtraNewLine = false) {
    if(prependNewLine) std::cout << '\n';
    std::cout << color(FG_GREEN) << "SUCCESS : " << color(FG_DEFAULT) << msg << '\n';
    if(appendExtraNewLine) std::cout << '\n';
    std::cout.flush();
}

/* Red message */
template <typename T>
void log_error(const T& msg, bool prependNewLine = false, bool appendExtraNewLine = false){
    if(prependNewLine) std::cerr << '\n';
    std::cerr << color(FG_RED) << "ERROR : " << color(FG_DEFAULT) << msg << std::endl;
    if(appendExtraNewLine) std::cerr << '\n';
    std::cerr.flush();
}

/* Yellow message */
template <typename T>
void log_error_warning(const T& msg, bool prependNewLine = false, bool appendExtraNewLine = false) {
    if(prependNewLine) std::cerr << '\n';
    std::cerr << color(FG_YELLOW) << "WARNING : " << color(FG_DEFAULT) << msg << '\n';
    if(appendExtraNewLine) std::cerr << '\n';
    std::cerr.flush();
}

#undef color

#endif // MYLOGGER_H
