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

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    if (!fin) {
        cerr << "input.txt 無法開啟" << endl;
        return 1;
    }
    MinHeap<int> h;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        int num;
        while (ss >> num) h.Push(num);
    }

    // 依序彈出（最小到最大），寫入 output.txt
    while (!h.IsEmpty()) {
        fout << h.Top() << " ";
        h.Pop();
    }
    fout << endl;
    fin.close();
    fout.close();
    return 0;
}
