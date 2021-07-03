#include<bits/stdc++.h>
using namespace std;

// Questions: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
class Solution {
public:
    // My Own Logic - 2nd Best
    // It simulates multiple for loops using a vector
    // Time: 9.10 seconds
    vector<string> letterCombinations(string digits) {
        int N = digits.size();
        vector<string> mapper = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result;
        string combi(N, '\0');

        if (N == 0) return result;  // this is required because "N-1 == -1" is used to create vector "iters"
        if (N == 1) {
            for (char ch: mapper[digits[0] - '0']) {
                combi[0] = ch;
                result.push_back(combi);
            }
            return result;
        }

        vector<int> mapper_size;
        for (const string &i: mapper) mapper_size.push_back(i.size());

        vector<int> iters(N - 1, 0);  // for loop variables i,j,k,...

        // Start of Main Logic
        for (int i = 0; i < N; ++i) {
            combi[i] = mapper[digits[i] - '0'][0];
        }

        while (true) {
            for (const char ch: mapper[digits[N - 1] - '0']) {
                combi[N - 1] = ch;  // update the last character
                result.push_back(combi);
            }

            const auto n = iters.size() - 1;  // index to last element of "iters"
            ++iters[n];
            combi[n] = mapper[digits[n] - '0'][iters[n] % mapper_size[digits[n] - '0']];
            for (int i = iters.size() - 2; i >= 0; --i) {
                if (iters[i+1] != mapper_size[digits[i+1] - '0']) {
                    break;
                }
                iters[i+1] = 0;  // iters[i+1] %= mapper_size[digits[i+1] - '0'];
                ++iters[i];
                combi[i] = mapper[digits[i] - '0'][iters[i] % mapper_size[digits[i] - '0']];
            }
            if (iters[0] == mapper_size[digits[0] - '0']) {
                break;
            }
        }

        return result;
    }
};

int main () {
    auto res = Solution().letterCombinations("2345678923456789");
    cout << res[10] << '\n';
    return 0;
}

/*
(dev) ➜  ~ /usr/bin/time -v ./sp2
adgjmptwadgjmpvy
    Command being timed: "./sp2"
    User time (seconds): 5.69
    System time (seconds): 3.40
    Percent of CPU this job got: 99%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:09.10
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 12586020
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 0
    Minor (reclaiming a frame) page faults: 4223034
    Voluntary context switches: 1
    Involuntary context switches: 37
    Swaps: 0
    File system inputs: 0
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0

*/
