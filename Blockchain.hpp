#pragma once
#include<iostream>
#include "Block.hpp"
#include "Transaction.hpp"
#include "Wallet.h"

#include <vector>

using namespace std;

class Blockchain {
    private:
        unsigned int difficulty;
        vector<Block> chain;
        vector<Transaction> pending;
        int miningReward;

    public:
       Blockchain(); 
       void addTransaction(int coins);
       bool isChainValid();
       bool minePendingTransactions(string minerAddress);
       int getBalanceOfAddress();
       void prettyPrint();
       Wallet w;

    private:
        Block getLatestBlock();
};
