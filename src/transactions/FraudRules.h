#ifndef FRAUDRULES_H
#define FRAUDRULES_H

#include "Transaction.h"
#include <vector>
#include <unordered_set>
using namespace std;

class FraudRules {
private:
    unordered_set<int> blacklistedAccounts;

public:
    bool isBlacklisted(int acc);
    void addToBlacklist(int acc);
    double amountRule(Transaction t, const vector<Transaction>& last5);
    double locationRule(Transaction t, const vector<Transaction>& last5);
    double rapidTxnRule(Transaction t, const vector<Transaction>& last5);
    double evaluateRisk(Transaction t, const vector<Transaction>& last5);
};

long computeTimestamp(const string& date, const string& time);
vector<Transaction> readTransactionsFromFile(const string& filename);

#endif // FRAUDRULES_H

