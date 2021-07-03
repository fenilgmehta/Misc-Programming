#include<bits/stdc++.h>
using namespace std;

// Questions: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
class Solution {
    const string mapper[10] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int N;
public:
    // Everything is passed to the function
    // Little slow as compared to sp1.cpp and sp2.cpp
    // Time: 9.41 seconds
    void helper(const int i, const string &digits, string &combi, vector<string> &res) {
        if (i == digits.size()) {
            res.push_back(combi);
            return;
        }
        for (const char ch: mapper[digits[i] - '0']) {
            combi[i] = ch;
            helper(i+1, digits, combi, res);
        }
    }

    vector<string> letterCombinations(string digits) {
        N = digits.size();
        if (N == 0) return {};

        string combi(digits.size(), '\0');
        vector<string> result;
        helper(0, digits, combi, result);
        return result;
    }
};

int main () {
    auto res = Solution().letterCombinations("2345678923456789");
    cout << res[10] << '\n';
    return 0;
}

/*
(dev) ➜  ~ /usr/bin/time -v ./sp3
adgjmptwadgjmpvy
    Command being timed: "./sp3"
    User time (seconds): 5.93
    System time (seconds): 3.47
    Percent of CPU this job got: 99%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:09.41
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 12585984
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 0
    Minor (reclaiming a frame) page faults: 4223034
    Voluntary context switches: 37
    Involuntary context switches: 264
    Swaps: 0
    File system inputs: 0
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0

*/
