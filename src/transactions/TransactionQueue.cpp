#include "TransactionQueue.h"

TransactionQueue::TransactionQueue() : front(nullptr), rear(nullptr) {}

void TransactionQueue::enqueue(Transaction t) {
    Node* temp = new Node(t);
    if (rear == nullptr) {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

bool TransactionQueue::dequeue(Transaction &removed) {
    if (front == nullptr) return false;
    Node* temp = front;
    removed = temp->data;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete temp;
    return true;
}

bool TransactionQueue::isEmpty() {
    return front == nullptr;
}

