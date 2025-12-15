#ifndef ACCOUNTBST_H
#define ACCOUNTBST_H

#include "../transactions/Transaction.h"
#include <vector>
#include <string>

class TransactionList {
    struct Node {
        Transaction t;
        Node* next;
        Node(const Transaction& tx) : t(tx), next(nullptr) {}
    };
    Node* head;

public:
    TransactionList() : head(nullptr) {}
    void add(const Transaction& t);
    std::vector<Transaction> getLastN(int n) const;
};

class BSTNode {
public:
    int accountID;
    std::string holder;
    bool isBlacklisted;
    TransactionList history;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int id, const std::string& h)
        : accountID(id), holder(h),
          isBlacklisted(false),
          left(nullptr), right(nullptr) {}
};

BSTNode* insert(BSTNode* root, int id, const std::string& name);
BSTNode* search(BSTNode* root, int id);

#endif
