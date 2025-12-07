#include "FraudRules.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

bool FraudRules::isBlacklisted(int acc) {
    return blacklistedAccounts.count(acc);
}

void FraudRules::addToBlacklist(int acc) {
    blacklistedAccounts.insert(acc);
}

double FraudRules::amountRule(Transaction t, const vector<Transaction>& last5) {
    if (last5.empty()) return 0;
    double avg = 0;
    for (auto &x : last5) avg += x.amount;
    avg /= last5.size();
    if (t.amount > avg * 3) return 30;
    if (t.amount > avg * 2) return 15;
    return 0;
}

double FraudRules::locationRule(Transaction t, const vector<Transaction>& last5) {
    for (auto &x : last5)
        if (x.location == t.location) return 0;
    return 20;
}

double FraudRules::rapidTxnRule(Transaction t, const vector<Transaction>& last5) {
    int count = 0;
    for (auto &x : last5)
        if (abs(t.timestamp - x.timestamp) <= 10) count++;
    if (count >= 3) return 25;
    if (count == 2) return 10;
    return 0;
}

double FraudRules::evaluateRisk(Transaction t, const vector<Transaction>& last5) {
    if (isBlacklisted(t.fromAccount)) return -1;
    double score = 0;
    score += amountRule(t, last5);
    score += locationRule(t, last5);
    score += rapidTxnRule(t, last5);
    return score;
}

// ---------------- Utility functions ----------------

long computeTimestamp(const string& date, const string& time) {
    int day = stoi(date.substr(8,2));
    int hour = stoi(time.substr(0,2));
    int min = stoi(time.substr(3,2));
    int sec = stoi(time.substr(6,2));
    return day*10000 + hour*100 + min;
}

vector<Transaction> readTransactionsFromFile(const string& filename) {
    vector<Transaction> transactions;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return transactions;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Transaction t;
        ss >> t.amount >> t.type >> t.fromAccount >> t.location >> t.date >> t.time;
        t.timestamp = computeTimestamp(t.date, t.time);
        transactions.push_back(t);
    }

    file.close();
    return transactions;
}

