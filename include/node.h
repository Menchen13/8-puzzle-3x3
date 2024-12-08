#ifndef _field_
#define _field_

#include <array>
#include <stddef.h>

//enum of goal states to solve for
//refers to the goal states in the README
enum Goal_States{
    A,
    B
};

//enum of directions the empty square can move
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
    
    //internal variable to hold the amount of moves mode to reach current field-state
    size_t movecount;

    //internal variable used to hold the position of the empty square
    //used for move operations
    int zeroPos;

    //internal variable to hold the heuristically calculated cost of the field state
    //the heuristic system used is manattan distance
    int cost;

    //internal variable to hold the parent node
    //needed for print_path
    Node* parent;    
public:
    //Construct a new field object with the passed array as a starting point.
    //initialises the fieldArray and zeroPos. All other attributes are set to zero.
    //this expects the starting point to be a valid configuration.
    explicit Node(std::array<int, 9> &a);

    //no default constutor intended, dont need compiler to create it
    Node() = delete;

    //copy constructor
    Node(const Node&);

    //since no dynamic memory allocation takes place in the class the dtor will be = default
    ~Node() = default;

    // Calculate the heuristic cost of the node for goal state A using manhattan distance and set cost attribute 
    friend void calc_cost_A(Node *);

    // Calculate the heuristic cost of the node for goal state B using manhattan distance and set cost attribute 
    friend void calc_cost_B(Node *);

    //returns the goal_state the current board is solvable for
    //needed to determine which calc_cost function is to be used
    const Goal_States get_goal_state();

    std::array<int, 9> get_fieldArray();

    //returns the heuristically calculated cost of the field
    int get_cost() const;

    //returns the movecount to reach the field-state
    int get_movecount() const;

    //sets parent attribute to p
    void set_parent(Node* p);

    //returns true if the empty square can move in the direction.
    //returns false otherwise
    bool is_legal(direction);

    //moves the empty space in direction.
    //assumes the move is legal
    //also updates movecount and zeroPos
    void move(direction);

    //prints the path taken to reach the current state.
    void print_path();

    //prints the fieldArray to stdout
    void print_field();

};

//redeclaring calc_cost functions as external functions

void calc_cost_B(Node* node);
void calc_cost_A(Node* node);
#endif //_field_