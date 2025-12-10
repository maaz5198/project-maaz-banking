#include <iostream>

using namespace std;

class BankAccount
{
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNo = 0, string name = "", double bal = 0)
    {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    void setAccount(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    void deposit(double amount)
    {
        balance += amount;
    }

    bool withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            return true;
        }
        return false;
    }

    int getAccNo()
    {
        return accountNumber;
    }
    double getBalance()
    {
        return balance;
    }

    virtual void displayAccount()
    {
        cout << "Account No: " << accountNumber << endl;
        cout << "Holder Name: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual void calculateInterest()
    {
        cout << "No interest calculation for base account." << endl;
    }
};

class SavingAccount : public BankAccount
{
    double interestRate;

public:
    SavingAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal)
    {
        this->interestRate = rate;
    }

    void setSavingAccount(int accNo, string name, double bal, double rate)
    {
        setAccount(accNo, name, bal);
        this->interestRate = rate;
    }

    void calculateInterest() override
    {
        double interest = balance * (interestRate / 100);
        cout << "Saving Account Interest: " << interest << endl;
    }
};

int main()
{
    BankAccount *accounts[10];
    int totalAccounts = 0;
    int choice, accNo, duration;
    string name;
    double balance, rate, amount;

    do
    {
        cout << " BANKING SYSTEM MENU" << endl;
        cout << "1. Create Saving Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Display Account" << endl;
        cout << "5. Calculate Interest" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (totalAccounts < 10)
            {
                cout << "Enter Account Number: ";
                cin >> accNo;
                cout << "Enter Account Holder Name: ";
                cin >> name;
                cout << "Enter Initial Balance: ";
                cin >> balance;
                cout << "Enter Interest Rate (%): ";
                cin >> rate;

                accounts[totalAccounts] = new SavingAccount(accNo, name, balance, rate);
                totalAccounts++;
                cout << "Saving Account Created!" << endl;
            }
            else
            {
                cout << "Account limit reached!" << endl;
            }
            break;

        case 2:
            cout << "Enter Account Index (0-" << totalAccounts - 1 << "): ";
            cin >> accNo;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            if (accNo >= 0 && accNo < totalAccounts)
            {
                accounts[accNo]->deposit(amount);
                cout << "Deposited successfully. New Balance: "
                     << accounts[accNo]->getBalance() << endl;
            }
            else
            {
                cout << "Invalid account index!\n";
            }
            break;

        case 3:
            cout << "Enter Account Index (0-" << totalAccounts - 1 << "): ";
            cin >> accNo;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            if (accNo >= 0 && accNo < totalAccounts)
            {
                if (accounts[accNo]->withdraw(amount))
                    cout << "Withdrawn successfully. New Balance: "
                         << accounts[accNo]->getBalance() << endl;
                else
                    cout << "Withdrawal failed! Insufficient balance." << endl;
            }
            else
            {
                cout << "Invalid account index!" << endl;
            }
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;

            {
                bool found = false;
                for (int i = 0; i < totalAccounts; i++)
                {
                    if (accounts[i]->getAccNo() == accNo)
                    {
                        accounts[i]->displayAccount();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Account not found!" << endl;
                }
            }
            break;

        case 5:
            cout << "Enter Account Index (0-" << totalAccounts - 1 << "): ";
            cin >> accNo;
            if (accNo >= 0 && accNo < totalAccounts)
                accounts[accNo]->calculateInterest();
            else
                cout << "Invalid account index!" << endl;
            break;

        case 0:
            cout << "Exiting... Thank you!" << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 0);

    for (int i = 0; i < totalAccounts; i++)
        delete accounts[i];

    return 0;
}