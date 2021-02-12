/**
 * \file conway.h
 * \author Graham Riches (graham.riches@live.com)
 * \brief 
 * \version 0.1
 * \date 2021-02-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

/********************************** Includes *******************************************/
#include <random>
#include <vector>
#include <utility>
#include <functional>


/********************************** Types  *******************************************/

/**
 * \brief apply a random seed function that returns a type T to create a 2D grid of random T
 * 
 * \tparam T output type
 * \tparam SeedFunction function to seed the grid: seed :: void -> T
 * \param rows how many rows in the grid
 * \param columns how many columns in the grid
 * \param seed seeder function
 * \retval std::vector<std::vector<T>> 
 */
template <typename T>
std::vector<std::vector<T>> random_seed(int rows, int columns, std::function<T(void)> seed) {
    std::vector<std::vector<T>> tiles(rows, std::vector<T>(columns));    
    
    std::transform(tiles.begin(), tiles.end(), tiles.begin(), [seed](auto&& row) { 
        std::generate(row.begin(), row.end(), seed); 
        return row; 
    });
    
    return tiles;
}

 /**
 * \brief create a random seeded grid of booleans
 * 
 * \param rows how many row in the grid
 * \param columns how many columns in the grid
 * \retval game_of_life 
 */
std::vector<std::vector<bool>> random_boolean_grid(int rows, int columns) {    
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> bool_distribution(0, 1);

    //!< lambda to bind the arguments for the distribution
    std::function<bool(void)> get_bool = [&] () mutable {         
        return static_cast<bool>(bool_distribution(random_engine)); 
    };    
    return random_seed(rows, columns, get_bool);
}


/**
* \brief create a random seeded grid of integers
* 
* \param rows how many row in the grid
* \param columns how many columns in the grid
* \retval game_of_life 
*/
std::vector<std::vector<int>> random_int_grid(int rows, int columns) {    
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> int_distribution(0, 255);

    //!< lambda to bind the arguments for the distribution
    std::function<int(void)> get_int = [&] () mutable {         
        return int_distribution(random_engine); 
    };    
    return random_seed(rows, columns, get_int);
}


template <typename RulesFunction>
class game_of_life {
  public:
    /**
     * \brief Construct a new game of life object
     * 
     * \param seed arena seed that contains the initial generation
     * \param rules rules function that determines the next generation
     */
    game_of_life(std::vector<std::vector<bool>>&& seed, RulesFunction&& rules)
    : _tiles(std::move(seed))
    , _rules(rules) {}

   

  private:
    std::vector<std::vector<bool>> _tiles;
    RulesFunction _rules;
};