/**
 * @file field.h
 * @brief Header File für die field
 * @version 0.1
 * @date 2024-11-12
 * 
 * 
 */
#ifndef _field_
#define _field_

#include <array>
#include <stddef.h>
enum direction {
    up,
    down,
    left,
    right
};

class Node
{
private:
    //Internal array to hold the field
    //0-2: row 1; 3-5 row 2; 6-8 row 3
    std::array<int, 9> fieldArray;
    
    //internal variable to hold the amout of moves mode to reach current field-state
    size_t movecount;

    //internal variable used to hold the position of the empty square
    //used for move operations
    int zeroPos;

    //internal variable to hold the heuristically calculated cost of the field state
    //the heuristic system used is manattan distance
    int cost;

    Node* parent;    
public:
    //Construct a new field object with the passed in array as a starting point
    //this expects the starting point to be a valid configuration.
    explicit Node(std::array<int, 9> &a);

    //no default constutor intendet, dont need compiler to create it
    Node() = delete;

    //copy constructor
    Node(const Node&);

    //Destroy the field object
    //since no dynamic memory allocation takes place in the class the dtor will be = default
    ~Node() = default;

    // Calculate the heuristic cost of the node using manhattan distance and set attribute cost
    void calc_cost();

    //returns the heuristically calculated cost of the field
    int get_cost() const;

    //returns the movecount to reach the field-state
    int get_movecount() const;

    void set_parent(Node*);

    //returns true if the empty square can move in the direction
    bool is_legal(direction);

    //moves the empty space in direction.
    //also updates movecount and zeroPos
    void move(direction);

    //prints the path take to reach the current state.
    void print_path();

    //prints the fieldArray to stdout
    void print_field();

};
#endif //_field_