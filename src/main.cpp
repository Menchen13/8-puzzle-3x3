#include <iostream>
#include "node.h"
#include "solver.h"
#include <algorithm>
#include <random>

//returns true if the array contains a legal field
bool legal_field(std::array<int, 9> field);
std::array<int, 9 > random_field();

int main(){
    auto field = random_field();
    Node * test = new Node(field);
    test->print_field();
    solve(test, A_star{});

    // std::array<int,9> start = {8,0,4,6,3,7,5,2,1};
    // Node* startNode = new Node(start);
    // solve(startNode, A_star{});

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

std::array<int, 9> random_field(){
   std::array<int, 9> field = {0,1,2,3,4,5,6,7,8}; 
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(field.begin(), field.end(), g);
    return field;
}