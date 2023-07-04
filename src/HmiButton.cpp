/**
 * @file HmiButton.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Button for HMI
 * @version 0.1 Created class
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "HmiButton.hpp"
#include "libraries/json.hpp"
#include <iostream>

using nlohmann::json;

json HmiButton::handleWebRequest(const HttpRequest& request){
    if (request.getMethod() == "POST" && !m_isDisabled && m_isVisible){
        try{
            std::cout << request.getBody() << std::endl;
            json requestBody = json::parse(request.getBody());
            if (requestBody == true){
                m_isOn = true;
                system("python3 turnOn.py");
            }
            else if (requestBody == false){
                m_isOn = false;
                system("python3 turnOff.py");
            }
        }
        catch(...){

        }
    }

    json response;

    response["isOn"]            = m_isOn;
    response["isDisabled"]      = m_isDisabled;
    response["isVisible"]       = m_isVisible;
    response["errorOnClick"]    = m_errorOnClick;

    return response;
}

void HmiButton::setState(bool isOn){
    m_isOn = isOn;
}

void HmiButton::setDisabled(bool isDisabled){
    m_isDisabled = isDisabled;
}

void HmiButton::setVisible(bool isVisible){
    m_isVisible = isVisible;
}

void HmiButton::setErrorOnClick(const std::string errorOnClick){
    m_errorOnClick = errorOnClick;
}

bool HmiButton::isOn() const{
    return m_isOn;
}

bool HmiButton::isDisabled() const{
    return m_isDisabled;
}

bool HmiButton::isVisible() const {
    return m_isVisible;
}
