#include<bits/stdc++.h>
using namespace std;

// Questions: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
class Solution {
    const string mapper[10] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int N;
    char* mdigits;
    size_t idx;
    string *ptr;
    string combi;
public:
    // My Own Logic - this is the BEST
    // Passing data using object's data members instead of passing by method parameters
    // Time: 8.10 seconds
    void helper(const int i) {
        if (i == N) {
            ptr[idx] = combi;
            ++idx;
            return;
        }
        for (const char ch: mapper[mdigits[i] - '0']) {
            combi[i] = ch;
            helper(i+1);
        }
    }

    vector<string> letterCombinations(string digits) {
        N = digits.size();
        if (N == 0) return {};

        mdigits = digits.data();
        combi.resize(digits.size());

        int64_t res_size = 1;
        for (char ch: digits) res_size *= mapper[ch - '0'].size();
        vector<string> result(res_size);
        ptr = result.data();
        idx = 0;

        helper(0);
        if (idx == result.size()) cout << "cool\n";
        return result;
    }
};

int main () {
    auto res = Solution().letterCombinations("2345678923456789");
    cout << res[10] << '\n';
    return 0;
}

/*
(dev) ➜  ~ /usr/bin/time -v ./sp1
cool
adgjmptwadgjmpvy
    Command being timed: "./sp1"
    User time (seconds): 6.02
    System time (seconds): 2.07
    Percent of CPU this job got: 99%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:08.10
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 10631812
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 0
    Minor (reclaiming a frame) page faults: 2657339
    Voluntary context switches: 1
    Involuntary context switches: 43
    Swaps: 0
    File system inputs: 0
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0

*/
