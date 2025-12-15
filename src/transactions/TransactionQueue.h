#ifndef TRANSACTIONQUEUE_H
#define TRANSACTIONQUEUE_H

#include "Transaction.h"

class TransactionQueue {
private:
    struct Node {
        Transaction data;
        Node* next;
        Node(Transaction t) : data(t), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    TransactionQueue();
    ~TransactionQueue();
    void enqueue(const Transaction& t);
    bool dequeue(Transaction& removed);
    bool isEmpty() const;
    void printAll() const;
};

#endif
