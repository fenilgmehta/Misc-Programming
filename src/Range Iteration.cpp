#include <iostream>
using namespace std;

//####################################################################################################################

// REFER: https://stackoverflow.com/questions/33556196/c11-range-based-loop-how-does-it-really-work
// REFER: https://github.com/whoshuu/cpp_range/blob/master/include/range.h
// REFER: https://gist.github.com/asottile/5294000

// NOTE: These struct's generate the same Assembly code as a simple for loop
//       when compiled with -O2 flag using `x86-64 gcc v7.1 and v10.1`

template<typename S>
struct range_iterator{
    typedef std::random_access_iterator_tag iterator_category;
    typedef S value_type;       // int
    typedef S difference_type;  // int
    typedef range_iterator<S>* pointer;         // range_iterator<int>*
    typedef range_iterator<S>& reference;       // range_iterator<int>&
    typedef const range_iterator<S>& const_reference;       // const range_iterator<int>&
    
    S current;
    const S step;

    inline range_iterator(const S &f1, const S &s1): current{f1}, step{s1} {}
    inline bool operator!=(const_reference zz) const {return (step >= 0) ? (current < zz.current) : (current > zz.current);}
    inline reference operator++(){ current += step; return *this; }  // current = (current <= l) ? current : l;
    inline reference operator+=(const difference_type& val) { current+=step*val; return *this; }
    inline difference_type operator-(const range_iterator<S>& zz) const { return (current-zz.current + (step-1))/step; }
    inline const value_type& operator*() const { return current; }
    inline pointer operator->() { return this; }
    inline reference operator=(const_reference zz) { current = zz.current; return *this; }
};

template<typename T>
struct range{
    T f1, l1, s1;
    inline explicit range(T last): f1{0}, l1{last}, s1{1} {}
    inline explicit range(T first, T last, T step=1): f1{first}, l1{last}, s1{step} {}
    inline range_iterator<T> begin() const { return range_iterator<T>(f1, s1); }
    inline const range_iterator<T> end() const { return range_iterator<T>(l1, s1); }
};

//####################################################################################################################

int main(){
    cout << endl << "range<int>(20) = ";
    for(int i: range<int>(20))
        cout << i << ", ";

    cout << endl << "range<int>(10, 20) = ";
    for(int i: range<int>(10, 20))
        cout << i << ", ";

    cout << endl << "range<int>(10, 20, 3) = ";
    for(int i: range<int>(10, 20, 3))
        cout << i << ", ";

    cout << endl << "range<int>(20, 10, -1) = ";
    for(int i: range<int>(20, 10, -1))
        cout << i << ", ";

    cout << endl << "range<int>(20, 10, -3) = ";
    for(int i: range<int>(20, 10, -3))
        cout << i << ", ";

    cout << endl << "range<int>(20, 10, 1) = ";
    for(int i: range<int>(20, 10, 1))
        cout << i << ", ";

    cout << endl << "range<int>(20, 10, 3) = ";
    for(int i: range<int>(20, 10, 3))
        cout << i << ", ";

    cout << "\n\n";
    range<long> a(10);
    cout << endl;
    cout << "** "; for(long i: a) cout << i << ", "; cout << endl;
    cout << "** "; for(const long &i: a) cout << i << ", "; cout << endl;
    cout << "** "; for(long i: a) cout << ++i << ", "; cout << endl;

    cout << endl;
    return 0;
}