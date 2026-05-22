#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accNo;

        cout << "Enter Customer Name: ";
        cin >> name;

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() {
        cout << left << setw(15) << accNo
             << setw(20) << name
             << setw(15) << balance << endl;
    }

    int getAccNo() {
        return accNo;
    }

    void depositMoney() {
        float amount;

        cout << "\nEnter Amount to Deposit: ";
        cin >> amount;

        balance += amount;

        cout << "Amount Deposited Successfully!\n";
    }

    void withdrawMoney() {
        float amount;

        cout << "\nEnter Amount to Withdraw: ";
        cin >> amount;

        if(amount <= balance) {
            balance -= amount;
            cout << "Withdrawal Successful!\n";
        }
        else {
            cout << "Insufficient Balance!\n";
        }
    }
};

void addAccount() {
    BankAccount b;

    ofstream file("bank.dat", ios::binary | ios::app);

    b.createAccount();

    file.write((char*)&b, sizeof(b));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    BankAccount b;

    ifstream file("bank.dat", ios::binary);

    cout << "\n-------------------------------------------------\n";
    cout << left << setw(15) << "Account No"
         << setw(20) << "Name"
         << setw(15) << "Balance" << endl;
    cout << "-------------------------------------------------\n";

    while(file.read((char*)&b, sizeof(b))) {
        b.showAccount();
    }

    file.close();
}

void searchAccount() {
    BankAccount b;

    int acc;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    cout << "\nEnter Account Number to Search: ";
    cin >> acc;

    while(file.read((char*)&b, sizeof(b))) {
        if(b.getAccNo() == acc) {

            cout << "\nAccount Found:\n";

            cout << "-------------------------------------------------\n";
            cout << left << setw(15) << "Account No"
                 << setw(20) << "Name"
                 << setw(15) << "Balance" << endl;
            cout << "-------------------------------------------------\n";

            b.showAccount();

            found = true;
        }
    }

    if(!found) {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

void depositAmount() {
    BankAccount b;

    int acc;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> acc;

    while(file.read((char*)&b, sizeof(b))) {

        if(b.getAccNo() == acc) {

            cout << "\nAccount Found!\n";

            b.depositMoney();

            int pos = (-1) * sizeof(b);

            file.seekp(pos, ios::cur);

            file.write((char*)&b, sizeof(b));

            found = true;

            break;
        }
    }

    if(!found) {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

void withdrawAmount() {
    BankAccount b;

    int acc;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> acc;

    while(file.read((char*)&b, sizeof(b))) {

        if(b.getAccNo() == acc) {

            cout << "\nAccount Found!\n";

            b.withdrawMoney();

            int pos = (-1) * sizeof(b);

            file.seekp(pos, ios::cur);

            file.write((char*)&b, sizeof(b));

            found = true;

            break;
        }
    }

    if(!found) {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

void deleteAccount() {
    BankAccount b;

    int acc;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Account Number to Delete: ";
    cin >> acc;

    while(file.read((char*)&b, sizeof(b))) {

        if(b.getAccNo() != acc) {
            temp.write((char*)&b, sizeof(b));
        }
        else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if(found)
        cout << "\nAccount Deleted Successfully!\n";
    else
        cout << "\nAccount Not Found!\n";
}

int main() {

    int choice;

    do {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";

        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                addAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                depositAmount();
                break;

            case 5:
                withdrawAmount();
                break;

            case 6:
                deleteAccount();
                break;

            case 7:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 7);

    return 0;
}
