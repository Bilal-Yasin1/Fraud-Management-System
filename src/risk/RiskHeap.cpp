#include "RiskHeap.h"
#include <algorithm>
using namespace std;

void RiskHeap::heapifyUp(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[i].riskScore > heap[p].riskScore)
            swap(heap[i], heap[p]), i = p;
        else break;
    }
}

void RiskHeap::heapifyDown(int i) {
    int n = heap.size();
    while (true) {
        int l = 2*i+1, r = 2*i+2, largest = i;
        if (l < n && heap[l].riskScore > heap[largest].riskScore) largest = l;
        if (r < n && heap[r].riskScore > heap[largest].riskScore) largest = r;
        if (largest != i)
            swap(heap[i], heap[largest]), i = largest;
        else break;
    }
}

void RiskHeap::insert(const ScoredTransaction& t) {
    heap.push_back(t);
    heapifyUp(heap.size() - 1);
}

ScoredTransaction RiskHeap::extractMax() {
    ScoredTransaction top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) heapifyDown(0);
    return top;
}

bool RiskHeap::isEmpty() const {
    return heap.empty();
}


std::vector<ScoredTransaction> RiskHeap::getAll() const {
    return heap;
}