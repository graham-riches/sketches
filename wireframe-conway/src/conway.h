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
 * \param width how many columns in the grid
 * \param height how many rows in the grid
 * \param seed seeder function
 * \retval std::vector<std::vector<T>> 
 */
template <typename T>
std::vector<std::vector<T>> random_seed(int width, int height, std::function<T(void)> seed) {
    std::vector<std::vector<T>> tiles(height, std::vector<T>(width));    
    
    std::transform(tiles.begin(), tiles.end(), tiles.begin(), [seed](auto&& row) { 
        std::generate(row.begin(), row.end(), seed); 
        return row; 
    });
    
    return tiles;
}

 /**
 * \brief create a random seeded grid of booleans
 * 
 * \param width how many columns in the grid
 * \param height how many row in the grid
 * \param density seeding density
 * \retval game_of_life 
 */
inline std::vector<std::vector<bool>> random_boolean_grid(int width, int height, int density=30) {    
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> distribution(0, 100);

    //!< lambda to bind the arguments for the distribution
    std::function<bool(void)> get_bool = [&] () mutable {         
        return static_cast<bool>(distribution(random_engine) <= density); 
    };    
    return random_seed(width, height, get_bool);
}


/**
* \brief create a random seeded grid of integers
* 
* \param rows how many row in the grid
* \param columns how many columns in the grid
* \retval game_of_life 
*/
inline std::vector<std::vector<int>> random_int_grid(int width, int height) {    
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> int_distribution(0, 255);

    //!< lambda to bind the arguments for the distribution
    std::function<int(void)> get_int = [&] () mutable {         
        return int_distribution(random_engine); 
    };    
    return random_seed(width, height, get_int);
}



class game_of_life {
  public:
    /* default constructor */
    game_of_life(void) = default;

    /**
     * \brief Construct a new game of life object
     * 
     * \param seed arena seed that contains the initial generation     
     */
    game_of_life(std::vector<std::vector<bool>>&& seed)
    : _tiles(std::move(seed)) {
        _rows = _tiles.size();
        _columns = (_rows >= 1 ) ? _tiles[0].size() : 0;
    }

    /**
     * \brief apply the game of life rules and return a reference to the next generation
     * 
     * \return next generation
    */
    std::vector<std::vector<bool>>& next_generation() {
        std::vector<std::vector<bool>> new_tiles = _tiles;

        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _columns; j++) {
                new_tiles[i][j] = apply_rules(_tiles[i][j], count_live_neighbours(i, j));
            }
        }
        _tiles = new_tiles;
        return _tiles;
    }

  private:
    /**
     * \brief count the number of live neighbours a cell has
     * \param row the row index of the cell
     * \param column the column index of the cell
     * \return count of live neighbours
    */
    int count_live_neighbours(int row, int column) {
        //!< get the neighbour bounding box
        int start_row = (row >= 1) ? row - 1 : row;
        int end_row  = (row < _rows - 1) ? row + 1 : _rows - 1;
        int start_column = (column >= 1) ? column - 1 : column;
        int end_column = (column < _columns - 1) ? column + 1 : _columns - 1;

        //!< get all the neighbours and count the total
        int count = 0;
        for (int i = start_row; i <= end_row; i++){
            for (int j = start_column; j <= end_column; j++) {
                if ((i != row) || (j != column)){
                    count += _tiles[i][j];
                }                
            }
        }
        return count;
    }

    /**
     * \brief apply the game of life rules to get a new state
     * \param alive current cell state
     * \param live_neighbours how many live neighbour cells there are
     * \return the new state
    */
    bool apply_rules(bool alive, int live_neighbours) {
        return alive && ((live_neighbours == 3) || (live_neighbours == 2)) ? true
             : !alive && (live_neighbours == 3) ? true
             : false;
    }

    int _rows;
    int _columns;
    std::vector<std::vector<bool>> _tiles;    
};