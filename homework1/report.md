# 41343131

作業一

## 1. 問題 1

### 1.1 解題說明

本題要求寫出MinHeap的ADT，並實現具體程式。

#### 1.1.1 解題策略

與MaxHeap邏輯相同，但具體方式有些許不同(大小差異)。
使用一個vector儲存整個Heap.

### 1.2 程式實作

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

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
```

如程式所示

```cpp
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {};
    virtual bool empty() const = 0;
    virtual const T& top() const = 0;
    virtual void push(const T&) = 0;
    virtual void pop() = 0;
};
```

依照題目要求做出ADT，這邊我將方法轉換成C/C++風格。

基於vector以n節點取得左右、父節點的方法:

```cpp
size_t _i_left(size_t i) {
        return 2 * i;
    };
size_t _i_right(size_t i) {
        return 2 *i + 1;
    };
size_t _i_parent(size_t i) {
        return i / 2;
    };
```

再來是最重要的調整

```cpp
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
        } (_ct[i] <= _ct[min]) break;
        std::swap(_ct[i], _ct[min]);
        i = min;
    }
};
```

### 1.3 效能分析

| method | AVG/worst |
| - | - |
| `push(T)` | $O(log n)$ |
| `pop()` | $O(log n)$ |
| `top()` | $O(1)$ |
| `size()` | $O(1)$ |

### 1.4 測試與驗證

#### 1.4.1 測試案例

```cpp
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
```

### 1.5 申論與開發報告

#### 1.5.1 設計的過程

之前做Polynomial時有使用到，Heap挺好用的，在某些狀況下效率特別高。
每次放入跟取出會需要重新調整他們的位置，以保持順序正確。
比較不習慣的是，`pop()`不會回傳。

## 2. 問題 2

### 2.1 解題說明

#### 2.1.1 解題策略

### 2.2 程式實作

### 2.3 效能分析

### 2.4 測試與驗證

#### 2.4.1 測試案例

#### 2.4.2 執行指令

#### 2.4.3 結論

### 2.5 申論與開發報告

#### 2.5.1 設計的過程

## 程式實作

[問題一](#12-程式實作)

[問題二](#22-程式實作)

## 效能分析

[問題一](#13-效能分析)

[問題二](#23-效能分析)

## 測試與驗證

[問題一](#14-測試與驗證)

[問題二](#24-測試與驗證)

## 解題說明

[問題一](#11-解題說明)

[問題二](#21-解題說明)

## 申論及開發報告

[問題一](#15-申論與開發報告)

[問題二](#25-申論與開發報告)
