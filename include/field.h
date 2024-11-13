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

#include <corecrt.h>
#include <array>

class field
{
private:
    /**
     * @brief Internal array to hold the field
     * @note 0-2: row 1; 3-5 row 2; 6-8 row 3
     */
    std::array<int, 9> fieldArray;
    /**
     * @brief internal variable to hold the amout of moves mode during the game
     */
    size_t movecount;
public:

    /**
     * @brief Construct a new field object with a random starting point
     * 
     */
    field();
    /**
     * @brief Construct a new field object with the passed in array as a starting point
     * 
     */
    explicit field(std::array<int, 9> &a);
    /**
     * @brief Destroy the field object
     * @note since no dynamic memory allocation takes place in the class the dtor will be = default
     */
    ~field() = default;

    /**
     * @brief Prints the playing Field to stdout.
     * @author LÖWE
     * 
     */
    void print();

    /**
     * @brief Returns true if the puzzle is solved, according to the solve states
     * \image latex ../image/Goal_States.png "Goal States"
     * 
     * @return true 
     * @return false 
     */
    bool is_solved();

};
#endif //_field_