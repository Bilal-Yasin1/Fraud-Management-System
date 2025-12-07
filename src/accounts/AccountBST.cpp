using namespace std;
#include<bits/stdc++.h>
// transactions:
class transaction
{
public:
    double amount;
    string currency;
    string type;
    int accountID;
    string date;
    string time;
    string location;
    int riskScore;
    // default constructor:
    transaction(){}
    // parameterised one:
    transaction(double a, string c,string t,int a,string d,string ti, string l)
    {
        amount=a;currency=c;type=t;accountID=a;date=d;time=ti;location=l;
    }
};
void captureCurrentDateTime(string& dateStr, string& timeStr) 
{
    // 1. Get the current calendar time as a time_t object
    time_t now = time(0);
    // 2. Convert time_t to a tm structure for local time, which holds date/time components
    // The current time for this execution is Sunday, December 7, 2025 at 2:40:57 PM PKT.
    struct tm* local_time_info = localtime(&now);
    // Character buffers to hold the formatted output strings
    char date_buffer[20];
    char time_buffer[20];
    // 3. Format the Date into the dateStr variable
    // %Y: Year (e.g., 2025) | %m: Month (01-12) | %d: Day of month (01-31)
    strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", local_time_info);
    dateStr = date_buffer;
    // 4. Format the Time into the timeStr variable
    // %H: Hour (00-23) | %M: Minute (00-59) | %S: Second (00-59)
    strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", local_time_info);
    timeStr = time_buffer;
}
// Node of linkedlist:
class llnode
{
public:
    transaction t;
    llnode* next;
    llnode(transaction obj)
    {
        t=obj;
        next=NULL;
    }
};
// LinkedList of transactions:
class ll
{
    llnode* head;
    llnode* tail;
public:
    ll()
    {
        head=tail=NULL;
    }
    void push_front(transaction obj)
    {
        llnode* newNode=new llnode(obj);
        if(head==NULL)
        {
            head=tail=newNode;
            return;
        }
        newNode->next=head;
        head=newNode;
        return;
    }
    void push_back(transaction obj)
    {
        llnode* newNode=new llnode(obj);
        if(head==NULL)
        {
            head=tail=newNode;
            return;
        }
        tail->next=newNode;
        tail=newNode;
        return;
    }
    vector<string> retrievelastlocations(int n)
    {
        llnode* temp=head;
        int count=0;
        while(temp!=NULL)
        {
            ++count;
            temp=temp->next;
        }
        temp=head;
        vector<string>v;
        if(count>5)
        {
            int k=0;
            temp=head;
            while((count-k)!=5)
            {
                temp=temp->next;
                ++k;
            }
            while(temp!=NULL)
            {
                v.push_back(temp->t.location);
                temp=temp->next;
            }
        }
        else
        {
            temp=head;
            while(temp!=NULL)
            {
                v.push_back(temp->t.location);
                temp=temp->next;
            }
        }
        return v;
    }
    vector<string> retrievelastdates(int n)
    {
        llnode* temp=head;
        int count=0;
        while(temp!=NULL)
        {
            ++count;
            temp=temp->next;
        }
        temp=head;
        vector<string>v;
        if(count>5)
        {
            int k=0;
            temp=head;
            while((count-k)!=5)
            {
                temp=temp->next;
                ++k;
            }
            while(temp!=NULL)
            {
                v.push_back(temp->t.date);
                temp=temp->next;
            }
        }
        else
        {
            temp=head;
            while(temp!=NULL)
            {
                v.push_back(temp->t.date);
                temp=temp->next;
            }
        }
        return v;
    }
    vector<string> retrievelasttime(int n)
    {
        llnode* temp=head;
        int count=0;
        while(temp!=NULL)
        {
            ++count;
            temp=temp->next;
        }
        temp=head;
        vector<string>v;
        if(count>5)
        {
            int k=0;
            temp=head;
            while((count-k)!=5)
            {
                temp=temp->next;
                ++k;
            }
            while(temp!=NULL)
            {
                v.push_back(temp->t.time);
                temp=temp->next;
            }
        }
        else
        {
            temp=head;
            while(temp!=NULL)
            {
                v.push_back(temp->t.time);
                temp=temp->next;
            }
        }
        return v;
    }
};
class BSTNode
{
public:
    int accountID;
    string accountHolderName;
    BSTNode* left;
    BSTNode* right;
    llnode* head;
    bool isBlackList;
    BSTNode(int val,string name)
    {
        accountID=val;
        accountHolderName=name;
        left=right=NULL;
        head=NULL;
        isBlackList=false;
    }
};
BSTNode* insert(BSTNode* root,int accID,string accHolder)
{
    if(root==NULL)
    {
        return new BSTNode(accID,accHolder);
    }
    if(accID<root->accountID)
    {
        root->left=insert(root->left,accID,accHolder);
    }
    else if(accID>root->accountID)
    {
        root->right=insert(root->right,accID,accHolder);
    }
    return root;
}
BSTNode* search(BSTNode* root,int accID)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(accID<root->accountID)
    {
        return search(root->left,accID);
    }
    else if(accID>root->accountID)
    {
        return search(root->right,accID);
    }
    else
    {
        return root;
    }
}
void inOrder(BSTNode* root)
{
    if(root==NULL)
    {
        return;
    }
    inOrder(root->left);
    cout<<"Account ID: "<<root->accountID<<endl;
    cout<<"Account Holder Name: "<<root->accountHolderName<<endl;
    inOrder(root->right);
}
int main()
{
    cout<<"works fine"<<endl;
    string date,time;
    captureCurrentDateTime(date,time);
    transaction t(123300,"PKR","CREDIT",1333,date,time,"USA");
    cout<<t.amount<<" "<<t.currency<<" "<<t.type<<" "<<t.accountID<<" "<<t.date<<" "<<t.time<<" "<<t.location<<endl;
}