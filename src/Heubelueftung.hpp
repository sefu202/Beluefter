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
#include "Widgets/HmiButton.hpp"
#include "Subsystems/Subsystem.hpp"
#include "Widgets/ErrorDisplay.hpp"
#include "Widgets/SchematicComponents/GenericComponent.hpp"


class Heubelueftung : public Subsystem{
public:
    Heubelueftung();

    
    void update();

    void simulate();

    json handleWebRequest(const json& request) override;

private:
    HmiButton m_btnRcOn;
    HmiButton m_btnAuto;
    HmiButton m_btnOn;
    GenericComponent m_motorStarterQ1;
    ErrorDisplay m_errorDisplay;

};