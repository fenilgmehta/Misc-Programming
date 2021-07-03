#include<bits/stdc++.h>
using namespace std;

// Questions: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// For this code, refer: https://leetcode.com/problems/letter-combinations-of-a-phone-number/discuss/8090/Iterative-c%2B%2B-solution-in-0ms
class Solution {
public:
    const vector<string> pad = {
        "", "", "abc", "def", "ghi", "jkl",
        "mno", "pqrs", "tuv", "wxyz"
    };
    
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        vector<string> result;
        result.push_back("");
        
        for(auto digit: digits) {
            vector<string> tmp;
            for(auto candidate: pad[digit - '0']) {
                for(auto s: result) {
                    tmp.push_back(s + candidate);
                }
            }
            result.swap(tmp);
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
(dev) ➜  ~ /usr/bin/time -v ./sp5
Command terminated by signal 9   <----------------
    Command being timed: "./sp5"
    User time (seconds): 8.02
    System time (seconds): 4.75
    Percent of CPU this job got: 94%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:13.56
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 13220560
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 4
    Minor (reclaiming a frame) page faults: 5169335
    Voluntary context switches: 412
    Involuntary context switches: 1389
    Swaps: 0
    File system inputs: 192
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0

*/
