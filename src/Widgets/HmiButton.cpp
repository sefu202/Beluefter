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

json HmiButton::handleWebRequest(const json& request){
    if (request.contains(getOwnId()) && !m_isDisabled && m_isVisible){
        try{
            json myRequest = request[getOwnId()];
            if (myRequest["isOn"] == true){
                m_isOn = true;
                // log button
            }
            else if (myRequest["isOn"] == false){
                m_isOn = false;
                // todo log button
            }
            else{
                // todo log error
            }
        }
        catch(...){
            // todo log error
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

HmiButton::operator bool() const {
    return isOn();
}
