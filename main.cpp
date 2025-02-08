#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct BankAccount {
    string accountNumber, accountHolderName, email, mobileNumber;
    double accountBalance;
};

BankAccount accounts[30];
int totalAccounts = 0;

void displayHeader() {
    cout << "\n******************************************\n";
    cout << "|         BANKING SYSTEM                 |\n";
    cout << "******************************************\n";
    cout << "|        Created by:Syed Azan Mehdi Shah |\n";
    cout << "****************************************** \n\n";
    cout << "****************************************************\n";
    cout << "               BANKING SYSTEM OBJECTIVE              \n";
    cout << "****************************************************\n";
    cout << "| 1. Open New Account - Create and store details    |\n";
    cout << "| 2. Send Money - Secure fund transfers             |\n";
    cout << "| 3. Show All Accounts - List all accounts          |\n";
    cout << "| 4. Show Transactions - View history               |\n";
    cout << "| 5. Delete All Accounts - Remove all records       |\n";
    cout << "| 6. Quit - Exit safely                             |\n";
    cout << "****************************************************\n";
}

void saveAccountsToFile() {
    ofstream file("BankData.txt");
    if (file) {
        file << totalAccounts << endl;
        for (int i = 0; i < totalAccounts; i++)
            file << accounts[i].accountNumber << "," << accounts[i].accountHolderName << "," << accounts[i].email << ","
                 << accounts[i].accountBalance << "," << accounts[i].mobileNumber << endl;
    }
}

void loadAccountsFromFile() {
    ifstream file("BankData.txt");
    if (file) {
        file >> totalAccounts;
        file.ignore();
        for (int i = 0; i < totalAccounts; i++) {
            string line;
            getline(file, line);
            stringstream ss(line);
            getline(ss, accounts[i].accountNumber, ',');
            getline(ss, accounts[i].accountHolderName, ',');
            getline(ss, accounts[i].email, ',');
            ss >> accounts[i].accountBalance;
            ss.ignore();
            getline(ss, accounts[i].mobileNumber, ',');
        }
    }
}

void createNewAccount() {
    if (totalAccounts >= 30) {
        cout << "\nDatabase Full!";
        return;
    }

    cout << "\nEnter Name: ";
    cin.ignore();
    getline(cin, accounts[totalAccounts].accountHolderName);
    cout << "Enter Account No: ";
    cin >> accounts[totalAccounts].accountNumber;
    cout << "Enter Email: ";
    cin >> accounts[totalAccounts].email;
    cout << "Enter Initial Balance: ";
    cin >> accounts[totalAccounts].accountBalance;
    cout << "Enter Mobile No: ";
    cin >> accounts[totalAccounts].mobileNumber;
    totalAccounts++;
    saveAccountsToFile();
    cout << "\nAccount Created Successfully!";
}

void displayAllAccounts() {
    if (totalAccounts == 0) {
        cout << "\nNo Accounts Found!";
        return;
    }
    for (int i = 0; i < totalAccounts; i++) {
        cout << "\n*********************************************";
        cout << "\nAccount No   : " << accounts[i].accountNumber;
        cout << "\nName         : " << accounts[i].accountHolderName;
        cout << "\nEmail        : " << accounts[i].email;
        cout << "\nBalance      : " << accounts[i].accountBalance;
        cout << "\nMobile No    : " << accounts[i].mobileNumber;
        cout << "\n******************************************";
    }
}

void deleteAllAccounts() {
    totalAccounts = 0;
    saveAccountsToFile();
    cout << "\nAll Accounts Deleted Successfully!";
}

void processMoneyTransfer() {
    string senderAcc, receiverAcc;
    double transferAmount;
    cout << "\nEnter Your Account No: ";
    cin >> senderAcc;
    cout << "Enter Receiver's Account No: ";
    cin >> receiverAcc;
    cout << "Enter Amount to Send: ";
    cin >> transferAmount;

    if (senderAcc == receiverAcc) {
        cout << "\nCannot transfer money to the same account!";
        return;
    }

    int senderIndex = -1, receiverIndex = -1;
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == senderAcc) senderIndex = i;
        if (accounts[i].accountNumber == receiverAcc) receiverIndex = i;
    }

    if (senderIndex == -1 || receiverIndex == -1) {
        cout << "\nInvalid Account Number!";
        return;
    }

    if (accounts[senderIndex].accountBalance < transferAmount) {
        cout << "\nInsufficient Balance!";
        return;
    }

    accounts[senderIndex].accountBalance -= transferAmount;
    accounts[receiverIndex].accountBalance += transferAmount;
    saveAccountsToFile();
    cout << "\nTransaction Successful!";
}

void displayTransactionHistory() {
    ifstream file("Transactions.txt");
    if (file) {
        string line;
        cout << "\n------------------------------------------\n";
        cout << "|         TRANSACTION HISTORY            |\n";
        cout << "------------------------------------------\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
    } else {
        cout << "\nNo Transactions Found!";
    }
}

int main() {
    displayHeader();
    loadAccountsFromFile();
    while (true) {
        int choice;
        cout << "\nMenu:\n";
        cout << "1. Open New Account\n";
        cout << "2. Send Money\n";
        cout << "3. Show All Accounts\n";
        cout << "4. Show Transactions\n";
        cout << "5. Delete All Accounts\n";
        cout << "6. Quit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createNewAccount(); break;
            case 2: processMoneyTransfer(); break;
            case 3: displayAllAccounts(); break;
            case 4: displayTransactionHistory(); break;
            case 5: deleteAllAccounts(); break;
            case 6: cout << "\nThank You for Using the System :)!"; return 0;
            default: cout << "\nInvalid Choice! Please try again.";
        }
    }
}
