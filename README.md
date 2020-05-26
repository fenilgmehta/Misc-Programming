# Misc-Programming
This repository contains various types of programs.


## How to start
- [Learn Competitive Programming In Just One Month For Free | How To Start Competitive Programming](https://youtu.be/cepkYAI1JgM)
    * [https://cses.fi/](https://cses.fi/)
    * [https://cses.fi/problemset/](https://cses.fi/problemset/)
    * [Guide to Competitive Programming - Learning and Improving Algorithms Through Contests](https://link.springer.com/content/pdf/10.1007%2F978-3-319-72547-5.pdf)
    * [Competitive Programmer’s Handbook - Antti Laaksonen Draft August 19, 2019](https://github.com/pllk/cphb/blob/f269ae391910742788ac0d6626df1e221281f191/book.pdf)
- [How to start Competitive Programming?](https://youtu.be/xAeiXy8-9Y8)
- [How To Become Red Coder? (codeforces.com)](https://youtu.be/y7169jEvb-Y)
- [Don't Make These Mistakes (1st and 2nd Year)](https://youtu.be/-_gRnYmWkCE)
- [How do competitive programmers become so good at problem solving skills ? What is their approach in solving a high level programming question ?](https://www.quora.com/How-do-competitive-programmers-become-so-good-at-problem-solving-skills-what-is-their-approach-in-solving-a-high-level-programming-question)
- [How smart are red coders ?](https://www.quora.com/How-smart-are-the-red-coders-on-TopCoder)
- [How should one win the ACM ICPC? What efforts should I put forth starting from my 1st year of engineering (IT) ?](https://www.quora.com/How-should-one-win-the-ACM-ICPC-What-efforts-should-I-put-forth-starting-from-my-1st-year-of-engineering-IT/answer/Ana-Echavarria)


## Tips
- It is highly suggested to do Competitive Programming in group so that everyone is motivated to continue even after small failures.
- One should try to solve problems which are slightly above their capacity but not too hard so that he/she does not get demotivated. Secondly, beginers should try to think of solution for 15-30 minutes, and:
    * If one is able to solve the question, then too they should see the tutorial for the question to see other peoples approach and also view the solution of those people whose code got accepted and took the least amount of time and memory.
    * If one is not able to solve the question, then see the tutorial/solution as beginners have a lot to learn and the brain won't get an idea to implement a new data structure required to solve the problem. And, one should understand the concepts required for the question throughly so that he/she is able to solve similar questions in future.
- Lastly, continue practicing question because if one stops problem solving for just a month, even then the confidence goes down. So, regularly solve question and praticipate in competitions to be confident of your skills.


## Good code references
- [https://github.com/trekhleb/javascript-algorithms](https://github.com/trekhleb/javascript-algorithms) - this repository give implementation, simple explanation and sources to refer for a particular topic
- [https://github.com/indy256/codelibrary/](https://github.com/indy256/codelibrary/)


## Tree
1. [Tree1.cpp](Tree1.cpp)
    [ ] Depth First Search (DFS)
2. [Types of trees in data structures](https://www.quora.com/What-are-the-types-of-trees-in-data-structures)


## Graph
1. [Graph1.cpp](Graph1.cpp)
    * [ ] Depth First Search (DFS)
    * [ ] Dijkstra's shortest path
2. [https://cp\-algorithms.com/graph/01\_bfs.html](https://cp-algorithms.com/graph/01_bfs.html)


## Useful Data Structures and Programs
1. [Competitive Programming Template (Big).cpp](Competitive%20Programming%20Template%20(Big).cpp)
2. [Competitive Prog-ramming Template (Small).cpp](Competitive%20Programming%20Template%20(Small).cpp)
3. [uBigInt.cpp](uBigInt.cpp) - infinite size unsigned integers
4. [Matrix2d.cpp](Matrix2d.cpp) - 2 dimetional array
5. [Disjoint Set Union (Union Find).cpp](Disjoint%20Set%20Union%20(Union%20Find).cpp)
6. [String Data Structures.cpp](String%20Data%20Structures.cpp)
    * [ ] Trie (Ternary Search Tree - space optimized Trie)
    * [ ] Suffix Tree
    * [ ] Suffix Array


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
