#include <bits/stdc++.h> // This is all in one include library
using namespace std;

//####################################################################################################################



// BY: https://codeforces.com/profile/Chilli
// REFER: https://codeforces.com/blog/entry/60737?#comment-452245
// REFER: https://codeforces.com/contest/1006/submission/41804666
// One thing worth mentioning: return x ^ RANDOM is not enough for a safe hash function. gp_hash_table uses a
// modulo power of two policy, so giving it many values that are the same modulo a large power of two such as
// `pow(2,16)` is enough to make it extremely slow. x ^ RANDOM doesn't do anything to mitigate this, since two
// values that are equivalent modulo `pow(2,16)` are still equivalent after xor-ing with the same number.
template<typename KeyT>
struct custom_hash_fast {
    inline size_t hash_f(KeyT x) const {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        return static_cast<size_t>(x);
    }
    inline size_t operator()(const KeyT x) const { return hash_f(x); }
};



// REFER: https://codeforces.com/blog/entry/62393
// REFER: https://gist.github.com/Chillee/3bd6ee4429abb4a2e7c19959fb1490ae#file-hash-table-cpp
// BY: https://codeforces.com/profile/Chilli
// This is the most resilient hash function to collisions
template<typename KeyT>
struct custom_hash_MY {
    // UNUSED
    // static uint_least16_t hash_combine(uint_least16_t a, uint_least16_t b) { return a * 31 + b; }

    // Generate RANDOM using random data stored in RAM  👇
    const uint64_t RANDOM = reinterpret_cast<uint64_t>(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();

    inline static size_t splitmix64(uint64_t x) {
        // REFER: http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return static_cast<size_t>(x ^ (x >> 31));
    }

    inline size_t operator()(const KeyT x) const {
        return static_cast<uint64_t>(splitmix64(x)) ^ RANDOM;
        // return splitmix64(static_cast<uint64_t>(x) ^ FIXED_RANDOM);
        // return splitmix64(static_cast<uint64_t>(x) + FIXED_RANDOM);
    }

    template<typename KeyAA, typename KeyBB>
    inline size_t operator()(pair<KeyAA,KeyBB> x) const {
        // REFER: https://codeforces.com/blog/entry/62393?#comment-464775
        return splitmix64(x.first ^ (x.second >> 1)) ^ RANDOM;
		
        // REFER: https://codeforces.com/blog/entry/62393?#comment-466049
        // return splitmix64(x.first + RANDOM)^(splitmix64(x.second + RANDOM) >> 1);
	}
};



template<typename KeyType>
using safe_unordered_set=unordered_set<KeyType, custom_hash_MY<KeyType>>;

template<typename KeyType, typename MappedType>
using safe_unordered_map=unordered_map<KeyType, MappedType, custom_hash_MY<KeyType>>;

// safe_unordered_map<int,int> aaa;
// safe_unordered_map<pair<int,long>,int> bbb;
// safe_unordered_set<int> ccc;
// safe_unordered_set<pair<long, int>>  ddd;



//####################################################################################################################



// #include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/tree_policy.hpp>      // Including tree_order_statistics_node_update
using namespace __gnu_pbds;



// 𝗥𝗘𝗙𝗘𝗥: https://codeforces.com/blog/entry/60737
// 𝗜𝗠𝗣𝗢𝗥𝗧𝗔𝗡𝗧: gp_hash_table is the way to go, not cc_hash_table. gp_hash_table
// sacrifices ~10% reading/writing speed to gain 3-6x in insertion/deletion/clearing.
// 𝗡𝗢𝗧𝗘: gp_hash_table continues to perform great with pairs.

// Unordered_map uses collision chaining + prime buckets. gp_hash_table uses open addressing + power of 2 buckets.
// That makes it run into issues with the default "hash function" for integers, which is just the identity.
template<typename KeyType, typename MappedType, typename HashType>
using safe_gp_hash_table=gp_hash_table<KeyType, MappedType, HashType>;

template<typename KeyType, typename MappedType, typename HashType>
using safe_cc_hash_table=cc_hash_table<KeyType, MappedType, HashType>;




// Ordered Set is a policy based data structure in g++ that keeps the unique elements in sorted order.
// Functions: order_of_key(key), find_by_order(idx)
// REFER: https://www.geeksforgeeks.org/implementing-upper_bound-and-lower_bound-for-ordered-set-in-c/?ref=leftbar-rightbar
template<typename KeyType> using indexed_set=tree<KeyType, null_type, less<KeyType>, rb_tree_tag, tree_order_statistics_node_update>;

// A drawback of using less_equal instead of less is that lower_bound works as upper_bound  // REFER: https://stackoverflow.com/questions/44238144/order-statistics-tree-using-gnu-pbds-for-multiset
template<typename KeyType> using indexed_multiset=tree<KeyType, null_type, less_equal<KeyType>, rb_tree_tag, tree_order_statistics_node_update>;

/*
REFER: https://cses.fi/problemset/hack/1739/entry/425176/
Note :  There is a problem with erase() function in ordered_multiset (for less_equal<int> tag).
        lower_bound() works as upper_bound() and vice-versa.
        Be careful to use.
        i) find_by_order(k) : kth smallest element counting from 0 .
        ii) order_of_key(k) : number of elements strictly smaller than k.
*/



// TODO: check https://codeforces.com/blog/entry/10355



//####################################################################################################################


int main() {
    // auto ptr = make_unique<char>().get();
    // cout << (uint64_t)ptr << endl;
    // cout << reinterpret_cast<uint64_t>(make_unique<char>().get()) << endl;

    return 0;
}
