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

	// Segment is good IF the sum of elements in the segment is at least "s"
	// IF any segment [a,b] in arr[...l..a..b..r...] is good, THEN [l,r] is also good
	//                                   +--+        IF [a,b] is good
	//                                +--------+     THEN [l,r] is also good
	i64 result = 0;
	i64 sum = 0;
	for (i32 l = 0, r = 0; r < n; ++r) {
		sum += arr[r];
		while (sum - arr[l] >= s) {
			sum -= arr[l];
			++l;
		}
		if (sum >= s)
			result += (l+1);
	}
	cout << result << '\n';

	return 0;
}
