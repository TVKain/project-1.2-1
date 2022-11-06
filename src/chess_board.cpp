#include "chess_board.hpp"
#include "array_list.hpp"
#include "util.hpp"

#include <iostream>
#include <iomanip>
#include <utility>
#include <thread>
#include <chrono>

chess_board::chess_board(int m, int n) {
    for (int i = 0; i < m; ++i) {
        board.push_back(ds::array_list<int>(n, 0));
    }
    row_length = m;
    column_length = n;
}

int chess_board::get_row_length() {
    return row_length;
}
    
int chess_board::get_column_length() {
    return column_length;
}

void chess_board::resize_board(int m, int n) {
    board.clear();

    for (int i = 0; i < m; ++i) {
        board.push_back(ds::array_list<int>(n, 0));
    }
    row_length = m;
    column_length = n;
}

std::ostream& operator<<(std::ostream &os, const chess_board &cb) {
    auto board = cb.board;
    for (int i = 0; i < cb.row_length; ++i) {
        for (int j = 0; j < cb.column_length; ++j) {
            os << std::setw(2) << board[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}


ds::array_list<std::pair<int, int>> chess_board::calculate_possible_moves(std::pair<int, int> location) {
    ds::array_list<std::pair<int, int>> moves;
    ds::array_list<std::pair<int, int>> ret;

    int row = location.first;
    int column = location.second;

    int up = row - 2;
    int down = row + 2; // row - 1
    int left = column - 2; // column - 1
    int right = column + 2; // column + 1
    
    /* Possible moves for up */
    if (up >= 0) {
        if (column - 1 >= 0) {
            moves.push_back(std::make_pair(up, column - 1));
        }
        if (column + 1 < column_length) {
            moves.push_back(std::make_pair(up, column + 1));
        }
    }

    /* Possible moves for right */
    if (right < column_length) {
        if (row - 1 >= 0) {
            moves.push_back(std::make_pair(row - 1, right));
        }
        if (row + 1 < row_length) {
            moves.push_back(std::make_pair(row + 1, right));
        }
    }

    /* Possible moves for down */
    if (down < row_length) {
        if (column + 1 < column_length) {
            moves.push_back(std::make_pair(down, column + 1));
        }
        if (column - 1 >= 0) {
            moves.push_back(std::make_pair(down, column - 1));
        }
    }

    /* Possible moves for left */
    if (left >= 0) {
        if (row + 1 < row_length) {
            moves.push_back(std::make_pair(row + 1, left));
        }
        if (row - 1 >= 0) {
            moves.push_back(std::make_pair(row - 1, left));
        }
    }

    /* Filter possible moves if they are occupied discard them */
    for (auto &it : moves) {
        if (board[it.first][it.second] == 0) {
            ret.push_back(std::make_pair(it.first, it.second));
        }
    }

    return ret;
}


bool chess_board::knight_tour_solve(std::pair<int, int> init_location) {
    board.clear();
    
    for (int i = 0; i < row_length; ++i) {
        board.push_back(ds::array_list<int>(column_length, 0));
    }

    board[init_location.first][init_location.second] = 1;

    return knight_tour_solve(init_location, 1);
}


/* **********************************************************************
   * @brief: Solve knight tour using backtracking 
   * @params: 
   *          std::pair<int,int>  indicates the initial location
   *          int                 indicates the current move
   * @return boolean: 
   *          true if there is a solution
   *          false otherwise
   * @procedure: 
   *    Uses 2 stacks:
   *          stack_execute keeps track of:
   *                location of moves that could be executed
   *                the current move count
   *          stack_history: keeps track of 
   *                 location of moves that have been executed
   *                 the corresponding move count 
   *    The main body is a do while loop that terminates when either 
   *    condition is statisfied:
   *          current_move_count equals row_length * column_length 
   *          stack is empty
   *    At the beginning of the loops all possible moves from the 
   *    current_location is generated and push onto the stack_execute
   *    
   *    Then if the move count at the top of the stack is smaller than or 
   *    equal to the current_move, it means that no moves can be made. 
   *    We'll backtrack and erase all configuration from the stack_history 
   *    
   *    After that, we'll set the current_move_count to the move_count at
   *    the top of the stack_execute, and the current_location to the 
   *    location at the top of the stack_execute. 
   *    Pop it from the stacK_execute and push it onto the stack_history
   * ******************************************************************** */
bool chess_board::knight_tour_solve(std::pair<int, int> init_location, int init_move) {
    ds::array_list<std::pair<std::pair<int,int>, int>> stack_execute;
    ds::array_list<std::pair<std::pair<int, int>, int>> stack_history;

    auto current_location = init_location;
    auto current_move_count = init_move;

    do {
        auto possible_moves = calculate_possible_moves(current_location);

        /* Add all possible moves to the stack */
        for (int i = possible_moves.size() - 1; i >= 0; --i) {
            stack_execute.push_back(std::make_pair(possible_moves[i], current_move_count + 1));
        }

        /*
         * If tmp_move smaller than or equal the current_move that means no moves can be made 
         * We'll backtrack and erase all configuration until we reach the tmp_move
         */
        auto tmp_move = stack_execute.back().second;
        while (tmp_move <= current_move_count) {
            /* Get the location from the stack history and erase them to 0 */
            auto tmp_location = stack_history.back().first;
            stack_history.pop_back();
            board[tmp_location.first][tmp_location.second] = 0;

            /* decrement current_move */
            --current_move_count;
        }
        
        current_move_count = stack_execute.back().second;
        current_location = stack_execute.back().first;
        board[current_location.first][current_location.second] = current_move_count;
        stack_history.push_back(std::make_pair(current_location, current_move_count));        
        
        stack_execute.pop_back();

        if (current_move_count == row_length * column_length) {
            return true;
        }

    } while (!stack_execute.empty());

    return false;
}

/*
 ♙♗♖♕♔♚♛♜♝♞♟♘
 │ ─ ┌ ┐ └ ┘ ┬ ┴ ├ ┤ ┼
*/
void chess_board::draw_chess_board(ds::array_list<ds::array_list<int>> &copy_board) {
    auto min_location = util::find_min_positive_in_2d_array(copy_board);

    for (int i = 0; i < row_length; ++i) {        
        for (int j = 0; j < column_length; ++j) {
            if (i == 0) {
                if (j == 0) {
                std::cout << "┌────";
                } else if (j == column_length - 1) {
                    std::cout << "┬────┐";
                } else {
                    std::cout << "┬────";
                }
            }
        }
        if (i == 0) {
            std::cout << std::endl;
        }
            

        for (int j = 0; j < column_length; ++j) {
            if (j == column_length - 1) {
                /* Place the knight on the min location and mark it as its negative */
                if (min_location.first == i && min_location.second == j) {  
                    std::cout << "│\u2002" << " ♞" <<"\u2002│";
                    copy_board[i][j] = -copy_board[i][j];
                } else if (copy_board[i][j] < 0) {
                    std::string string_num = std::to_string(-copy_board[i][j]);

                    if (string_num.length() == 1) {
                        std::cout << "│\u2002" << " " << string_num <<"\u2002│";
                    } else {
                        std::cout << "│\u2002" << string_num <<"\u2002│";
                    }
                    
                } else {
                    std::cout << "│\u2002" << "  " <<"\u2002│";
                }
            } else {
                if (min_location.first == i && min_location.second == j) {  
                    /* Place the knight on the min location and mark it as its negative */
                    std::cout << "│\u2002" << " ♞" <<"\u2002";
                    copy_board[i][j] = -copy_board[i][j];
                } else if (copy_board[i][j] < 0) {
                    std::string string_num = std::to_string(-copy_board[i][j]);

                    if (string_num.length() == 1) {
                        std::cout << "│\u2002" << " " << string_num <<"\u2002";
                    } else {
                        std::cout << "│\u2002" << string_num <<"\u2002";
                    }
                } else {
                    std::cout << "│\u2002" << "  " <<"\u2002";
                }
            }
        }

        std::cout << std::endl;

        for (int j = 0; j < column_length; ++j) {
            if (i == row_length - 1) {
                if (j == 0) {
                    std::cout << "└────";
                } else if (j == column_length - 1) {
                    std::cout << "┴────┘";
                } else {
                    std::cout << "┴────";
                }
            } else {
                if (j == 0) {
                    std::cout << "├────";
                } else if (j == column_length - 1) {
                    std::cout << "┼────┤";
                } else {
                    std::cout << "┼────";
                }
            }
        }
        
        std::cout << std::endl;
    }

}

/* ***************************************
 * @brief: Simulate knight tour solution
 * @params:
 *      sleep_time: time between each move
 * *************************************** */
void chess_board::knight_tour_solution_animate(unsigned int sleep_time) {
    ds::array_list<ds::array_list<int>> copy_board(board);

    std::cout << "\033[2J\033[1;1H";
    while (true) {
        draw_chess_board(copy_board);

        if (util::contains_negative_int(copy_board)) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        std::cout << "\033[2J\033[1;1H";
    }    
}




