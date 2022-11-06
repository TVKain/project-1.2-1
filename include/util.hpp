#pragma once
#ifndef UTIL_HPP
#define UTIL_HPP

#include "array_list.hpp"

#define clear_input() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') 

namespace util {
   /* ******************************************************
    * @brief find the minimum positive element in a 2d array 
    * @params 2d array
    * @return std::pair<int, int> 
    *         where first indicate the row index 
    *         second indicates the column index
    * ****************************************************** */ 
    std::pair<int, int> find_min_positive_in_2d_array(ds::array_list<ds::array_list<int>> &);


    /* *******************************************************
     * @brief check if 2d array contains negative integer
     * @params 2d array
     * @return 
     *      true if 2d array contains negative integer
     *      false otherwise
     * ******************************************************* */  
    bool contains_negative_int(ds::array_list<ds::array_list<int>>);
}



#endif