#include <iostream>
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

#define int int32_t

//####################################################################################################################

template<typename T, typename U> std::vector<T> MatrixVector(int n, U v){ return std::vector<T>(n, v);}
template<typename T, class... Args> auto MatrixVector(int n, Args... args){auto val = MatrixVector<T>(args...); return std::vector<decltype(val)>(n, move(val));}
// auto matrixM = MatrixVector<int32_t>(9,8,7,6,5)  // dimention = 9*8*7*6, default value=5

//####################################################################################################################

#define DEBUG_Matrix2d_LOCAL

template<typename T>
struct Matrix2d{
#define LOCAL_CHECK_RANGE(_l, _h1, _h2) if (i1 < (_l) || (_h1) <= i1 || i2 < (_l) || (_h2) <= i2) { throw std::invalid_argument("EXCEPTION: Out of bound on arr["+to_string(d1)+"]["+to_string(d2)+"] ---> " + to_string(i1) + ", " + to_string(i2)); }

    template<typename S>
    struct Matrix2d_iterator{
        S *first, *last;
        inline S* begin() {return first;}
        inline S* end() {return last;}
        inline Matrix2d_iterator(S* f, S* l): first{f}, last{l} {}
    };

    T *arr;
    uint64_t arr_size, d1, d2;

    explicit Matrix2d(const size_t &t_d1, const size_t &t_d2=1): arr_size{t_d1 * t_d2}, d1{t_d1}, d2{t_d2} { arr = new int[arr_size]; }

    ~Matrix2d() { delete []arr; }

    // *** BELOW are 0-indexed methods ***

    template<typename S>
    inline T& at(const S &i1, const S &i2) {
        #ifdef DEBUG_Matrix2d_LOCAL
            LOCAL_CHECK_RANGE(0,d1,d2)
        #endif
        return arr[i1 * d2 + i2];
    }

    template<typename S>
    inline T& flat(const S &idx) { return arr[idx]; }

    template<typename S>
    inline T* row(const S &i1) { return &(arr+(i1*d2)); }

    /* 0-indexed, iterate from [ arr.at(idx1, idx2), arr.at(e1,e2) ) 
     * If e1 is default, then iterate TILL end
     * If e2 is default, then iterate TILL row `e1` but not inclusive
     */
    Matrix2d_iterator<T> iter(int idx1=0, int idx2=0, int e1=-1, int e2=0) {
        T *f = arr + (idx1*d2) + idx2;
        T *l = arr;
        if(e1==-1) l += arr_size;
        else l += (e1*d2) + e2;
        return Matrix2d_iterator<T>(f, l);
    }

    // *** BELOW are 1-indexed methods ***

    template<typename S>
    inline T& at1(const S &i1, const S &i2) {
        #ifdef DEBUG_Matrix2d_LOCAL
            LOCAL_CHECK_RANGE(1,d1+1,d2+1)
        #endif
        return arr[(i1-1) * d2 + (i2-1)];
    }

    template<typename S>
    inline T& flat1(const S &idx) { return arr[idx-1]; }

    template<typename S>
    inline T* row1(const S &i1) { return &(arr+((i1-1)*d2)); }

    /* 1-indexed, iterate from [ arr.at1(idx1, idx2), arr.at1(e1,e2) ) */
    Matrix2d_iterator<T> iter1(int idx1=1, int idx2=1, int e1=0, int e2=1) {
        return iter(idx1-1, idx2-1, e1-1, e2-1);
    }

    // *** BELOW are GENERIC functions ***

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

    inline void fill(const T &val) { std::fill_n(arr, arr_size, val); }
    inline T* begin() { return arr; }
    inline T* end() { return arr+arr_size; }
};
/* 

template<typename T>
struct Matrix2d{
    T *arr;
    long arr_size, d1, d2;

    explicit Matrix2d(const size_t &t_d1, const size_t &t_d2=1): arr_size{t_d1 * t_d2}, d1{t_d1}, d2{t_d2} { arr = new int[arr_size]; }
    ~Matrix2d() { delete []arr; }

    inline T& at(const size_t &i1, const size_t &i2) { return arr[i1 * d2 + i2]; }
    inline void fill(const T &val) { std::fill_n(arr, arr_size, val); }

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

 */
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

    int j = 0;
    for(int &i: arr)
        i=j++;
    cout << endl << arr.debug() << endl;
    
    cout << "arr = ";
    for(int a: arr) cout << a << ", "; cout << endl;
    cout << "range 0-indexed [ arr.at(0,0), end ) = ";
    for(int a: arr.iter(0,0)) cout << a << ", "; cout << endl;
    cout << "range 1-indexed [ arr.at1(1,2), arr.at1(3,2) ) = ";
    for(int a: arr.iter1(1,2,3,2)) cout << a << ", "; cout << endl;

    // This will cause abrupt exit of the program as (4,4) is out or range
    // cout << endl << arr.at(4,4) << endl;

    cout << endl;

    return 0;
}