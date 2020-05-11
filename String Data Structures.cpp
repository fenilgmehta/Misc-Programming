#include <iostream>
#include <cstdint>
#include <queue>
using namespace std;

#define int int32_t

//####################################################################################################################

struct Trie{
    struct TernaryTree{
        char ch;
        bool is_end_of_word;
        TernaryTree *left, *right, *down;
        TernaryTree(const char t_ch, const bool t_is_word): ch{t_ch}, is_end_of_word{t_is_word}, \
            left{nullptr}, right{nullptr}, down{nullptr} {}
    };

    TernaryTree root;
    size_t words;

    Trie(): root('\0', false), words{0} {}

    ~Trie(){
        clear_memeory(root.down);
    }

    void clear_memeory(const TernaryTree *ptr){
        if(ptr == nullptr) return;
        clear_memeory(ptr->left);
        clear_memeory(ptr->down);
        clear_memeory(ptr->right);
        delete ptr;
    }

    /* Returns: true if `str` is present in the Trie, else false */
    bool find(const char *str){
        TernaryTree *ptr = &root;
        for(; *str != '\0'; ++str){
            if(ptr->down == nullptr) return false;

            ptr = ptr->down;
            while((*str) != ptr->ch){
                if((*str) < ptr->ch){
                    if(ptr->left == nullptr) return false;
                    ptr = ptr->left;
                } else {
                    if(ptr->right == nullptr) return false;
                    ptr = ptr->right;
                }
            }
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

            ptr = ptr->down;
            while((*str) != ptr->ch){
                if((*str) < ptr->ch){
                    if(ptr->left == nullptr) ptr->left = new TernaryTree(*str, false);
                    ptr = ptr->left;
                } else {
                    if(ptr->right == nullptr) ptr->right = new TernaryTree(*str, false);
                    ptr = ptr->right;
                }
            }
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


// Used for Codeforces question: https://codeforces.com/problemset/problem/4/C
// This implementation shows how many times a string is requested for insertion
struct TrieSimple{
    struct TernaryTree{
        TernaryTree *left, *down, *right;
        int count;
        char ch;
        TernaryTree(const char &t_ch, const int &t_count): ch{t_ch}, count{t_count}, \
            left{nullptr}, down{nullptr}, right{nullptr} {}
    };
    TernaryTree root;
    int words;

    TrieSimple(): root{'\0',-1}, words{0} {};

    ~TrieSimple(){
        clear_memeory(root.down);
    }

    void clear_memeory(const TernaryTree *ptr){
        if(ptr == nullptr) return;
        clear_memeory(ptr->left);
        clear_memeory(ptr->down);
        clear_memeory(ptr->right);
        delete ptr;
    }
    
    int& insert(const char *str){
        TernaryTree *ptr = &root;
        for(; (*str) != '\0'; ++str){
            if(ptr->down == nullptr){
                ptr->down = new TernaryTree(*str, 0);
                ptr = ptr->down;
                continue;
            }

            ptr = ptr->down;
            while(ptr->ch != (*str)){
                if(ptr->ch < (*str)){
                    if(ptr->left == nullptr) ptr->left = new TernaryTree(*str, 0);
                    ptr = ptr->left;
                } else {  // (*str) < ptr->ch
                    if(ptr->right == nullptr) ptr->right = new TernaryTree(*str, 0);
                    ptr = ptr->right;
                }
            }
        }

        ++ptr->count;
        return ptr->count;
    }
};

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