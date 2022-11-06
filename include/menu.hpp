#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include "chess_board.hpp"

#include <string>
#include <limits>
#include <iostream>
#include <utility>

class menu {
private:
    int choice;
    chess_board cb;
    bool board_size_set;
    bool init_location_set;
    bool knight_tour_solution_ready;
    std::pair<int,int> init_location;
public:
    menu() :    choice(0), cb(1, 1), 
                board_size_set(false), init_location_set(false), 
                knight_tour_solution_ready(false) {}

    int get_choice();
    void print_menu();
    void input_choice(std::string);
    void input_board_length();
    void input_initial_location();
    void run_solve_knight_tour();
    void run_animate_knight_tour();
};









#endif