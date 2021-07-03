#include<bits/stdc++.h>
using namespace std;

// Questions: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// For this code, refer: https://leetcode.com/problems/letter-combinations-of-a-phone-number/discuss/990670/Recursion-Faster-than-100
class Solution {
    map<char,string> m;
    vector<string> output;
    void dfs(string digits,int index,string& s)
    {      
        if(index >= digits.size())
        {
            output.push_back(s);
            return;
        }
        for(auto i : m[digits[index]])
        {
            s.push_back(i);
            dfs(digits,index+1,s);
            s = s.substr(0, s.size()-1);
        }
    }
public:
        Solution() {
        m = {
            {'2',"abc"},
            {'3',"def"},
            {'4',"ghi"},
            {'5',"jkl"},
            {'6',"mno"},
            {'7',"pqrs"},
            {'8',"tuv"},
            {'9',"wxyz"}
        };
    }
    vector<string> letterCombinations(string digits) {
        if(digits == "")
            return output;
        if(digits.length() == 1)
        {
            for(auto i : m[digits[0]])
            {
                string s;
                s.push_back(i);
                output.push_back(s);
                
            }
            return output;
        }
        string s = "";
        dfs(digits,0,s);
        return output;
    }
};

int main () {
    auto res = Solution().letterCombinations("2345678923456789");
    cout << res[10] << '\n';
    return 0;
}

/*
(dev) ➜  ~ /usr/bin/time -v ./sp6
Command terminated by signal 9   <----------------
    Command being timed: "./sp6"
    User time (seconds): 12.23
    System time (seconds): 4.80
    Percent of CPU this job got: 97%
    Elapsed (wall clock) time (h:mm:ss or m:ss): 0:17.45
    Average shared text size (kbytes): 0
    Average unshared data size (kbytes): 0
    Average stack size (kbytes): 0
    Average total size (kbytes): 0
    Maximum resident set size (kbytes): 13169100
    Average resident set size (kbytes): 0
    Major (requiring I/O) page faults: 39
    Minor (reclaiming a frame) page faults: 5389529
    Voluntary context switches: 239
    Involuntary context switches: 1162
    Swaps: 0
    File system inputs: 6632
    File system outputs: 0
    Socket messages sent: 0
    Socket messages received: 0
    Signals delivered: 0
    Page size (bytes): 4096
    Exit status: 0

*/
