#pragma once
#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <iostream>
#include <utility>

#include "array_list.hpp"


class chess_board {
private:
    ds::array_list<ds::array_list<int>> board;
    int row_length;
    int column_length;

    

    /* ************************************************************
     * @brief: Solve knight tour using backtracking 
     * @params: 
     *          std::pair<int,int>  indicates the initial location
     *          int                 indicates the current move
     * @return boolean: 
     *          true if there is a solution
     *          false otherwise
     * *************************************************************/
    bool knight_tour_solve(std::pair<int, int>, int);

    /* *************************************************
     * @brief: Draw chess board with unicode characters
     * ************************************************* */
    void draw_chess_board(ds::array_list<ds::array_list<int>> &);


       /* *******************************************************
     * @brief: calculate possible moves from current position 
     * @params: 
     *        std::pair<int, int> 
     *        first indicates the row index
     *        second indicates the column index
     * @return: 
     *        An array of std::pair<int,int> of possible moves
     * ******************************************************* */
    ds::array_list<std::pair<int, int>> calculate_possible_moves(std::pair<int, int>);
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
     *         it will reset content of board
     * @params: 
     *      m: number of rows
     *      n: number of columns
     * ******************************************************** */
    void resize_board(int m, int n);

 

    /* ****************************************
     * @brief: Overload << operator for output
     * ****************************************/
    friend std::ostream& operator<<(std::ostream &os, const chess_board &cb);

    /* *************************************************************
     * @brief: Initialize 2d array and location to solve knight tour
     * @params: std::pair<int,int> indicates the initial location
     * @return boolean: 
     *          true if there is a solution
     *          false otherwise
     * *************************************************************/
    bool knight_tour_solve(std::pair<int, int>);


    /* ***************************************
    * @brief: Simulate knight tour solution
    * @params:
    *      sleep_time: time between each move
    * *************************************** */
    void knight_tour_solution_animate(unsigned int sleep_time);
};




#endif