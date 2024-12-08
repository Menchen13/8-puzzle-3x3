#ifndef _SOLVER_
#define _SOLVER_
#include "node.h"
#include <queue>
#include <unordered_set>


//comparator for Nodes
//implements A* search by sorting nodes by cost + movecount
struct A_star{
    bool operator()(const Node* Item1, const Node* Item2){
        return((Item1->get_cost() + Item1->get_movecount()) > (Item2->get_cost() + Item2->get_movecount()));
    }
};

//comparator for Nodes
//implements greedy search by sorting by only cost
struct Greedy{
    bool operator()(const Node* Item1, const Node* Item2){
        return(Item1->get_cost() > Item2->get_cost());
    }
};

struct Arrayhash {
    std::size_t operator()(const std::array<int, 9>& arr) const{
        std::size_t hashValue = 0;
        for(const int& elem : arr){
            //custom hash function for the field array using magic number for 32-integers and bitshiftss
            hashValue ^= std::hash<int>()(elem) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        }
        return hashValue;
    }
};

//function to solve 8-puzzle-problem from a given start node with a given comparator for nodes(search strategie)
//this function is in the header cause it was the only way i could get these template shenanigans to work ¯\_(ツ)_/¯
template<typename T>
void solve(Node* start, T comp){


    //Priority queue of generated nodes.
    //comparator used decides search strategy
    std::priority_queue<Node*, std::vector<Node*>, T> pq(comp);

    //vector to hold the nodes checked.
    //this is nessecary to keep track of the pointers for memory safety
    std::vector<Node*> used;

    //hashset to store already seens states
    std::unordered_set<std::array<int,9>, Arrayhash> seen;

    //function pointer to be used for calculating the cost of a node
    void (*calc_cost)(Node*);

    //set function pointer to calc_cost function based on goal_state
    //thought this would better performance drasticly, but in the end it was just an excuse to learn about function pointers and friendly methods
    calc_cost = (start->get_goal_state() == B) ? calc_cost_B : calc_cost_A;

    //calculate cost for start Node, now that goal state has been determined
    calc_cost(start);


    //add starting Node to the queue
    pq.push(start);

    //array to loop over when creating child nodes
    std::array<direction, 4> directions ={direction::up, direction::down, direction::left, direction::right};



    while(!pq.empty()){
        //always use the node with the lowest estimated cost -> top of the pq
        Node* current = pq.top();

        //remove node from list so it doesnt get checked multiple times
        pq.pop();
        
        //add Node to the used vector as it wont be found in the pq anymore.
        used.push_back(current);

        //add the state of a checked node into the hashset
        seen.insert(current->get_fieldArray());

        //if the estimated cost of the node is == 0, then it is a goal state.
        //and if a goal state is the least expensive/current node, then the optimal solution has been found!
        if(current->get_cost() == 0){
            //print path taken to reach goal and exit
            current->print_path();

            //free memory for Nodes used
            for (size_t i = 0; i < used.size(); i++){
                delete used.at(i);
            }

            //free memory for Nodes still in pq
            while(!pq.empty()){
                delete pq.top();
                pq.pop();
            }
            
            

            return;
        }
        
        //iterate over all possible next moves -> all directions for the empty space to move
        for(auto direction: directions){
            //only generate nodes for "legal" moves
            if(current->is_legal(direction)){
                //use current node as base
                Node* child = new Node(*current);

                //make move on the board, this automatically increments the movecount.
                child->move(direction);

                //if child state has been seen before dont add it to pq and free memory
                if(seen.find(child->get_fieldArray()) != seen.end()){
                    //free memory
                    delete child;
                    continue;
                }

                //set current node as parent for child node
                child->set_parent(current);


                //calculate new cost of the field and update attribute of child node
                calc_cost(child);
                
                //add child node to the queue
                pq.push(child);
            }
        }
    } //since all start states are solvable the programm can never reach pq.empty() before finding a solution
}

#endif //_SOLVER_