#include<bits/stdc++.h>
using namespace std;

using i32=int32_t;
using i64=int64_t;

int main() {
	i32 n;
	i32 k;
	cin >> n >> k;
	
	// NOTE: All numbers in "arr" are +ve. This make the solution easy.
	vector<i32> arr(n);
	for (i32 i = 0; i < n; ++i) cin >> arr[i];

	// Segment is good IF there are no more than "k" (i.e. at most "k") unique elements
	// IF any segment [l,r] in arr[...l..a..b..r...] is good, THEN [a,b] is also good
	//                                +--------+     IF [l,r] is good
	//                                   +--+        THEN [a,b] is also good
	i64 result = 0;
	map<i32,i32> m;
	for (i32 l = 0, r = 0; r < n; ++r) {
		m[arr[r]] += 1;
		while (m.size() > k) {
			auto it = m.lower_bound(arr[l]);
			if (it->second == 1) {
				m.erase(it);
			} else {
				it->second -= 1;
			}
			++l;
		}
		result += (r-l+1);
	}
	cout << result << '\n';

	return 0;
}
