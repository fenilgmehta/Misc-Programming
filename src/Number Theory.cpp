#include <bits/stdc++.h> // This is all in one include library
using namespace std;
//------------------------------------------------
#define db(a) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<#a<<"\033[1;31m"<<" : "<<"\033[0m"<<a<<'\n'; cout.flush(); cerr.flush();}
#define dbiter(...) dbgIter(#__VA_ARGS__, __VA_ARGS__)
template <class T> void dbgIter(const char *sdbg, T a, T b) {cerr<<"\033[1;31m"<<"Debug: "<<"\033[0m"; cerr<<sdbg; cerr<<"\033[1;31m"<<" = "<<"\033[0m"; cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n"; cout.flush(); cerr.flush();}
#define endl '\n'       // WARNING: REMOVE this is working on interactive programs
#define int int32_t
#define long int64_t    // WARNING: REMOVE this when using `long double`

//####################################################################################################################

// NOT tested
template <int64_t mod=1000000007>
struct ModInt{
    int64_t v;
    ModInt(int64_t v1=0):v(v1){}
    static int64_t mod_pow(int64_t r,int64_t n,int64_t m=1000000007){
        int64_t re=1,d=r%m;
        if(n<0) (n%=m-1)+=m-1;
        for(;n;n/=2){
            if(n&1) (re*=d)%=m;
                (d*=d)%=m;
        }
        return re;
    }
    inline ModInt operator+(const ModInt &n)const{return v+n.v<mod ? v+n.v : v+n.v-mod;}
    inline ModInt operator-(const ModInt &n)const{return v-n.v<0 ? v-n.v+mod : v-n.v;}
    inline ModInt operator*(const ModInt &n)const{return int64_t(v)*n.v%mod;}
    inline ModInt operator/(const ModInt &n)const{return int64_t(v)*mod_pow(n.v%mod,-1,mod)%mod;}
    template<typename T>inline ModInt operator+(const T &n)const{return v+n<mod ? v+n : v+n-mod;}
    template<typename T>inline ModInt operator-(const T &n)const{return v-n<0 ? v-n+mod : v-n;}
    template<typename T>inline ModInt operator*(const T &n)const{return int64_t(v)*(n%mod)%mod;}
    template<typename T>inline ModInt operator/(const T &n)const{return int64_t(v)*mod_pow(n%mod,-1,mod)%mod;}
    inline ModInt& operator+=(const ModInt &n){v+=n.v; if(v>=mod) v-=mod; return *this;}
    inline ModInt& operator-=(const ModInt &n){v-=n.v; if(v<0) v+=mod; return *this;}
    inline ModInt& operator*=(const ModInt &n){v=int64_t(v)*n.v%mod; return *this;}
    inline ModInt& operator/=(const ModInt &n){v=int64_t(v)*mod_pow(n.v,-1,mod)%mod; return *this;}
    template<typename T>inline ModInt& operator+=(const T &n){v+=n; if(v>=mod) v-=mod; return *this;}
    template<typename T>inline ModInt& operator-=(const T &n){v-=n; if(v<0) v+=mod; return *this;}
    template<typename T>inline ModInt& operator*=(const T &n){v=int64_t(v)*n%mod; return *this;}
    template<typename T>inline ModInt& operator/=(const T &n){v=int64_t(v)*mod_pow(n,-1,mod)%mod; return *this;}
};

template<int mod> inline ostream& operator<<(ostream &os,const ModInt<mod> &n){return os<<n.v;};
template<int mod> inline ModInt<mod> operator+(const int64_t &n,const ModInt<mod> &m){return m.v+n<mod ? m.v+n : m.v+n-mod;}
template<int mod> inline ModInt<mod> operator-(const int64_t &n,const ModInt<mod> &m){return n-m.v<0 ? n-m.v+mod : n-m.v;}
template<int mod> inline ModInt<mod> operator*(const int64_t &n,const ModInt<mod> &m){return int64_t(m.v)*(n%mod)%mod;}
template<int mod> inline ModInt<mod> operator/(const int64_t &n,const ModInt<mod> &m){return int64_t(m.v)*ModInt<mod>::mod_pow(n%mod,-1,mod)%mod;}
template<int mod> inline ModInt<mod> mod_pow(ModInt<mod> r,int64_t n){ ModInt<mod> re(1); if(n<0)(n%=mod-1)+=mod-1; for(;n;n/=2){if(n&1) re*=r; r*=r;} return re;}


template<typename T>
struct ModularOperations{
    const T M;
    inline ModularOperations(const T m): M{m} {}
    inline T add(const T a, const T b) const { return mod(a%M + b%M); }
    inline T sub(const T a, const T b) const { return mod(a%M - b%M); }
    inline T mul(const T a, const T b) const { return mod((a%M) * (b%M)); }
    inline T div(const T a, const T b) const { return mod(a / b); }
    inline T mod(const T a) const { return (a>=0) ? (a%M) : (a%M + M); }
};

//####################################################################################################################

// Computes (val1 * val2) % mod
// This is useful when value of (val1 * val2) can not fit into int64_t but (val1 + val2) does fit into int64_t
int64_t simple_product(int64_t val1, int64_t val2, uint64_t mod){
    int64_t result = 0;
    int64_t base = val1 % mod;
    val2 %= mod;
    while(val2 > 0){
        if(val2 & 1){
            result = (result + base) % mod;
        }
        base = (base + base) % mod;
        val2 >>= 1;
    }
    return result;
}

// To compute base^exp under modulo "mod"
// NOTE: valid ONLY for +ve exponent
// Works with __int128 as well ---> #define int128 __int128
template<typename IntegerType>
IntegerType fast_exponent(IntegerType base, IntegerType exp, const IntegerType mod=1000000007) {
    IntegerType result = 1;
    base %= mod;
    while (exp > 0) {
        if ((exp & 1) == 1) {
            result = (result * base) % mod; // result = simple_product(result, base, mod);
        }
        base = (base * base) % mod; // base = simple_product(base, base, mod);
        exp >>= 1; //exp = exp / 2;
    }
    return result;
}

//####################################################################################################################

// ### IMPORTANT
// NOTE: you can also use __gcd(x,y) to get the GCD of "x" and "y", this function is present in algorithms. The header is mentioned below
// #include <algorithm>

template<typename IntegerType>
IntegerType gcd(IntegerType m, IntegerType n) {
    while (n != 0) {
        IntegerType t = m % n;  // m > n
        m = n;
        n = t;
	}
    return m;
}

// Iterative version of GCD
// For both +ve and -ve numbers
template<typename T>
T gcd_iterative(T a, T b) {
    if (a < 0) a = (-a);
    if (b < 0) b = (-b);

    while (b != 0) {
        // here (a > b) for each iteration
        a %= b;

        if (a == 0) return b;
        b %= a;
    }
    return a;
}

//##########################################################

/*

---> How does Extended Algorithm Work?
As seen above, x and y are results for inputs a and b,
    a.x + b.y = gcd     ----(1)

And x1 and y1 are results for inputs b%a and a
    (b%a).x1 + a.y1 = gcd

When we put b%a = (b - floor(a/b).a) in above, we get following.

    (b - floor(a/b).a).x1 + a.y1  = gcd

Above equation can also be written as below
    b.x1 + a.(y1 - floor(a/b).x1) = gcd     ---(2)

After comparing coefficients of 'a' and 'b' in (1) and (2), we get following
    x = y1 - floor(a/b) * x1
    y = x1


---> Other proofs
Euclids algorithm to find GCD
Proof 1: A number divides a and b if and only if it divides b and a – b.
Proof_2: Suppose a = xg, b = yg for some x, y, g. a%b = a-kb for some k. So a%b = a-kb = xg - kyg = g(x-ky). So g is still a divisor of both a%b and b
Hence GCD of a,b = b,a%b  (assume a>b)

---> How is Extended Algorithm Useful?
The extended Euclidean algorithm is particularly useful when a and b are coprime (or gcd is 1). Since x is the modular multiplicative inverse of “a modulo b”, and y is the modular multiplicative inverse of “b modulo a”. In particular, the computation of the modular multiplicative inverse is an essential step in RSA public-key encryption method.

*/

// Extended Euclidean algorithm also finds integer coefficients x and y such that: ax + by = gcd(a, b)
// Refer CLRS book for working
template<typename T, typename S>
T gcd_extended(T a, T b, S& x, S& y) {
    // Base Case
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }

    S x1, y1; // To store results of recursive call
    T gcd = gcd_extended(b % a, a, x1, y1);

    // Update x and y using results of recursive call
    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}


//####################################################################################################################

// REFERENCE: https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
// Function to find modular inverse of `a` under modulo `m`
// Works when `a` and `m` are coprime
int64_t mod_inverse(int64_t a, int64_t m) {
    int64_t x, y;
    int64_t g = gcd_extended(a, m, x, y);
    if (g == 1) {
        // m is added to handle negative x
        return ((x%m) + m) % m;
    } else {
        cerr << "ERROR: Modular Inverse doesn't exist for a=" << a << ", m=" << m << "\n";
        return -1;
    }
}

// NOT tested
int64_t mod_inverse_iterative(int64_t b, int64_t m){
    b%=m;
    int64_t x=0, y=1, r, q, a=m;
    while(b){
        q=a/b;
        r=a%b;
        a=b;
        b=r;
        r=x;
        x=y;
        y=r-q*y;
    }
    x+=m;
    return x%m;
}

// Function to find modular inverse of 'a' under modulo 'm'
// ASSUMPTION: 'm' is prime
// Fermat’s Little theorem, O(Log m) [Works when ‘m’ is prime]
int64_t mod_inverse_primeM(int64_t a, int64_t m) {
    int64_t g = __gcd(a, m);
    if (g != 1) {
        cerr << "ERROR: Inverse doesn't exist";
        return -1;
    } else {
        // If a and m are relatively prime, then modulo inverse is a^(m-2) mod m
        // cout << "Modular multiplicative inverse is " << power(a, m-2, m);
        return fast_exponent(a, m-2, m);
    }
}

//####################################################################################################################

// Function to return LCM of two numbers
/*
    Fastest way to find LCM(a, b) is = (a*b) / GCD(a, b)
    Proof:
    let a = xg and b = yg;  here g is the GCD(a, b)
    so LCM = xyg = xg * yg / g = (a*b) / GCD(a, b)
*/

// Requirements:
// #include<algorithm>
template<typename T>
T lcm(const T a, const T b) {
    return (a * b) / __gcd(a, b);
}


// Returns LCM of array elements
template<typename T>
int64_t lcm_array(T& arr, int32_t size) {
    // Initialize result
    int64_t ans = arr[0];

    // ans contains LCM of arr[0],..arr[i] after i'th iteration,
    for (int32_t i = 1; i < size; i++)
        ans = (arr[i] * ans) / __gcd(arr[i], ans);

    return ans;
}

//####################################################################################################################

//####################################################################################################################

namespace Fibonacci1{
// We consider the index of first Fibonacci number as 1
// We consider the index of second Fibonacci number as 2
// and so on

// The following link explains the concept in an excellent manner
// REFERENCE: http://fusharblog.com/solving-linear-recurrence-for-programming-contest/

#define mod 1000000007
    struct FibMatrix{int64_t a1,a2,b1,b2;};
    FibMatrix result, factor;

    inline FibMatrix matrix_mul(const FibMatrix &m1, const FibMatrix &m2/*, const int64_t mod*/) {
        // m1 = (m1 * m2) % mod
        return FibMatrix {
            ((m1.a1*m2.a1) % mod + (m1.a2*m2.b1) % mod) % mod,
            ((m1.a1*m2.a2) % mod + (m1.a2*m2.b2) % mod) % mod,
            ((m1.b1*m2.a1) % mod + (m1.b2*m2.b1) % mod) % mod,
            ((m1.b1*m2.a2) % mod + (m1.b2*m2.b2) % mod) % mod
        };
    }

    // This function will return the nth Fibonacci number such that the first two numbers in the series are fib1 and fib2
    int64_t fib(int64_t n, int64_t fib1=1, int64_t fib2=1/*, const int64_t mod*/) {
        if (n == 1) return (fib1 % mod);
        else if (n == 2) return (fib2 % mod);

        result = {1,0,0,1}, factor = {1,1,1,0};

        // NOTE: perform fast exponent
        // result = factor ^ (n-2)
        n-=2;
        while (n > 0) {
            if ((n & 1) == 1) { // condition: (exp % 2 == 1)
                result = matrix_mul(result, factor);  // result *= base;
            }
            factor = matrix_mul(factor, factor);
            n >>= 1;  // n = n / 2;
        }

        fib1 %= mod;
        fib2 %= mod;
        return (((fib2 * result.a1) % mod) + ((fib1 * result.a2) % mod)) % mod;
    }

    // this will return the Fibonacci number which was requested most recently
    int64_t get_last_fib(int64_t fib1=1, int64_t fib2=1){
        return (((fib2 * result.a1) % mod) + ((fib1 * result.a2) % mod)) % mod;
    }
#undef mod
};

//##########################################################

namespace Fibonacci2{
#define mod 1000000007
    int64_t a,b,c,d;
    int64_t ans[2]={};
    
    void fast_fib(int64_t n) {
        if(n == 0) {
            ans[0] = 0;
            ans[1] = 1;
            return;
        }
        fast_fib((n/2));
        a = ans[0];             // F(n)
        b = ans[1];             // F(n+1)
        c = 2*b - a;
        if(c < 0) c += mod;
        c = (a * c) % mod;      // F(2n)
        d = (a*a + b*b) % mod;  // F(2n + 1)
        if(n%2 == 0) {
            ans[0] = c;
            ans[1] = d;
        } else {
            ans[0] = d;
            ans[1] = c+d;
        }
    }

    inline int64_t fib(const int64_t n, const int64_t fib1=1, const int64_t fib2=1){
        switch(n){
            case 0: return 0;
            case 1: return fib1;
            case 2: return fib2;
        }
        fast_fib(n-2);
        return ((ans[0]*fib1)%mod+(ans[1]*fib2)%mod)%mod;
    }
#undef mod
}

//####################################################################################################################

template<typename IntegerType>
inline bool is_power_of_2(const IntegerType n){
    return (n > 0) && ((n & (n-1))==0);
}

template<typename IntegerType>
IntegerType next_power_of_2(const IntegerType n) {
    IntegerType p = 1;
    if (n && !(n & (n-1)))
        return n;

    while (p < n)
        p <<= 1;

    return p;
}

//####################################################################################################################

int main() {
    cout << endl;

    cout << "__gcd(36,48) = " << __gcd(36,48) << endl;
    cout << endl;

    int t1=4, t2=7;    
    cout << "1st Fib(4,7) = " << Fibonacci1::fib(1,t1,t2) << endl;
    cout << "2nd Fib(4,7) = " << Fibonacci1::fib(2,t1,t2) << endl;
    cout << "3rd Fib(4,7) = " << Fibonacci1::fib(3,t1,t2) << endl;
    cout << "4th Fib(4,7) = " << Fibonacci1::fib(4,t1,t2) << endl;
    cout << "5th Fib(4,7) = " << Fibonacci1::fib(5,t1,t2) << endl;
    cout << endl;

    cout << boolalpha << "is_power_of_2(0) = " << is_power_of_2(0) << endl;
    cout << boolalpha << "is_power_of_2(1) = " << is_power_of_2(1) << endl;
    cout << boolalpha << "is_power_of_2(2) = " << is_power_of_2(2) << endl;
    cout << boolalpha << "is_power_of_2(3) = " << is_power_of_2(3) << endl;
    cout << boolalpha << "is_power_of_2(4) = " << is_power_of_2(4) << endl;
    cout << boolalpha << "is_power_of_2(5) = " << is_power_of_2(5) << endl;
    cout << boolalpha << "is_power_of_2(6) = " << is_power_of_2(6) << endl;
    cout << endl;

    cout << "next_power_of_2(0) = " << next_power_of_2(0) << endl;
    cout << "next_power_of_2(1) = " << next_power_of_2(1) << endl;
    cout << "next_power_of_2(2) = " << next_power_of_2(2) << endl;
    cout << "next_power_of_2(3) = " << next_power_of_2(3) << endl;
    cout << "next_power_of_2(4) = " << next_power_of_2(4) << endl;
    cout << "next_power_of_2(13) = " << next_power_of_2(13) << endl;
    cout << "next_power_of_2(16) = " << next_power_of_2(16) << endl;
    cout << endl;

    return 0;
}
