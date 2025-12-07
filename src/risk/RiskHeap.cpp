#include <iostream>
#include <vector>
using namespace std;

// Transaction structure (score already assigned by Team Member 2)
struct ScoredTransaction {
    int riskScore;      // Already calculated
    int transactionID;
    int accountID;
    int amount;
    string location;

    ScoredTransaction() {}
    ScoredTransaction(int score, int tid, int acc, int amt, string loc)
        : riskScore(score), transactionID(tid), accountID(acc), amount(amt), location(loc) {}
};

// Team Member 3: Max-Heap to store scored transactions
class RiskHeap {
private:
    vector<ScoredTransaction> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].riskScore > heap[parent].riskScore) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left].riskScore > heap[largest].riskScore)
                largest = left;
            if (right < size && heap[right].riskScore > heap[largest].riskScore)
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else break;
        }
    }

public:
    // Insert a transaction with already calculated risk
    void insert(const ScoredTransaction &tx) {
        heap.push_back(tx);
        heapifyUp(heap.size() - 1);
    }

    // Return transaction with highest risk without removing
    ScoredTransaction getMax() {
        if (heap.empty()) {
            cout << "Heap is empty!\n";
            return ScoredTransaction();
        }
        return heap[0];
    }

    // Remove and return transaction with highest risk
    ScoredTransaction extractMax() {
        if (heap.empty()) {
            cout << "Heap is empty!\n";
            return ScoredTransaction();
        }

        ScoredTransaction top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return top;
    }

    bool isEmpty() { return heap.empty(); }

    // Approve the top transaction
    void approveTop() {
        if (!heap.empty()) {
            ScoredTransaction tx = extractMax();
            cout << "Approved Transaction ID: " << tx.transactionID
                 << " | Risk Score: " << tx.riskScore << endl;
            // Integration: add to BST
        }
    }

    // Reject the top transaction
    void rejectTop() {
        if (!heap.empty()) {
            ScoredTransaction tx = extractMax();
            cout << "Rejected Transaction ID: " << tx.transactionID
                 << " | Account ID Blacklisted: " << tx.accountID << endl;
            // Integration: add account to blacklist
        }
    }

    void printHeap() {
        cout << "\n--- Risk Heap ---\n";
        for (auto &tx : heap) {
            cout << "TxID: " << tx.transactionID
                 << " | AccID: " << tx.accountID
                 << " | Amount: " << tx.amount
                 << " | Location: " << tx.location
                 << " | Risk: " << tx.riskScore << endl;
        }
        cout << "----------------\n";
    }
};


// Example usage
int main() {
    RiskHeap heap;

    // Insert transactions (risk score calculated by Team Member 2)
    heap.insert(ScoredTransaction(85, 101, 5001, 20000, "Karachi"));
    heap.insert(ScoredTransaction(90, 102, 5002, 30000, "Dubai"));
    heap.insert(ScoredTransaction(70, 103, 5003, 15000, "Lahore"));
    heap.insert(ScoredTransaction(95, 104, 5004, 40000, "USA"));

    heap.printHeap();

    cout << "\nApproving top risky transaction...\n";
    heap.approveTop();

    heap.printHeap();

    cout << "\nRejecting next top risky transaction...\n";
    heap.rejectTop();

    heap.printHeap();

    return 0;
}

