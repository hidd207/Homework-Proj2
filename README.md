# 作業二
# 組員:41243216 李宗燁

## 題目 1：最大堆／最小堆實作

### 題目敘述
請寫一個 C++ 抽象類別（abstract class）針對 ADT MinPQ用來定義一個最小優先佇列。接著，寫一個繼承這個抽象類別的 C++ 類別 MinHeap，並實作 MinPQ 所有的虛擬函式（virtual functions）。每個函式的時間複雜度應該和 MaxHeap 的對應函式相同。
---
### 解題策略

- 利用 vector 作為底層儲存資料，採用完全二元樹邏輯。
- 插入元素時採用「sift up」操作，刪除堆頂時用「sift down」。
- 使用虛擬類別設計介面，利於擴充與多型測試。

---
### 程式實作
```
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
## 題目 2
(a) 寫一個隨機插入的 BST 程式並量測高度，並畫出高度與 log₂n 的比值。  
(b) 寫出 BST 的刪除節點函數，並分析時間複雜度。
---
