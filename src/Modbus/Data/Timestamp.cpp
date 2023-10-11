/**
 * @file Timestamp.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Timestamp implementation
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Timestamp.hpp"

std::string Timestamp::getTimeUTC() const {
    return std::asctime(std::gmtime(&m_timestamp));
}

std::string Timestamp::getTimeLocal() const {
    return std::asctime(std::localtime(&m_timestamp));
}

Timestamp Timestamp::now(){
    return Timestamp(std::time(nullptr));
}

Timestamp::Timestamp(std::time_t timestamp){
    m_timestamp = timestamp;
}
