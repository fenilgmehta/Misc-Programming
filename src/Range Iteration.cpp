#include <iostream>
//####################################################################################################################

// REFER: https://stackoverflow.com/questions/33556196/c11-range-based-loop-how-does-it-really-work
// REFER: https://github.com/whoshuu/cpp_range/blob/master/include/range.h
// REFER: https://gist.github.com/asottile/5294000

// NOTE: These struct's generate the same Assembly code as a simple for loop
//       when compiled with -O2 flag using `x86-64 gcc v7.1 and v10.1`

namespace NumericRange{
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
        inline difference_type operator-(const_reference zz) const { return (current-zz.current + (step-1))/step; }
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
}
using namespace NumericRange;

//####################################################################################################################

/* This struct is useful when you want to iterate
 * through a slice of a container
 */
namespace ContainerRange{
    template<typename Iter>
    struct rangeiter_iterator{
        Iter f, l;
        inline rangeiter_iterator(Iter first, Iter last): f{first}, l{last} {}
        inline auto begin() {return f;}
        inline auto end() {return l;}
        inline auto reverse() {
            auto f_new = make_reverse_iterator(l);
            return rangeiter_iterator<decltype(f_new)>(make_reverse_iterator(l), make_reverse_iterator(f));
        }
        template<typename T>
        friend std::istream& operator >> (std::istream &is, rangeiter_iterator<T> &&ri);
        template<typename T>
        friend std::istream& operator >> (std::istream &is, rangeiter_iterator<T> &ri);
    };

    template<typename T>
    std::istream& operator >> (std::istream &is, rangeiter_iterator<T>&& ri) { for(auto &i: ri) std::cin>>i; return is; }

    template<typename T>
    std::istream& operator >> (std::istream &is, rangeiter_iterator<T>& ri) { for(auto &i: ri) std::cin>>i; return is; }

    template<typename ContainerC>
    auto rangeiter(ContainerC &c) { return rangeiter_iterator(begin(c), end(c)); }

    template<typename ContainerC, typename SizeS>
    auto rangeiter(ContainerC &c, SizeS count) { 
        auto f = begin(c);
        return rangeiter_iterator<decltype(f)>(f, next(f, count));
    }

    template<typename ContainerC, typename SizeS>
    auto rangeiter(ContainerC &c, SizeS count_first, SizeS count_last) { 
        auto f = begin(c);
        return rangeiter_iterator<decltype(f)>(next(f, count_first), next(f, count_last));
    }

    template<typename Iter>
    auto rangeiter(Iter first, Iter last) {
        return rangeiter_iterator<Iter>(first, last);
    }
}
using namespace ContainerRange;


//####################################################################################################################

#define loop(iname, params...) for(auto &iname: range<int64_t>(params))
#define loopiter(iname, params...) for(auto &iname: rangeiter(params))
#define loopiterR(iname, params...) for(auto &iname: rangeiter(params).reverse())

//####################################################################################################################

/* If any number 123456789 is passed, then it will iterate as { 9,8,7,6,5,4,3,2,1 } */
template<typename T>
struct digits{
    T n;
    explicit digits(const T &num): n{num} {}
    digits<T>& begin() {return *this;}
    digits<T>& end(){return *this;}
    bool operator != (digits<T> &other) {return this->n != 0;}
    T operator *(){return n % 10;}
    void operator++() {n /= 10;}
};

//####################################################################################################################

#include <vector>
using namespace std;

int main(){
    cout << endl << "loop(5)              = ";  loop(i, 5)            cout << i << ", ";
    cout << endl << "loop(10, 20)         = ";  loop(i, 10, 20)       cout << i << ", ";
    cout << endl << "loop(10, 18, 3)      = ";  loop(i, 10, 18, 3)    cout << i << ", ";
    cout << endl << "loop(19, 11, -2)     = ";  loop(i, 19, 11, -2)   cout << i << ", ";

    // WORKS :)
    cout << endl << "** loop(100, 10000000000000, 1000000000000)       = " ;
    loop(i, 100, 10000000000000, 1000000000000) cout << i << ", ";
    cout << endl << "** loop(100l, 10000000000000l, 1000000000000l)    = " ;
    loop(i, 100l, 10000000000000l, 1000000000000l) cout << i << ", ";
    cout << endl << "** loop(100ll, 10000000000000ll, 1000000000000ll) = " ;
    for(auto &i: range<int64_t>(100, 10000000000000, 1000000000000)) cout << i << ", ";

    cout << "\n\n----------------------------------------\n";

    // Following examples show the good ways to use the structs defined above
    cout << endl << "range<int>(5)              = "; for(auto i: range<int>(5))             cout << i << ", ";
    cout << endl << "range<int>(10, 20)         = "; for(auto i: range<int>(10, 20))        cout << i << ", ";
    cout << endl << "range<int>(10, 18, 3)      = "; for(auto i: range<int>(10, 18, 3))     cout << i << ", ";
    cout << endl << "range<int>(19, 11, -2)     = "; for(auto i: range<int>(19, 11, -2))    cout << i << ", ";

    cout << "\n\n";
    range<long> a(10);
    cout << "\n** "; for(long i: a)           cout << i << ", ";
    cout << "\n** "; for(const long &i: a)    cout << i << ", ";
    cout << "\n** "; for(long i: a)           cout << ++i << ", ";

    cout << "\n\n----------------------------------------\n";

    vector<int> arr = {80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95};
    // cin >> rangeiter(arr, 3);

    cout << endl << "loopiter(arr)             = ";  loopiter(i, arr)           cout << i << ", ";
    cout << endl << "loopiter(arr, 6)          = ";  loopiter(i, arr, 6)        cout << i << ", ";
    cout << endl << "loopiter(arr, 8, 13)      = ";  loopiter(i, arr, 8, 13)    cout << i << ", ";
    cout << endl << "loopiterR(arr, 8, 13)     = ";  loopiterR(i, arr, 8, 13)   cout << i << ", ";
    cout << endl;
    cout << endl << "rangeiter(arr)                  = "; for(auto &i: rangeiter(arr))          cout << i << ", ";
    cout << endl << "rangeiter(arr, 6)               = "; for(auto &i: rangeiter(arr, 6))       cout << i << ", ";
    cout << endl << "rangeiter(arr, 8, 13)           = "; for(auto &i: rangeiter(arr, 8, 13))   cout << i << ", ";
    cout << endl << "rangeiter(arr, 8, 13)''         = "; for(auto &i: rangeiter(arr, 8, 13).reverse().reverse()) cout << i << ", ";
    cout << endl << "rangeiter(arr, 8, 13).reverse() = "; for(auto &i: rangeiter(arr, 8, 13).reverse()) cout << i << ", ";

    cout << "\n\n";
    return 0;
}