#include <iostream>
#include <algorithm>
#include <random>
#include <csignal>
#include <mylog.hpp>
using namespace std;

#define int int32_t

// Code and Explanation - REFER: https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/
// Explanation          - REFER: https://stackoverflow.com/questions/7198121/quicksort-and-hoare-partition
// Video for visualization     : https://www.youtube.com/watch?v=XDfHjgOzDLE
template<typename RandomAccessIterator>
void QuickSort(RandomAccessIterator arrPtr, int32_t len) {
    if (len <= 1) return;

    int32_t mid = len / 2;
    if (not(arrPtr[mid] <= arrPtr[len-1])) iter_swap(arrPtr+mid, arrPtr+len-1);
    if (not(arrPtr[0] <= arrPtr[len-1])) iter_swap(arrPtr+0, arrPtr+len-1);
    if (arrPtr[0] < arrPtr[mid]) iter_swap(arrPtr+0, arrPtr+mid);  // median will be at index 0

    // ❗NOTE: It is mandatory to have the median at index 0
    auto pivot = *arrPtr;  // median of arr[0,..., mid,..., len-1]

    // Hoare's Partition Scheme
    int32_t i = -1, j = len;
    while (true) {
        do { ++i; }
        while (arrPtr[i] < pivot);
        do { --j; }
        while (pivot < arrPtr[j]);

        if (i >= j) break;
        swap(arrPtr[i], arrPtr[j]);
    }

    // [0...j...i...len)
    QuickSort(arrPtr, j+1);  // [0, j] ---> len j+1
    QuickSort(arrPtr + (j+1), len - (j+1));  // [j+1, len-1]
    // PROBABLY, instead of using the recursion on the range [0,j] and [j+1,len) -> we can
    // call the recursive sort on the range [0,j] and [i,len). I had tried so in
    // https://leetcode.com/problems/sort-the-matrix-diagonally
    return;

    /*
        // This is same as Hoare's Partition Scheme
        int i = 0, j = len - 1;
        while (i <= j) {  // corner case: {0, 2, 1, 3, 4} because of which "<=" is used instead of "<"
            while (arrPtr[i] < pivot) ++i;
            while (pivot < arrPtr[j]) --j;

            // This is a little bit faster than the below alternative
            if (i <= j) {  // corner case: {18, 17, 17, 19} because of which "<=" is used instead of "<"
                if (i != j) iter_swap(arrPtr+i, arrPtr+j);
                ++i;
                --j;
            }
            // if (i >= j) break;
            // iter_swap(arrPtr+i, arrPtr+j);
            // ++i;
            // --j;
        }
        // [0...j...i...len)
        QuickSort(arrPtr, i);  // [0, i-1]
        QuickSort(arrPtr + i, len - i);  // [i, len-1]
    */
}

// ---

// REFER: https://stackoverflow.com/questions/12149593/how-can-i-create-an-array-of-random-numbers-in-c
std::vector<int> create_random_data(int n) {
    std::random_device r;
    std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937       eng(seed); // a source of random data

    std::uniform_int_distribution<int> dist;
    std::vector<int> v(n);

    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

int32_t *globalarr = nullptr;
int32_t globalarrSize = 0;

void handle_signals(int signalNum) {
    // REFER: https://www.geeksforgeeks.org/signals-c-language/
    if (signalNum == SIGTERM) {
        // signal 15
        cout << "\n\nglobalarrSize = " << globalarrSize;
        cout << "\n\nglobalarr =\n\n";
        for (int i = 0; i < globalarrSize; ++i) cout << globalarr[i] << " ";
        cout << endl;
        exit(15);  // bash ---> exit(128 + 15);
    }
}

int main () {
    signal(SIGTERM, handle_signals);

    int testingMethod, arrLen;
    cout << "Enter testingMethod (1:bruteforce, 2:random, 3:customArray) = ";
    cin >> testingMethod;
    cout << endl;
    cout << "Enter arrLen = ";
    cin >> arrLen;
    cout << endl;

    globalarrSize = arrLen;
    vector<int> arr(arrLen), temp(arrLen);
    if (testingMethod == 1) {
        // Brute-force
        iota(arr.begin(), arr.end(), 0);
        int64_t status_curr=1, status_max=1;
        for (int i = 1; i <= arrLen; ++i) status_max *= i;
        do {
            cout << "\rstatus = " << status_curr << " / " << status_max << " ( " << (100 * status_curr / status_max) << " % )";
            status_curr += 1;
            db("------------");
            temp = arr;
            globalarr = &arr[0];
            QuickSort(temp.begin(), arrLen);
            if (is_sorted(temp.begin(), temp.end()) == false) {
                cout << "\nERROR: temp not sorted" << endl;
                db(temp);
                db(arr);
                return 1;
            }
        } while (next_permutation(arr.begin(), arr.end()));
    } else if (testingMethod == 2) {
        // Fixed number of random testcases
        int testcaseCount = 10000;
        cout << "Enter testcaseCount = ";
        cin >> testcaseCount;
        cout << endl;
        for (int i = 0; i < testcaseCount; ++i) {
            cout << "\rstatus = " << (i+1) << " / " << testcaseCount << " ( " << (100 * (i+1) / testcaseCount) << " % )";
            arr = temp = create_random_data(arrLen);
            globalarr = &arr[0];
            QuickSort(temp.begin(), arrLen);
            if (is_sorted(temp.begin(), temp.end()) == false) {
                cout << "ERROR: temp not sorted" << endl;
                db(temp);
            }
        }
    } else if (testingMethod == 3)  {
        for (int i = 0; i < arrLen; ++i) cin >> arr[i];
        temp = arr;
        QuickSort(temp.begin(), arrLen);
        if (is_sorted(temp.begin(), temp.end()) == false) {
            cout << "ERROR: temp not sorted" << endl;
            db(temp);
        }
    } else {
        cout << "Invalid input for \"testingMethod\"" << endl;
    }

    cout << endl;
    return 0;
}
