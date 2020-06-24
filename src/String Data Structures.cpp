#include <iostream>
#include <algorithm>
#include <cstdint>
#include <queue>
using namespace std;

#define int int32_t

// DEBUG macros, to set the flag from commnad line, comment the below line and use `g++ name.cpp -DPRINT_DEBUG`
#define PRINT_DEBUG
#ifdef PRINT_DEBUG
    #define printFunction(outStream, functionName, argDelimiter, lineDelimiter) template <typename Arg, typename... Args> inline void functionName(Arg&& arg, Args&&... args) { outStream << arg; (void)(int[]){0, (void(outStream << argDelimiter << args),0)...}; outStream << lineDelimiter; }
    printFunction(cerr, printErr, " "<<"\033[1;41m"<<","<<"\033[0m"<<" ", '\n');
    #define db(...) dbg(#__VA_ARGS__, __VA_ARGS__)
    template<class T, class... U> void dbg(const char *sdbg, T h, U... a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<" "<<"\033[1;41m"<<"="<<"\033[0m"<<" "; printErr(h, a...);}
    template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "\033[1;32m" << "vector[ " << "\033[0m"; for (const auto& it : p) os << it << "\033[1;31m" << ", " << "\033[0m"; return os << "\033[1;32m" << "]" << "\033[0m";}
    #define dbiter(...) dbgIter(#__VA_ARGS__, __VA_ARGS__)
    template <class T> void dbgIter(const char *sdbg, T a, T b) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}
#else
    #define db(...) ;
    #define dbiter(...) ;
#endif

//####################################################################################################################

/* 
Tries:
    https://www.geeksforgeeks.org/trie-insert-and-search/
    https://www.geeksforgeeks.org/advantages-trie-data-structure/
    https://www.geeksforgeeks.org/ternary-search-tree/

*/

// This is a Ternary Search Tree - special trie data structure where the
// child nodes of a standard trie are ordered as a binary search tree.
// A simpler implementation with slight modification: https://codeforces.com/contest/4/submission/79724848
struct Trie{
    struct TernaryTree{
        char ch;
        bool is_end_of_word;
        TernaryTree *left, *right, *down;
        TernaryTree(const char t_ch, const bool t_is_word): ch{t_ch}, is_end_of_word{t_is_word}, \
            left{nullptr}, right{nullptr}, down{nullptr} {}

        pair<bool, TernaryTree*> find(const char &ch, const bool &add_if_absent, const bool &return_added_node) {
            TernaryTree *ptr = this;
            int flag = 0;
            while(ch != this->ch){
                if(ch < this->ch){
                    if(ptr->left == nullptr) { flag=1; break; }
                    ptr = ptr->left;
                } else {
                    if(ptr->right == nullptr) { flag=2; break; }
                    ptr = ptr->right;
                }
            }
            if(flag != 0 && add_if_absent) {
                if(flag==1) ptr->left = new TernaryTree(ch, false);
                else ptr->right = new TernaryTree(ch, false);
                if(return_added_node==true)
                    ptr = (flag==1) ? (ptr->left) : (ptr->right);
            }
            return {flag==0, ptr};
        }

        // reference to pointer is passed to avoid memory overhead
        static void clear_memeory(TernaryTree *&ptr){
            if(ptr == nullptr) return;
            clear_memeory(ptr->left);
            clear_memeory(ptr->down);
            clear_memeory(ptr->right);
            delete ptr;
        }
    };

    TernaryTree root;
    size_t words;

    Trie(): root('\0', false), words{0} {}

    ~Trie(){
        TernaryTree::clear_memeory(root.down);
    }

    /* Returns: true if `str` is present in the Trie, else false */
    bool find(const char *str){
        TernaryTree *ptr = &root;
        for(; *str != '\0'; ++str){
            if(ptr->down == nullptr) return false;

            pair<bool, Trie::TernaryTree*> res = ptr->down->find(*str, false, false);
            if(res.first == false) return false;
            ptr = res.second;
        }
        return ptr->is_end_of_word;
    }

    /* Returns: true if `str` is inserted, else false as `str` already present in the Trie */
    bool insert(const char *str){
        TernaryTree *ptr = &root;
        for(; *str != '\0'; ++str){
            if(ptr->down == nullptr){
                ptr->down = new TernaryTree(*str, false);
                ptr = ptr->down;
                continue;
            }

            pair<bool, Trie::TernaryTree*> res = ptr->down->find(*str, true, true);
            ptr = res.second;
        }
        if(ptr->is_end_of_word) return false; // str is already present in the Trie. Hence not inserted
        ++words;
        ptr->is_end_of_word = true;
        return true;
    }

    void in_order(TernaryTree* ptr, queue<TernaryTree*> &q){
        if(ptr == nullptr) return;
        in_order(ptr->left, q);
        q.push(ptr);
        in_order(ptr->right, q);
    }

    void print_bfs(){
        cout << "BFS:\n";
        if(root.down == nullptr) {
            cout << "    Trie is empty\n";
            return;
        }

        queue<TernaryTree*> q;
        TernaryTree *ptr;

        q.push(root.down);
        q.push(nullptr);
        while(q.front() != nullptr){
            while(q.front() != nullptr){
                ptr = q.front(); q.pop();
                in_order(ptr, q);
            }
            q.pop();
            q.push(nullptr);

            cout << "    ";
            while(q.front() != nullptr){
                ptr = q.front(); q.pop();
                cout << ptr->ch << " ";
                if(ptr->down != nullptr) q.push(ptr->down);
            }
            q.pop();
            q.push(nullptr);
            cout << endl;
        }
    }

    void print_strings(TernaryTree *&r, string &s){
        if(r == nullptr) return;
        print_strings(r->left, s);

        s.push_back(r->ch);
        if(r->is_end_of_word) cout << "    " << s << endl;
        print_strings(r->down, s);
        s.pop_back();
        
        print_strings(r->right, s);
    }

    void print_strings(){
        cout << "String present in Trie (in sorted order):\n";
        string s;
        print_strings(this->root.down, s);
    }
};

//####################################################################################################################

/* 

https://www.youtube.com/watch?v=NinWEPPrkDQ&t=483s      (BEST intorduction to Strings: suffix tree, suffix array, linear-time construction for large alphabets, suffix tray, document retrieval)
https://discuss.codechef.com/t/suffix-trees/2045        (Is there a tutorial for implementation and applications of suffix tree data-structure ?)
https://discuss.codechef.com/t/suffix-array-and-suffix-tree/11081       (Can anyone tell me the simplest implementation of Sufix Tree and Suffix Array(nlogn^2).?)
https://discuss.codechef.com/t/help-with-ukkonens-algorithm/47635       (Ukken’s algorithm for Suffix Tree construction)

Suffix Trie:
    https://www.youtube.com/watch?v=qh2leThTv0Y         (Basic Idea - logical implementation)
    https://www.codechef.com/problems/EST               (Practice Question)
    https://discuss.codechef.com/t/est-editorial/394    (Editorial of the above Question) 

Suffix Tree:
    https://www.geeksforgeeks.org/pattern-searching-using-suffix-tree/  (BEST)
    https://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english?rq=1    (Explanation)
    https://cp-algorithms.com/string/suffix-tree-ukkonen.html           (Explanation and Implementation)
    https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/suffixtrees.pdf    (PPT)
    https://en.wikipedia.org/wiki/Suffix_tree                           (Explanation)

Suffix Array:
    https://www.geeksforgeeks.org/suffix-array-set-1-introduction/      (BEST)
    https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
    https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/
    https://www.geeksforgeeks.org/suffix-tree-application-4-build-linear-time-suffix-array/?ref=rp
    https://web.stanford.edu/class/cs97si/suffix-array.pdf              (Best implementation/application tutorials for suffix array across Internet)
    https://cp-algorithms.com/string/suffix-array.html                  (Explanation and Implementation)

Suffix Automaton
    https://cp-algorithms.com/string/suffix-automaton.html              (Explanation and Implementation)

Others:
    https://gist.github.com/makagonov/f7ed8ce729da72621b321f0ab547debb  (Implementation - not checked)
    https://ideone.com/4GxpU2                                           (Implementation - not checked)

*/

//####################################################################################################################

/* 
Manacher's Algorithm
    https://www.youtube.com/watch?v=nbTSfrEfo6M     (BEST)
    https://medium.com/hackernoon/manachers-algorithm-explained-longest-palindromic-substring-22cb27a5e96f
    https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/
    https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-2/
    https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-3-2/
    https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-4/
*/

/* Input: "ababaaa"  --->  Output: [1, 2, 3, 2, 1, 2, 1] */
vector<int> manacher_odd(const string &s){
    // bool debug = (s=="bababaababbabaaababaaaaa") ? true : false;
    const int n = s.size();
    vector<int> d1(n);
    for(int i=0, c=0, r=0; i < n; ++i){
        // if(debug) db(i,c,r, d1[c-(i-c)], r-i+1);
        int &k = d1[i];
        k = (i < r) ? min(d1[c-(i-c)], r-i+1) : 1;  // use previous value
        while(0 <= (i-k) && (i+k) < n && s[i-k]==s[i+k]) ++k;  // trivial matching
        if(r < (i+k-1)) c=i, r=i+k-1;  // update center `c` and right `r`
    }
    return d1;
}

/*              5 */
/* Input: "ababa|aa"  --->  Output: [0, 0, 0, 0, 0, 1, 1] */
/*         01234 56 */
vector<int> manacher_even(const string &s){
    // bool debug = (s=="bababaababbabaaababaaaaa") ? true : false;
    const int n = s.size();
    vector<int> d2(n, 0);
    for(int i=1, c=0, r=0; i < n; ++i){
        // if(debug) db(i,c,r, d2[c-(i-c)], r-i+1);
        int &k = d2[i];
        k = (i <= r) ? min(d2[c-(i-c)],r-i+1) : 0;
        while(0 <= (i-k-1) && (i+k) < n && s[i-k-1]==s[i+k]) ++k;
        if(r < (i+k-1)) c=i, r=i+k-1;
    }
    return d2;
}

bool is_palindrome(const string &s){
    int n = s.size();
    for(int i = 1; 2*i <= n; ++i){
        if(s[i-1] != s[n-i]) return false;
    }
    return true;
}

/* Finds the maximum number of characters that match between the two string `a` and `b` */
int longest_match(const string &a, const string &b){
    // the index i,j of the `dp` denotes that a[:i] and b[:j] are used to calculate the longest match
    vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
    for(int i=1, iend = a.size(); i <= iend; ++i){      // rows
        for(int j=1, jend=b.size(); j <= jend; ++j){    // columns
            if(a[i-1]==b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
        }
    }
    // for(int i=0, iend=a.size(); i <= iend; ++i){
    //     for(int j=0; jend=b.size(); j <= jend; ++j)
    //         cout << dp[i][j] << " ";
    //     cout << endl;
    // }
    return dp[a.size()][b.size()];
}

/* 
The edit distance between two strings is the minimum number of operations required to transform one string into the other.
The allowed operations are:
    • Add one character to the string.
    • Remove one character from the string.
    • Replace one character in the string.
For example, the edit distance between LOVE and MOVIE is 2, because you can first replace L with M, and then add I.
*/
int min_edit_distance(string &a, string &b){
    vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
    for(int i = 1, iend = b.size() ; i <= iend; ++i) dp[0][i] = i;
    for(int i = 1, iend = a.size() ; i <= iend; ++i) dp[i][0] = i;

    for(int i = 1, iend = a.size() ; i <= iend; ++i){  // rows
        for(int j = 1, jend = b.size() ; j <= jend; ++i){  // columns
            if(a[i-1]==b[j-1]) 
                dp[i][j] = dp[i-1][j-1];
            else 
                dp[i][j] = 1 + min({
                                dp[i-1][j-1], // replace the last character of one string to other
                                dp[i-1][j],   // insert one character at the end of first string
                                dp[i][j-1]    // insert one character at the end of the second string
                               });
        }
    }
    return dp[a.size()][b.size()];
}

//####################################################################################################################

int main(){
    Trie t;
    cout << boolalpha << "t.insert(\"asdf\") = " << t.insert("asdf") << endl;
    cout << boolalpha << "t.find(\"asdf\") = " << t.find("asdf") << endl;
    cout << boolalpha << "t.find(\"asf\") = " << t.find("asf") << endl;
    cout << boolalpha << "t.find(\"asd\") = " << t.find("asd") << endl;
    cout << boolalpha << "t.insert(\"asap\") = " << t.insert("asap") << endl;
    cout << boolalpha << "t.insert(\"aszz\") = " << t.insert("aszz") << endl;

    cout << endl;
    t.print_strings();
    cout << endl;
    t.print_bfs();
    cout << endl;

    //--------------------------------

    cout << endl;
    cout << boolalpha << "is_palindrome(\"\") = " << is_palindrome("") << endl;
    cout << boolalpha << "is_palindrome(\"a\") = " << is_palindrome("a") << endl;
    cout << boolalpha << "is_palindrome(\"ab\") = " << is_palindrome("ab") << endl;
    cout << boolalpha << "is_palindrome(\"bb\") = " << is_palindrome("bb") << endl;
    cout << boolalpha << "is_palindrome(\"abc\") = " << is_palindrome("abc") << endl;
    cout << boolalpha << "is_palindrome(\"aba\") = " << is_palindrome("aba") << endl;
    cout << boolalpha << "is_palindrome(\"abaa\") = " << is_palindrome("abaa") << endl;
    cout << boolalpha << "is_palindrome(\"abba\") = " << is_palindrome("abba") << endl;
    cout << endl;

    //--------------------------------

    cout << endl << "Manacher's algorithm" << endl;
    string to_check[] = {"ababaaa", "aabaabababa", "baababababaab", "abababababababa", "bababaababbabaaababaaaaa", "aaaaaaaaaaaaa", "aaabbbaaabbbaaa", "bababaababababababbababab", "bababababbaabbabababa"};
    for(string i: to_check){
        auto v1 = manacher_odd(i);
        auto v2 = manacher_even(i);
        cout << "string i = " << i << endl;
        cout << "v1[:] = "; for(auto &j: v1) cout << j << ", "; cout << endl;
        cout << "v2[:] = "; for(auto &j: v2) cout << j << ", "; cout << endl;
        cout << endl;
    }

    return 0;
}
