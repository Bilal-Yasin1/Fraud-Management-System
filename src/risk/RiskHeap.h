#ifndef RISKHEAP_H
#define RISKHEAP_H

#include <vector>
#include <string>
#include "../transactions/Transaction.h"

struct ScoredTransaction {
    int riskScore;
    Transaction txn;  // full transaction

    ScoredTransaction(int risk, const Transaction& t)
        : riskScore(risk), txn(t) {}
};

class RiskHeap {
    std::vector<ScoredTransaction> heap;

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    void insert(const ScoredTransaction& t);
    ScoredTransaction extractMax();
    bool isEmpty() const;
    
    std::vector<ScoredTransaction> getAll() const;
};

#endif
