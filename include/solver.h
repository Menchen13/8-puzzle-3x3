#ifndef _SOLVER_
#define _SOLVER_
#include "node.h"
#include <queue>


//comparator for Nodes
struct A_star{
    bool operator()(const Node* Item1, const Node* Item2){
        return((Item1->get_cost() + Item1->get_movecount()) > (Item2->get_cost() + Item2->get_movecount()));
    }
};

//comparator for Nodes
struct Greedy{
    bool operator()(const Node* Item1, const Node* Item2){
        return(Item1->get_cost() > Item2->get_cost());
    }
};

//function to solve from a given start node
//this function is in the header cause it was the only way i could get this template shenanigans work ¯\_(ツ)_/¯
template<typename T>
void solve(Node* start, T comp){
    //Priority queue of generated nodes.
    std::priority_queue<Node*, std::vector<Node*>, T> pq(comp);

    //add starting Node to the queue
    pq.push(start);

    //array to loop over when creating child nodes
    std::array<direction, 4> directions ={direction::up, direction::down, direction::left, direction::right};

    while(!pq.empty()){
        //always use the node with the lowest estimated cost -> top of the pq
        Node* current = pq.top();

        //remove node from list so it doesnt get checked multiple times
        pq.pop();

        //if the estimated cost of the node is == 0, then it is a goal state.
        //and if a goal state is the least expensive node, then the optimal solution has been found!
        if(current->get_cost() == 0){
            //TODO
            current->print_path();
            return;
        }
        //iterate over all possible next moves -> all directions for the empty space to move
        for(auto direction: directions){
            //only generate nodes for "legal" moves
            if(current->is_legal(direction)){
                //use current node as base
                Node* child = new Node(*current);

                //set current node as parent for child node
                child->set_parent(current);

                //make move on the board, this automatically increments the movecount.
                child->move(direction);

                //calculate new cost of the field and update attribute of child node
                child->calc_cost();
                
                //add child node to the queue
                pq.push(child);
            }
        }
    }
}


#endif //_SOLVER_