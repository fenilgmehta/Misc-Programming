#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

#define int int32_t

//####################################################################################################################

/* 

*** Binary Index Tree / Fenwick Tree ***

REFER: https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
REFER: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/tutorial/

NOTE: 1-indexed BIT is used
NOTE: all range based parameters are considered as INCLUSIVE

Operator precedence (Top is high)
    unary minus
    bitwise &
    -=, +=

*/

// NOTE: the below struct is used to store `Prefix Sum`
template<typename T>
struct BinaryIndexTree{

    typedef int32_t size_type;
    size_type n;
    vector<T> bit;

    explicit BinaryIndexTree(const size_type &t_n, const T &t_default_value=0){
        n = t_n;
        bit.resize(t_n+1, t_default_value);
    }
    
    template<typename RandomIt>
    explicit BinaryIndexTree(RandomIt first, const RandomIt &last, const T &default_value=0){
        n = distance(first, last);
        bit.resize(n+1, default_value);
        for(size_type idx = 1; first != last; ++idx, ++first){
            update(idx, *first);
        }
    }

    void update(size_type idx, T diff){
        // -idx is 2's complement where the first bit storing 1 from the
        // RHS remains the same and everything to its LHS get toggled
        // i.e. `10101 𝟏𝟎𝟎𝟎`  ---> `01010 𝟏𝟎𝟎𝟎`
        // `idx&-idx` for `10101 𝟏𝟎𝟎𝟎` gives `00000 𝟏𝟎𝟎𝟎`
        for(; idx <= n; idx += idx&-idx) bit[idx] += diff;
    }

    /* Returns the Prefix Sum for the range [1, idx] */
    T query(size_type idx) const {
        T sum = 0;
        for(; idx > 0; idx -= idx&-idx) sum += bit[idx];
        return sum;
    }

    /* Returns the Prefix Sum for the range [idx_first, idx_last] */
    T query(const size_type &idx_first, const size_type &idx_last) const {
        return query(idx_last) - query(idx_first-1);
    }

    inline size_type size(){ return n; }
};

//####################################################################################################################

int main(){
    vector<int> freq = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    BinaryIndexTree<int> bit(freq.begin(), freq.end());

    cout << endl << "Binary Index Tree / Fenwick Tree (1-indexed)" << endl;
    cout << "\nPrefix sum from freq[1,1] = " << bit.query(1);  // 2 -> 2
    cout << "\nPrefix sum from freq[1,2] = " << bit.query(2);  // 3 -> 2, 1
    cout << "\nPrefix sum from freq[1,3] = " << bit.query(3);  // 4 -> 2, 1, 1
    cout << "\nPrefix sum from freq[1,4] = " << bit.query(4);  // 7 -> 2, 1, 1, 3
    cout << "\nPrefix sum from freq[5,9] = " << bit.query(5, 9);  // 20 -> 2, 3, 4, 5, 6
    bit.update(5, +9);
    cout << "\nPrefix sum from freq[5,9] = " << bit.query(5, 9);  // 29 -> 2+9, 3, 4, 5, 6

    cout << "\n\n";
	return 0;
}