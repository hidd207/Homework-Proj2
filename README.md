# 作業二
# 組員:41243216 李宗燁

# 題目 1：
### 最大堆／最小堆實作

# 題目敘述
請寫一個 C++ 抽象類別（abstract class）針對 ADT MinPQ用來定義一個最小優先佇列。接著，寫一個繼承這個抽象類別的 C++ 類別 MinHeap，並實作 MinPQ 所有的虛擬函式（virtual functions）。每個函式的時間複雜度應該和 MaxHeap 的對應函式相同。

---
# 解題策略
利用 vector 作為底層儲存資料，採用完全二元樹邏輯。
插入元素時採用「sift up」操作，刪除堆頂時用「sift down」。
使用虛擬類別設計介面，利於擴充與多型測試。   

---
# 程式實作
```cpp
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;           
    virtual const T& Top() const = 0;           
    virtual void Push(const T&) = 0;            
    virtual void Pop() = 0;                     
};
template <class T>
class MinHeap : public MinPQ<T>{
private:
    vector<T> heap;

    static int parent(int i) { return (i - 1) / 2; }
    static int left(int i) { return 2 * i + 1; }
    static int right(int i) { return 2 * i + 2; }

    void siftDown(int i) {
        int n = heap.size();
        while (left(i) < n) {
            int j = left(i);
            if (right(i) < n && heap[right(i)] < heap[j]) j = right(i);
            if (heap[i] <= heap[j]) break;
            swap(heap[i], heap[j]);
            i = j;
        }
    }
    void siftUp(int i) {
        while (i > 0 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
public:
    MinHeap() = default;
    MinHeap(const vector<T>& arr) : heap(arr) {
        for (int i = parent(heap.size() - 1); i >= 0; --i) {
            siftdown(i);
        }
    }
    virtual ~MinHeap(){}
    virtual bool IsEmpty() const override {
        return heap.empty();
    }
    virtual const T& Top() const override {
        if (heap.empty()) throw out_of_range("Heap is empty");
        return heap[0];
    }
    virtual void Push(const T& val) override {
        heap.push_back(val);
        siftUp(heap.size() - 1);
    }
    virtual void Pop() override {
        if (heap.empty()) throw out_of_range("Heap is empty");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) siftDown(0);
    }
};
```
---
# 效能分析 
Push和Pop 均為 $O(\log n)$，Top、IsEmpty 為 $O(1)$。  
空間複雜度為 $O(n)$。

---
# 測試與驗證 
當input文件輸入為10 9 8 7 6 5 4 3 2 1   
output輸出為1 2 3 4 5 6 7 8 9 10 

---
# 申論與開發報告 

本題練習 STL 以外的資料結構實作與介面設計。  
抽象化設計便於未來擴充與單元測試。  
了解二元堆基本操作與其時間複雜度。  

---
# 題目 2
### (a) 寫一個隨機插入的 BST 程式並量測高度，並畫出高度與 log₂n 的比值。  
### (b) 寫出 BST 的刪除節點函數，並分析時間複雜度。

---
# 題目敘述 
(a) 給定 $n$ 筆不同的整數資料，請以隨機順序依序插入二元搜尋樹。觀察並統計每一棵隨機生成 BST 的高度，計算其與 $\log_2 n$ 的比值，並分析此比值的變動情形。  
(b) 實作 BST 節點刪除操作，並討論其時間複雜度。

---
# 解題策略
先建立 $1 \sim n$ 的整數陣列，利用隨機演算法（如 `std::shuffle`）打亂順序，依序插入 BST。
插入每一筆資料時，維持 BST 的基本性質，節點值左小右大。
完成插入後，撰寫遞迴函式計算樹的最大高度，並與理論值 $\log_2 n$ 相除得比值。
針對刪除操作，實作經典 BST 刪除演算法，涵蓋葉節點、單子樹節點及雙子樹節點三種情況。
設計主程式可重複進行多組隨機插入，並記錄/輸出樹高與理論比值做分析與驗證。

---
# 程式實作
(a) 
```cpp
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
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
    void insert(int val) { root = insert(root, val); }
    int height() { return height(root); }
    void clear() { clear(root); root = nullptr; }
private:
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->val) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return node;
    }
    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main() {
    vector<int> ns = {100, 500, 1000, 2000, 3000, 5000, 10000};
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
    }
    return 0;
}
```
# 效能分析
每次插入平均 $O(\log n)$，最壞 $O(n)$。  
高度與 log₂(n) 的比值可反映隨機 BST 的高度波動。  
空間複雜度 $O(n)$。  

---
# 測試與驗證
|n|Height|log₂(n)|Height/log₂(n)|
|-------|--------|---------|----------------|
|100|15|6.64|2.26|
|500|16|8.97|1.78| 
|1000|24|9.97|2.41|
|2000|24|10.97|2.19|
|3000|28|11.55|2.42|
|5000|26|12.29|2.12|
|10000|31|13.29|2.33|  

多次測試，隨機 BST 的高度約為 log₂(n) 的 1.7～2.5 倍。

---
# 程式實作
(b)
```cpp
void remove(int key) {
    root = deleteNode(root, key);
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
        } else if (!node->right) {
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
```
# 時間複雜度分析
刪除操作需要先搜尋節點，再進行替換，最壞情況與搜尋相同，時間複雜度為 $O(h)$，其中 $h$ 為樹高。  
隨機/平衡 BST：$O(\log n)$。  
最壞（退化為鏈表）：$O(n)$。  
若為平衡二元搜尋樹則可保證 $O(\log n)$。  

---
# 申論與開發報告

本題主要探討二元搜尋樹（BST）在隨機插入與刪除操作下的結構變化與程式設計心得。
在(a)小題中，透過將 n 筆資料隨機順序插入 BST，發現 BST 的樹高會隨插入順序而產生明顯波動。雖然理論上完全平衡的 BST 高度應趨近於 $\log_2 n$，但隨機插入下實際樹高常落於 log₂(n) 的 1.7~2.5 倍之間。  
這說明一般 BST 結構對於資料順序非常敏感，當順序不佳時樹高可能大幅增加，導致搜尋與操作效率降低。若需高度穩定的搜尋效能，實務上建議使用自動平衡的樹結構（如 AVL 樹或紅黑樹）。  
在(b)小題，實作 BST 的節點刪除操作，涵蓋葉節點、僅有單子樹、以及同時有左右子樹等三種典型情形。程式設計時採用遞迴方法，先定位目標節點，再根據其子樹狀況執行對應的刪除邏輯。  
若遇到有兩個子樹的情形，則以右子樹最小值（或左子樹最大值）取代節點，再遞迴刪除該替代節點。  
整體刪除操作的時間複雜度為 $O(h)$，其中 $h$ 為樹高。這代表 BST 的效能受樹高影響很大，當樹高偏大時，最壞情況會退化為 $O(n)$。程式設計時亦需注意記憶體釋放，避免產生遺失或漏釋情形。

本題透過實作與觀察，讓我體會到資料結構設計的細節與其對效能的深遠影響，也更熟悉了 BST 相關操作的實踐方式。在專案開發過程中，透過多組隨機測試驗證程式正確性與穩定性，加深了我對資料結構運作機制的理解與應用能力。
---
# 題目3:
### 外部排序總輸入時間分析

---
# 題目敘述
(a)
有 $n$ 筆紀錄需要在一台記憶體容量為 $S$ 筆紀錄的電腦上排序。假設整個 $S$ 筆的記憶體都可以用來作為輸入/輸出緩衝區。輸入資料存放在磁碟上，並且一共分成 $m$ 個區段（runs）。假設每次磁碟存取時，搜尋時間為 $t_s$，延遲時間為 $t_l$，每筆資料的傳輸時間為 $t_t$。如果在外部排序的第二階段採用 $k$ 路歸併，並且將內部記憶體分割成輸入/輸出緩衝區，讓輸入、輸出與 CPU 處理可以重疊執行（如 7.21 範例中的 Buffering），請問此階段的總輸入時間是多少？  
(b)
假設將所有區段合併成一個的 CPU 時間為 $t_{CPU}$（可假設與 $k$ 無關，因此為常數）。給定：$t_s = 80$ 毫秒，$t_l = 20$ 毫秒，$n = 200,000$，$m = 64$，$t_t = 10^{-3}$ 秒/筆，$S = 2000$。請大略畫出總輸入時間 $t_{input}$ 與 $k$ 的關係圖。是否總會存在某個 $k$ 使得 $t_{CPU} \approx t_{input}$？













