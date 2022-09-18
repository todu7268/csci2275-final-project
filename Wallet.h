#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

extern string name1;
extern string name2;

struct Wallets{
    string name; //name of wallet holder
    string password; //password of wallet holder
    string address; //public BFC address to receive coins
    double amount; //amount of BFC currently in wallet
};

class Wallet{
private:
    vector<Wallets> wallets; // contains information about a person's wallet.
public:
    Wallet(); //constructor
    void updateWallet(); //updates the database after every edit
    double displayWalletContents(); //displays a user's wallet contents
    void addNewHolder(string, string, double); //adds new holder
    int split(string str, char ch,string arr[],int size); //helper function to split string.
    bool sendBFC(int amount); //sends BFC amount from 1 person to another, returns true if done, false if failed
    void fixWallet(); //helper function to fix vector<Wallets> wallet after updateWallet() function is called.
    string findAddress(string holder); //finds and returns the public address of given holder.
    string findName(string address); //finds a name given the address of the holder. This is a helper function, obviously.
    void minerReward(string name);
};