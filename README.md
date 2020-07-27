# Misc-Programming
This repository contains various types of programs. Almost all program can compile with C++14. The following files require C++17: "Graph1.cpp", "Range Iteration.cpp"

<!-- 

•

🅰🅱🅲🅳🅴🅵🅶🅷🅸🅹🅺🅻🅼🅽🅾🅿🆀🆁🆂🆃🆄🆅🆆🆇🆈🆉

𝟬𝟭𝟮𝟯𝟰𝟱𝟲𝟳𝟴𝟵
𝗮𝗯𝗰𝗱𝗲𝗳𝗴𝗵𝗶𝗷𝗸𝗹𝗺𝗻𝗼𝗽𝗾𝗿𝘀𝘁𝘂𝘃𝘄𝘅𝘆𝘇
𝗔𝗕𝗖𝗗𝗘𝗙𝗚𝗛𝗜𝗝𝗞𝗟𝗠𝗡𝗢𝗣𝗤𝗥𝗦𝗧𝗨𝗩𝗪𝗫𝗬𝗭
    𝗜𝗠𝗣𝗢𝗥𝗧𝗔𝗡𝗧
    𝗥𝗘𝗙𝗘𝗥
    𝗡𝗢𝗧𝗘
    𝟬/𝟭-𝗶𝗻𝗱𝗲𝘅𝗲𝗱
    𝗪𝗔𝗥𝗡𝗜𝗡𝗚
    𝘁𝗼𝗼

𝙖𝙗𝙘𝙙𝙚𝙛𝙜𝙝𝙞𝙟𝙠𝙡𝙢𝙣𝙤𝙥𝙦𝙧𝙨𝙩𝙪𝙫𝙬𝙭𝙮𝙯
𝘼𝘽𝘾𝘿𝙀𝙁𝙂𝙃𝙄𝙅𝙆𝙇𝙈𝙉𝙊𝙋𝙌𝙍𝙎𝙏𝙐𝙑𝙒𝙓𝙔𝙕


-->


## Contents
- [Misc-Programming](#misc-programming)
  - [Contents](#contents)
  - [How to start](#how-to-start)
  - [Tips](#tips)
  - [Useful Data Structures and Programs](#useful-data-structures-and-programs)
  - [Good code references](#good-code-references)
  - [C++ tips](#c-tips)


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


## Useful Data Structures and Programs
1. [Competitive Programming Template (Big).cpp](./src/Competitive%20Programming%20Template%20(Big).cpp)
2. [Competitive Prog-ramming Template (Small).cpp](./src/Competitive%20Programming%20Template%20(Small).cpp)
3. [Tree1.cpp](./src/Tree1.cpp)
    * [x] Depth First Search (DFS)
    * Read [Types of trees in data structures](https://www.quora.com/What-are-the-types-of-trees-in-data-structures)
4. [Graph1.cpp](./src/Graph1.cpp)
    * [x] Directed/Un-directed Unweighted Graph
        - [x] Depth First Search (DFS)
        - [x] Breadth First Search (BFS)
        - [x] bipartite_graph_split
        - [x] detect_cycle
        - [x] find_cycle
    * [x] Directed/Un-directed Weighted Graph
        - [x] minimum_spanning_tree_kruskals
        - [x] dijkstras (i.e. Dijkstra's shortest path)
        - [x] bellman_ford
        - [x] floyds_warshalls
        - [x] bfs_0_1
    * [x] GraphAdjMatrix - to store matrix of points
5. [Segment Trees.cpp](./src/Segment%20Trees.cpp)
    * [x] SegmentTree - optimized to space complexity of O(2*N)
        - Methods: size, resize, reset, operator[], build, setval, update, query, query_idx (for prefix sum)
    * [x] SegmentTreeSimple - use complete binary tree and iterative algorithms
        - Methods: size, resize, reset, operator[], build, setval, update, query
    * [x] SegmentTreeSimpleLazy - use complete binary tree and recursive algorithms
        - Methods: size, resize, reset, build, setval, query
6. [Binary Index Tree (Fenwick Tree).cpp](./src/Binary%20Index%20Tree%20(Fenwick%20Tree).cpp)
    * [x] update
    * [x] query
    * [x] size
    * [x] resize
    * [x] reset
    * [x] operator[]
    * [x] find (returns the index with given cumulative frequency in O(log(n)) time, return -1 if not found)
7. [uBigInt.cpp](./src/uBigInt.cpp) - infinite size unsigned integers
    * [x] Additions operators +, +=
    * [x] Subtraction operators -, -=
    * [x] Multiplication operators *, *=
    * [x] Modulous operators %, %=
    * [x] Binary shift operators <<=, >>=
    * [x] Comparision operators ==, !=, <, <=, >, >=
    * [x] to_dec()
    * [x] to_hex()
    * [x] to_uint64_t
    * [x] factorial
8. [Matrix2d.cpp](./src/Matrix2d.cpp) - 2 dimetional array
9.  [Disjoint Set Union (Union Find).cpp](./src/Disjoint%20Set%20Union%20(Union%20Find).cpp)
    * [x] find_set
    * [x] union_sets
    * [x] in_same_set
10. [String Data Structures.cpp](./src/String%20Data%20Structures.cpp)
    * [x] Trie (Ternary Search Tree - space optimized Trie)
    * [x] Palindrome check
    * [x] Longest Palindrome using Manacher's Algorithm
    * [x] longest_match - finds the maximum number of characters that match between two strings
    * [x] min_edit_distance - the edit distance between two strings is the minimum number of operations required to transform one string into the other.
    * [ ] Suffix Tree
    * [ ] Suffix Array
11. [Prime Numbers.cpp](./src/Prime%20Numbers.cpp)
    * [x] SieveOfEratosthenes
    * [x] SmallestPrimeFactor
    * [x] is_prime - using Fermat's Theorem
    * [x] is_prime_dp - using Dynamic Programming
    * [x] is_prime_simple - using school method
    * Read [Primes](https://github.com/going-digital/Prime64)
12. [Policy Data Structures and Hashing.cpp](./src/Policy%20Data%20Structures%20and%20Hashing.cpp)
    * Read [C++ STL: Order of magnitude faster hash tables with Policy Based Data Structures](https://codeforces.com/blog/entry/60737?#comment-446357)
    * Read [C++ STL: Policy based data structures](https://codeforces.com/blog/entry/11080)
        - `Tag` — class denoting a tree structure, which we will use. There are three base-classes provided in STL for this, it is `rb_tree_tag` (red-black tree), `splay_tree_tag` (splay tree) and `ov_tree_tag` (ordered-vector tree). Sadly, at competitions we can use only red-black trees for this because splay tree and OV-tree using linear-timed split operation that prevents us to use them.
    * Read [Blowing up unordered_map](https://codeforces.com/blog/entry/62393)


## Good code references
- Note that I have not seen all their codes. I think that they are good in general after taking an abstract level look at them
- [https://github.com/trekhleb/javascript-algorithms](https://github.com/trekhleb/javascript-algorithms) - this repository give implementation, simple explanation and sources to refer for a particular topic
- [https://github.com/indy256/codelibrary/](https://github.com/indy256/codelibrary/)
- [http://e-maxx.ru/algo/](http://e-maxx.ru/algo/)


## C++ tips
- IMPORTANT: read the Question carefully
- IMPORTANT: see INPUT limits carefully
- IMPORTANT: if unable to get a solution, then take a small break and think in different direction.
- Should be cautious about
    * `int` overflow
    * `array` bounds
    * special test-cases
-
    ```cpp
    int dp[10000]; /* will give better speed as compared to */
    std::vector<int> dp(100000); /* however prefer using std::vector */
    ```
- Use iterators to traverse a data structure
- Using ```#define MOD 1000000007``` will give better performance as compared to ```const int MOD = 1000000007;```
- ```if(a != 0) result++;``` can be written as ```result += !!a;```
- Use ```#include<bits/stdc++.h>``` for competitions but it will drastically increase the compilation time
- The following snippet affects the input/output speed
    ```cpp
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(20); cout << fixed;
    ```
- While testing the program for large input on local machine, always use 
    ```sh
    g++ -O2 fileName.cpp    # the -O2 will optimize the output file
    ```


<!-- ## Links to read -->

