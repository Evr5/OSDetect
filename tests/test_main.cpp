/**
* @file main.cpp
* @brief Entry point for the test program.
* @author Evr5
* @date 2025
*
* This file contains the main function of the C++ Test Template project.
*/

#include <iostream>
#include <cassert>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << "Running basic test..." << std::endl;
    assert(add(2, 3) == 5);
    std::cout << "Test passed!" << std::endl;
    std::cout << "Great! This project has passed all the tests!" << std::endl;
    return 0;
}