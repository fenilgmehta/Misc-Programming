#include<bits/stdc++.h>
using namespace std;

using i32=int32_t;
using i64=int64_t;

template<typename T>
T myGcd(T a, T b) {
	while (b != 0) {
		// a >= b
		a = a % b;
		swap(a, b);
	}
	return a;
}

template<typename T>
struct OperationGcd {
	T operator()(const T a, const T b) const {
		return myGcd<T>(a, b);
	}
};

template<typename T, typename Operation>
struct OperationStack {
	stack<pair<T,T>> s;
	Operation op;
	OperationStack(): s(), op() {}
	bool empty() const {
		return s.empty();
	}
	void push(const T val) {
		s.emplace(val, s.empty() ? val : op(val, s.top().second));
	}
	T popTop() {
		const auto val = s.top().first;
		s.pop();
		return val;
	}
	T rangeOperation(T default_value=T()) const {
		if (s.empty()) return default_value;
		return s.top().second;
	}
};

template<typename T, typename Operation>
struct OperationQueue {
	OperationStack<T, Operation> sOut, sIn;
	Operation op;
	OperationQueue(): sOut(), sIn(), op() {}
	void push(const T val) {
		sIn.push(val);
	}
	void push_front(const T val) {
		sOut.push(val);
	}
	T pop() {
		if (sOut.empty()) {
			while (not sIn.empty())
				sOut.push(sIn.popTop());
		}
		return sOut.popTop();
	}
	T rangeOperation() const {
		if (sIn.empty()) return sOut.rangeOperation();
		if (sOut.empty()) return sIn.rangeOperation();
		return op(sIn.rangeOperation(), sOut.rangeOperation());
	}
};

int main() {
	i32 n;
	cin >> n;
	
	vector<i64> arr(n);
	for (i32 i = 0; i < n; ++i) cin >> arr[i];

	// Segment is good IF the sum of elements in the segment is at least "s"
	// IF any segment [a,b] in arr[...l..a..b..r...] is good, THEN [l,r] is also good
	//                                   +--+        IF [a,b] is good
	//                                +--------+     THEN [l,r] is also good
	i32 result = numeric_limits<i32>::max();
	OperationQueue<i64,OperationGcd<i64>> q;
	for (i32 l = 0, r = 0; r < n; ++r) {
		q.push(arr[r]);
		// NOTE: There is a possibility that "q.rangeOperation()"
		//       is called when queue is empty. Hence, "default_value"
		//       parameter is added in the "OperationStack" struct
		while(q.rangeOperation() == 1) {
			result = min(result, r-l+1);
			q.pop();
			++l;
		}
	}
	if (result == numeric_limits<i32>::max()) result = -1;
	cout << result << '\n';

	return 0;
}
