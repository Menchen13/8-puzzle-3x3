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

field::field(std::array<int,9> &a) : movecount{0}, fieldArray(a){
    for(auto i: fieldArray){
        if(i == 0){
            zeroPos = i;
        }
    }
}

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

bool field::is_legal(direction dir){
    switch (dir)
    {
    case up:
        return(zeroPos > 2);
    case down:
        return(zeroPos < 6);
    case direction::left:
        return((zeroPos % 3) != 0);
    case direction::right:
        return((zeroPos % 3) != 2);
    }
}

bool field::move(direction dir){
    //makes sure the intendet move is legal.
    if(!is_legal(dir)){
        return false;
    }
    
    switch (dir)
    {
    case direction::up:
        break;

    case direction::down:
        break;

    case direction::left:
        break;

    case direction::right:
        break;
    
    default:
        break;
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
}