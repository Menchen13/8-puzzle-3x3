/**
 * @file main.cpp
 * @brief main function of the programm gets impelemetet here.
 * @version 0.1
 * @date 2024-11-12
 * 
 */
#include <iostream>
#include "node.h"
#include "solver.h"

//returns true if the array contains a legal field
bool legal_field(std::array<int, 9> field);

int main(){
    std::array<int,9> start = {8,0,4,6,3,7,5,2,1};
    Node* startNode = new Node(start);
    solve(startNode, A_star{});

}

bool legal_field(std::array<int, 9> field){
    //create checklist and set all elemets to false
    bool accounted[9] = {};

    for(auto i: field){
        if(i < 0 || i > 8){
            return false;
        }
        //double element in field
        if(accounted[i] == true){
            return false;
        }else{
            accounted[i] = true;
        }
    }   
    return true;
}