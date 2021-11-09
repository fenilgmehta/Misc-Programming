#include <bits/stdc++.h>
#include "mylog.hpp"
using namespace std;

template<typename Ta, typename Tb> inline auto min(Ta a, Tb b) { return (a <= b) ? a : b; }
template<typename Ta, typename Tb> inline auto max(Ta a, Tb b) { return (a >= b) ? a : b; }

// REFER: https://en.cppreference.com/w/cpp/header/string_view
// IMPORTANT: "MyStringView" does NOT handle reverse iterators
//            However, we can use a bool variable to store
//            whether MyStringView is storing reverse string or not
//            Accordingly modify "operator==" and "operator<<" methods
struct MyStringView {
	const char *ptr;
	const size_t len;
	// --- Constructors ---
	MyStringView(const char *aPtr): ptr{aPtr}, len(std::strlen(aPtr)) {}

	explicit MyStringView(const char *aPtr, const size_t aLen): ptr{aPtr}, len{aLen} {}

	template<typename MyStringViewOrString>
	explicit MyStringView(const MyStringViewOrString &aStr, const size_t aIdxStart=0,
		const size_t aLen=numeric_limits<size_t>::max()): ptr{aStr.data() + aIdxStart},
		len{min(aLen, aStr.size() - min(aIdxStart, aStr.size()))} {}

	template<typename T>
	explicit MyStringView(const T first, const T last): ptr{&(*first)},
		len{static_cast<size_t>(max(0,std::distance(first,last)))} {}
	// --- Basic Methods ---
	size_t size() const { return len; }
	const char* data() const { return ptr; }  // "ptr" will NOT always be null terminated
    const char& operator[](size_t idx) const { return ptr[idx]; }
	bool operator==(const MyStringView &aMSV) const {
		if (len != aMSV.len) return false;
		if (ptr == aMSV.ptr) return true;
		for (size_t i = 0; i < len; ++i) if (ptr[i] != aMSV.ptr[i]) return false;
		return true;
	}
	bool operator<(const MyStringView &aMSV) const {
		if (this->len == aMSV.len) {
			for (int i = 0; i < len; ++i) {
				if (this->ptr[i] == aMSV.ptr[i]) continue;
				return this->ptr[i] < aMSV.ptr[i];
			}
			return false;  // because "a" equals "b"
		}
		return this->len < aMSV.len;
	}
};

// REFER: https://stackoverflow.com/questions/19371845/using-cout-to-print-the-entire-contents-of-a-character-array
std::ostream& operator<<(std::ostream& os, const MyStringView &aMSV) {
	os.write(aMSV.ptr, aMSV.len);
	return os;
}

// REFER: https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
struct MyStringViewKeyHasher {
	std::size_t operator()(const MyStringView& k) const {
		using std::hash;
		return hash<int>()(k.len) ^ (((k.len > 0) ? (*k.ptr) : 0) << 20);
	}
};

// -----------------------------------------------------------------------------------------

int main () {
	string s = "0123456789abcdefg";
	cout << MyStringView(s, 1, 3) << endl;
	cout << MyStringView(s, 5, 3) << endl;
	cout << MyStringView(s, 10, 3) << endl;
	cout << MyStringView(s, 100, 3) << endl;
	cout << MyStringView(s, 2, 10) << endl;
	cout << MyStringView(s, 2, 30) << endl;
	cout << MyStringView(MyStringView(s, 2, 30), 8) << endl;
	cout << MyStringView(s.rbegin(), s.rend()) << endl;  // WARNING: creates problem
	cout << "---\n";

	string s2 = "abcdefg";
	string s3 = "abc";
	db(MyStringView(s, 10, 3) == MyStringView(s2, 0, 3));  // abc == abc ?
	db(MyStringView(s, 10, 3) == MyStringView(s2, 0, 4));  // abc == abcd ?
	db(MyStringView(s, 10, 3) == MyStringView(s2.begin(), s2.begin() + 3));  // abc == abc ?
	db(MyStringView(s, 10, 3) == MyStringView(s3.begin(), s3.end()));        // abc == abc ?

	db(MyStringView(s,0,0)=="");
	db(MyStringView(s,0,0)==MyStringView(""));

	unordered_map<MyStringView, string, MyStringViewKeyHasher> m;
	m[MyStringView(s, 1, 3)] = "123";
	m[MyStringView(s, 5, 3)] = "567";
	m[MyStringView(s, 10, 3)] = "abc";
	db(m);

	map<MyStringView, string> m2;
	m2[MyStringView(s, 1, 3)] = "123";
	m2[MyStringView(s, 5, 3)] = "567";
	m2[MyStringView(s, 10, 3)] = "abc";
	db(m2);

	return 0;
}
