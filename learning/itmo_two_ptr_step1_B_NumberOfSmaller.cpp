#include<bits/stdc++.h>
using namespace std;

using i32=int32_t;

int main() {
	i32 n,m;
	cin >> n >> m;
	vector<i32> a(n), b(m);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];

	int l = 0;
	for (int r = 0; r < b.size(); ++r) {
		while (l < a.size() and a[l] < b[r]) {
			++l;
		}
		cout << l << ' ';
	}
	cout << '\n';
	return 0;
}
