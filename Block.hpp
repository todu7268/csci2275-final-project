#pragma once
#include<iostream>
#include <vector>
#include "Transaction.hpp"
#include "Wallet.h"

using namespace std;

class Block {
private:
    long long nonce; // An arbitrary number crucial in mining
    vector<Transaction> transactions; //vector of transactions
    time_t timestamp; // Time when mined
    
public:
    string hash; // Hash of this block
    string previousHash; // Hash of previous block
    Block(vector<Transaction> _transactions, time_t _timestamp, string _previousHash);
    void setPreviousHash(string hash);
    string calculateHash();
    void mineBlock(unsigned int nDifficulty);
    string toString();
};

