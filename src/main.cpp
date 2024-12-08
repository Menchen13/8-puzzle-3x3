#include <iostream>
#include "node.h"
#include "solver.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <CLI11.hpp>

//returns true if the array contains a legal field
//needed for player input validation
bool legal_field(std::array<int, 9> field);

//generates a random and legal playing field
//used if the player doesnt provide a starting field
std::array<int, 9 > random_field();

//exit codes
//-1 bad starting field
//-2 bad search strategy flags
int main(int argc, char* argv[]){
    //comandline argument parsing using CLI11
    CLI::App app{"A Programm to solve the 8-puzzle problem for my lecture!\nIf no starting_field is provided a random one will be generated", "8-puzzle"};

    bool A = false;
    bool G = false;
    app.add_flag("-a", A, "Use A* search strategy(default)");
    app.add_flag("-g", G, "Use greedy search strategy");

    std::string starting_field;
    app.add_option("starting_field", starting_field, "Optional input: A field for the programm to start from. Example: 324015786");

    CLI11_PARSE(app, argc, argv);

    //set starting field based on CLI parameters
    std::array<int, 9> field;

    //if user provided a starting field
    //validate input and load it into the start array
    if(!starting_field.empty()){
        //check if lenght is correct before reading into array
        if(starting_field.length() != 9){
            std::cout << "Bad starting field! Use -h for more info!" << std::endl;
            return -1;
        }

        //read user input into array
        for (int i = 0; i < 9; i++)
        {
            // convert strings to numeric values
            field[i] = (starting_field.at(i) - '0');
        }

        //check if provided field is legal for puzzle
        if(!legal_field(field)){
            std::cout << "Bad starting field! Use -h for more info!" << std::endl;
            return -1;
        }
    }
    //if user did not provide a starting field
    //generate a random one, no validation needed in this case
    else{
        field = random_field();
    }

    //create start Node with field
    Node* start = new Node(field);

    //start the solver based on search strategy flags

    //if both flags are set exit with error code -2
    if(A && G){
        std::cout << "Bad search stategie flags! Use at most one flag!" << std::endl;
        delete start;
        return -2;
    }
    //if -g is used start solve with greedy
    if(G){
        auto start_time = std::chrono::high_resolution_clock::now();
        solve(start, Greedy{});
        auto end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Solved in: " << std::setprecision(3) <<duration.count() << " seconds!" << std::endl;
    }
    //else start solve with A*
    //this includes the default case, where no search strategy flag was passed
    else{
        auto start_time = std::chrono::high_resolution_clock::now();
        solve(start, A_star{});
        auto end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end_time - start_time;
        std::cout << "Solved in: " << std::setprecision(3) <<duration.count() << " seconds!" << std::endl;
    }
}

bool legal_field(std::array<int, 9> field){
    //create checklist and set all elemets to false
    bool accounted[9] = {};
    
    for(auto i: field){
        //illegal number
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
    //create a valid, random field, by shuffeling a valid field array.
    std::array<int, 9> field = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(field.begin(), field.end(), g);
    return field;
}