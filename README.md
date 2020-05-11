# Misc-Programming
This repository contains all sorts of programs.


## Good references
- [https://github.com/indy256/codelibrary/](https://github.com/indy256/codelibrary/)
- [How to start Competitive Programming?](https://youtu.be/xAeiXy8-9Y8)
- [How To Become Red Coder? (codeforces.com)](https://youtu.be/y7169jEvb-Y)
- [Don't Make These Mistakes (1st and 2nd Year)](https://youtu.be/-_gRnYmWkCE)
- [How do competitive programmers become so good at problem solving skills ? What is their approach in solving a high level programming question ?](https://www.quora.com/How-do-competitive-programmers-become-so-good-at-problem-solving-skills-what-is-their-approach-in-solving-a-high-level-programming-question)
- [How smart are red coders ?](https://www.quora.com/How-smart-are-the-red-coders-on-TopCoder)
- [How should one win the ACM ICPC? What efforts should I put forth starting from my 1st year of engineering (IT) ?](https://www.quora.com/How-should-one-win-the-ACM-ICPC-What-efforts-should-I-put-forth-starting-from-my-1st-year-of-engineering-IT/answer/Ana-Echavarria)


## Tree
1. [Tree1.cpp](Tree1.cpp)


## Graph
1. [Graph1.cpp](Graph1.cpp)
2. [https://cp\-algorithms.com/graph/01\_bfs.html](https://cp-algorithms.com/graph/01_bfs.html)


## Useful Data Structures and Programs
1. [Competitive Programming Template (Big).cpp](Competitive%20Programming%20Template%20(Big).cpp)
2. [Competitive Programming Template (Small).cpp](Competitive%20Programming%20Template%20(Small).cpp)
3. [uBigInt.cpp](uBigInt.cpp) - infinite size unsigned integers
4. [Matrix2d.cpp](Matrix2d.cpp) - 2 dimetional array
5. [Disjoint Set Union (Union Find).cpp](Disjoint%20Set%20Union%20(Union%20Find).cpp)
6. [String Data Structures.cpp](String%20Data%20Structures.cpp)


## Links to read
1. [Blowing up unordered_map](https://codeforces.com/blog/entry/62393)
   ```cpp
   struct custom_hash {
       inline static uint64_t splitmix64(uint64_t x) {
           // http://xorshift.di.unimi.it/splitmix64.c
           x += 0x9e3779b97f4a7c15;
           x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
           x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
           return x ^ (x >> 31);
       }   
       inline size_t operator()(uint64_t x) const {
           static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
           return splitmix64(x + FIXED_RANDOM);
       }
   };
   unordered_map<long long, int, custom_hash> safe_map;
   gp_hash_table<long long, int, custom_hash> safe_hash_table;
   ```
2. [C++ STL: Order of magnitude faster hash tables with Policy Based Data Structures](https://codeforces.com/blog/entry/60737?#comment-446357)
   ```cpp
   #include <ext/pb_ds/assoc_container.hpp>
   #include <ext/pb_ds/tree_policy.hpp>
   using namespace __gnu_pbds;
   typedef cc_hash_table<ll, ll, hash<ll>> ht;
   ```
3. [C++ STL: Policy based data structures](https://codeforces.com/blog/entry/11080)
4. [Primes](https://github.com/going-digital/Prime64)
