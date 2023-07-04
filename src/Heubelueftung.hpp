/**
 * @file Heubelueftung.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

// Includes
#include <vector>
#include <string>
#include "libraries/json.hpp"
#include "HmiButton.hpp"
#include "Subsystem.hpp"


class Heubelueftung : public Subsystem{
public:
    using json = nlohmann::json;

    enum ControlTypes : bool{
        eLocal = false, eRemote = true
    };
    enum ControlModes{
        eManual = false, eAutomatic = true
    };

    Heubelueftung(const json& systemCfg);


    void simulate();

    void update();

    json handleWebRequest(const HttpRequest& request);

private:
    bool m_hasTachometer;
    std::vector<ControlTypes> m_controlTypes;
    std::vector<ControlModes> m_controlModes;
    std::string m_plcAddress;

    uint16_t m_tacho;
    bool m_requestFanOn;
    bool m_fanOn;

    HmiButton m_btnControlType;
    HmiButton m_btnControlMode;
    HmiButton m_btnOn;

};