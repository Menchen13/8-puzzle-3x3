/**
 * @file main.cpp
 * @brief main function of the programm gets impelemetet here.
 * @version 0.1
 * @date 2024-11-12
 * 
 */
#include <iostream>
#include "field.h"

int main(){
    std::array<int,9> start = {0,1,2,3,4,5,7,6,8};
    field f(start);
    f.print();
}