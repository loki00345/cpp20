#include <iostream>
#include <string>
using namespace std;

class PaymentMethod {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentMethod() { }
};

class CreditCard : public PaymentMethod {
private:
    string cardNumber;
    string expirationDate;
    string cardHolderName;

public:
    CreditCard(const string& number, const string& expDate, const string& holderName)
        : cardNumber(number), expirationDate(expDate), cardHolderName(holderName) { }

    void processPayment(double amount) override {
        cout << "Processing payment of $" << amount << " using credit card " << cardNumber << ".\n";
    }
    ~CreditCard() { }
    static CreditCard* createFromInput() {
        string number, expDate, holderName;
        cout << "Enter card number: ";
        cin >> number;
        cout << "Enter expiration date (MM/YY): ";
        cin >> expDate;
        cout << "Enter card holder's name: ";
        cin.ignore();
        getline(cin, holderName);
        return new CreditCard(number, expDate, holderName);
    }
};

class PayPal : public PaymentMethod {
private:
    string email;

public:
    PayPal(const string& emailAddr) : email(emailAddr) { }

    void processPayment(double amount) override {
        cout << "Processing payment of $" << amount << " using PayPal with email " << email << ".\n";
    }

    ~PayPal() { }

    static PayPal* createFromInput() {
        string emailAddr;
        cout << "Enter PayPal email address: ";
        cin >> emailAddr;
        return new PayPal(emailAddr);
    }
};

class BankTransfer : public PaymentMethod {
private:
    string bankAccountNumber;
    string bankName;

public:
    BankTransfer(const string& accountNumber, const string& name)
        : bankAccountNumber(accountNumber), bankName(name) { }

    void processPayment(double amount) override {
        cout << "Processing payment of $" << amount << " via bank transfer to account " << bankAccountNumber << " at " << bankName << ".\n";
    }

    ~BankTransfer() { }
    static BankTransfer* createFromInput() {
        string accountNumber, bankName;
        cout << "Enter bank account number: ";
        cin >> accountNumber;
        cout << "Enter bank name: ";
        cin.ignore();
        getline(cin, bankName);
        return new BankTransfer(accountNumber, bankName);
    }
};

int main() {
    PaymentMethod* paymentMethods[3];
    int choice;

    cout << "Select payment method (1 - CreditCard, 2 - PayPal, 3 - BankTransfer): ";
    cin >> choice;

    switch (choice) {
    case 1:
        paymentMethods[0] = CreditCard::createFromInput();
        break;
    case 2:
        paymentMethods[0] = PayPal::createFromInput();
        break;
    case 3:
        paymentMethods[0] = BankTransfer::createFromInput();
        break;
    default:
        cout << "Invalid choice.\n";
        return 1;
    }

    double amount;
    cout << "Enter amount to process: ";
    cin >> amount;
    paymentMethods[0]->processPayment(amount);

    delete paymentMethods[0];

}