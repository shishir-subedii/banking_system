#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class BankAccount
{
private:
    string accountNumber;
    string name;
    float balance;

public:
    // Constructor
    BankAccount(string accNum = "", string accName = "", float accBalance = 0.0)
        : accountNumber(accNum), name(accName), balance(accBalance) {}

    // Getters
    string getAccountNumber() const { return accountNumber; }
    string getName() const { return name; }
    float getBalance() const { return balance; }

    // Setters
    void setBalance(float newBalance) { balance = newBalance; }

    // Methods
    void createAccount();
    static void searchAccount(const string &searchAccountNumber);
    static void displayAllAccounts();
    static void deleteAccount(const string &accountNumberToDelete);
    static void deposit(const string &accountNumberToDeposit, float depositAmount);
    static void withdraw(const string &accountNumberToWithdraw, float withdrawAmount);

    // File Handling Methods
    static bool accountExists(const string &accountNumber);
};

// Create a new account
void BankAccount::createAccount()
{
    ifstream ifs("accounts.txt");
    ofstream ofs("accounts.txt", ios::app); // Open file in append mode

    if (!ifs || !ofs)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    if (accountExists(accountNumber))
    {
        cout << "Account number already exists. Please choose a different number." << endl;
    }
    else
    {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "-------------------------\n";

        ofs << accountNumber << "," << name << "," << fixed << setprecision(2) << balance << endl;
        cout << "Account created and saved successfully.\n";
    }

    ifs.close();
    ofs.close();
}

// Check if an account exists
bool BankAccount::accountExists(const string &accountNumber)
{
    ifstream ifs("accounts.txt");
    if (!ifs)
    {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line;
    while (getline(ifs, line))
    {
        string existingAccountNumber;
        stringstream ss(line);

        // Read the account number from the file
        getline(ss, existingAccountNumber, ',');

        // Compare the entered account number with the existing one
        if (existingAccountNumber == accountNumber)
        {
            return true;
        }
    }

    ifs.close();
    return false;
}

// Search for an account
void BankAccount::searchAccount(const string &searchAccountNumber)
{
    cout << "\n-------------------------\n";
    ifstream ifs("accounts.txt");
    if (!ifs)
    {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    bool accountFound = false;

    while (getline(ifs, line))
    {
        stringstream ss(line);
        string accountNumber;
        string name;
        float balance;

        getline(ss, accountNumber, ',');
        getline(ss, name, ',');
        ss >> balance;

        if (accountNumber == searchAccountNumber)
        {
            cout << "Account Found!" << endl;
            cout << "Account Number: " << accountNumber << endl;
            cout << "Account Holder Name: " << name << endl;
            cout << "Balance: " << fixed << setprecision(2) << balance << endl;
            accountFound = true;
            break;
        }
    }

    if (!accountFound)
    {
        cout << "Account with number " << searchAccountNumber << " not found." << endl;
    }

    ifs.close();
}

// Display all accounts
void BankAccount::displayAllAccounts()
{
    cout << "\n-------------------------\n";
    ifstream ifs("accounts.txt");
    if (!ifs)
    {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    string line;

    cout << "Displaying all accounts:\n";
    cout << "========================\n";

    while (getline(ifs, line))
    {
        stringstream ss(line);
        string accountNumber;
        string name;
        float balance;

        getline(ss, accountNumber, ',');
        getline(ss, name, ',');
        ss >> balance;

        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << name << endl;
        cout << "Balance: " << fixed << setprecision(2) << balance << endl;
        cout << "------------------------\n";
    }

    ifs.close();
}

// Delete an account
void BankAccount::deleteAccount(const string &accountNumberToDelete)
{
    cout << "\n-------------------------\n";
    ifstream ifs("accounts.txt");
    ofstream ofs("temp.txt"); // Temporary file to store updated accounts

    if (!ifs || !ofs)
    {
        cout << "Error opening file for reading/writing!" << endl;
        return;
    }

    string line;
    bool accountFound = false;

    while (getline(ifs, line))
    {
        stringstream ss(line);
        string accountNumber;
        string name;
        float balance;

        getline(ss, accountNumber, ',');
        getline(ss, name, ',');
        ss >> balance;

        if (accountNumber == accountNumberToDelete)
        {
            accountFound = true;
            continue;
        }

        ofs << accountNumber << "," << name << "," << fixed << setprecision(2) << balance << endl;
    }

    ifs.close();
    ofs.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (accountFound)
    {
        cout << "Account with number " << accountNumberToDelete << " has been deleted successfully." << endl;
    }
    else
    {
        cout << "Account with number " << accountNumberToDelete << " not found." << endl;
    }
}

// Deposit into an account
void BankAccount::deposit(const string &accountNumberToDeposit, float depositAmount)
{
    cout << "\n-------------------------\n";
    ifstream ifs("accounts.txt");
    ofstream ofs("temp.txt"); // Temporary file to store updated accounts

    if (!ifs || !ofs)
    {
        cout << "Error opening file for reading/writing!" << endl;
        return;
    }

    string line;
    bool accountFound = false;

    while (getline(ifs, line))
    {
        stringstream ss(line);
        string accountNumber;
        string name;
        float balance;

        getline(ss, accountNumber, ',');
        getline(ss, name, ',');
        ss >> balance;

        if (accountNumber == accountNumberToDeposit)
        {
            balance += depositAmount;
            accountFound = true;
        }

        ofs << accountNumber << "," << name << "," << fixed << setprecision(2) << balance << endl;
    }

    ifs.close();
    ofs.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (accountFound)
    {
        cout << "Deposit successful!" << endl;
    }
    else
    {
        cout << "Account with number " << accountNumberToDeposit << " not found." << endl;
    }
}

// Withdraw from an account
void BankAccount::withdraw(const string &accountNumberToWithdraw, float withdrawAmount)
{
    cout << "\n-------------------------\n";
    ifstream ifs("accounts.txt");
    ofstream ofs("temp.txt"); // Temporary file to store updated accounts

    if (!ifs || !ofs)
    {
        cout << "Error opening file for reading/writing!" << endl;
        return;
    }

    string line;
    bool accountFound = false;

    while (getline(ifs, line))
    {
        stringstream ss(line);
        string accountNumber;
        string name;
        float balance;

        getline(ss, accountNumber, ',');
        getline(ss, name, ',');
        ss >> balance;

        if (accountNumber == accountNumberToWithdraw)
        {
            if (withdrawAmount > balance)
            {
                cout << "Insufficient funds for account number " << accountNumberToWithdraw << endl;
                ofs << accountNumber << "," << name << "," << fixed << setprecision(2) << balance << endl;
                continue;
            }
            balance -= withdrawAmount;
            accountFound = true;
        }

        ofs << accountNumber << "," << name << "," << fixed << setprecision(2) << balance << endl;
    }

    ifs.close();
    ofs.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (accountFound)
    {
        cout << "Withdrawal successful!" << endl;
    }
    else
    {
        cout << "Account with number " << accountNumberToWithdraw << " not found." << endl;
    }
}

int main()
{
    int choice;
    BankAccount account;

    do
    {
        cout << "\n-------------------------\n";
        cout << "\n1. Create Account";
        cout << "\n2. Search Account";
        cout << "\n3. Display All Accounts";
        cout << "\n4. Delete Account";
        cout << "\n5. Deposit";
        cout << "\n6. Withdraw";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.createAccount();
            break;
        case 2:
        {
            string searchAccountNumber;
            cout << "Enter Account Number to Search: ";
            cin >> searchAccountNumber;
            BankAccount::searchAccount(searchAccountNumber);
            break;
        }
        case 3:
            BankAccount::displayAllAccounts();
            break;
        case 4:
        {
            string accountNumberToDelete;
            cout << "Enter Account Number to Delete: ";
            cin >> accountNumberToDelete;
            BankAccount::deleteAccount(accountNumberToDelete);
            break;
        }
        case 5:
        {
            string accountNumberToDeposit;
            float depositAmount;
            cout << "Enter Account Number to Deposit: ";
            cin >> accountNumberToDeposit;
            cout << "Enter Amount to Deposit: ";
            cin >> depositAmount;
            BankAccount::deposit(accountNumberToDeposit, depositAmount);
            break;
        }
        case 6:
        {
            string accountNumberToWithdraw;
            float withdrawAmount;
            cout << "Enter Account Number to Withdraw: ";
            cin >> accountNumberToWithdraw;
            cout << "Enter Amount to Withdraw: ";
            cin >> withdrawAmount;
            BankAccount::withdraw(accountNumberToWithdraw, withdrawAmount);
            break;
        }
        case 7:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
