#include <iostream>
#include <vector>

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
    ~MinHeap() {};

    bool empty() const override {
        return !_size;
    };

    const T& top() const override {};

    void push(const T& obj) override {};

    void pop() override {};

    type_t size() const {
        return _container.size();
    };

private:
    type_t _i_left(type_t i) {
        return 2 * i;
    };
    type_t _i_right(type_t i) {
        return 2 *i + 1;
    };
    type_t _i_parent(type_t i) {
        return i / 2;
    };

private:
    vector<T> _container;

};

int main() {
    return 0;
}