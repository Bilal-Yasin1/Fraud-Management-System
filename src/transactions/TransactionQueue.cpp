#include "TransactionQueue.h"
#include <iostream>

TransactionQueue::TransactionQueue() : front(nullptr), rear(nullptr) {}

TransactionQueue::~TransactionQueue() {
    Transaction dummy;
    while (dequeue(dummy));
}

void TransactionQueue::enqueue(const Transaction& t) {
    Node* temp = new Node(t);
    if (!rear) {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

bool TransactionQueue::dequeue(Transaction& removed) {
    if (!front) return false;
    Node* temp = front;
    removed = temp->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return true;
}

bool TransactionQueue::isEmpty() const {
    return front == nullptr;
}

void TransactionQueue::printAll() const {
    Node* cur = front;
    while (cur) {
        const Transaction& t = cur->data;
        std::cout << "TxnID: " << t.transactionID
                  << " | AccID: " << t.accountID
                  << " | Amount: " << t.amount
                  << " | Type: " << t.type
                  << " | Location: " << t.location
                  << " | Date: " << t.date
                  << " | Time: " << t.time << std::endl;
        cur = cur->next;
    }
}
