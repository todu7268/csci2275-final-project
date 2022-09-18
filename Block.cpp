#include<iostream>
#include <sstream>


#include "Transaction.hpp"
#include "Block.hpp"
#include "sha256.hpp"

using namespace std;

Block::Block(vector<Transaction> _transactions, time_t _timestamp, string _previousHash) {
    nonce = -1;
    transactions = _transactions;
    previousHash = _previousHash;
    timestamp = _timestamp;
    hash = calculateHash();
}

void Block::setPreviousHash(string _previousHash) {
    previousHash = _previousHash;
}

string Block::calculateHash() {
    stringstream ss;
    ss<<previousHash<<nonce<<timestamp;
    for(size_t i=0; i<transactions.size(); i++)
        ss<<transactions[i].getSender()<<transactions[i].getReceiver()<<transactions[i].getAmount();
    return sha256(ss.str());
}

void Block::mineBlock(unsigned int difficulty) {
    string helper="";
    for (size_t i=0; i<difficulty; i++)
        helper += "0";
    for(;true;)
    {
        if (hash.substr(0,difficulty) == helper)
            break;
        nonce++;
        hash = calculateHash();
    }
    cout<<"Hash found: "<< hash<<endl;
    cout<<"Block mined!"<<endl;
}

string Block::toString() {
    stringstream ss;
    ss<<"Hash: "<<endl<<"\t"<<hash<<endl;
    ss<<"Transactions: "<<endl;
    for(size_t i=0; i<transactions.size(); i++)
    {
        ss<<"\t"<<transactions[i].toString()<<endl;
    }
    return ss.str();
}