#include "print_text.h"
#include <iostream>
#include <iomanip>
#include <string>

void PrintText() {
    std::string s1 = "CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM";
    std::string s2 = ":::::::::WELCOME TO THE MAIN MENU:::::::::";
    std::cout << std::setw(70) << s1 << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(70) << s2 << std::endl;
    std::cout << std::endl;
}

