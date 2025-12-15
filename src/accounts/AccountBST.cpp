#include "AccountBST.h"

using namespace std;

void TransactionList::add(const Transaction& t) {
    Node* n = new Node(t);
    n->next = head;
    head = n;
}

vector<Transaction> TransactionList::getLastN(int n) const {
    vector<Transaction> res;
    Node* cur = head;
    while (cur && n--) {
        res.push_back(cur->t);
        cur = cur->next;
    }
    return res;
}

BSTNode* insert(BSTNode* root, int id, const string& name) {
    if (!root) return new BSTNode(id, name);
    if (id < root->accountID)
        root->left = insert(root->left, id, name);
    else if (id > root->accountID)
        root->right = insert(root->right, id, name);
    return root;
}

BSTNode* search(BSTNode* root, int id) {
    if (!root || root->accountID == id)
        return root;
    if (id < root->accountID)
        return search(root->left, id);
    return search(root->right, id);
}
