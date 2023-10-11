/**
 * @file Heubelueftung.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Heubelueftung.hpp"
#include <iostream>
#include "json.hpp"

using nlohmann::json;


Heubelueftung::Heubelueftung(){
    registerChild("btnRcOn", m_btnRcOn);
    registerChild("btnAuto", m_btnAuto);
    registerChild("btnOn", m_btnOn);
    registerChild("Q1", m_motorStarterQ1);
    registerChild("errorDisplay", m_errorDisplay);

    m_btnRcOn.setDisabled(true);
    m_btnRcOn.setErrorOnClick("Only displays status");

    m_motorStarterQ1.setBmk("Q1");
    m_motorStarterQ1.setName("3RW40");
    m_motorStarterQ1.setBlink(false);
    m_motorStarterQ1.setColor("black");
}

void Heubelueftung::update(){
    if (!m_btnRcOn){
        // Btn Auto
        m_btnAuto.setDisabled(true);
        m_btnAuto.setErrorOnClick("Remote control is currently disabled");

        // Btn On
        m_btnOn.setDisabled(true);
        m_btnOn.setErrorOnClick("Remote control is currently disabled");
    }
    else{
        m_btnAuto.setDisabled(false);

        if (m_btnAuto){
            m_btnOn.setDisabled(true);
            m_btnOn.setErrorOnClick("Automatic control is currently enabled");
        }
        else{
            m_btnOn.setDisabled(false);
        }
    }
}

void Heubelueftung::simulate(){
    // Error display
    m_errorDisplay.setColor("green");
    m_errorDisplay.setErrorNumber("0000");
    m_errorDisplay.setErrorText("Heubelüftung läuft");

    m_btnRcOn.setState(true);

    m_motorStarterQ1.setColor("green");
    m_motorStarterQ1.setBlink(true);
}


json Heubelueftung::handleWebRequest(const json& request){
    json response;
    simulate();
    update();

    for (auto & [first, second] : getAllChildren()){
        response[first] = (*second).handleWebRequest(request);
    }
    
    return response;
}
