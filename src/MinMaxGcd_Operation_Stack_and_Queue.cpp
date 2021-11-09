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

template<typename T>
struct OperationGcd {
	T operator()(const T a, const T b) const {
		return __gcd(a, b);
	}
};

// ---

// Operation can be "OperationMin<T>", "OperationMax<T>", "OperationGcd<T>"
template<typename T, typename Operation>
struct OperationStack {
	// pair -> {original value, Min/Max/GCD of all the elements in the stack}
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
		const auto val = move(s.top().first);
		s.pop();
		return val;
	}
	T rangeOperation(T default_value=T()) const {
		if (s.empty()) return default_value;
		return s.top().second;
	}
};

// NOTE: MinMaxQueueFast is preferred over this for "min" and "max" operations
template<typename T, typename Operation>
struct OperationQueue {
	OperationStack<T, Operation> sOut, sIn;
	Operation op;
	OperationQueue(): sOut(), sIn(), op() {}
	bool empty() const {
		return sOut.empty() and sIn.empty();
	}
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

// ---

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
	// NOTE: We require "insertCount" and "removeCount" to allow the "pop" method
	//       to pop elements without knowing which element is to be popped
	void pop() {
		if ((not s.empty()) and s.front().second == removeCount)
			s.pop_front();
		removeCount += 1;
	}
	T rangeOperation() const {
		return s.front().first;
	}
};

// NOTE: In this struct, only the "pop" method differs from the above
//       struct. Here, we have to pass the value which is to be popped.
template<typename T, typename Operation>
struct MinMaxQueueFast_2 {
	deque<T> s;
	Operation op;
	MinMaxQueueFast_2(): s(), op() {}
	bool empty() const {
		return s.empty();
	}
	void push(T val) {
		// Comparison for Min Queue = s.back().first > val
		// NOTE: We can NOT use "localMinQueue.back() >= arr[idx]" because there can be a case
		//       where (X1 == X2) queue has front element as X2 but X1 goes out of window
		while ((not s.empty()) and op(s.back(), val))
			s.pop_back();
		s.push_back(val);
	}
	void pop(const T& val) {  // DIFFERENT
		if ((not s.empty()) and s.front() == val)
			s.pop_front();
	}
	T rangeOperation() const {
		return s.front();
	}
};

// ---

int main() {
	// NOTE: both of the below statements are the same
	// OperationQueue<i32,OperationMax<i32>> maxQ;
	MinMaxQueueFast<i32,std::less<i32>> maxQ;

	// Queue = 5,3,7,1,5
	//    front^       ^back

	maxQ.push(5);  // stack = 5
	cout << maxQ.rangeOperation() << endl;  // 5
	maxQ.push(3);  // stack = 5, 3
	cout << maxQ.rangeOperation() << endl;  // 5
	maxQ.push(7);  // stack = 7
	cout << maxQ.rangeOperation() << endl;  // 7
	maxQ.push(1);  // stack = 7, 1
	cout << maxQ.rangeOperation() << endl;  // 7
	maxQ.push(5);  // stack = 7, 5
	cout << maxQ.rangeOperation() << endl;  // 7

	cout << endl;

	maxQ.pop();
	cout << maxQ.rangeOperation() << endl;  // 7
	maxQ.pop();
	cout << maxQ.rangeOperation() << endl;  // 7
	maxQ.pop();
	cout << maxQ.rangeOperation() << endl;  // 5
	maxQ.pop();
	cout << maxQ.rangeOperation() << endl;  // 5
	maxQ.pop();

	cout << endl;

	cout << boolalpha << maxQ.empty() << endl;  // true

	return 0;
}
