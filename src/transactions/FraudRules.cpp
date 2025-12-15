#include "FraudRules.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

bool FraudRules::isBlacklisted(int acc) const {
    return blacklistedAccounts.count(acc);
}

void FraudRules::addToBlacklist(int acc) {
    blacklistedAccounts.insert(acc);
}

double FraudRules::amountRule(const Transaction& t,
                              const vector<Transaction>& last5) const {
    if (last5.empty()) return 0;

    double avg = 0;
    for (auto& x : last5) avg += x.amount;
    avg /= last5.size();

    if (t.amount > avg * 3) return 30;
    if (t.amount > avg * 2) return 15;
    return 0;
}

double FraudRules::locationRule(const Transaction& t,
                                const vector<Transaction>& last5) const {
    for (auto& x : last5)
        if (x.location == t.location)
            return 0;
    return last5.empty() ? 0 : 20;
}

double FraudRules::rapidTxnRule(const Transaction& t,
                                const vector<Transaction>& last5) const {
    int count = 0;
    for (auto& x : last5)
        if (abs(t.timestamp - x.timestamp) <= 10)
            count++;

    if (count >= 3) return 25;
    if (count == 2) return 10;
    return 0;
}

double FraudRules::evaluateRisk(const Transaction& t,
                                const vector<Transaction>& last5) const {
    if (isBlacklisted(t.accountID))
        return -1;

    return amountRule(t, last5)
         + locationRule(t, last5)
         + rapidTxnRule(t, last5);
}

// ---------------- Utilities ----------------

long computeTimestamp(const string& date, const string& time) {
    tm t{};
    t.tm_year = stoi(date.substr(0,4)) - 1900;
    t.tm_mon  = stoi(date.substr(5,2)) - 1;
    t.tm_mday = stoi(date.substr(8,2));
    t.tm_hour = stoi(time.substr(0,2));
    t.tm_min  = stoi(time.substr(3,2));
    t.tm_sec  = stoi(time.substr(6,2));
    return mktime(&t);
}

vector<Transaction> readTransactionsFromFile(const string& filename) {
    vector<Transaction> txns;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file\n";
        return txns;
    }

    Transaction t;
    while (file >> t.transactionID >> t.amount >> t.type
                >> t.accountID >> t.location >> t.date >> t.time) {
        t.timestamp = computeTimestamp(t.date, t.time);
        txns.push_back(t);
    }

    return txns;
}
