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
        cout << "height/log2(n) = " << bst.height() / d << endl;
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