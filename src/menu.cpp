#include "menu.hpp"
#include "util.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <utility>

void menu::start_menu() {
    for (;;) {
        print_menu();
        input_choice("Enter your choice: ");
        
        if (choice == 1) {
            input_board_length();
        } else if (choice == 2) {
            input_initial_location();
        } else if (choice == 3) {
            run_knight_tour_solve();
        } else if (choice == 4) {   
            run_animate_solution();
        } else if (choice == 5) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
    }    
}

void menu::input_choice(std::string prompt) {
    do {
        std::cout << prompt;
        std::cin >> choice;
        clear_input();

        if (choice < 1 || choice > 5) {
            std::cout << "Invalid input" << std::endl;
        }
    } while (choice < 1 || choice > 5);
}


/* This will change all flags to false */
void menu::input_board_length() {
    int row_length;
    int column_length;

    init_location_set = false;
    knight_tour_solution_ready = false;

    do {
        std::cout << "Input row length: "; 
        std::cin >> row_length;
        clear_input(); 

        if (row_length < 2) {
            std::cout << "Invalid input" << std::endl;
        }
    } while (row_length < 2);

    do {
        std::cout << "Input column lenght: "; 
        std::cin >> column_length;
        clear_input(); 

        if (column_length < 2) {
            std::cout << "Invalid input" << std::endl;
        }
    } while (column_length < 2);

    cb.resize_board(row_length, column_length);
    board_size_set = true;
}

void menu::input_initial_location() {
    if (!board_size_set) {
        std::cout << "Chess board size is not set" << std::endl;
        return;
    }

    int row; 
    int column;

    do {
        std::cout << "Input row index: ";
        std::cin >> row;
        clear_input(); 
        if (row < 0 || row >= cb.get_row_length()) {
            std::cout << "Invalid row index" << std::endl;
        }
    } while (row < 0 || row >= cb.get_row_length());

    do {
        std::cout << "Input column index: "; 
        std::cin >> column;
        clear_input(); 
        if (column < 0 || column >= cb.get_column_length()) {
            std::cout << "Invalid column index" << std::endl;
        }
    } while (column < 0 || column >= cb.get_column_length());

    init_location = std::make_pair(row, column);
    init_location_set = true;
}

void menu::run_knight_tour_solve() {
    if (!board_size_set) {
        std::cout << "Chess board size is not set" << std::endl;
        return;
    }

    if (!init_location_set) {
        std::cout << "Initial location is not set" << std::endl;
        return;
    }

    if (!cb.knight_tour_solve(init_location)) {
        std::cout << "No solution" << std::endl;
        knight_tour_solution_ready = false;
    } else {
        std::cout << cb << std::endl;
        knight_tour_solution_ready = true;
    }
}

void menu::run_animate_solution() {
    if (!knight_tour_solution_ready) {
        std::cout << "Knight tour solution is not ready or there is no solution" << std::endl;
        return;
    }

    cb.animate_solution(1200);
}

void menu::print_menu() {
    std::cout << "\n      KNIGHT'S TOUR MENU" << std::endl;
    std::cout << "1. Input board size" << std::endl;
    std::cout << "2. Input initial location" << std::endl;
    std::cout << "3. Solve knight's tour" << std::endl;
    std::cout << "4. Animate knight's tour solution" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

