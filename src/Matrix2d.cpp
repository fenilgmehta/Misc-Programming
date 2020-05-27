#include <iostream>
#include <cstdint>
#include <sstream>
#include <stdexcept>
using namespace std;

#define int int32_t

//####################################################################################################################

#define LOCAL

template<typename T>
struct Matrix2d{
#define LOCAL_CHECK_RANGE if (i1 < 0 || d1 <= i1 || i2 < 0 || d2 <= i2) { throw std::invalid_argument("EXCEPTION: Out of bound on arr["+to_string(d1)+"]["+to_string(d2)+"] ---> " + to_string(i1) + ", " + to_string(i2)); }

    T *arr;
    long arr_size, d1, d2;

    template<typename S>
    Matrix2d(const S &t_d1, const S &t_d2): arr_size{t_d1 * t_d2}, d1{t_d1}, d2{t_d2} {
        arr = new int[arr_size];
        /* cout << "constructor called " << d1  << "," << d2 << endl; */
    }

    ~Matrix2d() { delete []arr; /* cout << "destructor called " << d1  << "," << d2 << endl; */ }

    template<typename S>
    inline const T& at(const S &i1, const S &i2) const {
        #ifdef LOCAL
            LOCAL_CHECK_RANGE
        #endif
        return arr[i1 * d2 + i2];
    }

    template<typename S>
    inline T& at(const S &i1, const S &i2) {
        #ifdef LOCAL
            LOCAL_CHECK_RANGE
        #endif
        return arr[i1 * d2 + i2];
    }

    inline void fill(const T &val) { std::fill_n(arr, arr_size, val); }

    [[nodiscard]] Matrix2d<T> operator*(const Matrix2d<T> &mat) const {
        if(d2 != mat.d1) throw invalid_argument("Invalid row column combination for multiplication ---> [" + to_string(d1) + "," + to_string(d2) + "], ["+to_string(mat.d1)+","+to_string(mat.d2)+"]");

        Matrix2d<T> result(d1, mat.d2);
        for(int i = 0; i < d1; ++i)
            for(int j = 0; j < mat.d2; ++j){
                result.at(i,j) = 0;
                for(int k = 0; k < d2; ++k) result.at(i,j) += this->at(i,k) * mat.at(k,j);
            }
        return result;
    }

    [[nodiscard]] string debug(const string &name="mat") {
        stringstream ss;
        ss << name << "["<<d1<<','<<d2<<"] = ";
        for(int i = 0; i < arr_size; ++i){
            if(i%d2==0) ss << "\n    ";
            ss << arr[i] << " ";
        }
        return ss.str();
    }
};

//####################################################################################################################

int main(){
    Matrix2d<int> arr(3,2), arr2(2,4);
    arr.fill(7);
    arr2.fill(9);
    cout << arr.debug() << endl;
    cout << arr2.debug() << endl;

    // Matrix2d<int> arr3 = (arr * arr2);
    // cout << arr3.debug() << endl;
    cout << (arr * arr2).debug() << endl;

    try{
        cout << endl << "arr[2][1] = " << arr.at(2,1) << endl;
        cout << endl << arr.at(4,4) << endl;
    }catch(std::invalid_argument e){
        cout << "exception e = " << e.what() << endl;        
    }

    cout << endl << arr.at(4,4) << endl;

    return 0;
}