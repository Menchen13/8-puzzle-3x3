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

int main(){
    std::array<int,9> start = {8,2,4,0,3,1,6,5,7};
    Node* startNode = new Node(start);
    solve(startNode);

}