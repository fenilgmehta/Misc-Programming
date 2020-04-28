#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cassert>
#include <sstream>

//####################################################################################################################

/*
 *
 * NOTE: This implementation of infinite size unsigned integers
 *       is inspired from Python infinite size integers and their
 *       use in Competitive Programming.
 *
 * WORKING: The number is divided into equal parts of 30 bits
 *          and stored in a vector<uint32_t>
 *          Least Significant Bit is always stored at index 0.
 *
 * REFER: https://rushter.com/blog/python-integer-implementation/
 * REFER: https://github.com/python/cpython/blob/master/Include/longintrepr.h
 * REFER: https://github.com/python/cpython/blob/master/Include/longobject.h
 * REFER: https://github.com/python/cpython/blob/master/Objects/longobject.c
 *
 * NOTE: Methods which can be removed from uBigInt to reduce the size of code
 *       without breaking the code are:
 *       • operator <<=
 *       • operator >>=
 *       • to_hex()
 *       • to_dec()
 *       • to_uint64_t()
 *       • %, %=
 *       • compare(...), ==, !=, >=, >, <=, <
 *       • compare(...), operator -, -=
 * NOTE: The methods which are in same line have interdependency. So,
 * if you remove any method, then please remove everything to its right.
 * 
 */

struct uBigInt {
#define DECIMAL_BASE ((UINT_BASE) 1000000000)
#define BIT_SHIFT 30
#define BIT_SHIFT_BY_2 15
#define BIT_BASE ((UINT_BASE)1073741824)
#define BIT_MASK ((UINT_BASE)1073741823)
#define BIT_BASE_BARE 1073741824

    using UINT_COMPUTE = uint64_t;
    using UINT_BASE = uint32_t;

    std::vector<UINT_BASE> n;

    // REFER: https://github.com/python/cpython/blob/master/Objects/longobject.c#L2094
    unsigned char hexchar_to_int[256] = {
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 37, 37, 37, 37, 37, 37,
            37, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
            25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 37, 37, 37, 37, 37,
            37, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
            25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
            37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
    };

    /* Valid base = 2,8,10,16, any number <= 36
     * Unexpected results if anything other than [0-9][a-zA-Z] is there in std::string
     * The conversion process is case in-sensitive, i.e. [a-z] == [A-Z]. Example:
     *     • af == aF == Af == AF, where base is 16
     * */
    explicit uBigInt(const std::string &t_n, const int32_t &base) {
        n.clear();
        uBigInt mul(1);
        for (int32_t i = t_n.size() - 1; i >= 0; --i) {
            (*this) += mul * hexchar_to_int[t_n[i]];
            mul *= base;
        }
        if (n.empty()) n.push_back(0);
    }

    explicit uBigInt(uint64_t t_n = 0) {
        n.clear();
        while (t_n > 0) {
            n.push_back(t_n & BIT_MASK);
            t_n >>= BIT_SHIFT;
        }
    }

    /* Copy constructor */
    uBigInt(const uBigInt &t_n) { this->n = t_n.n; }

    // ------------------------------------------------
    [[nodiscard]] int32_t compare(const uBigInt &t_n) const {
        if (n.size() < t_n.n.size()) return -1;
        if (n.size() > t_n.n.size()) return 1;

        // Last index stores the Most Significant Bit
        for (int32_t i = n.size() - 1; i >= 0; --i) {
            if (n[i] < t_n.n[i]) return -1;
            if (n[i] > t_n.n[i]) return 1;
        }
        return 0;
    }

    [[nodiscard]] bool operator==(const uBigInt &t_n) const { return this->compare(t_n) == 0; }

    [[nodiscard]] bool operator!=(const uBigInt &t_n) const { return this->compare(t_n) != 0; }

    [[nodiscard]] bool operator>=(const uBigInt &t_n) const { return this->compare(t_n) >= 0; }

    [[nodiscard]] bool operator>(const uBigInt &t_n) const { return this->compare(t_n) > 0; }

    [[nodiscard]] bool operator<=(const uBigInt &t_n) const { return this->compare(t_n) <= 0; }

    [[nodiscard]] bool operator<(const uBigInt &t_n) const { return this->compare(t_n) < 0; }

    // ------------------------------------------------
    /* Inplace addition */
    uBigInt &operator+=(const uBigInt &t_n) {
        const int32_t min_len = std::min(n.size(), t_n.n.size());
        const int32_t max_len = std::max(n.size(), t_n.n.size());
        n.reserve(max_len + 1);

        UINT_COMPUTE c = 0;
        for (int32_t i = 0; i < min_len; ++i) {
            c = n[i] + t_n.n[i] + c;
            n[i] = c & BIT_MASK;
            c >>= BIT_SHIFT;
        }

        if (n.size() > t_n.n.size()) {
            for (int32_t i = min_len; i < max_len; ++i) {
                c = n[i] + c;
                n[i] = (c & BIT_MASK);
                c >>= BIT_SHIFT;
            }
        } else {
            for (int32_t i = min_len; i < max_len; ++i) {
                c = t_n.n[i] + c;
                n.push_back(c & BIT_MASK);
                c >>= BIT_SHIFT;
            }
        }

        if (c) n.push_back(c);
        return *this;
    }

    /* Inplace subtraction */
    uBigInt &operator-=(const uBigInt &t_n) {
        int32_t diff = this->compare(t_n);
        if (diff < 0) {
            std::cerr << "WARNING: -= called (a-b) but (a < b)\n";
            return *this;
        }

        if (diff == 0) {
            this->n.clear();
            this->n.push_back(0);
            return *this;
        }
        int32_t j, min_len = t_n.n.size();
        UINT_COMPUTE calc;
        for (int32_t i = 0; i < min_len; ++i) {
            calc = n[i];
            if (n[i] < t_n.n[i]) {
                calc += BIT_BASE_BARE;
                for (j = i + 1; n[j] == 0; ++j) {
                    n[j] = BIT_MASK;
                }
                --n[j];
            }
            n[i] = static_cast<UINT_BASE>(calc - t_n.n[i]);
        }
        return *this;
    }

    /* Inplace multiplication */
    uBigInt &operator*=(const UINT_BASE &t_n) {
        if (t_n == 0) {
            n.clear();
            n.push_back(0);
            return *this;
        }
        if (t_n > BIT_MASK) return (*this) *= uBigInt(t_n);
        UINT_COMPUTE c = 0;
        for (UINT_BASE &i: this->n) {
            c += static_cast<UINT_COMPUTE>(i) * t_n;
            i = static_cast<UINT_BASE>(c & BIT_MASK);
            c >>= BIT_SHIFT;
        }
        while (c) {
            this->n.push_back(static_cast<UINT_BASE>(c & BIT_MASK));
            c >>= BIT_SHIFT;
        }
        return *this;
    }

    // ------------------------------------------------
    inline uBigInt operator+(uBigInt t_n) const { return t_n += (*this); }

    inline uBigInt operator-(uBigInt t_n) const { return t_n -= (*this); }

    inline uBigInt operator*(const UINT_BASE &t_n) const { return uBigInt(*this) *= t_n; }

    // ------------------------------------------------
    uBigInt &operator*=(const uBigInt &t_n) {
        *this = (*this) * t_n;
        return *this;
    }

    uBigInt operator*(const uBigInt &t_n) const {
        uBigInt r(0), temp(*this);
        for (int32_t i = 0; i < t_n.n.size(); ++i) {
            r += temp * t_n.n[i];
            temp.n.insert(next(temp.n.begin(), i), 0);
        }
        return r;
    }

    // ------------------------------------------------

    UINT_BASE operator%(const UINT_BASE &t_mod) const {
        UINT_COMPUTE c = 0;
        for (auto i = n.rbegin(); i != n.rend(); advance(i, 1)) {
            c = (
                        (((c << BIT_SHIFT_BY_2) % t_mod) << BIT_SHIFT_BY_2) % t_mod
                        +
                        (*i) % t_mod
                ) % t_mod;
        }
        return (UINT_BASE) c;
    }

    uBigInt &operator%=(const UINT_BASE &t_mod) {
        UINT_BASE mod_val = (*this) % t_mod;
        this->n.clear();
        this->n.push_back(mod_val & BIT_MASK);
        if (mod_val > BIT_MASK) this->n.push_back(mod_val >> BIT_SHIFT);
        return *this;
    }

    uBigInt &operator<<=(UINT_BASE t_n) {
        if (n.empty() || (n.size() == 1 && n[0] == 0)) return *this;
        n.insert(n.begin(), t_n / BIT_SHIFT, 0);

        UINT_COMPUTE c = 0;
        t_n %= BIT_SHIFT;
        for (UINT_BASE &i: n) {
            c = (c >> BIT_SHIFT) + (static_cast<UINT_COMPUTE>(i) << t_n);
            i = static_cast<UINT_BASE>(c & BIT_MASK);
        }
        if (c >> BIT_SHIFT) n.push_back(c >> BIT_SHIFT);
        return *this;
    }

    uBigInt &operator>>=(UINT_BASE t_n) {
        size_t remove_0 = t_n / BIT_SHIFT;
        if (remove_0 >= n.size()) {
            n.clear();
            n.push_back(0);
            return *this;
        }
        n.erase(n.begin(), next(n.begin(), remove_0));

        UINT_COMPUTE c;
        t_n %= BIT_SHIFT;
        if (t_n == 0) return *this;
        for (int32_t i = 0; i < (n.size() - 1); ++i) {
            n[i] = (
                           (((UINT_COMPUTE) n[i + 1] << BIT_SHIFT) + n[i])
                                   >> t_n
                   ) & BIT_MASK;
        }
        n[n.size() - 1] >>= t_n;
        if ((*n.rbegin()) == 0 && n.size() != 0) n.pop_back();
        return *this;
    }

    // REFER: https://github.com/python/cpython/blob/master/Objects/longobject.c#L1680
    [[nodiscard]] std::string to_dec() const {
        if (n.empty()) return "0";
        if (n.size() == 1) return std::to_string(n[0]);

        std::vector<UINT_BASE> res10, mul10 = {1};
        res10.reserve(n.size() + 8);

        UINT_COMPUTE calc;
        for (int32_t i = 0; i < n.size(); ++i) {
            // Multiply n[i] with mul10 and add to res10
            calc = 0;
            for (int32_t j = 0, max_size = std::max(res10.size(), mul10.size());
                 j < max_size; ++j) {
                calc += ((j < res10.size()) ? res10[j] : 0)
                        +
                        ((j < mul10.size()) ? (static_cast<UINT_COMPUTE>(n[i]) * mul10[j]) : 0);
                if (j < res10.size()) res10[j] = static_cast<UINT_BASE>(calc % DECIMAL_BASE);
                else res10.push_back(static_cast<UINT_BASE>(calc % DECIMAL_BASE));
                calc /= DECIMAL_BASE;
            }
            while (calc) {
                res10.push_back(static_cast<UINT_BASE>(calc % DECIMAL_BASE));
                calc /= DECIMAL_BASE;
            }

            // (1<<30) * mul10
            if (i + 1 == n.size()) continue;
            calc = 0;
            for (UINT_BASE &k : mul10) {
                calc += static_cast<UINT_COMPUTE>(BIT_BASE_BARE) * k;
                k = static_cast<UINT_BASE>(calc % DECIMAL_BASE);
                calc /= DECIMAL_BASE;
            }
            while (calc) {
                mul10.push_back(static_cast<UINT_BASE>(calc % DECIMAL_BASE));
                calc /= DECIMAL_BASE;
            }
        }
        std::stringstream r1;
        r1 << res10[res10.size() - 1];
        for (int32_t i = res10.size() - 2; i >= 0; --i) {
            r1 << std::setfill('0') << std::setw(9) << res10[i];
        }
        std::string r2 = r1.str();
        while ((*r2.rend()) == '0') r2.pop_back();
        return r2;
    }

    /* returns: HEX value of uBigInt */
    [[nodiscard]] std::string to_hex() const {
        std::stringstream r;
        UINT_COMPUTE calc = 0, j = 0;
        for (int32_t i = 0; i < n.size(); ++i) {
            calc += (n[i] << ((i & 1) ? (2) : 0));
            for (j = 7 + (i & 1); j; --j) {
                r << std::hex << (calc & 15);
                calc >>= 4;
            }
        }
        if (n.size() & 1) r << std::hex << calc;

        std::string r1 = r.str();
        while ((*r1.rbegin()) == '0') r1.pop_back();
        if (r1.size() == 0) r1.push_back('0');
        std::reverse(r1.begin(), r1.end());
        return r1;
    }

    /* If uBigInt has more than 64 bits, then they are dropped */
    [[nodiscard]] uint64_t to_uint64_t() const {
        uint64_t c = 0;
        c = n[0] +
            ((n.size() >= 2) ? static_cast<int64_t>(n[1]) << 30 : 0) +
            ((n.size() >= 3) ? static_cast<int64_t>(n[2]) << 60 : 0);
        return c;
    }

#undef DECIMAL_BASE
#undef BIT_SHIFT
#undef BIT_SHIFT_BY_2
#undef BIT_BASE
#undef BIT_MASK
#undef BIT_BASE_BARE
};

//####################################################################################################################

/* Optimized implementation for calculation of large
 * factorials using Divide and Conquer paradigm.
 * */
uBigInt factorial(int32_t n, int32_t low = 1) {
    if ((n - low + 1) <= 10) {
        uBigInt r(1);
        for (int32_t i = low; i <= n; ++i) r *= i;
        return r;
    }
    uBigInt temp = factorial((n + low) / 2, low);
    return temp *= factorial(n, (n + low) / 2 + 1);
}

//####################################################################################################################

int main() {
    // ubi = unsigned BigInt = uBigInt

    // ----------------

    std::cout << "\n*** ubi1 = uBigInt(\"964ec395dc2\", 16)" << std::endl;
    uBigInt ubi1("964ec395dc2", 16);
    std::cout << "ubi1.to_hex() = " << ubi1.to_hex() << std::endl;
    std::cout << "ubi1.to_dec() = " << ubi1.to_dec() << std::endl;
    assert(ubi1.to_hex() == "964ec395dc2");
    assert(ubi1.to_dec() == "10329064562114");

    // ----------------

    std::cout << "\n*** ubi2 = uBigInt(\"1b30964ec395dc24069528d54bbda40d16e966ef9a70eb21b5b2943a321cdf10391745570cca9420c6ecb3b72ed2ee8b02ea2735c61a000000000000000000000000\", 16)" << std::endl;
    uBigInt ubi2(
            "1b30964ec395dc24069528d54bbda40d16e966ef9a70eb21b5b2943a321cdf10391745570cca9420c6ecb3b72ed2ee8b02ea2735c61a000000000000000000000000",
            16
    );
    std::cout << "ubi2.to_hex() = " << ubi2.to_hex() << std::endl;
    std::cout << "ubi2.to_dec() = " << ubi2.to_dec() << std::endl;
    assert(ubi2.to_hex() == "1b30964ec395dc24069528d54bbda40d16e966ef9a70eb21b5b2943a321cdf10391745570cca9420c6ecb3b72ed2ee8b02ea2735c61a000000000000000000000000");
    assert(ubi2.to_dec() == "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");

    // ----------------

    std::cout << "\n*** ubi3 = 987654321" << std::endl;
    uBigInt ubi3(987654321);

    ubi3 <<= 456;
    std::cout << "\nubi3 <<= 456" << std::endl;
    std::cout << "(987654321 << 456) = ubi3.to_hex() = " << ubi3.to_hex() << std::endl;
    std::cout << "(987654321 << 456) = ubi3.to_dec() = " << ubi3.to_dec() << std::endl;
    assert(ubi3.to_hex() == "3ade68b1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    assert(ubi3.to_dec() == "183773544120495059652713912957122959980023508983590198307418181514216717426575717623178056629498552242804196484936870735925836825987814974036115456");

    ubi3 >>= 456;
    std::cout << "\nubi3 >>= 456" << std::endl;
    std::cout << "((987654321 << 456) >> 456) = ubi3.to_hex() = " << ubi3.to_hex() << std::endl;
    std::cout << "((987654321 << 456) >> 456) = ubi3.to_dec() = " << ubi3.to_dec() << std::endl;
    assert(ubi3.to_hex() == "3ade68b1");  // (987654321, base=10) == (3ade68b1, base=16)
    assert(ubi3.to_dec() == "987654321");  // (987654321, base=10) == (3ade68b1, base=16)

    ubi3 >>= 456;
    std::cout << "\nubi3 >>= 456" << std::endl;
    std::cout << "(((987654321 << 456) >> 456) >> 456) = ubi3.to_hex() = " << ubi3.to_hex() << std::endl;
    std::cout << "(((987654321 << 456) >> 456) >> 456) = ubi3.to_dec() = " << ubi3.to_dec() << std::endl;
    assert(ubi3.to_hex() == "0");
    assert(ubi3.to_dec() == "0");

    // ----------------

    std::cout << "\n*** ubi4 = 100!" << std::endl;
    uBigInt ubi4(1);
    for (int64_t i = 2; i <= 100; ++i) ubi4 *= i;
    std::cout << "100! = ubi4.to_hex() = " << ubi4.to_hex() << std::endl;
    std::cout << "100! = ubi4.to_dec() = " << ubi4.to_dec() << std::endl;
    assert(ubi4.to_hex() == "1b30964ec395dc24069528d54bbda40d16e966ef9a70eb21b5b2943a321cdf10391745570cca9420c6ecb3b72ed2ee8b02ea2735c61a000000000000000000000000");
    assert(ubi4.to_dec() == "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");

    // ----------------

    std::cout << "\n*** ubi5 = 34562!, ubi6 = 72583!" << std::endl;
    uBigInt ubi5(1), ubi6(1);
    int fact1 = 34562, fact2 = 72583;
    for (int64_t i = 2; i <= fact1; ++i) ubi5 *= i;
    for (int64_t i = 2; i <= fact2; ++i) ubi6 *= i;
    std::cout << "(34562! * 72583!) % 234598791 = (ubi5 * ubi6) % (234598791) = " << ((ubi5 * ubi6) % (234598791)) << std::endl;
    assert(((ubi5 * ubi6) % (234598791)) == 34348776);

    std::cout << std::boolalpha << "assert(ubi5 == factorial(34562)) = " << (ubi5 == factorial(34562)) << std::endl;
    assert(ubi5 == factorial(34562));
    std::cout << std::boolalpha << "assert(ubi6 == factorial(72583)) = " << (ubi6 == factorial(72583)) << std::endl;
    assert(ubi6 == factorial(72583));
    std::cout << std::boolalpha << "assert(ubi5 < ubi6) = " << (ubi5 < ubi6) << std::endl;
    assert(ubi5 < ubi6);

    // ----------------

    std::cout << "\n*** `factorial(654321).to_dec()` gave the same result as `math.factorial(654321)` of Python 3.7.3" << std::endl;

    std::cout << std::endl;
    return 0;
}

/* PYTHON function for testing


import math
a,b=100,72583
a,b=math.factorial(a), math.factorial(b)
val = a
p=hex(val)[2:]
c=open('/home/student/Desktop/cppval_10000.txt','r').read().strip('\n').lstrip('0')
len(p), len(c), p[:10], c[:10], p==c, str(val)==c


def fun1(n,nmod):
  import math
  print(hex(math.factorial(n) % nmod))


def fun2(n, nstr):
  import math
  print(hex(math.factorial(n))[2:]==nstr)


def fun3(n, nstr):
  import math
  print('','',hex(math.factorial(n))[2:],'',nstr,'',sep='\n')


#-----------
def toint(vecc,base):
    from math import log2
    #vecc = [ 73741824, 1, ]
    #base = 10**9 # 2**30
    res, j = 0, 0
    for i in vecc:
        res += i * base**j
        j+=1
    print(f"res = {res}")
    print(f"res % (2**30) = {res % (2**30)}")
    print(f"log2(res) = {log2(res)}")
    print(f"log2(res) / 30 = {log2(res) / 30}")
    return res


def fix(vecc,num,base):
    res = []
    carry = 0
    for i in vecc:
        carry += i * num
        res.append(carry % base)
        carry //= base
    while carry > 0:
        res.append(carry % base)
        carry //= base
    return res



*/
