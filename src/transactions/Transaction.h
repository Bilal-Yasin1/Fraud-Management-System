#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

struct Transaction {
    int transactionID;
    int accountID;
    double amount;
    string type;      // CREDIT / DEBIT
    string location;
    string date;      // YYYY-MM-DD
    string time;      // HH:MM:SS
    long timestamp;   // epoch seconds
    int riskScore;

    Transaction() : transactionID(0), accountID(0), amount(0), riskScore(0) {}

    // Add this constructor
    Transaction(int txnID, int accID, double amt, const string& t,
                const string& loc, const string& d, const string& tm, long ts)
        : transactionID(txnID), accountID(accID), amount(amt), type(t),
          location(loc), date(d), time(tm), timestamp(ts), riskScore(0) {}
};

#endif
