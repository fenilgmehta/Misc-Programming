#include<bits/stdc++.h>
using namespace std;

class Solution {
    int pushN, popN;
    int idx;
    string combi;
public:
    void dfs(vector<string> &res) {
        if (pushN == 0) {
            // We do not update "popN" and "idx" in the below loop
            // because before the return statement we will have to
            // revert back to the same old values for the recursion
            // to work properly
            for (int i = 0; i < popN; ++i) {
                combi[idx + i] = ')';
            }
            res.push_back(combi);
            return;
        }
        
        // perform push (
        combi[idx] = '(';
        ++idx;
        --pushN;
        dfs(res);
        --idx;
        ++pushN;
        
        // perform pop )
        if (pushN < popN) {
            combi[idx] = ')';
            ++idx;
            --popN;
            dfs(res);
            --idx;
            ++popN;
        }
    }
    
    vector<string> generateParenthesis(int n) {
        pushN = popN = n;
        idx = 0;
        combi.resize(2 * n);
        
        vector<string> res;
        dfs(res);
        return res;
    }
};

int main() {
    auto res = Solution().generateParenthesis(17);
    cout << res[2][3] << '\n';
    return 0;
}

/*
(dev) ➜  Desktop g++ -O3 lc_parentheses1.cpp -o l1 ; sleep 1 ; /usr/bin/time -v ./l1
(
    Command being timed: "./l1"
    User time (seconds): 5.68
    System time (seconds): 2.94
    Percent of CPU this job got: 99%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:08.63
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 10131396
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 0
    Minor (reclaiming a frame) page faults: 3580817
    Voluntary context switches: 1
    Involuntary context switches: 35
    Swaps: 0
    File system inputs: 0
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0

*/
