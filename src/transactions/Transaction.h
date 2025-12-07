#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

struct Transaction {
    int fromAccount;
    int toAccount;
    double amount;
    string currency;
    string location;
    string type; // debit or credit
    string date; // "YYYY-MM-DD"
    string time; // "HH:MM:SS"
    long timestamp; // numeric timestamp for rapid txn rule
};

#endif // TRANSACTION_H

