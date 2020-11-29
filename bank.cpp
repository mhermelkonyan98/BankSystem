#include <iostream>
#include "bank.h"
#include "json.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>

using json = nlohmann::json;
typedef unsigned long long ull;

void Bank :: BankMenuText() {
    std::cout << "1. Create New Account" << std::endl;
    std::cout << "2. Update Information Of Existing Account" << std::endl;
    std::cout << "3. For Transactions" << std::endl;
    std::cout << "4. Check The Details Of Existing Account" << std::endl;
    std::cout << "5. Removing Existing Account" << std::endl;
    std::cout << "6. View Costomer's List" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

void Bank::Stop() {
    std::cout << std::endl;
    system("pause");
    std::cout << std::endl;
    BankStart();
}

void Bank::CreateNewAccount() {
    std::cout << "Enter Your Name:" << std::endl;
    std::cin >> name;
    std::cout << "Enter Your Password:" << std::endl;
    std::cin >> password;
    std::cout << "Enter Your ID:" << std::endl;
    std::cin >> id;
    std::cout << "Enter Cash:" << std::endl;
    std::cin >> cash;
    std::cout << "Enter Your Age:" << std::endl;
    std::cin >> age;

    json new_acc;
    new_acc["name"] = name;
    new_acc["password"] = password;
    new_acc["cash"] = cash;
    new_acc["ID"] = id;
    new_acc["age"] = age;

    std::ofstream fout(name + ".json");
    if (fout.is_open()) {
        fout << std::setw(4) << new_acc << std::endl;
    } else {
        fout.open(name + ".json");
        fout << std::setw(4) << new_acc << std::endl;
    }
    fout.close();

    json cust;
    std::ifstream ifs;
    ifs.open("customers.json");
    ifs >> cust;
    ifs.close();

    cust["customer's list"] += name;

    std::fstream fs;
    fs.open("customers.json", std::ios::out);
    fs << std::setw(4) << cust << std::endl;
    fs.close();

    std::cout << "Your Account Is Ready! Have A Nice Day!" << std::endl;
    std::cout << std::endl;
}

void Bank::UpdateAccount() {
    std::cout << "Enter Your Name:" << std::endl;
    std::cin >> temp_name;
    std::cout << "Enter Your Password:" << std::endl;
    std::cin >> temp_password;

    json jey;
    std::ifstream ifs;
    ifs.open(temp_name + ".json");
    if (ifs.is_open()) {
        ifs >> jey;
        if (jey["password"] == temp_password) {
            std::cout << "You Can Change Only Your Password." << std::endl;
            std::cout << "Enter New Password:" << std::endl;
            int temp;
            std::cin >> temp;
            jey["password"] = temp;

            std::fstream fs;
            fs.open(temp_name + ".json", std::ios::out);
            if (fs.is_open()) {
                fs << std::setw(4) << jey << std::endl;
                fs.close();
            } else {
                std::cout << "Cannot Open File! Try Again." << std::endl;
                UpdateAccount();
            }
            std::cout << "Your Account Is Updated!" << std::endl;
        } else {
            std::cout << "Password Is Incorrect! Try Again." << std::endl;
            UpdateAccount();
        }
        ifs.close();
    } else {
        std::cout << "Cannot Open File!" << std::endl;
        UpdateAccount();
    }


}

void Bank::CheckAccount() {
    json j;
    std::cout << "Enter Your Name:" << std::endl;
    std::cin >> temp_name;
    std::cout << "Enter Your Password:" << std::endl;
    std::cin >> temp_password;
    std::ifstream ifs;
    ifs.open(temp_name + ".json");
    if (ifs.is_open()) {
        ifs >> j;
        if (j["password"] == temp_password) {
            std::cout << j.dump(4) << std::endl;
        } else {
            std::cout << "Incorrect Name Or Password! Try Again." << std::endl;
            CheckAccount();
        }
        ifs.close();
    } else {
        std::cout << "Cannot Open File! Try Again." << std::endl;
        CheckAccount();
    }
}

void Bank::RemoveAccount() {
    std::cout << "If You Want To Remove Your Account Pleasy Enter Y" << std::endl;
    char ch;
    std::cin >> ch;
    if (ch == 'Y') {
        std::cout << "Enter Your Name" << std::endl;
        std::cin >> temp_name;
        std::cout << "Enter Your Password" << std::endl;
        std::cin >> temp_password;

        json jey1;
        std::ifstream ifs;
        ifs.open(temp_name + ".json");
        ifs >> jey1;
        ifs.close();
        if (jey1["password"] == temp_password) {
            std::string str = temp_name + ".json";
            int n = str.length();
            char char_array[n + 1];
            std::strncpy(char_array, str.c_str(), 50);
            std::remove(char_array);

            json jey;
            std::ifstream ifs;
            ifs.open("customers.json");
            ifs >> jey;
            ifs.close();

            json new_jey;

            for (ull i = 0; i < jey["customer's list"].size(); i++) {
                if (!(jey["customer's list"][i] == temp_name)) {
                    new_jey["customer's list"][i] = jey["customer's list"][i];
                }
            }

            std::fstream fs;
            fs.open("customers.json", std::ios::out);
            fs << std::setw(4) << new_jey << std::endl;
            fs.close();

            std::cout << "Your Account Is Removed!" << std::endl;
        } else {
            std::cout << "Your Password Is Incorrect! Try Again." << std::endl;
            ifs.close();
            RemoveAccount();
        }
    }
}

void Bank::ForTransactions() {
    std::cout << "Enter Your Name:" << std::endl;
    std::cin >> temp_name;
    std::cout << "Enter Your Password:" << std::endl;
    std::cin >> temp_password;

    std::ifstream ifs;
    json j_f;
    ifs.open(temp_name + ".json");
    if (ifs.is_open()) {
        ifs >> j_f;
        if (!(temp_password == j_f["password"])) {
            std::cout << "Your Password Is Incorrect! Try Again." << std::endl;
            ForTransactions();
        }
        ifs.close();
    } else {
        std::cout << "Cannot Open File! Try Again." << std::endl;
        ForTransactions();
    }

    std::cout << "Enter The Needed Amount:" << std::endl;
    int temp;
    std::cin >> temp;
    if (temp > j_f["cash"]) {
        std::cout << "Not Enough Money On Your Account!" << std::endl;
        ForTransactions();
    } else {
        int temp1 = j_f["cash"];;
        temp1 = temp1 - temp;
        j_f["cash"] = temp1;

        std::fstream fs1;
        fs1.open(temp_name + ".json", std::ios::out);
        if (fs1.is_open()) {
            fs1 << std::setw(4) << j_f << std::endl;
            fs1.close();
            std::cout << "Operation Is Completed!" << std::endl;
        } else {
            std::cout << "Cannot Open File!" << std::endl;
            ForTransactions();
        }
    }
}

void Bank::CustomersList() {
    std::cout << "Here Is Our Bank's Customer's List!" << std::endl;
    std::cout << std::endl;

    json jeey;
    std::ifstream ifs;
    ifs.open("customers.json");
    if (ifs.is_open()) {
        ifs >> jeey;
        std::cout << jeey.dump(4) << std::endl;
        ifs.close();
    } else {
        std::cout << "Cannot Open File! Try Again." << std::endl;
        BankStart();
    }
}

void Bank::BankStart() {
    BankMenuText();
    std::cout << std::endl;
    std::cout << "Enter Your Choice" << std::endl;
    std::cout << arrow << " ";
    std::cin >> choice;
    std::cout << std::endl;
    switch (choice) {
    case 1:
        CreateNewAccount();
        Stop();
        break;
    case 2:
        UpdateAccount();
        Stop();
        break;
    case 3:
        ForTransactions();
        Stop();
        break;
    case 4:
        CheckAccount();
        Stop();
        break;
    case 5:
        RemoveAccount();
        Stop();
        break;
    case 6:
        CustomersList();
        Stop();
        break;
    case 7:
        exit(0);
        break;
    default:
        std::cout << "Error. Retry!" << std::endl;
        BankStart();
        break;
    }
}

