#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "accounts/AccountBST.h"
#include "risk/RiskHeap.h"
#include "transactions/TransactionQueue.h"
#include "transactions/FraudRules.h"

using namespace std;

// Create transaction
Transaction createTransaction(int txnID, int accID, double amt, const string& t,
                              const string& loc, const string& d, const string& tm) {
    Transaction tx;
    tx.transactionID = txnID;
    tx.accountID = accID;
    tx.amount = amt;
    tx.type = t;
    tx.location = loc;
    tx.date = d;
    tx.time = tm;
    try {
        tx.timestamp = computeTimestamp(d, tm);
    } catch (...) {
        tx.timestamp = 0;
    }
    tx.riskScore = 0;
    return tx;
}

// Load accounts from file
BSTNode* loadAccounts(const string& filename) {
    BSTNode* root = nullptr;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open accounts file.\n";
        return root;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name;
        if (!getline(ss, idStr, ',') || !getline(ss, name)) continue;
        int id = stoi(idStr);
        root = insert(root, id, name);
    }
    return root;
}

// Load transactions from file into queue
vector<Transaction> loadTransactions(const string& filename, TransactionQueue& queue) {
    vector<Transaction> txns;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open transactions file.\n";
        return txns;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string txnIDStr, accIDStr, amtStr, type, loc, date, time;
        if (!getline(ss, txnIDStr, ',') || !getline(ss, accIDStr, ',') ||
            !getline(ss, amtStr, ',') || !getline(ss, type, ',') ||
            !getline(ss, loc, ',') || !getline(ss, date, ',') || !getline(ss, time)) {
            continue;
        }
        int txnID = stoi(txnIDStr);
        int accID = stoi(accIDStr);
        double amt = stod(amtStr);
        Transaction t = createTransaction(txnID, accID, amt, type, loc, date, time);
        queue.enqueue(t);
        txns.push_back(t);
    }
    return txns;
}

// List accounts in-order
void listAccounts(BSTNode* root) {
    if (!root) return;
    listAccounts(root->left);
    cout << "Account ID: " << root->accountID
         << " | Holder: " << root->holder
         << " | Blacklisted: " << (root->isBlacklisted ? "Yes" : "No") << endl;
    listAccounts(root->right);
}

int main() {
    // ---------------- Setup ----------------
    BSTNode* root = loadAccounts("accounts.txt");
    TransactionQueue txnQueue;
    FraudRules fraudSystem;
    RiskHeap riskHeap;

    // Load transactions from file
    vector<Transaction> preTxns = loadTransactions("transactions.txt", txnQueue);
    int txnCounter = 1;
    for (auto& t : preTxns)
        if (t.transactionID >= txnCounter) txnCounter = t.transactionID + 1;

    cout << "Loaded " << preTxns.size() << " transactions into queue.\n";

    // ---------------- Menu ----------------
    while (true) {
        cout << "\n--- Fraud Management Menu ---\n";
        cout << "1. Add a Transaction\n";
        cout << "2. Check Most Risky Transaction\n";
        cout << "3. List All Accounts\n";
        cout << "4. List All Current Transactions in Queue\n";
        cout << "5. List Transactions for an Account\n";
        cout << "6. Resolve Transactions in Queue\n";
        cout << "7. Resolve Most Risky Transaction\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int accID;
            double amt;
            string type, loc, date, time;

            cout << "Enter Account ID: ";
            cin >> accID;
            cin.ignore(); // consume newline

            cout << "Enter Amount: ";
            cin >> amt;
            cin.ignore();

            cout << "Enter Type (Credit/Debit): ";
            getline(cin, type);

            cout << "Enter Location: ";
            getline(cin, loc);

            cout << "Enter Date (YYYY-MM-DD): ";
            getline(cin, date);

            cout << "Enter Time (HH:MM:SS): ";
            getline(cin, time);

            try {
                Transaction t = createTransaction(txnCounter++, accID, amt, type, loc, date, time);
                txnQueue.enqueue(t);
                cout << "Transaction added to queue.\n";
            } catch (const exception& e) {
                cout << "Error creating transaction: " << e.what() << endl;
            }

        } else if (choice == 2) {
            if (riskHeap.isEmpty()) {
            cout << "No risky transactions available.\n";
            continue;
        }

        vector<ScoredTransaction> allRisky = riskHeap.getAll();
        cout << "All Risky Transactions:\n";
        for (auto& tx : allRisky) {
            const Transaction& t = tx.txn;
            cout << "Transaction ID: " << t.transactionID
                << " | Account: " << t.accountID
                << " | Risk Score: " << tx.riskScore
                << " | Amount: " << t.amount
                << " | Type: " << t.type
                << " | Location: " << t.location
                << " | Date: " << t.date
                << " | Time: " << t.time << endl;
        }

        } else if (choice == 3) {
            listAccounts(root);

        } else if (choice == 4) {
            cout << "Transactions in Queue:\n";
            Transaction temp;
            TransactionQueue tempQueue;
            while (txnQueue.dequeue(temp)) {
                cout << "TxnID: " << temp.transactionID
                     << " | AccID: " << temp.accountID
                     << " | Amount: " << temp.amount
                     << " | Type: " << temp.type << endl;
                tempQueue.enqueue(temp);
            }
            // restore queue
            while (tempQueue.dequeue(temp))
                txnQueue.enqueue(temp);

        } else if (choice == 5) {
            int accID;
            cout << "Enter Account ID: ";
            cin >> accID;

            BSTNode* accNode = search(root, accID);
            if (!accNode) {
                cout << "Account not found.\n";
                continue;
            }

            vector<Transaction> txns = accNode->history.getLastN(1000);
            cout << "Transactions for Account " << accID << ":\n";
            for (auto& t : txns) {
                cout << "TxnID: " << t.transactionID
                     << " | Amount: " << t.amount
                     << " | Type: " << t.type
                     << " | Location: " << t.location
                     << " | Date: " << t.date << " " << t.time << endl;
            }

        } else if (choice == 6) {
            cout << "Resolving all transactions in queue...\n";
            Transaction t;
            while (txnQueue.dequeue(t)) {
                BSTNode* accNode = search(root, t.accountID);
                if (!accNode) {
                    cout << "Account " << t.accountID << " not found. Skipping.\n";
                    continue;
                }

                if (fraudSystem.isBlacklisted(t.accountID) || accNode->isBlacklisted) {
                    cout << "Transaction from blacklisted account " << t.accountID << " rejected.\n";
                    continue;
                }

                vector<Transaction> lastTxns = accNode->history.getLastN(5);
                double risk = fraudSystem.evaluateRisk(t, lastTxns);

                if (risk > 0) {
                    t.riskScore = (int)risk;
                    riskHeap.insert(ScoredTransaction((int)risk, t));
                }
                accNode->history.add(t);
                cout << "Transaction resolved for Account " << t.accountID << endl;
            }

        } else if (choice == 7) {
            if (riskHeap.isEmpty()) {
                cout << "No risky transactions available.\n";
                continue;
            }

            ScoredTransaction tx = riskHeap.extractMax();
            Transaction t = tx.txn;  // full transaction

            cout << "Transaction ID: " << t.transactionID
                << " | Account: " << t.accountID
                << " | Risk Score: " << tx.riskScore
                << " | Amount: " << t.amount
                << " | Type: " << t.type
                << " | Location: " << t.location
                << " | Date: " << t.date
                << " | Time: " << t.time << endl;

            char decision;
            cout << "Approve (a) or Reject (r)? ";
            cin >> decision;

            BSTNode* accNode = search(root, t.accountID);
            if (!accNode) {
                cout << "Account not found. Transaction skipped.\n";
                continue;
            }
            if (decision == 'a' || decision == 'A') {
                if (accNode->isBlacklisted || fraudSystem.isBlacklisted(t.accountID)) {
                    cout << "Cannot approve transaction: Account is blacklisted.\n";
                } else {
                    accNode->history.add(t);
                    cout << "Transaction approved and added to account history.\n";
                }
            } else {
                accNode->isBlacklisted = true;
                cout << "Transaction rejected. Account blacklisted.\n";
            }

        } else if (choice == 8) {
            cout << "Exiting...\n";
            break;

        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
