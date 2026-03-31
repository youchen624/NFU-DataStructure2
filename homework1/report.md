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

撰寫BST，並進行測試。
未說明使用類型，因此預設使用`double`，也可有效避免重複。
刪除策略: 使用In-Order找最大堆當中最小值。

### 2.2 程式實作

其中使用指標來儲存BST，提高效率(相較陣列)。

使用`_search(T)`，查找回傳一對資料(`{ 父, 目標}`)。

```cpp
#include <iostream>
#include <cmath>
#include <random>
// #include <limits>

using namespace std;

template <class T>
class BST {         // left < right
private:
    class Node{
    public:
        T v;
        Node* left;
        Node* right;
        Node(T obj) : v(obj), left(nullptr), right(nullptr) {};
    };

    using PNode = std::pair<Node*, Node*>;
    /*using V3Node = struct {
        Node* parent;
        Node* target;
    };*/

public:
    BST() : _root(nullptr), _size(0) {};
    ~BST() { _clear(_root); };

    void push(T obj) {
        if (!_root) {
            _root = new Node(obj);
            ++_size;
        } else {
            Node* ptr = _root;
            while (true) {
                if (ptr->v == obj) return;  // repeat item not allowed
                if (ptr->v > obj) {
                    if (!ptr->left) {
                        ptr->left = new Node(obj);
                        ++_size;
                        return;
                    }
                    else ptr = ptr->left;
                } else {// <
                    if (!ptr->right) {
                        ptr->right = new Node(obj);
                        ++_size;
                        return;
                    }
                    else ptr = ptr->right;
                }
            }
        }
    };

    size_t height() const {
        return _get_height(_root);
    };

    size_t size() const {
        return _size;
    };

    size_t empty() const {
        return !size();
    };

    void remove(T obj) {
         // do nothing if it is not exist
        if (empty()) return;
        PNode p2ptr = _search(obj);
        Node* dp = p2ptr.second;
        Node* tmp = nullptr, tmp2 = p2ptr.second;
        if (!p2ptr.second) {
            return; // not exist
        // } else if (!p2ptr.first) {
        //     _root = nullptr;
        } else if (p2ptr.second->right) {
            tmp = p2ptr.second->right;
            tmp2 = p2ptr.second;
            while (tmp->left) {
                tmp2 = tmp;
                tmp = tmp->left;
            }

            if (tmp2 != p2ptr.second) {
                tmp2->left = tmp->right;
                tmp->right = p2ptr.second->right;
            }

            tmp->left = p2ptr.second->left;

            (p2ptr.first) ? ((p2ptr.first->right == p2ptr.second) ? p2ptr.first->right : p2ptr.first->left) : (_root) = tmp;

        } else if (p2ptr.second->left) {
            (p2ptr.first) ? ((p2ptr.first->right == p2ptr.second) ? p2ptr.first->right : p2ptr.first->left) : (_root) = p2ptr.second->left;
        } else {
            (p2ptr.first) ? ((p2ptr.first->right == p2ptr.second) ? p2ptr.first->right : p2ptr.first->left) : (_root) = nullptr;
        }
            delete dp;
            --_size;
    };

private:
    Node* _root;
    size_t _size;

    size_t _get_height(Node* node) const {
        if (node == nullptr)
            return 0;
        else
            return 1 + std::max(_get_height(node->right), _get_height(node->left));
    };

    PNode _search(T obj) {
        // returns nullptr if not exist
        // {parent, target}
        Node* pptr = nullptr;
        Node* ptr = _root;
        while (ptr && ptr->v != obj) {
            pptr = ptr;
            if (ptr->v < obj) ptr = ptr->right;
            else ptr = ptr->left;
        }
        return {pptr, ptr};
    };

    void _clear(Node* node) {
        if (node == nullptr) return;
        _clear(node->right);
        _clear(node->left);
        delete node;
    };
};

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis;
    
    int test[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (auto n : test) {
        double d = log2(n);
        BST<double> bst;
        
        int count = n;
        while (count--) {
            double val = dis(gen);
            bst.push(val);
        }
        cout << "height/log2(" << n << ") = " << bst.height() / d << endl;
    }
}

/*
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis;
    int n = 100, m = 100;
    BST<double> bst;
    vector<double> list;
    while (n--) {
        double val = dis(gen);
        bst.push(val);
        list.push_back(val);
    }
    cout << "height/log2(n) = " << bst.height() / log2(100) << endl;
    while (m--) {
        if (!list.empty()) {
            std::uniform_int_distribution<> dis(0, list.size() - 1);
            int index = dis(gen);
            double pickedValue = list[index];
            std::cout << "取出的值: " << pickedValue << std::endl;
            std::swap(list[index], list.back());
            list.pop_back();
        }
    }
}
*/
```

### 2.3 效能分析

`remove(T)`時間複雜度: $O(h)$，$h$=Tree高度。

### 2.4 測試與驗證

![高度曲線圖](../.img/BST%20Height%20Analysis%2020260331.png)

```cpp
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis;
    
    int test[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (auto n : test) {
        double d = log2(n);
        BST<double> bst;
        
        int count = n;
        while (count--) {
            double val = dis(gen);
            bst.push(val);
        }
        cout << "height/log2(n) = " << bst.height() / d << endl;
    }
}
```

```txt
height/log2(100) = 1.80618
height/log2(500) = 1.8961
height/log2(1000) = 2.10721
height/log2(2000) = 2.18863
height/log2(3000) = 2.33751
height/log2(4000) = 2.25643
height/log2(5000) = 2.60423
height/log2(6000) = 2.3903
height/log2(7000) = 2.42697
height/log2(8000) = 2.46803
height/log2(9000) = 2.13159
height/log2(10000) = 2.03195
```

據觀察，約為$1.8~2.6$。

RND節點：

```cpp
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis;
    int n = 100, m = 100;
    BST<double> bst;
    vector<double> list;
    while (n--) {
        double val = dis(gen);
        bst.push(val);
        list.push_back(val);
    }
    cout << "height/log2(n) = " << bst.height() / log2(100) << endl;
    while (m--) {
        if (!list.empty()) {
            std::uniform_int_distribution<> dis(0, list.size() - 1);
            int index = dis(gen);
            double pickedValue = list[index];
            std::cout << "取出的值: " << pickedValue << std::endl;
            std::swap(list[index], list.back());
            list.pop_back();
        }
    }
}
```

#### 2.4.1 結論

大致上穩定，BST在隨機中夠平衡，刪除method正常。

### 2.5 申論與開發報告

#### 2.5.1 設計的過程

最麻煩的在於刪除方法，沒有過多的優化邏輯，只單純的把邏輯一行一行加上去，有點死板。

不過有注意到BST有機率出現最差狀況，整棵樹傾斜的狀況，例如存入一段等差級數。

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
