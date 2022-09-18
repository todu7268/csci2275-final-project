#include "Wallet.h"

string name1; //global variables
string name2; //needed in blockchain class

void Wallet::fixWallet(){ //called after updateWallet() to make sure the vector in the class Wallet has correct values always.
    if (wallets.size() == 0)
        return;
    else
    {
        ifstream I;
        I.open("wallets.txt");
        string temp;
        string helpArr[4];
        int i=0;
        while (getline(I, temp)){
            split(temp,',', helpArr, 4);
            wallets[i].name = helpArr[0];
            wallets[i].address = helpArr[2];
            wallets[i].password = helpArr[1];
            wallets[i].amount = stod(helpArr[3]);
            i++;
        }
    }
}
Wallet::Wallet() { //constructor - does nothing if it's an empty database, and if database exists, it imports the data from the txt file
    ifstream I;
    I.open("wallets.txt");
    string temp;
    string helpArr[4];
    while (getline(I, temp)){
        split(temp,',', helpArr, 4);
        Wallets n;
        n.name = helpArr[0];
        n.password = helpArr[1];
        n.address = helpArr[2];
        n.amount = stod(helpArr[3]);
        wallets.push_back(n);
    }
}

void Wallet::updateWallet(){ //updates the wallets.txt file. Used after every change.
    ofstream O;
    O.open("wallets.txt");
    for (int i=0; i<wallets.size(); i++)
    {
        O << wallets[i].name + "," + wallets[i].password + "," + wallets[i].address + ",";
        O << wallets[i].amount;
        O<<endl;
    }
}

int Wallet::split(string str, char ch,string arr[],int size) //helper function
{
    if (str.length() == 0)
        return 0;
    string temp;
    int index = 0;
    int len = str.length();
    int count_words = 1;
    for(int i=0;i<len;i++)
    {
        if(str[i]==ch)
            count_words++;
    }

    if(count_words > size)
    {
        for(int i=0;i<len;i++)
        {
            if(str[i]==ch)
            {
                arr[index]=temp;
                index++;
                temp="";
            }
            else
                temp+=str[i];
        }
        arr[index]=temp;
        return -1;
    }
    for(int i=0;i<len;i++)
    {
        if(str[i]==ch)
        {
            arr[index]=temp;
            index++;
            temp="";
        }
        else
            temp+=str[i];
    }
    arr[index]=temp;
    return count_words;

}

double Wallet::displayWalletContents(){ //displays the contents of someone's wallet.
    string helpArr[4];
    ifstream I;
    I.open("wallets.txt");
    cout<<"Enter your name: ";
    string name;
    cin>>name;
    cout<<endl;
    string temp;
    bool isFound = false;
    while (getline(I, temp)){
        split (temp, ',', helpArr, 4);
        if (name == helpArr[0]){
            isFound = true;
            break;
        }
    }
    if (!isFound){
        cout<<"That name was not found in the database."<<endl;
        displayWalletContents();
    }

    else{
        cout<<"Enter your password: ";
        string password;
        cin>>password;
        cout<<endl;
        int i;
        for (i=3; i>0; i--)
        {
            if (password != helpArr[1])
            {
                cout<<"Password incorrect, "<<i<<" attempts remaining."<<endl;
                cout<<"Enter your password: ";
                cin>>password;
                cout<<endl;
                if (helpArr[1] == password)
                {
                    cout<<helpArr[0]<<", public address "<<helpArr[2]<<", currently has "<<helpArr[3]<<" BFC in his balance."<<endl<<endl;
                    return stod(helpArr[3]);
                }
            }
            else{
                cout<<helpArr[0]<<", public address "<<helpArr[2]<<" currently has "<<helpArr[3]<<" BFC in his balance."<<endl;
                return stod(helpArr[3]);
            }
        }
        if (i == 0){
            srand(time(NULL));
            for (;true;){
                int c, n;
                n = rand() % 100000 + 700000;
                cout<<"Please enter the following captcha: "<<n<<endl;
                cin>>c;
                if (c == n){
                    displayWalletContents();
                    break;
                }

                else
                    cout<<"Captcha incorrect."<<endl;
            }
        }
    }

}

string generateNewAddress() //helper function
{
    int i;
    srand(time(NULL));
    i = rand() % 100000 + 100000;
    string str = "0x" + to_string(i);
    return str;
}

void Wallet::addNewHolder(string name, string password, double amount){ //adds a new holder.
    for (int i=0; i< wallets.size(); i++)
    {
        if (name == wallets[i].name){
            cout<<"Name already taken."<<endl<<endl;
            return;
        }
    }
    Wallets n;
    n.name = name;
    string address = generateNewAddress();
    a:int i=0;
    for (i=0; i<wallets.size(); i++){
        if (wallets[i].address == address){
            address = generateNewAddress();
            goto a;
        }
    }
    n.address = address;
    n.password = password;
    n.amount = amount;
    wallets.push_back(n);
    updateWallet();
    fixWallet();
}

bool Wallet::sendBFC(int amount) { //function used to send buffcoins to another wallet.
    string helpArr[4];
    ifstream I;
    I.open("wallets.txt");
    string name;
    string temp;
    cout << "Enter your name: ";
    cin >> name;
    cout << endl;
    bool isFound = false;
    while (getline(I, temp)) {
        split(temp, ',', helpArr, 4);
        if (name == helpArr[0]) {
            isFound = true;
            name1 = name;
            break;
        }
    }
    if (!isFound) {
        cout << "That name was not found in the database." << endl;
        sendBFC(amount);
    } else {
        cout << "Enter your password: ";
        string password;
        cin >> password;
        cout << endl;
        int i;
        for (i = 3; i > 0; i--) {
            if (password != helpArr[1]) {
                cout << "Password incorrect, " << i << " attempts remaining." << endl;
                cout << "Enter your password: ";
                cin >> password;
                cout << endl;
                if (helpArr[1] == password) {
                    if (amount > stod(helpArr[3])) {
                        cout << "You have insufficient funds." << endl;
                        return false;
                    }
                    string receiverAddress;
                    string helpArr2[4];
                    bool isFound2 = false;
                    cout << "Enter the receiver address: ";
                    cin >> receiverAddress;
                    cout<<endl;
                    ifstream I1;
                    I1.open("wallets.txt");
                    while (getline(I1, temp)) {
                        split(temp, ',', helpArr2, 4);
                        if (receiverAddress == helpArr2[2]) {
                            isFound2 = true;
                            name2 = findName(receiverAddress);
                            break;
                        }
                    }
                    if (!isFound2) {
                        cout << "That address could not be found in the database." << endl;
                        sendBFC(amount);
                    } else {
                        int index1=0, index2=0;
                        for (int i = 0; i < wallets.size(); i++) {
                            if (name == wallets[i].name) {
                                index1 = i;
                                break;
                            }
                        }
                        for (int j = 0; j < wallets.size(); j++) {
                            if (receiverAddress == wallets[j].address) {
                                index2 = j;
                                break;
                            }
                        }

                        wallets[index1].amount -= amount;
                        wallets[index2].amount += amount;
                        updateWallet();
                        fixWallet();
                    }
                    return true;
                }
            } else {
                if (amount > stod(helpArr[3])) {
                    cout << "You have insufficient funds." << endl;
                    return false;
                }
                string receiverAddress;
                string helpArr2[4];
                bool isFound2 = false;
                cout << "Enter the receiver address: ";
                cin >> receiverAddress;
                cout<<endl;
                ifstream I1;
                I1.open("wallets.txt");
                while (getline(I1, temp)) {
                    split(temp, ',', helpArr2, 4);
                    if (receiverAddress == helpArr2[2]) {
                        isFound2 = true;
                        name2 = findName(receiverAddress);
                        break;
                    }
                }
                if (!isFound2) {
                    cout << "That address could not be found in the database." << endl;
                    sendBFC(amount);
                } else {
                    int index1=0, index2=0;
                    for (int i = 0; i < wallets.size(); i++) {
                        if (name == wallets[i].name) {
                            index1 = i;
                            break;
                        }
                    }
                    for (int j = 0; j < wallets.size(); j++) {
                        if (receiverAddress == wallets[j].address) {
                            index2 = j;
                            break;
                        }
                    }

                    wallets[index1].amount -= amount;
                    wallets[index2].amount += amount;
                    updateWallet();
                    fixWallet();
                }
                return true;
            }
        }
        if (i == 0) {
            srand(time(NULL));
            for (; true;) {
                int c, n;
                n = rand() % 100000 + 700000;
                cout << "Please enter the following captcha: " << n << endl;
                cin >> c;
                if (c == n) {
                    sendBFC(amount);
                    break;
                } else
                    cout << "Captcha incorrect." << endl;
            }
        }
    }
}

string Wallet::findAddress(string holder){
    for(size_t i=0; i<wallets.size(); i++)
        if (holder == wallets[i].name)
            return wallets[i].address;

    return "";
}

string Wallet::findName(string address) {
    for (size_t i=0; i<wallets.size(); i++)
        if (address == wallets[i].address)
            return wallets[i].name;

    return "";
}

void Wallet::minerReward(string name) {
    for (size_t i=0; i<wallets.size(); i++)
    {
        if(wallets[i].name == name)
            wallets[i].amount+=10;
    }
}