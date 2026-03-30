#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

/*
template<class T>
class Value2Node {
    public:
    T value;
    Value2Node* left;
    Value2Node* right;
};
*/

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {};
    virtual bool empty() const = 0;
    virtual const T& top() const = 0;
    virtual void push(const T&) = 0;
    virtual void pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
public:
    MinHeap() {
        _ct.push_back(T());
    };
    ~MinHeap() {};

    bool empty() const override {
        return !size();
    };

    const T& top() const override {
        if (empty()) throw std::out_of_range("heap is empty");
        return _ct[1];
    };

    void push(const T& obj) override {
        _ct.push_back(obj);
        _sift_up(size() - 1);
    };

    void pop() override {
        if (empty()) return;
        _ct[1] = _ct.back();
        _ct.pop_back();
        if (empty()) return;
        _sift_down(1);
    };

    size_t size() const {
        return _ct.size() - 1;
    };

private:
    // index getter
    size_t _i_left(size_t i) {
        return 2 * i;
    };
    size_t _i_right(size_t i) {
        return 2 *i + 1;
    };
    size_t _i_parent(size_t i) {
        return i / 2;
    };

    // sift er
    void _sift_up(size_t i) {
        while (i > 1 && _ct[i] < _ct[_i_parent(i)]) {
            std::swap(_ct[i], _ct[_i_parent(i)]);
            i /= 2;
        }
    };
    void _sift_down(size_t i) {
        while (_i_left(i) <= size()) {
            size_t min = _i_left(i);

            if (_i_right(i) <= size() && _ct[_i_right(i)] < _ct[_i_left(i)]) {
                min = _i_right(i);
            }

            if (_ct[i] <= _ct[min]) break;

            std::swap(_ct[i], _ct[min]);
            i = min;
        }
    };

private:
    vector<T> _ct;

};



int main() {
    try {
        MinHeap<int> min_heap;

        int a[] = {5, 3, 8, 1, 2};
        cout << "Test push: [5, 3, 8, 1, 2]" << endl;
        for (auto &v : a) {
            min_heap.push(v);
        }

        cout << "Test top:" << min_heap.top() << endl;
        cout << "Test size:" << min_heap.size() << endl;

        cout << "\nTest L<R:" << endl;
        // 1, 2, 3, 5, 8
        while (!min_heap.empty()) {
            cout << min_heap.top() << " ";
            min_heap.pop();
        }
        cout << endl;

        cout << "Test is empty:" << endl;
        if (min_heap.empty()) {
            cout << "Heap is empty" << endl;
        }

        cout << "top= " << endl;
        cout << min_heap.top() << endl;

    } catch (const std::out_of_range& e) {
        cout << "Catch error -- " << e.what() << endl;
    } catch (const std::exception& e) {
        cout << "other error -- " << e.what() << endl;
    }

    return 0;
}