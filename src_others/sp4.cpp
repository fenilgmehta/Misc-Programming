#include<bits/stdc++.h>
using namespace std;

// Questions: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
class Solution {
    const string mapper[10] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int N;
    string combi;
    vector<string> res;  // This is global
public:
    // This is the WORST because while performing return in
    // "letterCombinations", a copy of result will be created :(
    // which will cause the program to use 2x amount of RAM as
    // compared to sp1.cpp, sp2.cpp, sp3.cpp
    // Killed by the OS because it went out of memory
    void helper(const int i, const char* digits) {
        if (i == N) {
            res.push_back(combi);
            return;
        }
        for (const char ch: mapper[digits[i] - '0']) {
            combi[i] = ch;
            helper(i+1, digits);
        }
    }

    vector<string> letterCombinations(string digits) {
        N = digits.size();
        if (N == 0) return {};

        combi.clear();
        combi.resize(digits.size());
        res.clear();
        helper(0, digits.data());
        return res;
    }
};

int main () {
    auto res = Solution().letterCombinations("2345678923456789");
    cout << res[10] << '\n';
    return 0;
}

/*
(dev) ➜  ~ /usr/bin/time -v ./sp4
Command terminated by signal 9   <----------------
    Command being timed: "./sp4"
    User time (seconds): 6.30
    System time (seconds): 4.88
    Percent of CPU this job got: 93%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:12.02
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 13193040
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 23
    Minor (reclaiming a frame) page faults: 5405550
    Voluntary context switches: 563
    Involuntary context switches: 1350
    Swaps: 0
    File system inputs: 4064
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0

*/
