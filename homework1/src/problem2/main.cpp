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

public:
    BST() : _root(nullptr) {};

    void push(T obj) {
        if (!_root) _root = new Node(obj);
        else {
            Node* ptr = _root;
            while (true) {
                if (ptr->v == obj) return;  // repeat item not allowed
                if (ptr->v > obj) {
                    if (!ptr->left) {
                        ptr->left = new Node(obj);
                        return;
                    }
                    else ptr = ptr->left;
                } else {// <
                    if (!ptr->right) {
                        ptr->right = new Node(obj);
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

private:
    Node* _root;
    size_t _get_height(Node* node) const {
        if (node == nullptr)
            return 0;
        else
            return 1 + std::max(_get_height(node->right), _get_height(node->left));
    };
};

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis;

    int test[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (auto &v : test) {
        double d = log2(v);
        BST<double> bst;
        while (v--) {
            double val = dis(gen);
            bst.push(val);
        };
        cout << "height/log2(n) = " << bst.height() / d << endl;
    }
}