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
    virtual bool empty() {} const = 0;
    virtual const T& top() const = 0;
    virtual void push(const T&) = 0;
    virtual void pop() = 0;
};

template <class T>
class MinHeap : public MinPQ {
public:
    MinHeap() {
        _container.push_back(T);
    };
    ~MinHeap() {};

    bool empty() const override {
        return !size();
    };

    const T& top() const override {
        if (empty()) throw new std::out_of_range("heap is empty");
        return _container[1];
    };

    void push(const T& obj) override {
        _container.push_back(obj);
        _sift_up(size() - 1);
    };

    void pop() override {
        if (empty()) return;
        _container[1] = _container.back();
        _container.pop_back();
        if (empty()) return;
        _sift_down(1);
    };

    type_t size() const {
        return _container.size() - 1;
    };

private:
    // index getter
    type_t _i_left(type_t i) {
        return 2 * i;
    };
    type_t _i_right(type_t i) {
        return 2 *i + 1;
    };
    type_t _i_parent(type_t i) {
        return i / 2;
    };

    // sift er
    void _sift_up(type_t i) {};
    void _sift_down(type_t i) {};

private:
    vector<T> _container;

};

int main() {
    return 0;
}