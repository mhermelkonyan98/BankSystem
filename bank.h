#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>

class Bank {
private:
    int choice;
    std::string name;
    std::string temp_name;
    int password;
    int temp_password;
    int id;
    int cash;
    int age;
    const char arrow = '>';
public:
    void BankMenuText();
    void Stop();
    void BankStart();
    void CreateNewAccount();
    void UpdateAccount();
    void CheckAccount();
    void RemoveAccount();
    void ForTransactions();
    void CustomersList();
};


#endif // BANK_H

