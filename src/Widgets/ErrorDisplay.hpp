/**
 * @file ErrorDisplay.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Error Display
 * @version 0.1
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <string>
#include "Subsystem.hpp"

class ErrorDisplay : public Subsystem {
public:
    ErrorDisplay();
    ErrorDisplay(std::string color, std::string errorNumber, std::string errorText);

    void setColor(std::string color);

    void setErrorNumber(std::string errorNumber);

    void setErrorText(std::string errorText);
    
    json handleWebRequest(const json& request);

private:
    std::string m_color;
    std::string m_errorNumber;
    std::string m_errorText;

};