#pragma once
#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <iostream>
#include <utility>

#include "array_list.hpp"


class chess_board {
private:
    typedef std::pair<int, int> coordinate;

    ds::array_list<coordinate> solution;
    int row_length;
    int column_length;

    
    /* ************************************************************
     * @brief: Draw a frame of the solution with unicode characters
     * ************************************************************ */
    void draw_solution_frame(ds::array_list<ds::array_list<int>>);


    /* *******************************************************
     * @brief: calculate possible moves from current position 
     * @params: 
     *        std::array_list<coordinate> 
     *             Keeps track of moves that have been made 
     *        coordinate 
     *             first indicates the row index
     *             second indicates the column index
     * @return: 
     *        ds::array_list<coordinate> contains all possible moves
     * ******************************************************* */
    ds::array_list<coordinate> calculate_possible_moves(ds::array_list<coordinate>, coordinate);

public:
    /* Getters for row and column length */
    int get_row_length();
    int get_column_length();

    /* *******************************************************
     * @brief: construct an empty chess board with size: m x n
     * @params: 
     *      m: number of rows
     *      n: number of columns
     * ******************************************************* */
    chess_board(int m, int n);

    /* ********************************************************
     * @brief: resize chess board to m x n board, 
     * @params: 
     *      m: number of rows
     *      n: number of columns
     * ******************************************************** */
    void resize_board(int m, int n);
    
    /* ****************************************
    * @brief: Overload << operator for output
    * ***************************************** */
    friend std::ostream& operator<<(std::ostream &os, const chess_board &cb);
    
    /* *************************************************************
     * @brief: Solve knight tour's problem
     * @params: std::pair<int,int> indicates the initial location
     * @return boolean: 
     *          true if there is a solution
     *          false otherwise
     * @side-effects: 
     *          history of moves is stored in the field 'solution'
     * *************************************************************/
    bool knight_tour_solve(coordinate);

    /* ***************************************
    * @brief: Animate knight tour solution
    * @params:
    *      sleep_time: time between each move
    * *************************************** */
    void animate_solution(int sleep_time);
};




#endif