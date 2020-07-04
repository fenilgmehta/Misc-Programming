#include <bits/stdc++.h> // This is all in one include library
using namespace std;

//####################################################################################################################



// BY: https://codeforces.com/profile/Chilli
// REFER: https://gist.github.com/Chillee/3bd6ee4429abb4a2e7c19959fb1490ae#file-hash-table-cpp
// This is more resilient to collision
template<typename KeyT>
struct chash {
    static uint_least16_t hash_combine(uint_least16_t a, uint_least16_t b) { return a * 31 + b; }

    const uint64_t RANDOM = static_cast<uint64_t>(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    inline static size_t hash_f(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return static_cast<size_t>(x ^ (x >> 31));
    }

    inline size_t operator()(const KeyT x) const { return static_cast<uint64_t>(hash_f(x))^RANDOM; }

    template<typename KeyAA, typename KeyBB>
    inline size_t operator()(pair<KeyAA,KeyBB> x) const {
        return splitmix64(x.first ^ (x.second >> 1)) ^ RANDOM;  // REFER: https://codeforces.com/blog/entry/62393?#comment-464775
		// return splitmix64(x.first + RANDOM)^(splitmix64(x.second + RANDOM) >> 1);  // REFER: https://codeforces.com/blog/entry/62393?#comment-466049
	}
};



// BY: https://codeforces.com/profile/Chilli
// REFER: https://codeforces.com/blog/entry/60737?#comment-452245
// REFER: https://codeforces.com/contest/1006/submission/41804666
// One thing worth mentioning: return x ^ RANDOM is not enough for a safe hash function. gp_hash_table uses a
// modulo power of two policy, so giving it many values that are the same modulo a large power of two such as
// `pow(2,16)` is enough to make it extremely slow. x ^ RANDOM doesn't do anything to mitigate this, since two
// values that are equivalent modulo `pow(2,16)` are still equivalent after xor-ing with the same number.
template<typename KeyT>
struct chash_fast {
    inline size_t hash_f(KeyT x) const {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        return static_cast<size_t>(x);
    }
    inline size_t operator()(const KeyT x) const { return hash_f(x); }
};



// REFER: https://codeforces.com/blog/entry/62393
template<typename KeyT>
struct custom_hash {
    inline static size_t splitmix64(uint64_t x) {
        // REFER: http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return static_cast<size_t>(x ^ (x >> 31));
    }   
    inline size_t operator()(const KeyT x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(static_cast<uint64_t>(x) + FIXED_RANDOM);
    }
};



template<typename KeyType>
using safe_unordered_set=unordered_set<KeyType, custom_hash<KeyType>>;

template<typename KeyType, typename MappedType>
using safe_unordered_map=unordered_map<KeyType, MappedType, custom_hash<KeyType>>;



//####################################################################################################################



// // #include <ext/pb_ds/detail/standard_policies.hpp>
// #include <ext/pb_ds/assoc_container.hpp>  // Common file
// #include <ext/pb_ds/tree_policy.hpp>      // Including tree_order_statistics_node_update
// using namespace __gnu_pbds;
// 
// template<typename KeyType, typename MappedType>
// using cc_unordered_map=cc_hash_table<KeyType, MappedType/* , hash<KeyType> */>;
// 
// // Unordered_map uses collision chaining + prime buckets. gp_hash_table uses open addressing + power of 2 buckets.
// // That makes it run into issues with the default "hash function" for integers, which is just the identity.
// template<typename KeyType, typename MappedType>
// using safe_hash_table=gp_hash_table<KeyType, MappedType/* , hash<KeyType> */>;
// 
// // Ordered Set is a policy based data structure in g++ that keeps the unique elements in sorted order.
// // Functions: order_of_key(key), find_by_order(idx)
// // REFER: https://www.geeksforgeeks.org/implementing-upper_bound-and-lower_bound-for-ordered-set-in-c/?ref=leftbar-rightbar
// template<typename KeyType> using indexed_set1=tree<KeyType, null_type, less<KeyType>, rb_tree_tag, tree_order_statistics_node_update>;
// 
// // A drawback of using less_equal instead of less is that lower_bound works as upper_bound  // REFER: https://stackoverflow.com/questions/44238144/order-statistics-tree-using-gnu-pbds-for-multiset
// template<typename KeyType> using indexed_set2=tree<KeyType, null_type, less_equal<KeyType>, rb_tree_tag, tree_order_statistics_node_update>;



//####################################################################################################################


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(20); cout << fixed;

    return 0;
}
