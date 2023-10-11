/**
 * @file ErrorDisplay.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Error Display implementation
 * @version 0.1
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ErrorDisplay.hpp"


ErrorDisplay::ErrorDisplay(){

}

ErrorDisplay::ErrorDisplay(std::string color, std::string errorNumber, std::string errorText){
    m_color = color;
    m_errorNumber = errorNumber;
    m_errorText = errorText;
}

void ErrorDisplay::setColor(std::string color){
    m_color = color;
}

void ErrorDisplay::setErrorNumber(std::string errorNumber){
    m_errorNumber = errorNumber;
}

void ErrorDisplay::setErrorText(std::string errorText){
    m_errorText = errorText;
}

nlohmann::json ErrorDisplay::handleWebRequest(const json &request)
{
    json j;
    j["color"] = m_color;
    j["errorNumber"] = m_errorNumber;
    j["errorText"] = m_errorText;

    return j;
}
