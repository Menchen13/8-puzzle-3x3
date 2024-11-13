/**
 * @file field.cpp
 * @brief Implementation file for the field class
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "field.h"
#include <array>
#include <iostream>
using namespace std;

field::field(std::array<int,9> &a) : movecount{0}, fieldArray(a){}

void field::print(){
    for(int i = 0; i< 3; i++){
        cout << "|-----------|\n";
        cout << "| ";
        for(int j = 0; j < 3; j++){
            //tmp variable to hold current number
            int x = fieldArray[i*3+j];
            cout << (x == 0 ? " " : to_string(x)) << " | ";
        }
        cout << "\n";
    }
    cout << "|-----------|\n";
    cout << "Move: " << movecount << endl;
}

bool field::is_solved(){
    std::array<int,9> winState_A = {1,2,3,8,0,4,7,6,5};
    std::array<int, 9> winState_B = {0,1,2,3,4,5,6,7,8};

    return(fieldArray == winState_A || fieldArray == winState_B);
}

