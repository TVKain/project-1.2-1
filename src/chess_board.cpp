#include "chess_board.hpp"
#include "array_list.hpp"

#include <utility>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>

chess_board::chess_board(int m, int n) {
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
    row_length = m;
    column_length = n;
}

ds::array_list<chess_board::coordinate> chess_board::calculate_possible_moves(ds::array_list<chess_board::coordinate> made_moves, chess_board::coordinate current_coord) {
    ds::array_list<coordinate> possible_offsets = { {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2} };
    ds::array_list<coordinate> possible_moves; 

    for (const auto &offset : possible_offsets) {
        auto move = std::make_pair(offset.first + current_coord.first, offset.second + current_coord.second);

        bool first_pred = move.first >= 0 && move.first < row_length && move.second >= 0 && move.second < column_length;
        bool second_pred = std::find(made_moves.begin(), made_moves.end(), move) == made_moves.end();

        if (first_pred && second_pred) {
            possible_moves.push_back(move);
        }
    }

    return possible_moves;
}


bool chess_board::knight_tour_solve(coordinate init_coord) {
    ds::array_list<std::pair<ds::array_list<coordinate>, coordinate>> stack;

    auto init_moves = calculate_possible_moves(ds::array_list<coordinate>(), init_coord);

    for (const auto &init_move : init_moves) {
        stack.push_back(std::make_pair(ds::array_list<coordinate>{init_coord}, init_move));
    }

    while (!stack.empty()) {
        coordinate current_coord = stack.back().second;
        ds::array_list<coordinate> current_previous_moves = stack.back().first;

        stack.pop_back();

        if (current_previous_moves.size() == row_length * column_length - 1) {
            solution = ds::array_list<coordinate>(current_previous_moves);
            solution.push_back(current_coord);
            return true;
        }

        ds::array_list<coordinate> possible_moves = calculate_possible_moves(current_previous_moves, current_coord);

        if (possible_moves.size() != 0) {
            /* Take the move by push all possible moves on the stack */
            auto next_previous_moves = current_previous_moves;
            next_previous_moves.push_back(current_coord);
            
            for (const auto &possible_move : possible_moves) {
                stack.push_back(std::make_pair(next_previous_moves, possible_move));
            }
        }
    }

    return false;
}


void chess_board::animate_solution(int sleep_time) {
    ds::array_list<coordinate> coords_history;
    ds::array_list<coordinate> coords_to_move(solution);
    ds::array_list<ds::array_list<int>> board(row_length, ds::array_list<int>(column_length, 0));

    std::cout << "\033[2J\033[1;1H";
    while (!coords_to_move.empty()) {
        auto knight_at = coords_to_move[0];
        coords_to_move.erase(coords_to_move.begin());

        for (int i = 0; i < coords_history.size(); ++i) {
            auto coord = coords_history[i];
            board[coord.first][coord.second] = i + 1;
        }

        board[knight_at.first][knight_at.second] = -1;

        coords_history.push_back(knight_at);

        draw_solution_frame(board);

        for (int i = 0; i < row_length; ++i) {
            for (int j = 0; j < column_length; ++j) {
                board[i][j] = 0;
            }
        }
        if (coords_to_move.size() != 0) {
            std::cout << "\033[2J\033[1;1H";
        } 

        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
    
}

/*
♙♗♖♕♔♚♛♜♝♞♟♘
│ ─ ┌ ┐ └ ┘ ┬ ┴ ├ ┤ ┼
*/
void chess_board::draw_solution_frame(ds::array_list<ds::array_list<int>> board) {
    std::cout << "┌────";
    for (int j = 0; j < column_length - 2; ++j) {
        std::cout << "┬────";
    }
    std::cout << "┬────┐" << std::endl;  

    std::string content;
    for (int i = 0; i < row_length; ++i) {
        std::cout << "│";
        for (int j = 0; j < column_length; ++j) {
            if (board[i][j] == 0) {
                content = " ";
            } else if (board[i][j] == -1) {
                content = "♞ ";
            } else {
                content = std::to_string(board[i][j]);
            }
            std::cout << "\u2002" << std::setw(2) << content <<  "\u2002│";
        }
        std::cout << std::endl;

        if (i == row_length - 1) {
            std::cout << "└────";
            for (int j = 0; j < column_length - 2; ++j) {
                std::cout << "┴────";
            }
            std::cout << "┴────┘" << std::endl;  

        } else {
            std::cout << "├────";
            for (int j = 0; j < column_length - 2; ++j) {
                std::cout << "┼────";
            }
            std::cout << "┼────┤" << std::endl; 
        }
        
    }

}

std::ostream& operator<<(std::ostream &os, const chess_board &cb) {
    int board[cb.row_length][cb.column_length] = {0};
    ds::array_list<chess_board::coordinate> copy_solution(cb.solution);

    for (int i = 0; i < copy_solution.size(); ++i) {
        auto coord = copy_solution[i];

        board[coord.first][coord.second] = i + 1;
    }

    for (int i = 0; i < cb.row_length; ++i) {
        for (int j = 0; j < cb.column_length; ++j) {
            os << std::setw(2) << board[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}