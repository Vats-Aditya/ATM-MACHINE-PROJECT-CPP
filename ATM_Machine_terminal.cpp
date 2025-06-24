#include <iostream>
#include <fstream>
using namespace std;
textfile ()
{
ofstream pin("pin.txt");
pin<<"2345";
ofstream balanceamount("balance.txt");
balanceamount<<"1000";
}

//  Validate PIN from pin.txt
bool validatePIN() {
    int enteredPIN, storedPIN;
    ifstream pinFile("pin.txt");
    if (pinFile.is_open()) {
        pinFile >> storedPIN;
        pinFile.close();
    } else {
        cout << "PIN file not found. Default PIN set to 2345\n";
        storedPIN = 2345;}
    cout << "Enter your PIN: ";
    cin >> enteredPIN;
    return enteredPIN == storedPIN;
}

// Get balance from balance.txt
int getBalance() {
    int balance;
    ifstream inFile("balance.txt");
    if (inFile.is_open()) {
        inFile >> balance;
        inFile.close();
    } else {
        cout << "Balance file not found. Default balance set to ₹1000\n";
        balance = 1000;
    }
    return balance;
}

//Update balance to balance.txt
void updateBalance(int balance) {
    ofstream outFile("balance.txt");
    if (outFile.is_open()) {
        outFile << balance;
        outFile.close();
    } else {
        cout << "Error writing to balance file.\n";
    }
}

//Log transaction to log.txt
void logTransaction(string type, int amount, int balance) {
    ofstream logFile("log.txt", ios::app); 
    if (logFile.is_open()) {
        logFile << type << " ₹" << amount << " | New Balance: ₹" << balance << endl;
        logFile.close();
    } else {
        cout << "Unable to write to log file.\n";
    }
}

//Show menu
void showMenu() {
    cout << "\n===== ATM MENU =====\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

//Check balance
void checkBalance(int balance) {
    cout << "Your current balance is ₹" << balance << endl;
}

//Deposit function
int deposit(int balance) {
    int amount;
    cout << "Enter amount to deposit: ₹";
    cin >> amount;
    if (amount > 0) {
        balance += amount;
        cout << "Deposit successful. New balance: ₹" << balance << endl;
        logTransaction("Deposited", amount, balance);
    } else {
        cout << "Invalid deposit amount.\n";
    }
    return balance;
}

//Withdraw function
int withdraw(int balance) {
    int amount;
    cout << "Enter amount to withdraw: ₹";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid withdrawal amount.\n";
    } else if (amount > balance) {
        cout << "Insufficient balance.\n";
    } else {
        balance-=amount;
        cout<<"Withdrawal successful. New balance: ₹"<<balance<<endl;
        logTransaction("Withdrawn",amount,balance);
    }
    return balance;
}

//Main function of atm
int main() {
    int balance, choice;

    cout << "Welcome to Kotak Mahindra Bank\n";

    if (!validatePIN()) {
        cout << "Invalid PIN. Access denied.\n";
        return 0;
    }

    balance = getBalance();

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                balance = deposit(balance);
                updateBalance(balance);
                break;
            case 3:
                balance = withdraw(balance);
                updateBalance(balance);
                break;
            case 4:
                cout << "Thank you for using Kotak Mahindra Bank.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
