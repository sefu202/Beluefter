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

Heubelueftung::Heubelueftung(const json& systemCfg){
    registerChild("btnOn", m_btnOn);
    registerChild("btnControlType", m_btnControlType);
    registerChild("btnControlMode", m_btnControlMode);

    json properties = systemCfg.at("properties");
    m_hasTachometer = properties.at("tachometer").get<bool>();

    for (auto& str : properties.at("control-types")){
        if (str == "local"){
            m_controlTypes.push_back(eLocal);
        }
        if (str == "remote"){
            m_controlTypes.push_back(eRemote);
        }
    }

    for (auto& str : properties.at("control-modes")){
        if (str == "manual"){
            m_controlModes.push_back(eManual);
        }
        if (str == "auto"){
            m_controlModes.push_back(eAutomatic);
        }
    }

}

void Heubelueftung::simulate()
{

    const uint16_t tachoMax = 1455; // 1455 rpm

    m_fanOn = m_requestFanOn;

    if (m_fanOn && m_tacho < tachoMax){
        m_tacho++;
    }

    if (m_fanOn && m_tacho > 0){
        m_tacho--;
    }
}

void Heubelueftung::update(){
}

json Heubelueftung::handleWebRequest(const HttpRequest& request){
    simulate();
    json response;


    
    return response.dump(4);
}
