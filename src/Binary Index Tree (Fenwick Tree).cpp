#include <iostream>
#include <cstdint>
#include <vector>
#include <iomanip>
using namespace std;

#define int int32_t

//####################################################################################################################

/* 

*** Binary Index Tree / Fenwick Tree ***

REFER: https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
REFER: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/tutorial/

NOTE: all index values in method parameters are assumed to be 𝟭-𝗶𝗻𝗱𝗲𝘅𝗲𝗱
NOTE: all range based parameters are considered as INCLUSIVE, i.e. [l, r] ---> r is included

Operator precedence (Top is high)
    unary minus
    bitwise &
    -=, +=

*/

// NOTE: the below struct is used to store `Prefix Sum` by default
template<typename T, typename CombinerFunction = plus<T>, typename SplitterFunction = minus<T>>
struct BinaryIndexTree{

    typedef int32_t size_type;
    size_type n;
    vector<T> bit;
    CombinerFunction combine;
    SplitterFunction split;

    explicit BinaryIndexTree(const size_type &t_n, const T &t_default_value=0): combine(), split(){
        this->resize(t_n, t_default_value);
    }
    
    // TODO: can optimize this to O(n) time complexity
    template<typename RandomIt>
    explicit BinaryIndexTree(RandomIt first, const RandomIt &last, const T &t_default_value=0): combine(), split(){
        this->resize(distance(first, last), t_default_value);
        for(size_type idx = 1; first != last; ++idx, ++first){
            update(idx, *first);
        }
    }

    void update(size_type idx, const T &diff){
        if(idx <= 0) { cerr << "-ve idx not allowed in BinaryIndexTree::update(...)\n"; return; }
        for(; idx <= n; move_to_parent(idx)) bit[idx] = combine(bit[idx], diff);
    }

    /* Returns the Prefix Sum for the range [1, idx] */
    T query(size_type idx) const {
        T res = 0;
        for(; idx > 0; move_left(idx)) res = combine(res, bit[idx]);
        return res;
    }

    /* Returns the Prefix Sum for the range [idx_first, idx_last] */
    T query(const size_type &idx_first, const size_type &idx_last) const {
        return split(query(idx_last), query(idx_first-1));
    }

    inline size_type size() const { return n; }
    inline void resize(const size_type &t_n, const T &t_default_value=0) { n = t_n; bit.resize(t_n+1, t_default_value); }
    inline void reset(const T &t_default_value=0) { fill(begin(bit), end(bit), t_default_value); }

    /* Returns base array value at index `idx`. The array is 1-indexed with range [1, n] */
    T operator[](size_type idx) const {
        if(idx <= 0) return T();
        T res = bit[idx];
        const size_type left_sibling_idx = idx - (idx & -idx);
        for(--idx; idx != left_sibling_idx; move_left(idx))
            res = split(res, bit[idx]);
        return res;  // res = split(bit[idx], bit[children of idx])
    }

    // • -idx is 2's complement where the first bit storing 1 from the
    //   RHS remains the same and everything to its LHS get toggled
    //   i.e. `10101 𝟏𝟎𝟎𝟎`  ---> `01010 𝟏𝟎𝟎𝟎`
    
    // • `idx&-idx` for `10101 𝟏𝟎𝟎𝟎` gives `00000 𝟏𝟎𝟎𝟎`
    template<typename Index>
    inline static void move_to_parent(Index &idx) { idx += (idx & -idx); }

    template<typename Index>
    inline static void move_left(Index &idx) { idx ^= (idx & -idx); }  // idx -= (idx & -idx) is also correct

    template<typename Index>
    inline static void move_to_right_sibling(Index &idx) { idx |= (idx & -idx) >> 1; }

    template<typename Index>
    inline static void move_to_first_child(Index &idx) { idx -= (idx & -idx) >> 1; }
};

/* Only useful when BinaryIndexTree store prefix sum
 * Returns: index with given cumulative frequency in O(log(n)) time, return -1 if not found
 */
template<typename T>
auto find(const BinaryIndexTree<T> &bit, T prefixSumFreq){
    int32_t idx = 1;
    while((idx << 1) < bit.size()) idx <<= 1;

    int32_t result_idx = -1;
    while(not (idx & 1)){
        const T &qVal = bit.bit[idx];
        if(prefixSumFreq == qVal) {
            result_idx = idx;  // this is done to ensure that the first occurence of prefixSumFreq is returned instead of any random
            bit.move_to_first_child(idx);
            continue;
        }

        prefixSumFreq -= qVal;
        if(prefixSumFreq > 0){
            bit.move_to_right_sibling(idx);
            while(idx > bit.size()) bit.move_to_first_child(idx);
        } else {
            prefixSumFreq += qVal;
            bit.move_to_first_child(idx);
        }
    }

    if(prefixSumFreq == bit.bit[idx]) return idx;
    return result_idx;
}

//####################################################################################################################

int main(){
    // NOTE: any commutative operation which is associative can be used
    // BinaryIndexTree<int, plus<int>, minus<int>> b();
    // BinaryIndexTree<int, multiplies<int>, divides<int>> b();
    // BinaryIndexTree<int, bit_xor<int>, bit_xor<int>> b();

    vector<int> freq = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};  // size = 12
    BinaryIndexTree<int> bit(freq.begin(), freq.end());

    cout << endl << "Binary Index Tree / Fenwick Tree (1-indexed)" << endl;
    cout << "\nPrefix sum from freq[1,1] = " << setw(2) << bit.query(1);  // 2 -> 2
    cout << "\nPrefix sum from freq[1,2] = " << setw(2) << bit.query(2);  // 3 -> 2, 1
    cout << "\nPrefix sum from freq[1,3] = " << setw(2) << bit.query(3);  // 4 -> 2, 1, 1
    cout << "\nPrefix sum from freq[1,4] = " << setw(2) << bit.query(4);  // 7 -> 2, 1, 1, 3
    cout << "\nPrefix sum from freq[5,9] = " << setw(2) << bit.query(5, 9);  // 20 -> 2, 3, 4, 5, 6
    bit.update(5, +9);
    cout << "\n*** bit.update(5, +9) successfully executed ***";
    cout << "\nPrefix sum from freq[5,9] = " << setw(2) << bit.query(5, 9);  // 29 -> 2+9, 3, 4, 5, 6
    cout << endl;

    cout << "\nIndex      = 1, 2, 3, 4,  5,  6,  7,  8,  9, 10, 11, 12";
    cout << "\nbit.bit[i] = 2, 3, 1, 7, 11, 14,  4, 30,  6, 13,  8, 30";
    cout << "\nPrefix sum = 2, 3, 4, 7, 18, 21, 25, 30, 36, 43, 51, 60";
    cout << endl;

    cout << boolalpha << "\nbool(bit[1]  ==  2)  = " << (bit[1]  ==  2);
    cout << boolalpha << "\nbool(bit[2]  ==  1)  = " << (bit[2]  ==  1);
    cout << boolalpha << "\nbool(bit[3]  ==  1)  = " << (bit[3]  ==  1);
    cout << boolalpha << "\nbool(bit[4]  ==  3)  = " << (bit[4]  ==  3);
    cout << boolalpha << "\nbool(bit[5]  == 11)  = " << (bit[5]  == 11);
    cout << boolalpha << "\nbool(bit[6]  ==  3)  = " << (bit[6]  ==  3);
    cout << boolalpha << "\nbool(bit[7]  ==  4)  = " << (bit[7]  ==  4);
    cout << boolalpha << "\nbool(bit[8]  ==  5)  = " << (bit[8]  ==  5);
    cout << boolalpha << "\nbool(bit[9]  ==  6)  = " << (bit[9]  ==  6);
    cout << boolalpha << "\nbool(bit[10] ==  7)  = " << (bit[10] ==  7);
    cout << boolalpha << "\nbool(bit[11] ==  8)  = " << (bit[11] ==  8);
    cout << boolalpha << "\nbool(bit[12] ==  9)  = " << (bit[12] ==  9);
    cout << endl;

    cout << boolalpha << "\nbool(find(bit,  2) ==  1 ) = " << setw(2) << (find(bit,  2) ==  1);
    cout << boolalpha << "\nbool(find(bit,  3) ==  2 ) = " << setw(2) << (find(bit,  3) ==  2);
    cout << boolalpha << "\nbool(find(bit,  4) ==  3 ) = " << setw(2) << (find(bit,  4) ==  3);
    cout << boolalpha << "\nbool(find(bit,  7) ==  4 ) = " << setw(2) << (find(bit,  7) ==  4);
    cout << boolalpha << "\nbool(find(bit, 18) ==  5 ) = " << setw(2) << (find(bit, 18) ==  5);
    cout << boolalpha << "\nbool(find(bit, 21) ==  6 ) = " << setw(2) << (find(bit, 21) ==  6);
    cout << boolalpha << "\nbool(find(bit, 25) ==  7 ) = " << setw(2) << (find(bit, 25) ==  7);
    cout << boolalpha << "\nbool(find(bit, 30) ==  8 ) = " << setw(2) << (find(bit, 30) ==  8);
    cout << boolalpha << "\nbool(find(bit, 36) ==  9 ) = " << setw(2) << (find(bit, 36) ==  9);
    cout << boolalpha << "\nbool(find(bit, 43) == 10 ) = " << setw(2) << (find(bit, 43) == 10);
    cout << boolalpha << "\nbool(find(bit, 51) == 11 ) = " << setw(2) << (find(bit, 51) == 11);
    cout << boolalpha << "\nbool(find(bit, 60) == 12 ) = " << setw(2) << (find(bit, 60) == 12);
    cout << endl;

    cout << "\n";
	return 0;
}