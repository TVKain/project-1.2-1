#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
#include <string>

#include "array_list.hpp"
#include "chess_board.hpp"
#include "menu.hpp"


int main() {
    menu m;

    for (;;) {
        m.print_menu();
        m.input_choice("Enter your choice: ");


        if (m.get_choice() == 1) {
            m.input_board_length();
        } else if (m.get_choice() == 2) {
            m.input_initial_location();
        } else if (m.get_choice() == 3) {
            m.run_solve_knight_tour();
        } else if (m.get_choice() == 4) {   
            m.run_animate_knight_tour();
        } else if (m.get_choice() == 5) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
    }    

    return 0;
}




