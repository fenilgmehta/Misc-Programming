#include<bits/stdc++.h>
using namespace std;

using i32=int32_t;
using i64=int64_t;

int main() {
	i32 n;
	i64 s;
	cin >> n >> s;
	
	// NOTE: All numbers in "arr" are +ve. This make the solution easy.
	vector<i32> arr(n);
	for (i32 i = 0; i < n; ++i) cin >> arr[i];

	// Segment is good IF the sum of elements in the segment is at most "s"
	// IF any segment [l,r] in arr[...l..a..b..r...] is good, THEN [a,b] is also good
	//                                +--------+     IF [l,r] is good
	//                                   +--+        THEN [a,b] is also good
	i64 result = 0;
	i64 sum = 0;
	for (i32 l = 0, r = 0; r < n; ++r) {
		sum += arr[r];
		while (sum > s) {
			sum -= arr[l];
			++l;
		}
		result += (r-l+1);
	}
	cout << result << '\n';

	return 0;
}
