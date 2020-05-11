#include <iostream>
#include <cstdint>
#include <queue>
using namespace std;

#define int int32_t

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
            // cout << ptr->ch << " . -> " << (&ptr) << endl;
            // if(ptr->left != nullptr) cout << ptr->ch << " l -> " << (&(ptr->left)) << endl;
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

    void bfs(){
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
};

//####################################################################################################################

/* 

https://www.youtube.com/watch?v=NinWEPPrkDQ&t=483s      (Strings: suffix tree, suffix array, linear-time construction for large alphabets, suffix tray, document retrieval)
https://discuss.codechef.com/t/suffix-trees/2045        (Is there a tutorial for implementation and applications of suffix tree data-structure ?)
https://discuss.codechef.com/t/suffix-array-and-suffix-tree/11081       (Can anyone tell me the simplest implementation of Sufix Tree and Suffix Array(nlogn^2).?)
https://discuss.codechef.com/t/help-with-ukkonens-algorithm/47635       (Ukken’s algorithm for Suffix Tree construction)

Suffix Trie:
    https://www.youtube.com/watch?v=qh2leThTv0Y         (Basic Idea - logical implementation)
    https://www.codechef.com/problems/EST               (Practice Question)
    https://discuss.codechef.com/t/est-editorial/394    (Editorial of the above Question) 

Suffix Tree:
    https://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english?rq=1    (Explanation)
    https://cp-algorithms.com/string/suffix-tree-ukkonen.html           (Explanation and Implementation)
    https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/suffixtrees.pdf    (PPT)
    https://en.wikipedia.org/wiki/Suffix_tree                           (Explanation)

Suffix Array:
    https://web.stanford.edu/class/cs97si/suffix-array.pdf      (Best implementation/application tutorials for suffix array across Internet)
    https://cp-algorithms.com/string/suffix-array.html          (Explanation and Implementation)

Suffix Automaton
    https://cp-algorithms.com/string/suffix-automaton.html      (Explanation and Implementation)

Others:
    https://gist.github.com/makagonov/f7ed8ce729da72621b321f0ab547debb  (Implementation - not checked)
    https://ideone.com/4GxpU2                                           (Implementation - not checked)

*/

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
    t.bfs();
    cout << endl;
    
    return 0;
}
