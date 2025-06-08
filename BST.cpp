#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
using namespace std;


struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};


class BST {
public:
    Node* root;
    BST() : root(nullptr) {}

    
    void insert(int val) {
        root = insert(root, val);
    }

   
    void remove(int key) {
        root = deleteNode(root, key);
    }

   
    int height() {
        return height(root);
    }

    
    void inorder() {
        inorder(root);
        cout << endl;
    }

    
    void clear() {
        clear(root);
        root = nullptr;
    }

private:
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->val) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return node;
    }

    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->val)
            node->left = deleteNode(node->left, key);
        else if (key > node->val)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left) {
                Node* r = node->right;
                delete node;
                return r;
            }
            else if (!node->right) {
                Node* l = node->left;
                delete node;
                return l;
            }
            
            Node* succ = node->right;
            while (succ->left) succ = succ->left;
            node->val = succ->val;
            node->right = deleteNode(node->right, succ->val);
        }
        return node;
    }

    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};


int main() {
    vector<int> ns = { 100, 500, 1000, 2000, 3000, 5000, 10000 };
    random_device rd;
    mt19937 gen(rd());

    cout << " n     Height   log2(n)   Height/log2(n)\n";
    cout << "-----------------------------------------\n";
    for (int n : ns) {
        BST tree;
        vector<int> vals(n);
        for (int i = 0; i < n; ++i) vals[i] = i + 1;
        shuffle(vals.begin(), vals.end(), gen);  
        for (int v : vals) tree.insert(v);

        int h = tree.height();
        double logn = log2(n);
        double ratio = h / logn;
        printf("%5d   %6d   %7.2f      %7.2f\n", n, h, logn, ratio);

      
        for (int i = 1; i <= n / 2; ++i)
            tree.remove(i);
        cout << "After deleting 1~" << n/2 << " : Height = " << tree.height() << endl;
        
    }
    return 0;
}
