#include<bits/stdc++.h>
using namespace std;

using i32=int32_t;
using i64=int64_t;

int main() {
	i32 n,m;
	cin >> n >> m;
	vector<i32> a(n), b(m);
	for (i32 i = 0; i < n; ++i) cin >> a[i];
	for (i32 i = 0; i < m; ++i) cin >> b[i];

	i64 count = 0, numCountL, numCountR;
	i32 l = 0;
	for (i32 r = 0; r < b.size();) {
		while (l < a.size() and a[l] < b[r]) ++l;
		if (l < a.size() and a[l] == b[r]) {
			numCountL = 0, numCountR = 0;
			while (l < a.size() and a[l] == b[r]) {
				++numCountL;
				++l;
			}
			while (r < b.size() and a[l-1] == b[r]) {
				++numCountR;
				++r;
			}
			count += numCountL * numCountR;
		} else {
			++r;
		}
	}
	cout << count << '\n';
    
    /*
	Sample Testcase
        8 7
        1 1 3 3 3 5 8 8
        1 3 3 4 5 5 5
    */

	return 0;
}
