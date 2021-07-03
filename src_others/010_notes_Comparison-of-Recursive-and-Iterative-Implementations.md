# Comparison of Recursive and Iterative Implementations


### Summary

After comparing multiple solutions for the same problem which either use `recursion`, simulate recursion using `stack` or use any other method to simulate `multiple for loops`, it was found that recursive implementations are:
1. Are easy to code
2. Execute faster than any other implementation
3. Generally have same time and space complexity as iterative implementations


### Testing Details

- Note: all programs were executed on an device with 16 GB RAM and each solution was executed in the same environment

- The question used testing purpose: [letter-combinations-of-a-phone-number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)

- Six implementations were used for testing purpose.
	- Command used for compilation: `g++ -std=c++17 -O3 spN.cpp -o spN`
	- `/usr/bin/time -v ./spN` was used to measure execution time, memory usage and many other metrics
	- The input used for testing: `2345678923456789`
	- Note: mostly, all the below solutions passed all test cases on leetcode
	1. [Solution 1](./sp1.cpp) - Used recursion and used object's data members in recursive method instead of passing data as reference using method parameters
		- Running time: `8.1` seconds
	2. [Solution 2](./sp2.cpp) - Iterative implementation which uses a vector to simulate multiple for loops
		- Running time: `9.1` seconds
	3. [Solution 3](./sp3.cpp) - Used recursion and passed data as reference using method parameters
		- Running time: `9.4` seconds
	4. [Solution 4](./sp4.cpp) - Used recursion but poor design
		- Running time: `12.0+` seconds, Operating System killed this program because it went out of memory
	5. [Solution 5](./sp5.cpp) - Iterative implementation which uses two vectors as queue
		- Running time: `13.5+` seconds, Operating System killed this program because it went out of memory
	6. [Solution 6](./sp6.cpp) - Used recursion but poor design
		- Running time: `17.4+` seconds, Operating System killed this program because it went out of memory

- Comparison of two recursive implementations: [generate-parentheses](https://leetcode.com/problems/generate-parentheses/)
	- The input used for testing: `17`
	- Note: both the below solutions passed all test cases on leetcode
	1. [Solution 1](./lc_parentheses1.cpp) - avoided time consuming string concatenation operation and used a single string for everything
		- Running time: `8.6` seconds
	2. [Solution 1](./lc_parentheses1.cpp) - created new string for each recursive call
		- Running time: `40.7` seconds

