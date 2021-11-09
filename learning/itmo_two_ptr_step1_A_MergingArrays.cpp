#include<bits/stdc++.h>
using namespace std;

using i32=int32_t;

// REFER: https://codeforces.com/edu/course/2  >  Step1  >  Practice  >  A
int main() {
	i32 n,m;
	cin >> n >> m;
	vector<i32> a(n), b(m);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];

	for (int l = 0, r = 0; l < a.size() or r < b.size();) {
		if (r >= b.size() or (l < a.size() and a[l] <= b[r])) {
			cout << a[l] << ' ';
			++l;
		} else if (r < b.size()) {
			cout << b[r] << ' ';
			++r;
		}
	}
	cout << '\n';
	return 0;
}
