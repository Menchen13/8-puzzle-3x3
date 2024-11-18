/**
 * @file field.cpp
 * @brief Implementation file for the field class
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "node.h"
#include <array>
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;

Node::Node(std::array<int,9> &a) : movecount{0}, fieldArray(a), parent{nullptr}{
    calc_cost();
    for(int i = 0; i < 9; i++){
        if(fieldArray[i] == 0){
            zeroPos = i;
            break;
        }
    }
}

Node::Node(const Node& other): fieldArray{other.fieldArray}, movecount{other.movecount}, zeroPos{other.zeroPos}, cost{other.cost}, parent{other.parent} {}

void Node::calc_cost(){
    cost = 0;
    for(int i = 0; i < 9; i++){
        int distance = abs(i - fieldArray[i]);
        cost += (distance / 3) + (distance % 3);

    }
}

void Node::print_field(){
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
    cout << "Cost: " << cost << endl;
}

int Node::get_cost() const{
    return cost;
}

int Node::get_movecount() const{
    return movecount;
}

void Node::set_parent(Node* p){
    parent = p;
}

bool Node::is_legal(direction dir){
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
    default:
        return false;
    }
}

void Node::move(direction dir){

    movecount++;
    switch (dir)
    {
    case direction::up:
        std::swap(fieldArray[zeroPos - 3],fieldArray[zeroPos]);
        zeroPos -= 3;
        break;

    case direction::down:
        std::swap(fieldArray[zeroPos + 3],fieldArray[zeroPos]);
        zeroPos += 3;
        break;

    case direction::left:
        std::swap(fieldArray[zeroPos - 1],fieldArray[zeroPos]);
        zeroPos -= 1;
        break;

    case direction::right:
        std::swap(fieldArray[zeroPos + 1], fieldArray[zeroPos]);
        zeroPos += 1;
        break;
    
    default:
        break;
    }
}


void Node::print_path(){
    //base case for recursion
    //start node has been reached -> no parent
    if(parent == nullptr){
        print_field();
        return;
    }
    parent->print_path();
    print_field();
}