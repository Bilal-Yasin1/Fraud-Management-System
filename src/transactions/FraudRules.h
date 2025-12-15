#ifndef FRAUDRULES_H
#define FRAUDRULES_H

#include "Transaction.h"
#include <vector>
#include <unordered_set>

class FraudRules {
private:
    std::unordered_set<int> blacklistedAccounts;

public:
    bool isBlacklisted(int acc) const;
    void addToBlacklist(int acc);

    double amountRule(const Transaction& t,
                      const std::vector<Transaction>& last5) const;
    double locationRule(const Transaction& t,
                        const std::vector<Transaction>& last5) const;
    double rapidTxnRule(const Transaction& t,
                        const std::vector<Transaction>& last5) const;

    double evaluateRisk(const Transaction& t,
                        const std::vector<Transaction>& last5) const;
};

// utilities
long computeTimestamp(const std::string& date,
                      const std::string& time);

std::vector<Transaction> readTransactionsFromFile(const std::string& filename);

#endif
