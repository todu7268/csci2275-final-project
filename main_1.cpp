#include <iostream>
#include <fstream>
#include "Blockchain.hpp"
#include "Block.hpp"
#include "sha256.hpp"
#include "Transaction.hpp"
#include "Wallet.h"

using namespace std;

int main(int argc, char* argv[])
{
    Blockchain BuffCUoin;
    int input = 0;
    int coins;
    string name;
    string password;

    for (;input != 6;)
    {
        cout<<"Select a numerical option: "<<endl;
        cout<<"1. Add Transaction"<<endl;
        cout<<"2. Mine Pending Transactions"<<endl;
        cout<<"3. Display Wallet Contents"<<endl;
        cout<<"4. Display Public Address"<<endl;
        cout<<"5. Add New Holder"<<endl;
        cout<<"6. Quit"<<endl;
        cout<<"#> ";
        cin>>input;
        cout<<endl;
        switch(input){
            case 1:
                cout<<"How many coins do you wish to send? "<<endl;
                cin>>coins;
                BuffCUoin.addTransaction(coins);
                break;
            case 2:
                cout<<"Enter your name: ";
                cin>>name;
                cout<<endl;
                BuffCUoin.minePendingTransactions(name);
                break;
            case 3:
                BuffCUoin.getBalanceOfAddress();
                break;
            case 4:
                cout<<"Enter the name of holder: ";
                cin>>name;
                cout<<endl;
                if (BuffCUoin.w.findAddress(name) != "")
                {
                    cout<<"The public address of "<<name<<" is: "<<BuffCUoin.w.findAddress(name)<<endl;
                }
                else{
                    cout<<"That name could not be found in the database."<<endl;
                }
                break;
            case 5:
                cout<<"Enter name of new holder: ";
                cin>>name;
                cout<<endl;
                cout<<"Enter the password: ";
                cin>>password;
                cout<<endl;
                BuffCUoin.w.addNewHolder(name, password, 0);
                break;

            case 6: {
                cout<<"Quitting, goodbye!"<<endl;
                break;
            }
            default:
                cout<<"Invalid input!"<<endl;
        }
    }
    return 0;
}
