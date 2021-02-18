/**
 * \file ripple.hpp
 * \author Graham Riches (graham.riches@live.com)
 * \brief mathematical model (roughly) of a ripple
 * \version 0.1
 * \date 2021-02-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

/********************************** Includes *******************************************/
#include <cmath>

/********************************** Constants *******************************************/
constexpr float pi = 3.1415926;
constexpr float g = 9.81;

/********************************** Functions *******************************************/
/**
 * \brief function to create a normalized sin wave from 0 to 1
 * 
 * \tparam T input type
 * \param t 
 * \retval auto 
 */
template <typename T>
auto normalized_sin(T&& t) {
    return 0.50 * std::sin(t) + 0.5;
}

/**
 * \brief function to create a normalized cosine wave from 0 to 1
 * 
 * \tparam T 
 * \param t 
 * \retval auto 
 */
template <typename T>
auto normalized_cos(T&& t) {
    return 0.50 * std::cos(t) + 0.5;
}

/********************************** Types *******************************************/
/**
 * \brief model of a ripple
 */
struct ripple {
    /**
     * \brief Construct a new ripple object
     * 
     * \param impulse initial impulse of the ripple which dictates the magnitude of the amplitude
     * \param propagation spatial radius of the wave (i.e. how tight or loose the ripples are)
     * \param damping time decay of the ripple
     */
    ripple(float impulse, float propagation, float damping)
    : impulse(impulse)
    , propagation(propagation)
    , damping(damping) {}


    /**
     * \brief Get the output of the ripple in space and time
     * 
     * \param radius the spatial coordinate (in polar coordinates only the radius matters)
     * \param time_sec time since the initial impulse
     * \retval float ripple output
     */
    float get_value(float radius, float time_sec) {                
        auto decay = std::exp(-damping * radius);
        auto u = std::sqrt(2.0) * g * std::pow(time_sec, 2.0) / (4 * radius);        
        return (1 - decay) * (impulse/std::pow(radius, 2.0)) * (u / pi) * normalized_cos(propagation * u + (pi/2));        
    }

    //!< Parameters
    float propagation;
    float damping;
    float impulse;
};
