#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

struct Transaction {
    int fromAccount;       // account ID
    double amount;
    string type;           // deposit or withdrawal
    string location;
    string date;           // "YYYY-MM-DD"
    string time;           // "HH:MM:SS"
    long timestamp;        // numeric timestamp for rapid txn rule
};

#endif // TRANSACTION_H

