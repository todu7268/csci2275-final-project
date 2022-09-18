#include<iostream>
#include <sstream>

#include "Transaction.hpp"
#include "Block.hpp"
#include "Blockchain.hpp"
#include<vector>

using namespace std;

Blockchain::Blockchain() {
    string temp;
    string helparr[4];

    ifstream I("wallets.txt");
    while(getline(I, temp)){
        w.split(temp, ',', helparr, 4);
        Transaction n("BFC", helparr[0], stod(helparr[3]));
        pending.push_back(n);
    }
    Block g(pending, time(nullptr),"Beginning state");
    chain.push_back(g);

    size_t size1 = pending.size();
    for (size_t i=0; i<size1; i++)
    {
        pending.pop_back(); //empty the pending vector since pending is supposed to be empty at the start
    }


    difficulty = 4;
    miningReward = 10;
}

Block Blockchain::getLatestBlock() { 
    return chain.back();
}

void Blockchain::addTransaction(int coins) {
    bool isSuccess = w.sendBFC(coins); //sendBFC is a bool function, it returns true if transaction was successful

    if (isSuccess){ //if transaction was successful
        Transaction n(name1, name2, coins); //make a new transaction variable
        pending.push_back(n); //push it back into the pending vector.
    }

    //No else statement here because error message is coded up in sendBFC function.
}

bool Blockchain::isChainValid() { 
    for (size_t i=1; i<chain.size();i++)
    {
        if (chain[i].previousHash != chain[i-1].hash) //if the previous hash of the current block doesn't match hash of the previous block
            return false;
        string helper = ""; //create an empty string
        for (size_t j = 0; j<difficulty; j++)
        {
            helper += "0"; //helper just finds what the first #difficulty substring would be.
            //Lets say difficulty is 5, this is going to go from 0 to 4, and helper will be "00000".
            //Now, "00000" has to be the beginning substring, so we check that
        }
        if (chain[i].hash.substr(0,difficulty) != helper)
            return false;
    }
    return true;
}

bool Blockchain::minePendingTransactions(string minerAddress) {
    string prevHash;
    prevHash = chain[chain.size() - 1].hash;
    Block n(pending, time(nullptr), prevHash);
    n.mineBlock(difficulty);
    size_t size = pending.size();
    for (size_t i = 0; i<size; i++){
        pending.pop_back();
    }
    chain.push_back(n);
    Transaction t("BFC", minerAddress, 10);
    pending.push_back(t);
    w.fixWallet();
    w.minerReward(minerAddress); //increments the miner's amount by 10
    w.updateWallet(); //updates the wallet database
    return true;
}

int Blockchain::getBalanceOfAddress() {
    int i = w.displayWalletContents(); //displayWalletContents() prints the contents of one's wallet
    //The wallet has to be accessed by the usernames and passwords in the database, though.
    //That's why we pass nothing inside here, we take it as a user input inside our displayWalletContents() function.
    //displayWalletContents returns a double, the number of coins we have in the wallet, so that's what we return.
    return i;
}

void Blockchain::prettyPrint() {
    for (size_t i=0; i<chain.size(); i++)
    {
        cout<<"Block index "<<i<<":"<<endl; //prints out the block index number
        cout<<chain[i].toString(); //prints out the block (transactions, hash)
        cout<<"----------------------------"<<endl<<endl; //after each block puts some dashes and 2 new lines to make it more readable
    }
}