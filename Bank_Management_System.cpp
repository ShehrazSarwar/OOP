// Header Files
#include <iostream>
#include <string>
using namespace std;

// Forward Declarations Of The Classes Here
class BankManager;

class BankAccount // Class That Holds The Account Informations
{
    // Declarations Here
    static int TotalAccounts;   // Static Inorder To Count Total Accounts Created Everytime
    static int Last_Acc_Number; // Static Inorder To Track The Last Account Number

    // Basic Information
    int accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(string name) // Member Function To Create An Account
    {
        accountHolder = name;
        accountNumber = ++Last_Acc_Number;
        TotalAccounts++; // increment by one into total
        balance = 0;     // default balance
        cout << "Bank Account created successfully Name " << accountHolder << "   Account Num: " << accountNumber << endl;
    }
    void deposit(int amount)
    {
        if (amount > 0) // Wrong Input Condition Inorder To Overcome the negative input from the user
        {
            balance = balance + amount;
            cout << "Successfully Deposited amount:$ " << amount << endl;
        }
        else
        {
            cout << "Amount can not be negative" << endl; // Incase of wrong input <0
        }
    }

    void Transfer(int amount) // Member Function To Transfer Cash
    {
        balance = balance + amount;
    }

    void withdraw(int amount) // Member Function To Withdraw Cash
    {
        if (amount > 0 && amount <= balance) // Wrong Input Checking Or if Balance is not much
        {
            balance = balance - amount;
            cout << "The Amount:$ " << amount << " Withdrawn Successfully" << endl;
        }
    }

    // Getter And Setters Here
    double getBalance() // Returning Balance
    {
        return balance;
    }

    int getTransferAccountNUM() // Returning Account Number
    {
        return accountNumber;
    }

    string getTransferAccountName() // Returning Account Name
    {
        return accountHolder;
    }

    friend int getTotalAccounts(); // Friend Function Declaration Here Definination Later

    void TransferFunds(BankAccount &Tranfer_Acc, int amount) // Function To TransferFunds Or Cash
    {
        if (amount > 0 && amount <= balance) // Condition To Check If The Number Is <0 or Balance Is Insufficient
        {
            balance = balance - amount;
            Tranfer_Acc.Transfer(amount); // Calling Transfer Member Function Here
            cout << "An amount of: " << amount << " Has Been Successfully Transfered " << endl;
        }
        else
        {
            cout << "You Dont Have Much Funds To Transfer" << endl; // Incase of wrong or invalid input
        }
    }
};
class BankManager // Class To Manage The Bank Accounts
{
private:
    BankAccount **accounts; // Aggregation Here As We Used Pointers
    int numAccounts;

public:
    BankManager() : numAccounts(0) // Constructor Here
    {
        accounts = new BankAccount *[1]; // Dynamically Allocating New BankAccounts
    }

    ~BankManager() // Destructor For Deallocation
    {
        for (int i = 0; i < numAccounts; ++i)
        {
            delete accounts[i]; // deallocating
        }
        delete[] accounts; // deallocating whole array here
    }

    BankAccount *createAccount(const string &accHolder = "N/A") // To Create New Accont
    {
        BankAccount **temp = new BankAccount *[numAccounts + 1]; // Dynamicaly allocating newaccounts
        for (int i = 0; i < numAccounts; ++i)
        {
            temp[i] = accounts[i]; // saving data of accounts to new array of temp
        }
        delete[] accounts; // deleting the previous one
        accounts = temp;   // saving data of new into account here

        BankAccount *newAccount = new BankAccount(accHolder);
        accounts[numAccounts] = newAccount; // saving new ACCOUNT TO ACCOUNTS
        numAccounts++;                      // Incrementing the no of accounts
        return newAccount;                  // returning the new account
    }

    void deleteAccount(int accNumber) // mem function for account closing or deletion
    {
        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i]->getTransferAccountNUM() == accNumber) // comparing account numbers
            {
                delete accounts[i]; // deallocation

                for (int j = i; j < numAccounts - 1; ++j) // fill the gap after deleting
                {
                    accounts[j] = accounts[j + 1];
                }
                numAccounts--; // deleting one account
                cout << "Account deleted/closed successfully!" << endl;
                return; // out of function
            }
        }
        cout << "Account not found!" << endl; // incase of wrong number
    }

    BankAccount *findAccount(int accNumber) // Member function of type BankAccount inorder to find account
    {
        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i]->getTransferAccountNUM() == accNumber) // comparing here with the accNumber
            {
                return accounts[i]; // returning that account if found!
            }
        }
        return nullptr; // Means Account not found so returning nullptr
    }

    void displayAllAccounts() // Member function to display all the accounts
    {
        if (numAccounts == 0) // handling wrong input here
        {
            cout << "No accounts found!" << endl; // no account found msg
            return;
        }
        cout << "Bank Accounts:" << endl;
        for (int i = 0; i < numAccounts; ++i) // using for loop inorder to display all accounts
        {
            cout << "Account Number: " << accounts[i]->getTransferAccountNUM() << endl;  // Acc number
            cout << "Account Holder: " << accounts[i]->getTransferAccountName() << endl; // Holder name
            cout << "Balance:$ " << accounts[i]->getBalance() << endl;                   // display balance
            cout << endl;
        }
    }
};

// Initializing static member variables
int BankAccount::TotalAccounts = 0;      // setting to zero
int BankAccount::Last_Acc_Number = 5213; // starting account number from this

int getTotalAccounts() // friend function definition
{
    return BankAccount::TotalAccounts; // Return Total Number OF Accounts herre
}

int main() // Main function
{
    // Declaring objects and some variables
    BankManager manager;
    int choice;
    int accountNumber;
    string accountName;
    double amount;

    do // To make it more functional or optimized, we use do here for proper program flow
    {
        // Showing main menu options
        cout << "\nWelcome To Shehz Islamic Bank" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Transfer Funds" << endl;
        cout << "5. Delete Account" << endl;
        cout << "6. Display All Accounts" << endl;
        cout << "7. Exit" << endl;

        cout << "Please Enter your choice: "; // Taking input for the menu
        cin >> choice;

        switch (choice) // To run the corresponding case
        {
        case 1:
        {
            cout << "Enter account holder's name: ";
            cin >> accountName;
            manager.createAccount(accountName); // Creating an account through createAccount mem func
            break;
        }
        case 2:
        {
            cout << "Enter account number: ";
            cin >> accountNumber;
            BankAccount *account = manager.findAccount(accountNumber); // finding account here
            if (account)
            {
                cout << "Enter deposit amount: ";
                cin >> amount;
                account->deposit(amount); // Deposit money into the account
            }
            else
            {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Enter account number: ";
            cin >> accountNumber;
            BankAccount *account = manager.findAccount(accountNumber); // finding account
            if (account)
            {
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                account->withdraw(amount); // Withdraw money from the account through withdraw mem function
            }
            else
            {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 4:
        {
            int MainAccNumber, destinationAccountNumber; // Declarations
            cout << "Enter source account number: ";
            cin >> MainAccNumber;
            cout << "Enter destination account number: ";
            cin >> destinationAccountNumber;
            BankAccount *MainAcc = manager.findAccount(MainAccNumber);                       // calling mem fun find account for mainAcc source one
            BankAccount *destinationAccount = manager.findAccount(destinationAccountNumber); // calling mem fun find account for Destination source one

            // If accounts are found, transfer funds
            if (MainAcc && destinationAccount)
            {
                cout << "Enter transfer amount: ";
                cin >> amount;
                MainAcc->TransferFunds(*destinationAccount, amount); // Transfer chash or funds between accounts
            }
            else
            {
                cout << "One or both accounts not found!" << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Enter account number to delete: ";
            cin >> accountNumber;
            manager.deleteAccount(accountNumber); // Delete account through member function deleteAccount
            break;
        }
        case 6:
        {
            manager.displayAllAccounts(); // Displaying all accounts
            break;
        }
        case 7:
        {
            cout << "Thank you for choosing our bank..." << endl; // Exiting the program
            break;
        }
        default:
        {
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
        }
    } while (choice != 7); // Loop until user chooses to exit

    return 0;
}
