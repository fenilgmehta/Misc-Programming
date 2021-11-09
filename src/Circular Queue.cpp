#include <iostream>
#include <vector>
using namespace std;



template<typename T>
struct CircularQueue {
    int n, idxFront, idxBack;
    std::vector<T> q;

    explicit CircularQueue(int t_size=128): n{t_size}, idxFront{-1}, idxBack{-1}, q(t_size) {}

    // q = . . 1 2 3 . . .
    //    front^   ^rear
    bool push_back(const T &key) {
        if (this->full()) {
            // cerr << "\nError: queue is full\n";
            return false;
        }

        if (idxFront == -1) idxFront = 0;  // q is empty
        idxBack = (idxBack + 1) % n;
        q[idxBack] = key;
        return true;
    }

    T pop_front() {
        const int oldFront = idxFront;
        // if only 1 element was present before the call to pop
        if (idxFront == idxBack) idxFront = idxBack = -1;
        else idxFront = (idxFront + 1) % n;
        // exception will be thrown if "q" is empty()
        return q.at(oldFront);
    }

    void pop_push(){
        if(full()) {
            // cout << "\n**cool faster**\n";
            idxFront = (idxFront+1) % n;
            idxBack = (idxBack+1) % n;
        } else {
            push_back(pop_front());
        }
    }

    T& front() {
        // exception will be thrown if "q" is empty()
        return q.at(idxFront);
    }

    T& back() {
        // exception will be thrown if "q" is empty()
        return q.at(idxBack);
    }

    bool push_front(const T &key) {
        if (full()) return false;
        if (empty()) idxFront = idxBack = 0;
        else idxFront = (idxFront - 1 + n) % n;
        q[idxFront] = key;
        return true;
    }

    T pop_back() {
        const int oldBack = idxBack;
        if (idxFront == idxBack) idxFront = idxBack = -1;
        else idxBack = (idxBack - 1 + n) % n;
        // exception will be thrown if "q" is empty()
        return q.at(oldBack);
    }

    inline void clear() { idxFront = idxBack = -1; }
    inline bool empty() const { return idxFront == -1; }
    inline bool full() const { return idxFront == (idxBack + 1) % n; }
    inline int capacity() const { return n; }
    inline int size() const { return empty() ? 0 : ((idxFront <= idxBack) ? (idxBack - idxFront + 1) : (n+idxBack-idxFront+1)); }
    // inline int begin() const { return idxFront; }
    // inline int end() const { return empty() ? idxFront : ((idxFront <= idxBack) ? (idxBack+1) : (idxBack+n)); }
    inline int begin() const { return 0; }
    inline int end() const { return size(); }
    inline T& operator[](const int &idx) { return q[(idxFront+idx) % n]; }
};



int main(){
    CircularQueue<int> cq(4);

    cout << endl;
    cout << "cq.size() = " << cq.size() << endl;
    cout << "Elements of circular queue = [";
    for(int i = cq.begin(), i_end = cq.end(); i != i_end; ++i) cout << cq[i] << ", ";
    cout << "]" << endl;

    cq.push_back(1);
    cq.push_back(2);
    cq.push_back(3);

    cout << endl;
    cout << "cq.size() = " << cq.size() << endl;
    cout << "Elements of circular queue = [";
    for(int i = cq.begin(), i_end = cq.end(); i != i_end; ++i) cout << cq[i] << ", ";
    cout << "]" << endl;

    cq.pop_front();
    cq.push_back(4);
    cq.push_back(5);

    cout << endl;
    cout << "cq.empty() = " << boolalpha << cq.empty() << endl;
    cout << "cq.size() = " << cq.size() << endl;
    cout << "Elements of circular queue = [";
    for(int i = cq.begin(), i_end = cq.end(); i != i_end; ++i) cout << cq[i] << ", ";
    cout << "]" << endl;

    cout << endl;
    cout << "cq.push_back(6) = " << boolalpha << cq.push_back(6) << endl;
    cout << "cq.push_back(7) = " << boolalpha << cq.push_back(7) << endl;

    cout << endl;
    cout << "cq.empty() = " << boolalpha << cq.empty() << endl;
    cout << "cq.full() = " << boolalpha << cq.full() << endl;
    cout << "cq.size() = " << cq.size() << endl;
    cout << "Elements of circular queue = [";
    for(int i = cq.begin(), i_end = cq.end(); i != i_end; ++i) cout << cq[i] << ", ";
    cout << "]" << endl;

    cout << "------------" << endl;
    for(int i = 4; i--;){
        cq.pop_push();  // faster than below solution
        // cq.push_back(cq.pop_front());
        cout << endl;
        cout << "cq.empty() = " << boolalpha << cq.empty() << endl;
        cout << "cq.full() = " << boolalpha << cq.full() << endl;
        cout << "cq.size() = " << cq.size() << endl;
        cout << "Elements of circular queue = [";
        // cout << cq.begin() << ", " << cq.end() << endl;
        for(int i = cq.begin(), i_end = cq.end(); i != i_end; ++i) cout << cq[i] << ", ";
        cout << "]" << endl;
    }

    cout << endl << "Clearing all the queue elements (size, empty(), full()): ";
    cq.clear();  // faster than below solution
    // while(not cq.empty()) cq.pop_front();
    cout << boolalpha << cq.size() << ", " << cq.empty() << ", " << cq.full() << endl;

    cout << endl;
    vector<int> arr;
    arr.front();
    return 0;
}
