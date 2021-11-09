#include<bits/stdc++.h>
using namespace std;

using i32=int32_t;
using i64=int64_t;

// NOTE: Do not forget to put "const" after the method parameters
//       it tells the compiler that the method does not modify the object.
//       Otherwise we get compilation error.
template<typename T>
struct OperationMin {
	T operator()(const T a, const T b) const {
		return min(a,b);
	}
};
template<typename T>
struct OperationMax {
	T operator()(const T a, const T b) const {
		return max(a,b);
	}
};

// Operation can be "OperationMin<T>" or "OperationMax<T>"
template<typename T, typename Operation>
struct MinMaxStack {
	stack<pair<T,T>> s;  // pair -> {original value, Min/Max of all the elements in the stack}
	Operation op;
	MinMaxStack(): s(), op() {}
	bool empty() const { return s.empty(); }
	void push(const T val) {
		s.emplace(val, s.empty() ? val : op(val, s.top().second));
	}
	T popTop() {
		const auto val = move(s.top());
		s.pop();
		return val.first;
	}
	T rangeOperation() const {
		return s.top().second;
	}
};

template<typename T, typename Operation>
struct MinMaxQueue {
	MinMaxStack<T, Operation> sOut, sIn;
	Operation op;
	MinMaxQueue(): sOut(), sIn(), op() {}
	void push(T val) {
		sIn.push(val);
	}
	T pop() {
		if (sOut.empty()) {
			while (not sIn.empty()) {
				sOut.push(sIn.popTop());
			}
		}
		return sOut.popTop();
	}
	T rangeOperation() const {
		if (sIn.empty()) return sOut.rangeOperation();
		if (sOut.empty()) return sIn.rangeOperation();
		return op(sIn.rangeOperation(), sOut.rangeOperation());
	}
};

// Template works similar to Priority Queue
// Operation can be "std::less<T>" or "std::greater<T>"
//                   max operation     min operation
template<typename T, typename Operation>
struct MinMaxQueueFast {
	i32 insertCount, removeCount;
	deque<pair<T,i32>> s;
	Operation op;
	MinMaxQueueFast(): insertCount{0}, removeCount{0}, s(), op() {}
	bool empty() const {
		return insertCount == removeCount;
	}
	void push(T val) {
		// Comparison for Min Queue = s.back().first > val
		while ((not s.empty()) and op(s.back().first, val))
			s.pop_back();
		s.emplace_back(val, insertCount);
		insertCount += 1;
	}
	void pop() {
		if ((not s.empty()) and s.front().second == removeCount)
			s.pop_front();
		removeCount += 1;
	}
	T rangeOperation() const {
		return s.front().first;
	}
};


int main() {
	i32 n;
	i64 k;
	cin >> n >> k;
	
	vector<i64> arr(n);
	for (i32 i = 0; i < n; ++i) cin >> arr[i];

	// Segment is good IF difference between the maximum and minimum elements on this segment is at most "k"
	// IF any segment [l,r] in arr[...l..a..b..r...] is good, THEN [a,b] is also good
	//                                +--------+     IF [l,r] is good (i.e. max1 - min1 <= k)
	//                                   +--+        THEN [a,b] is also good (i.e. max2 - min2 <= k)
	//                                               BECAUSE min1 <= min2 <= max2 <= max1
	i64 result = 0;
	MinMaxQueueFast<i64,std::less<i64>> qmax;
	MinMaxQueueFast<i64,std::greater<i64>> qmin;
	for (i32 l = 0, r = 0; r < n; ++r) {
		qmin.push(arr[r]);
		qmax.push(arr[r]);
		while (qmax.rangeOperation() - qmin.rangeOperation() > k) {
			qmin.pop();
			qmax.pop();
			++l;
		}
		result += (r-l+1);
	}
	cout << result << '\n';

	return 0;
}
