/**
 * @file Timestamp.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Timstamp class
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #pragma once

#include <cstdint>
#include <string>
#include <ctime>

/**
 * @class Timestamp 
 * @brief Timestamp class
 */
class Timestamp{
public:
    /**
    * @brief Get uct time for timestamp
    * 
    * @return std::string time
    */
    std::string getTimeUTC() const;

    /**
    * @brief Get local time for timestamp
    * 
    * @return std::string time
    */
    std::string getTimeLocal() const;

    /**
    * @brief get current timestamp
    * 
    * @return Timestamp 
    */
    static Timestamp now();

private:
    Timestamp(std::time_t timestamp);
    std::time_t m_timestamp;

};